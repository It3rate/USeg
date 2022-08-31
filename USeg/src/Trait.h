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
		static int const focalCounter = 1;
		std::vector<std::unique_ptr<Focal>> focals_{};
		
		// unot always points positive left on a trait line. Unot one will be less than unot zero for a positive unot.
		Focal *unot_;
		LL unot_max_;
		Focal *unit_;
		LL unit_max_; 
		inline LL UnotZeroTicks() const { return unot_->start_; }
		inline LL UnotOneTicks() const { return unot_->end_; }
		inline LL UnitZeroTicks() const { return unit_->start_; }
		inline LL UnitOneTicks() const { return unit_->end_; }

		inline LL TickCount() const { return TicksPerUnit() * unit_max_ + TicksPerUnot() * unot_max_ + abs(ZeroDiffTicks()); }
		inline LL TicksPerUnit() const { return UnitOneTicks() - UnitZeroTicks(); }
		inline LL TicksPerUnot() const { return UnotOneTicks() - UnotZeroTicks(); }
		inline LL ZeroDiffTicks() const { return UnitZeroTicks() + UnotZeroTicks(); }
		
		inline LL DecimalToUnotTicks(const double decimal) const { return UnotZeroTicks() + ScaleTicks(TicksPerUnot(), decimal); }
		inline LL DecimalToUnitTicks(const double decimal) const { return UnitZeroTicks() + ScaleTicks(TicksPerUnit(), decimal); }
		inline double UnotTicksToDecimal(LL ticks) const { return ticks / TicksPerUnot() - UnotZeroTicks() / TicksPerUnot(); }
		inline double UnitTicksToDecimal(LL ticks) const { return  ticks / TicksPerUnit() - UnitZeroTicks() / TicksPerUnit(); }

		inline void MoveUnot(const LL distance) const { unot_->start_ += distance; unot_->end_ += distance; }
		inline void ScaleUnot(const double scale) const { unot_->end_ = UnotZeroTicks() + ScaleTicks(TicksPerUnot(), scale); }
		inline void MoveUnit(const LL distance) const { unit_->start_ += distance; unit_->end_ += distance; }
		inline void ScaleUnit(const double scale) const { unit_->end_ = UnitZeroTicks() + ScaleTicks(TicksPerUnit(), scale	); }
		
		Focal* AddFocal(LL start, LL end);

	public:
		Trait(const LL unot_zero, const LL unot_one, const LL unot_max, const LL unit_zero, const LL unit_one, const LL unit_max);
		explicit Trait(const LL ticks_per_unit, const LL min, const LL max);

		//void Value(const Focal* focal);
		void SetValue(Focal* focal, const std::complex<double> value) const;
		std::complex<double> Value(const Focal* focal) const;
		inline double StartValue(const Focal* focal) const { return UnotTicksToDecimal(focal->start_); }
		inline double EndValue(const Focal* focal) const { return UnitTicksToDecimal(focal->end_); }

		void Move(Focal* focal, double distance) const;
		void MoveStart(Focal* focal, double distance) const;
		void MoveEnd(Focal* focal, double distance) const;
		void Scale(Focal* focal, double scale) const;
		void ScaleStart(Focal* focal, double scale) const;
		void ScaleEnd(Focal* focal, double scale) const;

		void SwapValues(Focal* focal) const;
		
		//Focal* FocalAt(int index)[]
		Focal* AddFocalByValue(const double imag_start, const double real_end);
		Focal* AddFocalByValue(const std::complex<double> complex);

		static inline LL ScaleTicks(const LL ticks, const double scale) { return static_cast<LL>(scale * static_cast<double>(ticks)); }
	};
	static const unsigned int UNKNOWN_TRAIT = 0;
}
