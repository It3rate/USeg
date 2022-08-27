#pragma once

#include<memory>
#include "Globals.h"

namespace umath
{
	class Trait;

	class Focal
	{
	private:
	public:
		LL start_;
		LL end_;
		std::shared_ptr<Trait> trait_;
		
		Focal(const LL start, const LL end, std::shared_ptr<Trait> trait);
		Focal(const LL start, const LL end);
	};

}