#include "Library.h"

int umath::Library::AddSegment(double unit, double unot, int trait_index)
{
	segments_.push_back(std::make_unique<Segment>(unit, unot));
	return segments_.size();
}

umath::Trait* umath::Library::AddTrait(const LL ticks_per_unit, const LL min, const LL max)
{
	traits_.emplace_back(std::make_unique<Trait>(ticks_per_unit, min, max));
	return traits_.back().get();
}
