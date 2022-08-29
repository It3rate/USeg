#pragma once

#include <complex>
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
		Trait& trait_;
		
		Focal(const LL start, const LL end, Trait& trait);

		double GetUnotStart() const;
		double GetUnitEnd() const;
		std::complex<double> GetComplex();
	};

}
