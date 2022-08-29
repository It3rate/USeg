#include "Trait.h"
#include <cassert>

using namespace umath;

umath::Trait::Trait(const LL unot_zero, const LL unot_one, const LL unot_max, const LL unit_zero, const LL unit_one, const LL unit_max):
	unot_( unot_zero, unot_one, *this ), unot_max_( unot_max),
	unit_( unit_zero, unit_one, *this), unit_max_( unit_max)
{
}

umath::Trait::Trait(const LL ticks_per_unit, const LL min, const LL max) :
	unot_(0, -ticks_per_unit, *this), unot_max_(-ticks_per_unit  * min),
	unit_(0, ticks_per_unit, *this), unit_max_(ticks_per_unit * max)
{
} 

umath::Focal* umath::Trait::AddFocal(const double imag_start, const double real_end)
{
	auto start = DecimalToUnotTicks(imag_start);
	auto end = DecimalToUnitTicks(real_end);
	focals_.emplace_back(std::make_unique<Focal>(start, end, *this));
	return focals_.back().get();
}

Focal* umath::Trait::AddFocal(const std::complex<double> complex)
{
	auto start = DecimalToUnotTicks(complex.imag());
	auto end = DecimalToUnitTicks(complex.real());
	focals_.emplace_back(std::make_unique<Focal>(start, end, *this));
	return focals_.back().get();
}

double umath::Trait::GetUnotStart(const Focal* focal) const { return UnotTicksToDecimal(focal->start_); }
double umath::Trait::GetUnitEnd(const Focal* focal) const { return UnitTicksToDecimal(focal->end_); }
std::complex<double> umath::Trait::GetComplex(const Focal* focal) const
{
	return std::complex<double>{UnitTicksToDecimal(focal->end_), UnotTicksToDecimal(focal->start_)};
}

