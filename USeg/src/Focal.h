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

		std::complex<double> Value() const;
		double StartValue() const;
		double EndValue() const;

		void Move(const double distance);
		void MoveStart(double distance);
		void MoveEnd(double distance);
		
		void Scale(double scale);
		void ScaleStart(double scale);
		void ScaleEnd(double scale);
		
		//void SwapValues(const Focal* focal, double distance);
	};

}
