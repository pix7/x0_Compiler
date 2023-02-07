#include "global.h"

// CompoundStat 语句处理
//compound_stat = "{" statement_list "}"

int CompoundStat()
{
    if (sym == lbrace)
    {
        if (!getsym()) return 0;
        if (!StatementList()) return 0;
        if (sym == rbrace)
        {
            if (!getsym()) return 0;
        }
        else /* 缺少 '}' */
        {
             ErrorHandler(5);
        }
    }
    else /* 缺少 '{' */
    {
         ErrorHandler(6);
    }
    return 1;
}
