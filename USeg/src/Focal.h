#pragma once

#include <complex>
#include <iomanip>
#include <iostream>
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

		void SetValue(const std::complex<double> value);
		std::complex<double> Value() const;
		double StartValue() const;
		double EndValue() const;
		void SwapValues();

		//void SwapValues(const Focal* focal, double distance);
		void Move(const double distance);
		void MoveStart(double distance);
		void MoveEnd(double distance);
		
		void Scale(double scale);
		void ScaleStart(double scale);
		void ScaleEnd(double scale);


		void Add(const Focal* other);
		void Sub(const Focal* other);
		void Mul(const Focal* other);
		void Div(const Focal* other);
		void Add(const std::complex<double> other);
		void Sub(const std::complex<double> other);
		void Mul(const std::complex<double> other);
		void Div(const std::complex<double> other);


		
		friend std::ostream& operator<<(std::ostream& os, Focal* focal) { os << *focal; return os; }
		friend std::ostream& operator<<(std::ostream& os, Focal& focal)
		{
			os << "[" << std::fixed << std::setprecision(2) << focal.StartValue() << "_" << focal.EndValue() << "..." << focal.start_ << "_" << focal.end_ << "]";
			return os;
		}
	};
}
