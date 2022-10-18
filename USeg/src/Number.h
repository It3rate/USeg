#pragma once

#include <complex>
#include "Focal.h"
#include "Domain.h"

namespace umath
{
	/*
	 * A full (complex) number that specifies Focals for it's unit, unot and segment. All three normally belong to the same trait.
	 */
	class Number
	{
	private:
		inline LL UnotZeroTicks() const { return domain_.unot_.start_; }
		inline LL UnotOneTicks() const { return domain_.unot_.end_; }
		inline LL UnitZeroTicks() const { return domain_.unit_.start_; }
		inline LL UnitOneTicks() const { return domain_.unit_.end_; }
		inline LL TicksPerUnit() const { return UnitOneTicks() - UnitZeroTicks(); }
		inline LL TicksPerUnot() const { return UnotOneTicks() - UnotZeroTicks(); }
		inline LL DecimalToUnotTicks(const double decimal) const { return UnotZeroTicks() + ScaleTicks(TicksPerUnot(), decimal); }
		inline LL DecimalToUnitTicks(const double decimal) const { return UnitZeroTicks() + ScaleTicks(TicksPerUnit(), decimal); }
		inline double UnotTicksToDecimal(LL ticks) const { return ticks / TicksPerUnot() - UnotZeroTicks() / TicksPerUnot(); }
		inline double UnitTicksToDecimal(LL ticks) const { return  ticks / TicksPerUnit() - UnitZeroTicks() / TicksPerUnit(); }
		static inline LL ScaleTicks(const LL ticks, const double scale) { return static_cast<LL>(scale * static_cast<double>(ticks)); }

		Focal& segment_;
		Domain& domain_;
		//Focal& unit_;
		Number(Focal& segment);
		Number(Focal& segment, Domain& unit);

		std::complex<double> Value() const;
		void SetValue(const std::complex<double> value) const;
		inline double StartValue(const Focal* focal) const { return UnotTicksToDecimal(focal->start_); }
		inline double EndValue(const Focal* focal) const { return UnitTicksToDecimal(focal->end_); }
		std::complex<double> Reciprocal(const Focal* focal) const;

		
	};
}
