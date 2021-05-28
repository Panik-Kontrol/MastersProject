#include "and.h"
#include "atom.h"
#include "base_formula.h"
#include "iff.h"
#include "imp.h"
#include "or.h"

BaseFormula::BaseFormula(){

}

void BaseFormula::getAtoms(AtomSet &aSet) const
{
    UNUSED_VARIABLE(aSet);
}

bool BaseFormula::equalTo(const Formula &f) const
{
    const BaseFormula *base = f.get();
    return typeid (*this) == typeid (*base);
}

bool operator==(const Formula &lhs, const Formula &rhs)
{
    return lhs->equalTo(rhs);
}

std::ostream& operator<<(std::ostream &out, const Formula &f)
{
    return f->print(out);
}

BaseFormula::~BaseFormula()
{

}
Variable BaseFormula::getUniqueVarName(const AtomSet &atoms) {
    Variable unique;
    do {
        unique = "s" + std::to_string(s_UniqueCounter++);
    } while (atoms.find(unique) != atoms.end());

    return unique;
}

Formula BaseFormula::tseitinTransformation()
{
    AtomSet atoms;
    Formula simplified = simplify();

    simplified->getAtoms(atoms);

    Formula substitutedFormulas = nullptr;
    bool isSubformula = false;
    Formula result = _tseitinTransformation(simplified, atoms, substitutedFormulas, isSubformula);

    if (substitutedFormulas.get() == nullptr) {
        return result;
    } else {
        return std::make_shared<And>(result, substitutedFormulas);
    }
}

Formula BaseFormula::_tseitinTransformation(const Formula &formula, AtomSet &atoms, Formula &substitutedFormulas, bool isSubformula) {
    if (!isOfType<BinaryConnective>(formula)){
        return formula;
    }

    Formula op1, op2;
    std::tie(op1, op2) = ((BinaryConnective*) formula.get())->operands();

    Formula leftSubformula = _tseitinTransformation(op1, atoms, substitutedFormulas, true);
    Formula rightSubformula = _tseitinTransformation(op2, atoms, substitutedFormulas, true);

    Variable varName = getUniqueVarName(atoms);
    Formula atom = std::make_shared<Atom>(varName);

    Formula subformula;

    if (isOfType<And>(formula)) {
        subformula = std::make_shared<And>(leftSubformula, rightSubformula);
    } else if(isOfType<Or>(formula)) {
        subformula = std::make_shared<Or>(leftSubformula, rightSubformula);
    } else if(isOfType<Imp>(formula)) {
        subformula = std::make_shared<Imp>(leftSubformula, rightSubformula);
    } else if(isOfType<Iff>(formula)) {
        subformula = std::make_shared<Iff>(leftSubformula, rightSubformula);
    } else {
        throw std::runtime_error{"Unknown binary connective"};
    }

    if(isSubformula){
        if (substitutedFormulas.get() == nullptr) {
            // initialize substitutedFormulas
            substitutedFormulas = std::make_shared<Iff>(atom, subformula);
        } else {
            // append substitution si <=> subformula
            substitutedFormulas = std::make_shared<And>(substitutedFormulas, std::make_shared<Iff>(atom, subformula));
        }
        return atom;
    }
    return std::make_shared<Iff>(atom, subformula);
}

