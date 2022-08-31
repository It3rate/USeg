#include "Focal.h"

#include <utility>
#include "Trait.h"

namespace umath
{
	Focal::Focal(const LL start, const LL end, Trait& trait) :start_(start), end_(end), trait_(trait)
	{
	}

	void Focal::SetValue(const std::complex<double> value){ trait_.SetValue(this, value); }
	std::complex<double> Focal::Value() const { return trait_.Value(this); }
	double Focal::StartValue() const { return trait_.StartValue(this); }
	double Focal::EndValue() const { return trait_.EndValue(this); }
	void Focal::SwapValues(){ return trait_.SwapValues(this); }

	void Focal::Move(const double distance) { trait_.Move(this, distance); }
	void Focal::MoveStart(const double distance) { trait_.MoveStart(this, distance); }
	void Focal::MoveEnd(const double distance) { trait_.MoveEnd(this, distance); }

	void Focal::Scale(const double scale) { trait_.Scale(this, scale); }
	void Focal::ScaleStart(const double scale) { trait_.ScaleStart(this, scale); }
	void Focal::ScaleEnd(const double scale) { trait_.ScaleEnd(this, scale); }

	void Focal::Add(const Focal* other){ SetValue(Value() + other->Value()); }
	void Focal::Sub(const Focal* other) { SetValue(Value() - other->Value()); }
	void Focal::Mul(const Focal* other) { SetValue(Value() * other->Value()); }
	void Focal::Div(const Focal* other) { SetValue(Value() / other->Value()); }

	void Focal::Add(const std::complex<double> other) { SetValue(Value() + other); }
	void Focal::Sub(const std::complex<double> other) { SetValue(Value() - other); }
	void Focal::Mul(const std::complex<double> other) { SetValue(Value() * other); }
	void Focal::Div(const std::complex<double> other) { SetValue(Value() / other); }
}