#include "unary_connective.h"

UnaryConnective::UnaryConnective(const Formula &op)
    :BaseFormula (), m_op{op}
{}

Formula UnaryConnective::operand() const
{
    return m_op;
}

unsigned UnaryConnective::complexity() const
{
    return m_op->complexity() + 1;
}

bool UnaryConnective::equalTo(const Formula &f) const
{
    if(BaseFormula::equalTo(f)){
        const UnaryConnective *pF = static_cast<const UnaryConnective *>(f.get());
        return pF->m_op == m_op;
    }
    return false;
}

void UnaryConnective::getAtoms(AtomSet &aSet) const
{
    return m_op->getAtoms(aSet);
}
