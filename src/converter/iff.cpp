#include "iff.h"
#include "constant.h"
#include "not.h"
#include "and.h"
#include "or.h"


Iff::Iff(const Formula &op1, const Formula &op2)
    : BinaryConnective(op1, op2)
{

}

std::string Iff::symbol() const
{
    return "<=>";
}

Formula Iff::substitute(const Formula &what, const Formula &with) const
{
  return substituteImpl<Iff>(what, with);
}

Formula Iff::simplify() const
{
    GET_OPERANDS(simplifiedOp1, simplifiedOp2);
    simplifiedOp1 = simplifiedOp1->simplify();
    simplifiedOp2 = simplifiedOp2->simplify();

    if(BaseFormula::isOfType<True>(simplifiedOp1)){
        return simplifiedOp2;
    }
    else if(BaseFormula::isOfType<True>(simplifiedOp2)){
        return simplifiedOp1;
    }
    else if(BaseFormula::isOfType<False>(simplifiedOp1)){
        return std::make_shared<Not>(simplifiedOp2)->simplify();
    }
    else if(BaseFormula::isOfType<False>(simplifiedOp2)){
        return std::make_shared<Not>(simplifiedOp1)->simplify();
    }

    return std::make_shared<Iff>(simplifiedOp1, simplifiedOp2);
}

Formula Iff::nnf() const
{
    GET_OPERANDS(op1, op2);
    return std::make_shared<And>(std::make_shared<Or>(std::make_shared<Not>(op1)->nnf(), op2->nnf()),
                                 std::make_shared<Or>(op1->nnf(), std::make_shared<Not>(op2)->nnf()));
}

