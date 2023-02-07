#include "global.h"

// factor 语句处理
//factor = "(" expression ")"| var | NUM

int factor()
{
    if (sym == lparen)
    {
        if (!getsym()) return 0;
        if (!expression()) return 0;
        if (sym == rparen)
        {
            if (!getsym()) return 0;
        }
        else /* 缺少 ')' */
        {
             ErrorHandler(9);
        }
    }
    else if (sym == ident || sym == incsym || sym == decsym)
    {
        ObjectKind kind;
        int address;
        int IncOrDec;
        if (!Var(&kind, &address, &IncOrDec)) return 0;

        switch (IncOrDec)
        {
        case 1:  /* v++ */
            Gen(lod, 0, address);
            Gen(lit, 0, 1);
            Gen(opr, 0, 2);
            Gen(sto, 0, address);/*符号表中变量+1*/
            Gen(lit, 0, 1);
            Gen(opr, 0, 3);  /*栈中变量-1即恢复原值*/
            break;
        case 2:  /* v-- */
            Gen(lod, 0, address);
            Gen(lit, 0, 1);
            Gen(opr, 0, 3);
            Gen(sto, 0, address); /*符号表中变量-1*/
            Gen(lit, 0, 1);
            Gen(opr, 0, 2);  /*栈中变量+1即恢复原值*/
            break;
        case 3:  /* ++v */
            Gen(lod, 0, address);
            Gen(lit, 0, 1);
            Gen(opr, 0, 2);
            Gen(sto, 0, address);
            break;
        case 4:  /* --v */
            Gen(lod, 0, address);
            Gen(lit, 0, 1);
            Gen(opr, 0, 3);
            Gen(sto, 0, address);
            break;
        case 5: /* v */
            Gen(lod, 0, address);
            break;
        }
    }
    else if (sym == intnum)
    {
        Gen(lit, 0, intNum);
        if (!getsym()) return 0;
    }
    else /* factor语法错误 */
    {
        ErrorHandler(10);
    }
    return 1;
}
