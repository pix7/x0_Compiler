#include "global.h"

//type语句,判断字符类型是Int还是Char

DataType type()
{
    switch (sym)
    {
    case intsym:
        if (!getsym()) return Nul;
        return Int;
    case charsym:
        if (!getsym()) return Nul;
        return Char;
    default:
        return Nul;   /* 数据类型非法 */
    }
    return Int;
}
