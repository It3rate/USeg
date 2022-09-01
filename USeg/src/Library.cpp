#include "Library.h"

namespace umath
{
	Trait* Library::AddTrait(const LL ticks_per_unit, const LL positive_extent)
	{
		int id = traitCounter_++;
		traitMap_.try_emplace(id, std::make_unique<Trait>(ticks_per_unit, positive_extent));
		return traitMap_.at(id).get();
	}
}
