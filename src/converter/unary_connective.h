#ifndef UNARY_CONNECTIVE_H
#define UNARY_CONNECTIVE_H

#include "base_formula.h"

class UnaryConnective : public BaseFormula
{
public:
    UnaryConnective(const Formula &op);

    unsigned complexity() const;
    bool equalTo(const Formula &f) const;
    void getAtoms(AtomSet &aSet) const;

    Formula operand() const;
private:
    Formula m_op;
};

#endif // UNARY_CONNECTIVE_H
