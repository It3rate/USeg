#pragma once
#include <functional>
#include <istream>
#include <ostream>

namespace umath
{
    template<typename T = double>
	class Number
    {
        T val_;
    public:
        Number() {}
        explicit Number(const T& rhs) : val_(rhs)
        {
        }

        Number& operator=(T const& in) { val_ = in; return *this; }
		explicit operator T () const { return val_; }

	    friend std::ostream& operator<<(std::ostream& out_stream, Number const& num) {
	        return out_stream << num.val_;
	    }

	    friend std::istream& operator>>(std::istream& in_stream, Number& num) {
	        try {
	            T input;
				in_stream >> input;
	            num = input;
	        }
	        catch (...) {
				in_stream.setstate(std::ios::failbit);
	        }
	        return in_stream;
	    }
    };
}
