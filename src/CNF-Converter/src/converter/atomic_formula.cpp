#include "atomic_formula.h"

AtomicFormula::AtomicFormula()
    :BaseFormula ()
{}

unsigned AtomicFormula::complexity() const
{
    return 0;
}

Formula AtomicFormula::substitute(const Formula &what, const Formula &with) const
{
    if(equalTo(what)){
        return with;
    }
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula AtomicFormula::simplify() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula AtomicFormula::nnf() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

