#include "global.h"

//声明语句处理
// declaration_stat = type ID ";" | type ID "[" NUM "]" ";"

int DeclarationStat(int* ptr_address)
{
    DataType dt = type();
    if (dt == Nul) return 0;

    if (sym == ident)
    {
        if (!getsym()) return 0;
        if (sym == lbracket)  /* 定义数组 */
        {
            int size[MAX_DIMENSION] = { 0 };
            int d = 0;
            int space = 1; /* 为数组分配的空间 */
            while (sym == lbracket)
            {
                if (!getsym()) return 0;
                if (sym == intnum)
                {
                    size[d++] = intNum;
                    space *= intNum;
                    if (!getsym()) return 0;
                    if (sym == rbracket)
                    {
                        if (!getsym()) return 0;
                    }
                    else /* 缺少 ']' */
                    {
                         ErrorHandler(18);
                    }
                }
                else /* 数组定义缺少整数 */
                {
                      ErrorHandler(19);
                }
            }

            if (dt == Char) /* 定义char数组 */
            {
                EnterTable(charArray, *ptr_address, size, d, 0);
                *ptr_address = *ptr_address + space;
            }
            else if (dt == Int) /* 定义int数组 */
            {
                EnterTable(intArray, *ptr_address, size, d, 0);
                *ptr_address = *ptr_address + space;
            }
        }
        else /* 定义非数组变量 */
        {
            int size[MAX_DIMENSION] = { 0 };
            int d = 0;
            if (dt == Char) /* 定义char变量 */
            {
                EnterTable(charVar, *ptr_address, size, d, 0);
                *ptr_address = *ptr_address + 1;
            }
            else if (dt == Int) /* 定义int变量 */
            {
                EnterTable(intVar, *ptr_address, size, d, 0);
                *ptr_address = *ptr_address + 1;
            }
        }

        if (sym == semic)
        {
            if (!getsym()) return 0;
        }
        else /* 缺少';' */
        {
              ErrorHandler(8);
        }

    }
    else /* 缺少标识符 */
    {
         ErrorHandler(20);
    }
    return 1;
}

// DeclarationList 语句处理
//declaration_list = [declaration_list declaration_stat |declaration_stat]
//消除左递归后变为 declaration_list = [declaration_stat declaration_list])
int DeclarationList(int* ptr_address)
{
    // 若符号sym在DeclarationStat开始字符集合中则按 DeclarationStat处理
    while (sym == charsym || sym == intsym)
    {
        if (!DeclarationStat(ptr_address)) return 0;
    }
    return 1;
}
