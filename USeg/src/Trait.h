#pragma once

#include <vector>

#include "MeasuredSeg.h"
#include "Segment.h"

namespace umath
{
	class Trait
	{
	public:
		inline static int id_counter_ = 1;
		
		int trait_id_;
		std::vector<MeasuredSeg> segments_;
		std::vector<Segment> unit_list_;
		std::vector<Segment> unot_list_;
		
		Trait();
	};
	static const unsigned int UNKNOWN_TRAIT = 0;
}
