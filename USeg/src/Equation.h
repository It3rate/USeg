#pragma once

#include "Focal.h"
#include "Selection.h"
#include "Operation.h"

namespace umath
{
	class Equation
	{
		// select items, choose op, generate result, allow repeats or recursion
		
		/* Equations have the option of preserving steps or not. Eg a derivation of e or pi doesn't need to preserve steps
		 * (and could always recreate them at a different resolution).
		 * Equations can be a large or small as user sees fit? Akin to a 'step', not just a single operation.
		 * Seems like a tree - has loops, but all loops can unwind due to no infinity (optimization aside)
		 *
		 * Some equations can be reversed, eg add with subtract, but branched equations may need guessing within ranges
		 * eg a rectangle area is a linear influence of both width and height, but if changing the area we aren't sure which to adjust (but there are bounds).
		 * Perhaps this is how some flows are two way, and some are less so. Even an unknown variable can move things from calculation to probability ranges.
		 * btw characterized ranges are an acceptable, expected and useful answer. Prediction is predicated on this.
		 */
	private:
	public:
		Focal* focal_; // play the equation over the resolution/length of the focal. Allows binding to internal positions, and keying Equation context in a trait.
		Selection* selection_; // if the equations modifies the selection, this can be cached, or reverse calculated.
		Operation* operation_;
		Selection* result_; // output of operation, can be fed back or forwarded as input (automatically the new selection)
	};

}