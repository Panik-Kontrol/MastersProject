#ifndef NOT_H
#define NOT_H

#include "unary_connective.h"
#include "constant.h"

class Not : public UnaryConnective
{
public:
    Not(const Formula &op);
    virtual std::ostream& print(std::ostream &out) const;
    virtual Formula substitute(const Formula &what, const Formula &with) const;
    virtual Formula simplify() const ;
    virtual Formula nnf() const;
};


#endif // NOT_H
