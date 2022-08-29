#include "Focal.h"

#include <utility>
#include "Trait.h"

umath::Focal::Focal(const LL start, const LL end, Trait& trait) :start_(start), end_(end), trait_(trait)
{
}

std::complex<double> umath::Focal::Value() const { return trait_.Value(this); }
double umath::Focal::StartValue() const { return trait_.StartValue(this); }
double umath::Focal::EndValue() const { return trait_.EndValue(this); }

void umath::Focal::Move(const double distance) { trait_.Move(this, distance); }
void umath::Focal::MoveStart(const double distance) { trait_.MoveStart(this, distance); }
void umath::Focal::MoveEnd(const double distance) { trait_.MoveEnd(this, distance); }

void umath::Focal::Scale(const double scale) { trait_.Scale(this, scale); }
void umath::Focal::ScaleStart(const double scale) { trait_.ScaleStart(this, scale); }
void umath::Focal::ScaleEnd(const double scale) { trait_.ScaleEnd(this, scale); }
