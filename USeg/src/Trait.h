#pragma once

#include <vector>

#include "Globals.h"
#include "MeasuredSeg.h"
#include "Segment.h"
#include "Focal.h"

namespace umath
{
	class Trait
	{
	private:
		ULL min_;
		ULL max_;
		ULL ticks_per_unit_;
		ULL zero_dif_ticks_;

		ULL midpoint_;
		ULL unit_zero_;
		ULL unit_one_;
		ULL unot_zero_;
		ULL unot_one_;
		std::vector<std::unique_ptr<Focal>> focals_;

		inline unsigned int tick_length_(){ return ticks_per_unit_ * (max_ - min_) + zero_dif_ticks_;}

	public:
		int trait_id_;
		std::vector<MeasuredSeg> segments_;
		std::vector<Segment> unit_list_;
		std::vector<Segment> unot_list_;

		Trait(ULL ticks_per_unit, ULL min, ULL max, ULL zero_dif_ticks = 0);

		// use https://stackoverflow.com/questions/11711034/stdshared-ptr-of-this
		Focal& AddFocal(double start, double end);

		
	};
	static const unsigned int UNKNOWN_TRAIT = 0;
}
