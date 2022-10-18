#include "Number.h"
#include "Trait.h"

namespace umath
{
	//Number::Number(Focal& segment) :
	//	segment_(segment), unit_(segment.trait_.Unit()), unot_(segment.trait_.Unot())
	//{
	//}
	Number::Number(Focal& segment, Domain& domain) :
		segment_(segment), domain_(domain)
	{
	}

	std::complex<double> Number::Value() const
	{
		return std::complex<double>{UnitTicksToDecimal(segment_.end_), UnotTicksToDecimal(segment_.start_)};
	}
	void Number::SetValue(const std::complex<double> value) const
	{
		segment_.start_ = DecimalToUnotTicks(value.imag());
		segment_.end_ = DecimalToUnitTicks(value.real());
		//segment_.ClampToTrait();
	}
}