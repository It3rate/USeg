
#include <iostream>

#include "skia/core/SkCanvas.h"

#include "Library.h"
#include "Segment.h"


#include "GLFW/glfw3.h"
#define SK_GL
#include "skia/gpu/GrBackendSurface.h"
#include "skia/gpu/GrDirectContext.h"
#include "skia/gpu/gl/GrGLInterface.h"
#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorSpace.h"
#include "skia/core/SkSurface.h"

//#define GL_FRAMEBUFFER_SRGB 0x8DB9
//#define GL_SRGB8_ALPHA8 0x8C43

GrDirectContext* context_ = nullptr;
SkSurface* surface_ = nullptr;

void ErrorCallback(int error, const char* description) {
    fputs(description, stderr);
}

void KeyCallback(GLFWwindow* window, const int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void InitSkia(const int width, const int height) {
	const auto interface = GrGLMakeNativeInterface();
    context_ = GrDirectContext::MakeGL(interface).release();

    GrGLFramebufferInfo framebufferInfo;
    framebufferInfo.fFBOID = 0; // assume default framebuffer
    // We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
	//framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
    framebufferInfo.fFormat = GL_RGBA8;

	const SkColorType color_type = kRGBA_8888_SkColorType;
	const GrBackendRenderTarget backend_render_target(width, height,
	                                                  0, // sample count
	                                                  0, // stencil bits
	                                                  framebufferInfo);
     
    //(replace line below with this one to enable correct color spaces)
	//surface_ = SkSurface::MakeFromBackendRenderTarget(context_, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
    surface_ = SkSurface::MakeFromBackendRenderTarget(context_, backend_render_target, kBottomLeft_GrSurfaceOrigin, color_type, nullptr, nullptr).release();
    if (surface_ == nullptr) abort();
}

void CleanupSkia() {
    delete surface_;
    delete context_;
}

const int kWidth = 960;
const int kHeight = 640;
GLFWwindow* window;
SkCanvas* canvas;
void setupSkia()
{
    glfwSetErrorCallback(ErrorCallback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
    glfwWindowHint(GLFW_STENCIL_BITS, 0);
    //glfwWindowHint(GLFW_ALPHA_BITS, 0);
    glfwWindowHint(GLFW_DEPTH_BITS, 0);

    window = glfwCreateWindow(kWidth, kHeight, "Simple example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    //glEnable(GL_FRAMEBUFFER_SRGB);

    InitSkia(kWidth, kHeight);

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, KeyCallback);

    canvas = surface_->getCanvas();
}
void drawFocal(SkColor color, umath::Focal *focal, int yoffset = 100)
{
    static SkPaint paint;
    paint.setStrokeWidth(4);
    paint.setColor(color);
    canvas->drawLine(static_cast<float>(focal->start_), yoffset, static_cast<float>(focal->end_), yoffset, paint);
}

int main(void) {
    umath::Library& lib = umath::Library::GetInstance();

    auto* trait = lib.AddTrait(10LL, -180LL, 700LL);
    auto* f0 = trait->AddFocalByValue(-20LL, 50LL);
    auto* f1 = trait->AddFocalByValue(-60LL, 70LL);
    std::cout << f0 << "  " << f1 << "\n";
	
    f0->Add(f1);
    std::cout << f0 << "\n";
	
    setupSkia();

    while (!glfwWindowShouldClose(window)) {
        glfwWaitEvents();
        SkPaint paint;
        paint.setColor(SK_ColorWHITE);
        canvas->drawPaint(paint);
        drawFocal(SK_ColorBLUE, f0, 100);
        drawFocal(SK_ColorGREEN, f1, 110);
        context_->flush();

        glfwSwapBuffers(window);
    }

    CleanupSkia();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

