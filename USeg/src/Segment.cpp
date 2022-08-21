#include "Segment.h"
using namespace umath;

const Segment DEFAULT_UNIT { 0.0, 1.0 };
const Segment DEFAULT_UNOT { 0.0, -1.0 };

umath::Segment::Segment(const double start, const double end, const int trait_index):start_(start), end_(end), trait_index_(trait_index)
{
}

Segment::Segment(const double end) : start_(-end), end_(end), trait_index_(0)
{
}
