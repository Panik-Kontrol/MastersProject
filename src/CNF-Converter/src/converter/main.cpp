#include <iostream>
#include "propositional_logic.h"

using namespace std;

int main()
{
    Formula q = make_shared<Atom>("q");
    Formula r = make_shared<Atom>("r");
    Formula p = make_shared<Atom>("p");

    Formula f1 = make_shared<And>(q, r);
    Formula f2 = make_shared<Imp>(p, f1);

    Formula f3 = make_shared<Not>(p);
    Formula f4 = make_shared<Or>(q, f3);
    Formula f5 = make_shared<Iff>(r, f4);

    Formula f6 = make_shared<Imp>(f2, f5);

    cout << f6 << endl;
    cout << f6->tseitinTransformation() << endl;

    return 0;
}
