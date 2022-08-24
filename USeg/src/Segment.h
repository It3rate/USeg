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

		Segment(double i_start, double r_end);
		explicit Segment(double end);

		constexpr void Add(const Segment& _right);
		constexpr void Sub(const Segment& _right);
		constexpr void Mul(const Segment& _right);
		void Div(const Segment& _right);


		friend std::ostream& operator<<(std::ostream& out_stream, Segment const& seg) {
			return out_stream << '[' << seg.r_end_ << ',' << seg.i_start_ << ',' << ']';
		}
		friend std::istream& operator>>(std::istream& in_stream, Segment& seg) {
			try {
				double start;
				double end;
				in_stream >> start;
				in_stream >> end;
				seg = { start, end };
			}
			catch (...) {
				in_stream.setstate(std::ios::failbit);
			}
			return in_stream;
		}
	};
	extern const umath::Segment kDefaultUnit;
	extern const umath::Segment kDefaultUnot; 



}

