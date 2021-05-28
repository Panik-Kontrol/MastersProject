#ifndef BASE_FORMULA_H
#define BASE_FORMULA_H

#include "atom_set.h"

#include <memory>
#include <iostream>
#include <vector>
#include <experimental/optional>

class BaseFormula;
using Formula = std::shared_ptr<BaseFormula>;

class BaseFormula : public std::enable_shared_from_this<BaseFormula>
{
private:
    uint64_t s_UniqueCounter;
public:
    BaseFormula();

    virtual std::ostream& print(std::ostream &out) const = 0;
    virtual unsigned complexity() const = 0;
    virtual bool equalTo(const Formula &f) const;
    virtual void getAtoms(AtomSet &aSet) const;
    virtual Formula substitute(const Formula &what, const Formula &with) const = 0;
    virtual ~BaseFormula();
    virtual Formula tseitinTransformation();

    virtual Formula simplify() const = 0;
    virtual Formula nnf() const = 0;

    template <typename Derived>
    static const Derived* isOfType(const Formula &f);

    Variable getUniqueVarName(const AtomSet &atoms);

private:

    Formula _tseitinTransformation(const Formula &formula, AtomSet &atoms, Formula &substitutedFormulas, bool isSubformula);
};

bool operator==(const Formula &lhs, const Formula &rhs);
std::ostream& operator<<(std::ostream &out, const Formula &f);

template <typename Derived>
const Derived* BaseFormula::isOfType(const Formula &f){
    return dynamic_cast<const Derived*>(f.get());
}

#endif // BASE_FORMULA_H
