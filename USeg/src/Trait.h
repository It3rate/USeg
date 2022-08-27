#pragma once

#include <vector>
#include <memory>
#include <complex>

#include "Globals.h"
#include "MeasuredSeg.h"
#include "Segment.h"
#include "Focal.h"

namespace umath
{
	class Trait : std::enable_shared_from_this<Trait>
	{
	private:
		LL unot_zero_;
		LL unot_one_;
		LL unot_max_;
		LL unit_zero_;
		LL unit_one_;
		LL unit_max_;

		std::vector<std::unique_ptr<Focal>> focals_;

		inline LL TickCount() const { return TicksPerUnit() * unit_max_ + TicksPerUnot() * unot_max_ + abs(ZeroDiff()); }
		inline LL TicksPerUnit() const { return unit_one_ - unit_zero_; }
		inline LL TicksPerUnot() const { return unot_one_ - unot_zero_; }
		inline LL ZeroDiff() const { return unit_zero_ - unot_zero_; }
		inline LL DecimalToUnotTicks(const double decimal) const { return unot_zero_ + ScaleTicks(TicksPerUnot(), decimal); }
		inline LL DecimalToUnitTicks(const double decimal) const { return unit_zero_ + ScaleTicks(TicksPerUnit(), decimal); }
		inline LL UnotTicksToDecimal() const { return unit_zero_ - unot_zero_; }
		inline LL UnitTicksToDecimal() const { return unit_zero_ - unot_zero_; }

		static inline LL ScaleTicks(LL ticks, double scale) { return static_cast<LL>(scale * static_cast<double>(ticks)); }

	public:
		std::vector<MeasuredSeg> segments_;
		std::vector<Segment> unit_list_;
		std::vector<Segment> unot_list_;

		Trait(const LL unot_zero, const LL unot_one, const LL unot_max, const LL unit_zero, const LL unit_one, const LL unit_max);
		explicit Trait(const LL ticks_per_unit, const LL min, const LL max);
		
		inline void MoveUnot(const LL distance) { unot_zero_ += distance; unot_one_ += distance; }
		inline void ScaleUnot(const double scale) { unot_one_ = unot_zero_ + ScaleTicks(TicksPerUnot(), scale); }
		inline void MoveUnit(const LL distance) { unit_zero_ += distance; unit_one_ += distance; }
		inline void ScaleUnit(const double scale) { unit_one_ = unit_zero_ + ScaleTicks(TicksPerUnit(), scale); }

		Focal* AddFocal(const double decimal_start, const double decimal_end);
		Focal* AddFocal(const std::complex<double> complex);
		

		
	};
	static const unsigned int UNKNOWN_TRAIT = 0;
}
