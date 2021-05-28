#ifndef ATOMIC_FORMULA_H
#define ATOMIC_FORMULA_H

#include "base_formula.h"

class AtomicFormula : public BaseFormula{
public:
    AtomicFormula();
    virtual unsigned complexity() const;
    virtual Formula substitute(const Formula &what, const Formula &with) const;
    virtual Formula simplify() const ;
    virtual Formula nnf() const;
};



#endif // ATOMIC_FORMULA_H
