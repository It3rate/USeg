#pragma once
#include "Segment.h"

namespace UMath
{
	class MeasuredSeg
	{
	public:
		Segment m_segment;
		Segment m_unit;
		Segment m_unot;

		explicit MeasuredSeg(Segment segment, Segment unit = DEFAULT_UNIT, Segment unot = DEFAULT_UNOT);
	};
}

