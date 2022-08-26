#include "Library.h"

int umath::Library::AddSegment(double unit, double unot, int trait_index)
{
	segments_.push_back(std::make_unique<Segment>(unit, unot));
	return segments_.size();
}
