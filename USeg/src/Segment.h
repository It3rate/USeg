#pragma once
#include "Number.h"

class Trait;

namespace umath
{
	class Segment
	{
	public:
		Number<double> start_;
		Number<double> end_;
		int trait_index_;

		Segment(double start, double end , int trait_index = 0);
		explicit Segment(double end);
	};
	extern const umath::Segment kDefaultUnit;
	extern const umath::Segment kDefaultUnot;
}

