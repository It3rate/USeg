#include "Focal.h"

#include "Trait.h"

namespace umath
{
	Focal::Focal(const LL start, const LL end, Trait& trait) : Range(start, end), trait_(trait)
	{
	}

	std::complex<double> Focal::Reciprocal() const { return trait_.Reciprocal(this);} // probably should be clamped value, or just deal in focals
	
	void Focal::ClampToTrait()
	{
		const auto start = start_;
		const auto end = end_;
		start_ = trait_.unot_range_->Clamp(start);
		end_ = trait_.unit_range_->Clamp(end);
		if (start != start_) { start_overflowed_ = true; }
		if (end != end_) { end_overflowed_ = true; }
	}

	void Focal::SetValue(const std::complex<double> value){ trait_.SetValue(this, value); ClampToTrait();}
	std::complex<double> Focal::Value() const { return trait_.Value(this); }
	double Focal::StartValue() const { return trait_.StartValue(this); }
	double Focal::EndValue() const { return trait_.EndValue(this); }
	
	void Focal::SwapValues(){ return trait_.SwapValues(this);} // clamped by trait

	void Focal::Move(const double distance) { trait_.Move(this, distance); ClampToTrait();}
	void Focal::MoveStart(const double distance) { trait_.MoveStart(this, distance); ClampToTrait();}
	void Focal::MoveEnd(const double distance) { trait_.MoveEnd(this, distance); ClampToTrait();}

	void Focal::Scale(const double scale) { trait_.Scale(this, scale); ClampToTrait();}
	void Focal::ScaleStart(const double scale) { trait_.ScaleStart(this, scale); ClampToTrait();}
	void Focal::ScaleEnd(const double scale) { trait_.ScaleEnd(this, scale); ClampToTrait();}

	// needs to work with non zero oriented Focals, so manually.
	void Focal::Add(const Focal* other){ SetValue(Value() + other->Value()); ClampToTrait();}
	void Focal::Sub(const Focal* other) { SetValue(Value() - other->Value()); ClampToTrait();}
	void Focal::Mul(const Focal* other) { SetValue(Value() * other->Value()); ClampToTrait();}
	void Focal::Div(const Focal* other) { SetValue(Value() / other->Value()); ClampToTrait();}

	void Focal::Add(const std::complex<double> other) { SetValue(Value() + other); ClampToTrait();}
	void Focal::Sub(const std::complex<double> other) { SetValue(Value() - other); ClampToTrait();}
	void Focal::Mul(const std::complex<double> other) { SetValue(Value() * other); ClampToTrait();}
	void Focal::Div(const std::complex<double> other) { SetValue(Value() / other); ClampToTrait(); }

	void Focal::AddByTicks(const Focal* other) {
		end_ = end_ + other->end_;
		start_ = start_ + other->start_;
		ClampToTrait();
	}
	void Focal::SubByTicks(const Focal* other) {
		end_ = end_ - other->end_;
		start_ = start_ - other->start_;
		ClampToTrait();
	}
	void Focal::MulByTicks(const Focal* other) {
		double tmp = end_ * other->end_ - start_ * other->start_;
		start_ = end_ * other->start_ + start_ * other->end_;
		end_ = tmp;
		ClampToTrait();
	}
	void Focal::DivByTicks(const Focal* other) {
		double other_r = other->end_;
		double other_i = other->start_;

		// shouldn't have to deal with NaNs or div by zero eventually
		if (isnan(other_r) || isnan(other_i)) { // set NaN result for now
			throw std::invalid_argument("Focal argument contains Nan.");
			//end_ = std::numeric_limits<double>::quiet_NaN();
			//start_ = std::numeric_limits<double>::quiet_NaN();
		}
		else if ((other_i < 0 ? -other_i : +other_i) < (other_r < 0 ? -other_r : +other_r)) { // |other_i| < |other_r|
			double _wr = other_i / other_r;
			double _wd = other_r + _wr * other_i;

			double _tmp = (end_ + start_ * _wr) / _wd;
			start_ = (start_ - end_ * _wr) / _wd;
			end_ = _tmp;
		}
		else if (other_i == 0) { // other_i and other_r == 0
			start_ = trait_.unot_range_->end_; // std::numeric_limits<double>::quiet_NaN();
			end_ = trait_.unit_range_->end_; // std::numeric_limits<double>::quiet_NaN();
		}
		else { // 0 < |other_r| <= |other_i|
			double _wr = other_r / other_i;
			double _wd = other_i + _wr * other_r;
			if (isnan(_wd) || _wd == 0) {
				start_ = trait_.unot_range_->end_; // std::numeric_limits<double>::quiet_NaN();
				end_ = trait_.unit_range_->end_; // std::numeric_limits<double>::quiet_NaN();
			}
			else { // compute representable result
				double _tmp = (end_ * _wr + start_) / _wd;
				start_ = (start_ * _wr - end_) / _wd;
				end_ = _tmp;
			}
		}
		ClampToTrait();
	}

}