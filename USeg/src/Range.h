#pragma once
#include <ostream>
#include <istream>
#include <iomanip>

#include "Globals.h"

namespace umath
{
	enum Pointing { LEFT, EQUAL, RIGHT };
	
	class Range
	{
	public:
		LL start_;
		LL end_;

		Range(LL start, LL end);
		Range(LL end);

		Pointing Direction() const { return start_ < end_ ? Pointing::RIGHT : start_ > end_ ? Pointing::LEFT : Pointing::EQUAL; }
		LL Length() const { return end_ - start_; }
		LL AbsLength() const { return abs(end_ - start_); }

		
		friend std::ostream& operator<<(std::ostream& out_stream, Range const& seg) {
			return out_stream << '[' << std::fixed << std::setprecision(2) << seg.end_ << ',' << seg.start_ << ',' << ']';
		}
		friend std::istream& operator>>(std::istream& in_stream, Range& seg) {
			try {
				LL start;
				LL end;
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

}

