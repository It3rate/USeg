#include "Range.h"
#include <limits>
#include "Globals.h"

namespace umath
{
    Range::Range(LL start, LL end) : start_(start), end_(end)
    {
    }

    Range::Range(LL end) : start_(-end), end_(end)
    {
    }

}
