#include "atom.h"

Atom::Atom(Variable p)
  : AtomicFormula (), m_p(p)
{}

std::ostream &Atom::print(std::ostream &out) const
{
    return out << m_p;
}

bool Atom::equalTo(const Formula &f) const
{
    if(BaseFormula::equalTo(f)){
        const Atom* pF = static_cast<const Atom *>(f.get());
        return m_p == pF->m_p;
    }
    return false;
}

void Atom::getAtoms(AtomSet &aSet) const
{
    aSet.insert(m_p);
}
