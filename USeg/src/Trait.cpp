#include "Trait.h"
#include <cassert>

using namespace umath;

umath::Trait::Trait(const LL unot_zero, const LL unot_one, const LL unot_max, const LL unit_zero, const LL unit_one, const LL unit_max) :
	unot_zero_(unot_zero), unot_one_(unot_one), unot_max_(unot_max), unit_zero_(unit_zero), unit_one_(unit_one), unit_max_(unit_max)
{
}

umath::Trait::Trait(const LL ticks_per_unit, const LL min, const LL max)
{
	unot_zero_ = 0;
	unot_one_ = -ticks_per_unit;
	unot_max_ = unot_one_ * min;
	unit_zero_ = 0;
	unit_one_ = ticks_per_unit;
	unit_max_ = unit_one_ * max;
}

umath::Focal* umath::Trait::AddFocal(const double decimal_start, const double decimal_end)
{
	auto start = DecimalToUnotTicks(decimal_start);
	auto end = DecimalToUnitTicks(decimal_end);
	focals_.push_back(std::make_unique<Focal>(start, end, shared_from_this()));
	return focals_.back().get();
}

Focal* umath::Trait::AddFocal(const std::complex<double> complex)
{
	auto start = DecimalToUnotTicks(complex.imag());
	auto end = DecimalToUnitTicks(complex.real());
	focals_.push_back(std::make_unique<Focal>(start, end, shared_from_this()));
	return focals_.back().get();
}

