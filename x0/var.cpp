#include "global.h"

//SimpleVar()
//Var()


// SimpleVar 语句处理,被expression()调用
//判断赋值语句的变量
//simpVar=ID | ID "[" expression "]"

int SimpleVar(ObjectKind* ptr_kind, int* ptr_address)
{
    if (sym == ident)
    {
        int pos = FindPos(id);

        if (pos == -1)	/* 标识符未声明 */
        {
             ErrorHandler(21);
        }

        *ptr_address = symTable[pos].address;
        *ptr_kind = symTable[pos].kind;

        if (!getsym()) return 0;
        if (sym == lbracket)
        {

            if (*ptr_kind != intArray && *ptr_kind != charArray)
            {
                 ErrorHandler(22); /* 变量不为数组 */
            }

            /* 数组下标越界检查 */
            backup();
            int currentD = 0;
            while (sym == lbracket)
            {
                if (!getsym()) return 0;
                if (sym == intnum)
                {
                    int temp = intNum;
                    if (!getsym()) return 0;
                    if (sym == rbracket)
                    {
                        if (temp >= symTable[pos].size[currentD++])
                        {
                             ErrorHandler(23);  /* 数组下标越界 */
                        }
                        if (!getsym()) return 0;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            recover();

            while (sym == lbracket)
            {
                if (!getsym()) return 0;
                if (!expression()) return 0;
                if (sym == rbracket)
                {
                    if (!getsym()) return 0;
                }
                else
                {
                     ErrorHandler(18);/* 缺少 ']' */
                }
            }
        }
    }
    else /* 缺少标识符 */
    {
         ErrorHandler(20);
    }
    return 1;
}

// var 语句处理
//在simpvar的基础上实现自增自减
//判断var = (simplevar[" ++ "|" -- "])|((" ++ "|" -- ")simplevar)

int Var(ObjectKind* ptr_kind, int* ptr_address, int* ptr_IncOrDec)
{
    if (sym == ident)
    {
        if (!SimpleVar(ptr_kind, ptr_address)) return 0;
        if (sym == incsym)
        {
            *ptr_IncOrDec = 1;  /* 后接自增 */
            if (!getsym()) return 0;
        }
        else if (sym == decsym)
        {
            *ptr_IncOrDec = 2;  /* 后接自减 */
            if (!getsym()) return 0;
        }
        else
        {
            *ptr_IncOrDec = 5;  /* 无自增自减 */
        }
    }
    else if (sym == incsym || sym == decsym)
    {
        if (sym == incsym)
        {
            *ptr_IncOrDec = 3;  /* 前接自增 */
        }
        else
        {
            *ptr_IncOrDec = 4; /* 前接自减 */
        }
        if (!getsym()) return 0;
        if (!SimpleVar(ptr_kind, ptr_address)) return 0;
    }
    else /* 缺少标识符 */
    {
         ErrorHandler(20);
    }
    return 1;
}
