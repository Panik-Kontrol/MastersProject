#include "binary_connective.h"

BinaryConnective::BinaryConnective(const Formula &op1, const Formula &op2)
    : BaseFormula (), m_op1(op1), m_op2(op2)
{

}

std::ostream &BinaryConnective::print(std::ostream &out) const
{
    out << "(";
    m_op1->print(out);
    out << symbol();
    m_op2->print(out);
    return out << ")";
}

std::pair<Formula, Formula> BinaryConnective::operands() const
{
    return {m_op1, m_op2};
}

void BinaryConnective::getAtoms(AtomSet &aSet) const
{
    m_op1->getAtoms(aSet);
    m_op2->getAtoms(aSet);
}

unsigned BinaryConnective::complexity() const
{
    return m_op1->complexity() + m_op2->complexity() + 1;
}

bool BinaryConnective::equalTo(const Formula &f) const
{
    if(BaseFormula::equalTo(f)){
        const BinaryConnective *pF = static_cast<const BinaryConnective *>(f.get());
        return m_op1 == pF->m_op1 && m_op2 == pF->m_op2;
    }
    return false;
}
