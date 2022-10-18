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

		// ** All operations can be reduced to one or more proportional moves, maybe (select what point(s) move relative to what, for what lengths and repeats)
		// **        operations can be reduced to equations using only select>move primitives where amounts are recorded in segments as well.
		//   - fixed: elements remain at some proportional position regardless of other changes. (used in branches and joins).
		//   - shifts: points move together (non proportionately) to a proportional unit distance (this can just be two points doing multiplication)
		//   - addition: end proportional to beginning
		//   - multiplication: multiple points move proportionately  (by some 'additive' unit amount)
		//   - complex math: whole number line also moves proportionately
		//   - powers: repeating addition (becomes form of multiplication) or multiplication proportional moves, output becomes input.
		//   - turns: proportional move balances between two unit segments.
		
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