#include "global.h"

//SimpleExpr()
// expression()

// SimpleExpr 语句处理
 //simple_expr = additive_expr | additive_expr(">" | "<" | ">=" | "<=" | "==" | "!=") additive_expr
//  |odd additive_expr

int SimpleExpr()
{
    if (sym == oddsym)
    {
        if (!getsym()) return 0;
        if (!AdditiveExpr()) return 0;
        Gen(opr, 0, 6);
    }
    else
    {
        AdditiveExpr();

        if (sym == eqleql || sym == neql || sym == less || sym == greateql
            || sym == great || sym == lesseql)
        {
            enum symbol temps = sym;
            if (!getsym()) return 0;
            if (!AdditiveExpr()) return 0;

            switch (temps)
            {
            case eqleql:
                Gen(opr, 0, 8);
                break;
            case neql:
                Gen(opr, 0, 9);
                break;
            case less:
                Gen(opr, 0, 10);
                break;
            case greateql:
                Gen(opr, 0, 11);
                break;
            case great:
                Gen(opr, 0, 12);
                break;
            case lesseql:
                Gen(opr, 0, 13);
                break;

            default: /* 非法运算符 */
                 ErrorHandler(24);
            }
        }
    }
    return 1;
}

// expression 语句处理
//expression = var "=" expression | simple_expr

int expression()
{
    /* 判断为哪种语句 */
    if (sym == ident)
    {
        if (FindPos(id) != -1)
        {
            backup();		/* 需要继续判断 */
            int address;
            ObjectKind kind;
            if (!SimpleVar(&kind, &address)) return 0;
            if (sym == eql) /* 赋值语句 */
            {
                if (!getsym()) return 0;
                if (!expression()) return 0;
                Gen(sto, 0, address); /* 存入变量 */
            }
            else /* SimpleExpr */
            {
                recover();
                if (!SimpleExpr()) return 0;
                while (sym == xorsym)
                {
                    if (!getsym()) return 0;
                    if (!SimpleExpr()) return 0;
                    Gen(opr, 0, 17);
                }
            }
        }
    }
    else
    {
        if (!SimpleExpr()) return 0;
        while (sym == xorsym)
        {
            if (!getsym()) return 0;
            if (!SimpleExpr()) return 0;
            Gen(opr, 0, 17);
        }
    }
    return 1;
}

// ExpressionStat 语句处理
//expression_stat = expression ";" | ";"

int ExpressionStat()
{
    if (sym != semic)
    {
        if (!expression()) return 0;
        if (sym == semic)
        {
            if (!getsym()) return 0;
        }
        else /* 缺少 ';' */
        {
             ErrorHandler(8);
        }
    }
    else
    {
        if (!getsym()) return 0;
    }
    return 1;
}
