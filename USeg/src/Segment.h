#pragma once
#include "Number.h"

class Trait;

namespace UMath
{
	class Segment
	{
	public:
		Number<double> m_start;
		Number<double> m_end;
		Trait *m_trait;

		Segment(double start, double end , Trait* trait = nullptr);
		explicit Segment(double end);
	};
	extern const UMath::Segment DEFAULT_UNIT;
	extern const UMath::Segment DEFAULT_UNOT;
}

