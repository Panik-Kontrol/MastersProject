#include "not.h"
#include "constant.h"
#include "and.h"
#include "or.h"
#include "imp.h"
#include "iff.h"

Not::Not(const Formula &op)
    : UnaryConnective (op)
{}

std::ostream &Not::print(std::ostream &out) const
{
    out << "~";
    return operand()->print(out);
}

Formula Not::substitute(const Formula &what, const Formula &with) const
{
    if(equalTo(what))
    {
        return with;
    }
    return std::make_shared<Not>(operand()->substitute(what,with));
}

Formula Not::simplify() const
{
    Formula simplifiedOp = operand()->simplify();
    if(BaseFormula::isOfType<True>(simplifiedOp)){
        return std::make_shared<False>();
    } else if (BaseFormula::isOfType<False>(simplifiedOp)){
        return std::make_shared<True>();
    }
    return std::make_shared<Not>(simplifiedOp);
}

Formula Not::nnf() const
{
    Formula op = operand();
    if(BaseFormula::isOfType<Not>(op)){
        const Not* opNot = static_cast<const Not*>(op.get());
        return opNot->operand()->nnf();
    }
    else if(BaseFormula::isOfType<And>(op)){
        const And* opAdd = static_cast<const And*>(op.get());
        Formula op1, op2;
        std::tie(op1, op2) = opAdd->operands();
        return std::make_shared<Or>(std::make_shared<Not>(op1)->nnf(), std::make_shared<Not>(op2)->nnf());
    }
    else if(BaseFormula::isOfType<Or>(op)){
        const Or* opOr = static_cast<const Or*>(op.get());
        Formula op1, op2;
        std::tie(op1, op2) = opOr->operands();
        return std::make_shared<And>(std::make_shared<Not>(op1)->nnf(), std::make_shared<Not>(op2)->nnf());
    }
    else if(BaseFormula::isOfType<Imp>(op)){
        const Imp* opImp = static_cast<const Imp*>(op.get());
        Formula op1, op2;
        std::tie(op1, op2) = opImp->operands();
        return std::make_shared<And>(op1->nnf(), std::make_shared<Not>(op2)->nnf());
    }
    else if(BaseFormula::isOfType<Iff>(op)){
        const Iff* opIff = static_cast<const Iff*>(op.get());
        Formula op1, op2;
        std::tie(op1, op2) = opIff->operands();
        return std::make_shared<Or>(std::make_shared<And>(op1->nnf(), std::make_shared<Not>(op2)->nnf()),
                                    std::make_shared<And>(std::make_shared<Not>(op1)->nnf(), op2->nnf()));
    }

    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

