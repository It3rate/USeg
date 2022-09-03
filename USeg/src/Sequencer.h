#pragma once
#include <memory>

#include "History.h"

namespace umath
{
	class Sequencer
	{
	private:
	public:
		std::unique_ptr<History> history_;
	};
}
