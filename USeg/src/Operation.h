#pragma once

#include "Focal.h"
#include "Selection.h"

namespace umath
{
	// these are approximately the terminals in this math system. In flux,
	// eg jump is probably only possible with objects defined by ranges of focals. Bool is its own set of primitives.
	enum class OperationKind { Select, Stretch, Jump, Repeat, Turn, Twist, Bool, Branch, Join, Duplicate};
	
	class Operation
	{
		// **** All ops, history, sequences, equations should fit on traits as focals.
		
		// Operations on selection(s)
		// Select (can add segments)
		// Multiply (stretch)
		// Add (jump, shift)
		// Repeat (can add segments if repeated op does)
		// Turn
		// Twist (3d)
		// Bool ops (can split segment)
		// Branch (splits segment) (connections are 0, 1 or 2 way links)
		// Join (reduces segments)
		// Duplicate (adds segment)

		// Compare
		// Choose (can reduce unchosen segments)
	private:
	public:
		OperationKind& operationKind_;
		Focal* repeats_;
		
		static Selection& ShiftBy(Selection& selection, const Focal& amount);
		static Selection& ScaleBy(Selection& selection, const Focal& amount);
		static Selection& TurnBy(Selection& selection, const Focal& amount);
		static Selection& TwistBy(Selection& selection, const Focal& amount);


	};

}