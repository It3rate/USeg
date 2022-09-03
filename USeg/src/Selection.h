#pragma once
#include <vector>


#include "Focal.h"

namespace umath
{
	class Selection
	{
		// select segments (points are segments too)
		// - units, one points, zero points
		// - focals
		// - positions on focals (based on closest tick)

		// operation elements (from operation traits)
		// - threads, branches, joins, cross points
		// - inspected values (combos, step count, op count etc.)
		// - results of operations
		
		// select from history (abs or rel)
		// - previous selections
		// - operation(s)
		// - result(s)
		// - recursive or nested elements

		// Filtered, named, compared

		// Select: category(ops, results, selections) > time[step] > trait[index] > focal[index, index (branches)] > endPoint/Seg[all/position/ends]
		// can also select combos to derive points (eg cross points), range selections, filtered selections
		// can select by bool operations like overlap point, wrap segment, not touching segment etc.
		// *** All selections are segments with origin metadata.
	private:
	public:
		std::vector<Focal*> focals_; // can include points, they are mathematically the same as segments (eg 3-3i is a point at 3)
	};

}
