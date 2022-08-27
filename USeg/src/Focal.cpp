#include "Focal.h"

#include <utility>

umath::Focal::Focal(const LL start, const LL end, std::shared_ptr<Trait> trait) :start_(start), end_(end), trait_(std::move(trait))
{
}

umath::Focal::Focal(const LL start, const LL end) : start_(start), end_(end)
{
}
