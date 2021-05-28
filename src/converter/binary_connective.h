#ifndef BINARY_CONNECTIVE_H
#define BINARY_CONNECTIVE_H

#include "base_formula.h"
#include <string>
#include "constant.h"
#include "not.h"

#define GET_OPERANDS(x, y) \
  Formula x, y; \
  std::tie(x, y) = operands();

class BinaryConnective : public BaseFormula
{
public:
    BinaryConnective(const Formula &op1, const Formula &op2);

    virtual std::string symbol() const = 0;

    virtual std::ostream& print(std::ostream &out) const;

    virtual unsigned complexity() const;

    virtual bool equalTo(const Formula &f) const;

    virtual void getAtoms(AtomSet &aSet) const;

    std::pair<Formula, Formula> operands() const;
protected:
    template<typename Derived>
    Formula substituteImpl(const Formula &what, const Formula &with) const;
private:
    Formula m_op1;
    Formula m_op2;
};

template <typename Derived>
Formula BinaryConnective::substituteImpl(const Formula &what, const Formula &with) const
{
    if (equalTo(what))
      {
        return with;
      }
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    return std::make_shared<Derived>(op1->substitute(what, with), op2->substitute(what, with));
}

#endif // BINARY_CONNECTIVE_H
