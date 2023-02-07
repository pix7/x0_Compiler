#include "global.h"

// term 语句处理
 //term = factor {("*"|"/") factor }

int term()
{
    factor();
    while (sym == times || sym == slash || sym == modsym)
    {
        enum symbol temps = sym;
        if (!getsym()) return 0;
        if (!factor()) return 0;
        switch (temps)
        {
        case times:
            Gen(opr, 0, 4);
            break;
        case slash:
            Gen(opr, 0, 5);
            break;
        case modsym:
            Gen(opr, 0, 7);
            break;
        }
    }
    return 1;
}
