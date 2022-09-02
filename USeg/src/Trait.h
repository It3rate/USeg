#pragma once

#include <memory>
#include <complex>
#include <unordered_map>

#include "Globals.h"
#include "Focal.h"
#include "Range.h"

namespace umath 
{
	class Range;

	class Trait : public std::enable_shared_from_this<Trait>
	{
	private:
		friend Focal;
		inline static int  focalCounter_ = 1;
		std::unordered_map<int, std::unique_ptr<Focal>> focalMap_;
		
		// unot always points positive left on a trait line. Unot one will be less than unot zero for a positive unot.
		Focal *unot_;
		Focal* unot_range_;
		Focal *unit_;
		Focal* unit_range_;

		Focal* AddFocal(Range& range);
		Focal* AddFocal(LL start, LL end);
		void ValidateTrait() const;
		
		inline LL UnotZeroTicks() const { return unot_->start_; }
		inline LL UnotOneTicks() const { return unot_->end_; }
		inline LL UnitZeroTicks() const { return unit_->start_; }
		inline LL UnitOneTicks() const { return unit_->end_; }

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

	public:
		Trait(Range& unot, Range& unit, Range& unotRange, Range& unitRange);
		/**
		 * \brief Generate a trait with default zero based units of equal sizes extending to equal ranges in the unit and unot directions.
		 * \param ticks_per_unit Resolution of the unit.
		 * \param positive_extent Number of positive ticks allowed in unit and unot, will be mirrored for negative ticks.
		 */
		explicit Trait(const LL ticks_per_unit, const LL positive_extent);

		//void Value(const Focal* focal);
		void SetValue(Focal* focal, const std::complex<double> value) const;
		std::complex<double> Value(const Focal* focal) const;
		inline double StartValue(const Focal* focal) const { return UnotTicksToDecimal(focal->start_); }
		inline double EndValue(const Focal* focal) const { return UnitTicksToDecimal(focal->end_); }
		std::complex<double> Reciprocal(const Focal* focal) const;

		void Move(Focal* focal, double distance) const;
		void MoveStart(Focal* focal, double distance) const;
		void MoveEnd(Focal* focal, double distance) const;
		void Scale(Focal* focal, double scale) const;
		void ScaleStart(Focal* focal, double scale) const;
		void ScaleEnd(Focal* focal, double scale) const;

		static void SwapValues(Focal* focal);
		
		//Focal* FocalAt(int index)[]
		Focal* AddFocalByValue(const double i_start, const double r_end);
		Focal* AddFocalByValue(const std::complex<double> complex);

		static inline LL ScaleTicks(const LL ticks, const double scale) { return static_cast<LL>(scale * static_cast<double>(ticks)); }
	};
	static const unsigned int UNKNOWN_TRAIT = 0;
}
