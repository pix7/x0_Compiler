#include "global.h"

/* 生成中间代码 */
void Gen(FctCode fct, int l, int a)
{
    if (codeNum >= MAX_NUM_CODE) /* 程序过长 */
    {
        ErrorHandler(11);
    }
    if (a >= MAX_SIZE_ADDRESS) /* 地址越界 */
    {
        ErrorHandler(26);
    }

    code[codeNum].fct = fct;
    code[codeNum].l = l;
    code[codeNum].a = a;

    codeNum++;
}
