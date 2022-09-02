#include "Trait.h"
#include <cassert>

namespace umath
{

	Trait::Trait(Range& unot, Range& unit, Range& unotRange, Range& unitRange):
		unot_(AddFocal(unot)), unit_(AddFocal(unit)),
		unot_range_(AddFocal(unotRange)), unit_range_(AddFocal(unitRange))
	{
		ValidateTrait();
	}

	Trait::Trait(const LL ticks_per_unit, const LL positive_extent) :
		unot_(AddFocal(0, -ticks_per_unit)), unot_range_(AddFocal( positive_extent, -positive_extent)),
		unit_(AddFocal(0, ticks_per_unit)), unit_range_(AddFocal(-positive_extent, positive_extent))
	{
		ValidateTrait();
	}

	void Trait::ValidateTrait() const
	{
		assert(("Unot must not point right: ", unot_->Direction() != Pointing::RIGHT));
		assert(("Unot range must not point right: ", unot_range_->Direction() != Pointing::RIGHT));
		assert(("Unit must not point left: ", unit_->Direction() != Pointing::LEFT));
		assert(("Unit range must not point left: ", unit_range_->Direction() != Pointing::LEFT));
	}

	Focal* Trait::AddFocal(LL start, LL end)
	{
		const int id = focalCounter_++;
		focalMap_.try_emplace(id, std::make_unique<Focal> (start, end, *this));
		auto* const result = focalMap_.at(id).get();
		result->ClampToTrait();
		return result;
	}

	Focal* Trait::AddFocal(Range& range)
	{
		return AddFocal(range.start_, range.end_);
	}
	
	Focal* Trait::AddFocalByValue(const double i_start, const double r_end)
	{
		const auto start = DecimalToUnotTicks(i_start);
		const auto end = DecimalToUnitTicks(r_end);
		return AddFocal(start, end);
	}

	Focal* Trait::AddFocalByValue(const std::complex<double> complex)
	{
		const auto start = DecimalToUnotTicks(complex.imag());
		const auto end = DecimalToUnitTicks(complex.real());
		return AddFocal(start, end);
	}

	std::complex<double> Trait::Reciprocal(const Focal* focal) const { return 1.0 / Value(focal); }

	std::complex<double> Trait::Value(const Focal* focal) const
	{
		return std::complex<double>{UnitTicksToDecimal(focal->end_), UnotTicksToDecimal(focal->start_)};
	}
	void Trait::SetValue(Focal* focal, const std::complex<double> value) const
	{
		focal->start_ = DecimalToUnotTicks(value.imag());
		focal->end_ = DecimalToUnitTicks(value.real());
		focal->ClampToTrait();
	}

	void Trait::Move(Focal* focal, const double distance) const
	{
		MoveStart(focal, distance);
		MoveEnd(focal, distance);
		focal->ClampToTrait();
	}
	void Trait::MoveStart(Focal* focal, const double distance) const
	{
		focal->start_ = DecimalToUnotTicks(UnotTicksToDecimal(focal->start_) + distance);
		focal->ClampToTrait();
	}
	void Trait::MoveEnd(Focal* focal, const double distance) const
	{
		focal->end_ = DecimalToUnitTicks(UnitTicksToDecimal(focal->end_) + distance);
		focal->ClampToTrait();
	}
	void Trait::Scale(Focal* focal, double scale) const
	{
		ScaleStart(focal, scale); ScaleEnd(focal, scale);
		focal->ClampToTrait();
	}
	void Trait::ScaleStart(Focal* focal, double scale) const
	{
		focal->start_ = DecimalToUnotTicks(UnotTicksToDecimal(focal->start_) * scale);
		focal->ClampToTrait();
	}
	void Trait::ScaleEnd(Focal* focal, double scale) const
	{
		focal->end_ = DecimalToUnitTicks(UnitTicksToDecimal(focal->end_) * scale);
		focal->ClampToTrait();
	}


	void Trait::SwapValues(Focal* focal)
	{
		const auto temp = focal->start_;
		focal->start_ = focal->end_;
		focal->end_ = temp;
		focal->ClampToTrait();
	}
}
