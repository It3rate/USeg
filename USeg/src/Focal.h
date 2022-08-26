#pragma once

#include<memory>
#include "Globals.h"

class Trait;

namespace umath
{
	class Focal
	{
	private:
		ULL start_;
		ULL end_;
		std::shared_ptr<Trait> trait_;
	public:

		Focal(ULL start, ULL end, std::shared_ptr<Trait> trait);
	};

}