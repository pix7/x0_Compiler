#include "global.h"

// statement 语句处理
//statement = if_stat | while_stat | read_stat | write_stat
//| repeat_stat | compound_stat | expression_stat.
int statement()
{
    if (sym == ifsym)
    {
        return IfStat();
    }
    else if (sym == whilesym)
    {
        return WhileStat();
    }
    else if (sym == readsym)
    {
        return ReadStat();
    }
    else if (sym == writesym)
    {
        return WriteStat();
    }
    else if (sym == lbrace)
    {
        return CompoundStat();
    }
    else if (sym == reptsym)
    {
        return RepeatStat();
    }
    else
    {
        return ExpressionStat();
    }
}

// StatementList 语句处理
//statement_list = statement_list statement
//消除左递归变为statement_list = statement statement_list

int StatementList()
{
    /* 若符号sym在Statement开始字符集合中则按Statement处理 */
    while (sym == ifsym || sym == whilesym || sym == readsym
        || sym == writesym || sym == lbrace || sym == semic
        || sym == ident || sym == lparen || sym == intnum || sym==reptsym
        || sym == minus || sym == incsym || sym == decsym || sym == oddsym)
    {
        if (!statement()) return 0;
    }
    return 1;
}
