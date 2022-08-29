#include "Trait.h"
#include <cassert>

using namespace umath;


umath::Trait::Trait(const LL unot_zero, const LL unot_one, const LL unot_max, const LL unit_zero, const LL unit_one, const LL unit_max):
	unot_(AddFocal(unot_zero, unot_one)), unot_max_( unot_max),
	unit_(AddFocal(unit_zero, unit_one)), unit_max_( unit_max)
{
}

umath::Trait::Trait(const LL ticks_per_unit, const LL min, const LL max) :
	unot_(AddFocal(0, -ticks_per_unit)), unot_max_(-ticks_per_unit  * min),
	unit_(AddFocal(0, ticks_per_unit)), unit_max_(ticks_per_unit * max)
{
} 

Focal* umath::Trait::AddFocal(LL start, LL end)
{
	focals_.emplace_back(std::make_unique<Focal>(start, end, *this));
	return focals_.back().get();
}
umath::Focal* umath::Trait::AddFocalByValue(const double imag_start, const double real_end)
{
	auto start = DecimalToUnotTicks(imag_start);
	auto end = DecimalToUnitTicks(real_end);
	return AddFocal(start, end);
}

Focal* umath::Trait::AddFocalByValue(const std::complex<double> complex)
{
	auto start = DecimalToUnotTicks(complex.imag());
	auto end = DecimalToUnitTicks(complex.real());
	return AddFocal(start, end);
}

std::complex<double> umath::Trait::Value(const Focal* focal) const
{
	return std::complex<double>{UnitTicksToDecimal(focal->end_), UnotTicksToDecimal(focal->start_)};
}

void umath::Trait::Move(Focal* focal, const double distance) const{ MoveStart(focal, distance); MoveEnd(focal, distance); }
void umath::Trait::MoveStart(Focal* focal, const double distance) const { focal->start_ = DecimalToUnotTicks(UnotTicksToDecimal(focal->start_) + distance);}
void umath::Trait::MoveEnd(Focal* focal, const double distance) const { focal->end_ = DecimalToUnitTicks(UnitTicksToDecimal(focal->end_) + distance); }

void umath::Trait::Scale(Focal* focal, double scale) const{ ScaleStart(focal, scale); ScaleEnd(focal, scale); }
void umath::Trait::ScaleStart(Focal* focal, double scale) const { focal->start_ = DecimalToUnotTicks(UnotTicksToDecimal(focal->start_) * scale); }
void umath::Trait::ScaleEnd(Focal* focal, double scale) const { focal->end_ = DecimalToUnotTicks(UnotTicksToDecimal(focal->end_) * scale); }

void umath::Trait::SwapValues(Focal* focal) const
{
	auto temp = focal->start_;
	focal->start_ = focal->end_;
	focal->end_ = temp;
}

