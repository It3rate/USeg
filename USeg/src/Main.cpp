
#include <iostream>
#include <cstring>

#include "Library.h"
#include "Segment.h"

int main(int argc, char* argv[]) 
{
	umath::Library& lib = umath::Library::GetInstance();
	auto trait = lib.AddTrait(1000, -200, 200);
	auto* focal = trait->AddFocal(20, 50);
	std::cout << focal->start_ << "\n";
		
	const umath::Segment seg0(10.3,20.0);
	std::cout << "start = " << seg0.i_start_ << "\n";
	std::cout << "end = " << seg0.r_end_ << "\n";

    return 0;
}