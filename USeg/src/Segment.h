#pragma once
#include "Number.h"

class Trait;

namespace umath
{
	class Segment
	{
	public:
		double i_start_;
		double r_end_;
		int trait_index_;

		Segment(double start, double end , int trait_index = 0);
		explicit Segment(double end);

		constexpr void Add(const Segment& _right);
		constexpr void Sub(const Segment& _right);
		constexpr void Mul(const Segment& _right);
		void Div(const Segment& _right);
	};
	extern const umath::Segment kDefaultUnit;
	extern const umath::Segment kDefaultUnot; 
}

