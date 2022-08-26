#include "Trait.h"
#include <cassert>

umath::Trait::Trait(ULL ticks_per_unit, ULL min, ULL max, ULL zero_dif_ticks) :
	ticks_per_unit_(ticks_per_unit), min_(min), max_(max), zero_dif_ticks_(zero_dif_ticks)
{
	assert(max > min);
	assert(tick_length_() < ULLONG_MAX);
	midpoint_ = (ULLONG_MAX - tick_length_()) / 2;
	ULL half_zero_dif_rnd = zero_dif_ticks_ / 2;
	unit_zero_ = midpoint_ + half_zero_dif_rnd;
	unit_one_ = unit_zero_ + ticks_per_unit;
	unot_zero_ = midpoint_ - (zero_dif_ticks - half_zero_dif_rnd); // dif may be odd
	unot_one_ = unot_zero_ - ticks_per_unit;
}
