#pragma once
#include "Segment.h"

namespace umath
{
	class MeasuredSeg
	{
	public:
		Segment segment_;
		Segment unit_;
		Segment unot_;

		explicit MeasuredSeg(Segment segment, Segment unit = kDefaultUnit, Segment unot = kDefaultUnot);
	};
}

