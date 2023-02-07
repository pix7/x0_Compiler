#include "global.h"

//IfStat()
//ReadStat()
//WriteStat()
//WhileStat()


// IfStat 语句处理
//if_stat = "if" "(" expression ")" statement [ "else" statement]

int IfStat()
{
    if (sym == ifsym)
    {
        if (!getsym()) return 0;
        if (sym == lparen)
        {
            if (!getsym()) return 0;
            if (!expression()) return 0;
            int pos1 = codeNum; /* 记录中间代码行号以便回填 */
            Gen(jpc, 0, 0);/* 生成中间代码，跳转位置需要回填 */

            if (sym == rparen)
            {
                if (!getsym()) return 0;
                if (!statement()) return 0;
                if (sym == elsesym)
                {
                    int pos2 = codeNum; /* 记录中间代码行号以便回填 */
                    Gen(jmp, 0, 0);  /* 生成中间代码，跳转位置需要回填 */
                    code[pos1].a = codeNum; /* 回填 */
                    if (!getsym()) return 0;
                    if (!statement()) return 0;
                    code[pos2].a = codeNum; /* 回填 */
                }
                else
                {
                    code[pos1].a = codeNum; /* 回填 */
                }
            }
            else /* 缺少 ')' */
            {
                 ErrorHandler(9);
            }
        }
        else /* 缺少 '(' */
        {
             ErrorHandler(12);
        }
    }
    else /* 缺少 'if' */
    {
         ErrorHandler(13);
    }
    return 1;
}

// ReadStat 语句处理
//read_stat = "read" var ";"

int ReadStat()
{
    if (sym == readsym)
    {
        if (!getsym()) return 0;

        ObjectKind kind;
        int address;
        int IncOrDec; /* 自增自减情况 */
        if (!Var(&kind, &address, &IncOrDec)) return 0;

        /* read后不接自增自减变量 */
        if (IncOrDec != 5)
        {
             ErrorHandler(15);
        }

        ///* 生成中间代码 */
        switch (kind)
        {
        case intVar:
        case intArray:
            Gen(opr, Int, 16);  /* 读入int */
            break;
        case charVar:
        case charArray:
            Gen(opr, Char, 16);  /* 读入char */
            break;
        }


        Gen(sto, 0, address); /* 读到的内容存入变量 */

        if (sym == semic)
        {
            if (!getsym()) return 0;
        }
        else /* 缺少 ';' */
        {
             ErrorHandler(8);
        }
    }
    else /* 缺少 'read' */
    {
         ErrorHandler(16);
    }
    return 1;
}

// WriteStat 语句处理
 //write_stat = "write" expression ";"

int WriteStat()
{
    if (sym == writesym)
    {
        if (!getsym()) return 0;
        if (!expression()) return 0;
        if (sym == semic)
        {
            if (!getsym()) return 0;
        }
        else /* 缺少 ';' */
        {
             ErrorHandler(8);
        }
        Gen(opr, 0, 14); /* 输出 */
        Gen(opr, 0, 15); /* 输出换行符 */
    }
    else /* 缺少 'write' */
    {
         ErrorHandler(17);
    }
    return 1;
}


// WhileStat 语句处理
 //while_stat = "while" "(" expression ")" statement

int WhileStat()
{
    if (sym == whilesym)
    {
        if (!getsym()) return 0;
        if (sym == lparen)
        {
            int pos1 = codeNum;  /* 记录中间代码行号以便跳转 */
            if (!getsym()) return 0;
            if (!expression()) return 0;
            if (sym == rparen)
            {
                int pos2 = codeNum;  /* 记录中间代码行号以便回填 */
                Gen(jpc, 0, 0);  /* 生成中间代码，跳转位置需要回填 */
                if (!getsym()) return 0;
                if (!statement()) return 0;

                Gen(jmp, 0, pos1);
                code[pos2].a = codeNum; /* 回填 */
            }
            else /* 缺少 ')' */
            {
                 ErrorHandler(9);
            }
        }
        else /* 缺少 '(' */
        {
            ErrorHandler(12);
        }
    }
    else /* 缺少 'while' */
    {
         ErrorHandler(15);
    }
    return 1;
}

