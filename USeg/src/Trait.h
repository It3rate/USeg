#pragma once

#include <vector>

#include "MeasuredSeg.h"
#include "Segment.h"

namespace UMath
{
	class Trait
	{
	public:
		inline static int id_counter = 1;
		
		int trait_id;
		std::vector<MeasuredSeg> segments;
		std::vector<Segment> unit_list;
		std::vector<Segment> unot_list;
		
		Trait();
	};
	extern const UMath::Trait UNKNOWN_TRAIT;
}
