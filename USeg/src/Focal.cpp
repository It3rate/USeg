#include "Focal.h"

#include <utility>
#include "Trait.h"

umath::Focal::Focal(const LL start, const LL end, Trait& trait) :start_(start), end_(end), trait_(trait)
{
}

double umath::Focal::GetUnotStart() const { return trait_.GetUnotStart(this); }
double umath::Focal::GetUnitEnd() const { return trait_.GetUnitEnd(this); }

std::complex<double> umath::Focal::GetComplex()
{
	return trait_.GetComplex(this);
} 
