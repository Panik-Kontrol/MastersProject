#ifndef ATOM_H
#define ATOM_H

#include "atomic_formula.h"

class Atom : public AtomicFormula
{
public:
    Atom(Variable p);
    virtual std::ostream& print(std::ostream &out) const;
    virtual bool equalTo(const Formula &f) const;
    virtual void getAtoms(AtomSet &aSet) const;
private:
    Variable m_p;
};

#endif // ATOM_H
