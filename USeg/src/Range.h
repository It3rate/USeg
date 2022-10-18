#pragma once
#include <ostream>
#include <istream>
#include <iomanip>

#include "Globals.h"

namespace umath
{
	enum class Pointing { Left, Equal, Right };
	
	/*
	 * A generic segment with a start and end. Will point in a direction, but has no trait or unit. Base class for Focals, which specify a trait.
	 */
	class Range
	{
	private:
		inline LL Low() const { return start_ <= end_ ? start_ : end_; }
		inline LL High() const { return start_ >= end_ ? start_ : end_; }
	public:
		LL start_;
		LL end_;

		Range(LL start, LL end);
		Range(LL end);

		Pointing Direction() const { return start_ < end_ ? Pointing::Right : start_ > end_ ? Pointing::Left : Pointing::Equal; }
		LL Length() const { return end_ - start_; }
		LL AbsLength() const { return abs(end_ - start_); }
		inline LL Clamp(const LL value) const { return value < Low() ? Low() : value > High() ? High() : value; }
		inline void Clamp(Range &other) const { other.start_ = Clamp(other.start_); other.end_ = Clamp(other.end_); }

		
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

