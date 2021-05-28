
#include "constant.h"

True::True()
    :AtomicFormula ()
{}

std::ostream &True::print(std::ostream &out) const
{
    return out << "TRUE";
}

False::False()
    :AtomicFormula ()
{}

std::ostream &False::print(std::ostream &out) const
{
    return out << "FALSE";
}

