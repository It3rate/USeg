#pragma once

#include <vector>
#include <memory>
#include <complex>

#include "Globals.h"
#include "Segment.h"
#include "Focal.h"

namespace umath 
{
	class Trait : public std::enable_shared_from_this<Trait>
	{
	private:
		// unot always points positive left on a trait line. Unot one will be less than unot zero for a positive unot.
		Focal unot_;
		Focal unit_;
		LL unot_max_;
		LL unit_max_; 
		inline LL UnotZero() const { return unot_.start_; }
		inline LL UnotOne() const { return unot_.end_; }
		inline LL UnitZero() const { return unit_.start_; }
		inline LL UnitOne() const { return unit_.end_; }

		std::vector<std::unique_ptr<Focal>> focals_{};

		inline LL TickCount() const { return TicksPerUnit() * unit_max_ + TicksPerUnot() * unot_max_ + abs(ZeroDiff()); }
		inline LL TicksPerUnit() const { return UnitOne() - UnitZero(); }
		inline LL TicksPerUnot() const { return UnotOne() - UnotZero(); }
		inline LL ZeroDiff() const { return UnitZero() + UnotZero(); }
		inline LL DecimalToUnotTicks(const double decimal) const { return UnotZero() + ScaleTicks(TicksPerUnot(), decimal); }
		inline LL DecimalToUnitTicks(const double decimal) const { return UnitZero() + ScaleTicks(TicksPerUnit(), decimal); }
		inline double UnotTicksToDecimal(LL ticks) const { return UnotZero() / TicksPerUnot() + ticks / TicksPerUnot(); }
		inline double UnitTicksToDecimal(LL ticks) const { return UnitZero() / TicksPerUnit() + ticks / TicksPerUnit();
		}


	public:
		Trait(const LL unot_zero, const LL unot_one, const LL unot_max, const LL unit_zero, const LL unit_one, const LL unit_max);
		explicit Trait(const LL ticks_per_unit, const LL min, const LL max);
		
		void MoveUnot(const LL distance) { unot_.start_ += distance; unot_.end_ += distance; }
		void ScaleUnot(const double scale) { unot_.end_ = UnotZero() + ScaleTicks(TicksPerUnot(), scale); }
		void MoveUnit(const LL distance) { unit_.start_ += distance; unit_.end_ += distance; }
		void ScaleUnit(const double scale) { unit_.end_ = UnitZero() + ScaleTicks(TicksPerUnit(), scale	); }

		Focal* AddFocal(const double imag_start, const double real_end);
		Focal* AddFocal(const std::complex<double> complex);

		double GetUnotStart(const Focal* focal) const;
		double GetUnitEnd(const Focal* focal) const;
		std::complex<double> GetComplex(const Focal* focal) const;

		static inline LL ScaleTicks(const LL ticks, const double scale) { return static_cast<LL>(scale * static_cast<double>(ticks)); }
	};
	static const unsigned int UNKNOWN_TRAIT = 0;
}
