#include "Segment.h"
using namespace UMath;

const Segment DEFAULT_UNIT { 0.0, 1.0 };
const Segment DEFAULT_UNOT { 0.0, -1.0 };

UMath::Segment::Segment(double start, double end, Trait* trait):m_start(start), m_end(end), m_trait(trait)
{
}

Segment::Segment(const double end) : m_start(-end), m_end(end), m_trait(nullptr)
{
}
