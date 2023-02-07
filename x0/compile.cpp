#include "global.h"

/* 编译程序主体 */
int compile()
{
    Gen(jmp, 0, 1);
    if (!getsym()) return 0;

    if (sym == mainsym)
    {
        if (!getsym()) return 0;
        if (sym == lbrace)
        {
            if (!getsym()) return 0;

            /* 局部变量地址 */
            int address = 3;


            /* 分析定义语句时address增加 */
            if (!DeclarationList(&address)) return 0;

            Gen(ini, 0, address);

            if (!StatementList()) return 0;

            if (sym == rbrace)
            {
                Gen(opr, 0, 0);  /* main结束 */
                printf("\nCompile successfully!\n");
                fprintf(fout, "\nCompile successfully!\n");
            }
            else /* 缺少 '}' */
            {
                 ErrorHandler(5);
            }
        }
        else /* 缺少{ */
        {
             ErrorHandler(6);
        }

    }
    else /* 缺少main */
    {
         ErrorHandler(7);
    }
    return 1;
}
