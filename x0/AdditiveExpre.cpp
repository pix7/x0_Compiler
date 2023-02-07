#include "global.h"

// AdditiveExpr 语句处理
//additive_expr = ["-"]term {("+"|"-") term

int AdditiveExpr()
{
    if (sym == minus)  /*取负*/
    {
        if (!getsym()) return 0;
        if (!term()) return 0;
        Gen(opr, 0, 1);
    }
    else
    {
        if (!term()) return 0;;
    }

    while (sym == plus || sym == minus)
    {
        Symbol temps = sym;
        if (!getsym()) return 0;
        if (!term()) return 0;;

        switch (temps)
        {
        case plus:
            Gen(opr, 0, 2);
            break;
        case minus:
            Gen(opr, 0, 3);
            break;
        }
    }
    return 1;
}
