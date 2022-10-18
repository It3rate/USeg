#pragma once
#include "Focal.h"
#include "Selection.h"

namespace umath
{
	class Operator
	{
        using value_type = Focal*;
        using pointer = Focal*;
        using reference = Focal*;
        using iterator_category = std::random_access_iterator_tag;
        // Type of difference between two iterators.
        using difference_type = int;

        //Operator(Focal* value) : step_(0), value_(value){ }
		Operator(Focal* value, Focal* step) : step_(step), value_(value) { }
		Operator(Focal* start, Focal* step, Focal* stop) : step_(step), start_(start), stop_(stop) { }

        value_type& operator*() { return value_; }
        const value_type& operator*() const { return value_; }
        value_type* operator->() { return &value_; }

	/*	Operator& operator++() {
			value_ += *step_;
			return *this;
		}
		Operator& operator++(int) {
			value_ += *step_;
			return *this;
		}
		Operator& operator--() {
			value_ -= *step_;
			return *this;
		}
		Operator& operator--(int) {
			value_ -= *step_;
			return *this;
		}*/
        bool operator==(const Operator& rhs) const { return this->value_ == rhs.value_; }
        bool operator!=(const Operator& rhs) const { return !this->operator==(rhs); }


		//Operator begin()
		//{
		//	return Operator(start_, step_);
		//}

		//Operator end()
		//{
		//	return Operator(stop_);
		//}
    	
		Focal* start_;
		Focal* step_;
		Focal* value_;
		Focal* stop_;

		//// Required for make the class iterable with for-range based loop
		//auto begin() { return m_points.begin(); }
		//auto end() { return m_points.end(); }

		//// Required for make the class iterable with for-range based loop
		//auto cbegin() { return m_points.cbegin(); }
		//auto cend() { return m_points.cend(); }
		
		//using iterator_category = std::random_access_iterator_tag;
		//using difference_type = std::ptrdiff_t;
		//using value_type = Focal;
		//using pointer = Focal*;
		//using reference = Focal&;

		//Iterator(pointer ptr) : m_ptr(ptr) {}

		//reference operator*() const { return *m_ptr; }
		//pointer operator->() { return m_ptr; }
		//Iterator& operator++() { m_ptr++; return *this; }
		//Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		//friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		//friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

		//private:
		//	pointer m_ptr;
	};
}

