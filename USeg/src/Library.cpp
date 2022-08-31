#include "Library.h"

namespace umath
{
	Trait* Library::AddTrait(const LL ticks_per_unit, const LL min, const LL max)
	{
		traits_.emplace_back(std::make_unique<Trait>(ticks_per_unit, min, max));
		return traits_.back().get();
	}
}
