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

	void Trait::ValidateTrait()
	{
		assert(("Unot can not point right: ",unot_->Direction() != Pointing::RIGHT));
		assert(("Unot range can not point right: ", unot_range_->Direction() != Pointing::RIGHT));
		assert(("Unit can not point left: ", unit_->Direction() != Pointing::LEFT));
		assert(("Unit range can not point left: ", unit_range_->Direction() != Pointing::LEFT));
	}

	Focal* Trait::AddFocal(Range& range)
	{
		int id = focalCounter_++;
		focalMap_.try_emplace(id, std::make_unique<Focal>(range.start_, range.end_, *this));
		return focalMap_.at(id).get();
	}

	Focal* Trait::AddFocal(LL start, LL end)
	{
		int id = focalCounter_++;
		focalMap_.try_emplace(id, std::make_unique<Focal> (start, end, *this));
		return focalMap_.at(id).get();
	}
	
	Focal* Trait::AddFocalByValue(const double imag_start, const double real_end)
	{
		auto start = DecimalToUnotTicks(imag_start);
		auto end = DecimalToUnitTicks(real_end);
		return AddFocal(start, end);
	}

	Focal* Trait::AddFocalByValue(const std::complex<double> complex)
	{
		auto start = DecimalToUnotTicks(complex.imag());
		auto end = DecimalToUnitTicks(complex.real());
		return AddFocal(start, end);
	}


	void Trait::SetValue(Focal* focal, const std::complex<double> value) const
	{
		focal->start_ = DecimalToUnotTicks(value.imag());
		focal->end_ = DecimalToUnitTicks(value.real());
	}
	std::complex<double> Trait::Value(const Focal* focal) const
	{
		return std::complex<double>{UnitTicksToDecimal(focal->end_), UnotTicksToDecimal(focal->start_)};
	}
	std::complex<double> Trait::Reciprocal(const Focal* focal) const { return 1.0 / Value(focal); }

	void Trait::Move(Focal* focal, const double distance) const { MoveStart(focal, distance); MoveEnd(focal, distance); }
	void Trait::MoveStart(Focal* focal, const double distance) const { focal->start_ = DecimalToUnotTicks(UnotTicksToDecimal(focal->start_) + distance); }
	void Trait::MoveEnd(Focal* focal, const double distance) const { focal->end_ = DecimalToUnitTicks(UnitTicksToDecimal(focal->end_) + distance); }

	void Trait::Scale(Focal* focal, double scale) const { ScaleStart(focal, scale); ScaleEnd(focal, scale); }
	void Trait::ScaleStart(Focal* focal, double scale) const { focal->start_ = DecimalToUnotTicks(UnotTicksToDecimal(focal->start_) * scale); }
	void Trait::ScaleEnd(Focal* focal, double scale) const { focal->end_ = DecimalToUnitTicks(UnitTicksToDecimal(focal->end_) * scale); }


	void Trait::SwapValues(Focal* focal) const
	{
		auto temp = focal->start_;
		focal->start_ = focal->end_;
		focal->end_ = temp;
	}
}
