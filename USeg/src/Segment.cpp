#include "Segment.h"
using namespace umath;

const Segment DEFAULT_UNIT{ 0.0, 1.0 };
const Segment DEFAULT_UNOT{ 0.0, -1.0 };

Segment::Segment(const double start, const double end, const int trait_index) :
    i_start_(start), r_end_(end), trait_index_(trait_index)
{
}

Segment::Segment(const double end) : i_start_(-end), r_end_(end), trait_index_(0)
{
}

constexpr void Segment::Add(const Segment& _right) {
    this->r_end_ = this->r_end_ + _right.r_end_;
    this->i_start_ = this->i_start_ + _right.i_start_;
}
constexpr void Segment::Sub(const Segment& _right) {
    this->r_end_ = this->r_end_ - _right.r_end_;
    this->i_start_ = this->i_start_ - _right.i_start_;
}
constexpr void Segment::Mul(const Segment& _right) {
    double _tmp = this->r_end_ * _right.r_end_ - this->i_start_ * _right.i_start_;
    this->i_start_ = this->r_end_ * _right.i_start_ + this->i_start_ * _right.r_end_;
    this->r_end_ = _tmp;
}

void Segment::Div(const Segment& _right) {
    double _right_r = _right.r_end_;
    double _right_i = _right.i_start_;

    // shouldn't have to deal with NaNs or div by zero eventually
    if (isnan(_right_r) || isnan(_right_i)) { // set NaN result
        this->r_end_ = NAN;
        this->i_start_ = NAN;
    }
    else if ((_right_i < 0 ? -_right_i : +_right_i)
        < (_right_r < 0 ? -_right_r : +_right_r)) { // |_right_i| < |_right_r|
        double _wr = _right_i / _right_r;
        double _wd = _right_r + _wr * _right_i;

        double _tmp = (this->r_end_ + this->i_start_ * _wr) / _wd;
        this->i_start_ = (this->i_start_ - this->r_end_ * _wr) / _wd;
        this->r_end_ = _tmp;
    }
    else if (_right_i == 0) {
        this->r_end_ = NAN;
        this->i_start_ = NAN;
    }
    else { // 0 < |_right_r| <= |_right_i|
        double _wr = _right_r / _right_i;
        double _wd = _right_i + _wr * _right_r;
        if (isnan(_wd) || _wd == 0) {
            this->r_end_ = NAN;
            this->i_start_ = NAN;
        }
        else { // compute representable result
            double _tmp = (this->r_end_ * _wr + this->i_start_) / _wd;
            this->i_start_ = (this->i_start_ * _wr - this->r_end_) / _wd;
            this->r_end_ = _tmp;
        }
    }


}