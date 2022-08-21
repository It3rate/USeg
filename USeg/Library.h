#pragma once
#include <vector>
#include <memory>

#include "src/Segment.h"

namespace umath
{
	class Library
	{
	public:
		int AddSegment(double unit, double unot, int trait_index = 0);
	private:
		std::vector<std::unique_ptr<Segment>> segments_;
	};
}

