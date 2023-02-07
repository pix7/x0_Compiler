#include "global.h"


/* 解释并执行中间代码 */

/* 解释并执行中间代码 */
void Interpret()
{
    int p = 0;						/* 指令指针 */
    int b = 1;						/* 指令基址 */
    int t = 0;						/* 栈顶指针 */
    int s[MAX_SIZE_STACK];			/* 数据栈 */
    memset(s, 0, sizeof(s));		/* 栈初始化*/

    Instruction i;					/* 存放当前指令 */

    int d;							/* 存放数组维数 */
    int adr;						/* 数组元素的偏移量 */
    int pos;						/* 记录变量在符号表中的位置 */
    //int outputType = Int;			/* 记录栈顶元素类型以便输出 */
    //int codenNumprint = 0;			/* 记录中间代码行号 */


    printf("output of x0 program:\n");
    fprintf(fout, "output of x0 program:\n");
    s[0] = 0; /* s[0]不用 */
    s[1] = 0; /* 主程序的三个联系单元均置为0 */
    s[2] = 0;
    s[3] = 0;
    do {
        i = code[p];	/* 读当前指令 */

        //fprintf(fcode,"%d: %s, %d, %d\n", codenNumprint, fctCodeString[i.fct], i.l, i.a);
        //codenNumprint = codenNumprint + 1;
        p = p + 1;

        if (i.fct != opr && i.a != 14)
            outputType = Int;

        switch (i.fct)
        {
        case lit:	/* 将常量值取到栈顶 */
            t = t + 1;
            s[t] = i.a;
            break;
        case opr:	/* 数学、逻辑运算 */
            switch (i.a)
            {
            case 0:  /* 函数调用结束，返回 */
                t = b - 1;
                p = s[t + 3];
                b = s[t + 2];
                break;
            case 1: /* 栈顶元素取反 */
                s[t] = -s[t];
                break;
            case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
                t = t - 1;
                s[t] = s[t] + s[t + 1];
                break;
            case 3:/* 次栈顶项减去栈顶项 */
                t = t - 1;
                s[t] = s[t] - s[t + 1];
                break;
            case 4:/* 次栈顶项乘以栈顶项 */
                t = t - 1;
                s[t] = s[t] * s[t + 1];
                break;
            case 5:/* 次栈顶项除以栈顶项 */
                t = t - 1;
                s[t] = s[t] / s[t + 1];
                break;
            case 6:/* 栈顶元素的奇偶判断 */
                s[t] = s[t] % 2;
                break;
            case 7:/* 次栈顶项mod栈顶项 */
                t = t - 1;
                s[t] = s[t] % s[t + 1];
                break;
            case 8:/* 次栈顶项与栈顶项是否相等 */
                t = t - 1;
                s[t] = (s[t] == s[t + 1]);
                break;
            case 9:/* 次栈顶项与栈顶项是否不等 */
                t = t - 1;
                s[t] = (s[t] != s[t + 1]);
                break;
            case 10:/* 次栈顶项是否小于栈顶项 */
                t = t - 1;
                s[t] = (s[t] < s[t + 1]);
                break;
            case 11:/* 次栈顶项是否大于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] >= s[t + 1]);
                break;
            case 12:/* 次栈顶项是否大于栈顶项 */
                t = t - 1;
                s[t] = (s[t] > s[t + 1]);
                break;
            case 13: /* 次栈顶项是否小于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] <= s[t + 1]);
                break;
            case 14:/* 栈顶值输出 */
                if (outputType == Int)
                {
                    printf("%d", s[t]);
                    fprintf(fout, "%d", s[t]);
                }
                else
                {
                    printf("%c", s[t]);
                    fprintf(fout, "%c", s[t]);
                }

                t = t - 1;
                break;
            case 15:/* 输出换行符 */
                printf("\n");
                fprintf(fout, "\n");
                break;
            case 16:/* 读入一个输入置于栈顶 */
                t = t + 1;
                switch (i.l)
                {
                case Int:
                    //scanf("%d", &(s[t]));
                    fscanf(finput, "%d", &(s[t]));
                    fprintf(fout, ">>%d\n", s[t]);
                    break;
                case Char:
                    char tmp = ' ';
                    while (tmp == ' ' || tmp == '\n')
                        fscanf(finput, "%c", &tmp);
                    s[t] = int(tmp);
                    fprintf(fout, ">>%c\n", s[t]);
                    break;
                }
                break;
            case 17:/* 次栈顶项xor栈顶项 */
                t = t - 1;
                if (s[t] == s[t + 1])
                    s[t] = 0;
                else
                    s[t] = 1;
                break;
            }
            break;
        case lod:	/* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
            pos = FindPos(i.a);
            d = symTable[pos].d;
            adr = 0;
            for (int i = 0; i < d; i++)
            {
                adr = adr * symTable[pos].size[i] + s[t + 1 - d + i];
            }
            s[t + 1 - d] = s[b + i.a + adr];  /* 下标出栈，栈顶为读取的元素 */
            t = t + 1 - d;
            if (symTable[pos].kind == charVar || symTable[pos].kind == charArray)
                outputType = Char;
            break;

        case sto:	/* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
            pos = FindPos(i.a);
            d = symTable[pos].d;
            adr = 0;
            for (int i = 0; i < d; i++)
            {
                adr = adr * symTable[pos].size[i] + s[t - d + i];
            }
            s[b + i.a + adr] = s[t];
            s[t - d] = s[t];  /* 下标出栈，栈顶为读取的元素 */
            t = t - d;
            break;
        case ini:	/* 在数据栈中为被调用的过程开辟a个单元的数据区 */
            t = t + i.a;
            break;
        case jmp:	/* 直接跳转 */
            p = i.a;
            break;
        case jpc:	/* 条件跳转 */
            if (s[t] == 0)
                p = i.a;
            t = t - 1;
            break;
        }
    } while (p != 0);
    printf("End x0\n");
    fprintf(fout, "End x0.\n");

    fprintf(fout, "errornum is %d\n",errornum);

    /* 输出中间代码 */
    for (int n = 0; n < codeNum; n++)
        fprintf(fcode, "%d: %s, %d, %d\n", n, fctCodeString[code[n].fct], code[n].l, code[n].a);


    /* 输出符号表 */
    fprintf(ftable, "NAME\t KIND\t LEVEL\t ADR \n\n");
    for (int n = 0; n < tableSize; n++)
        fprintf(ftable, "%s\t %s\t %d\t %d \n", symTable[n].name, dataTypeString[symTable[n].kind], symTable[n].value, symTable[n].address);


    ///* 输出栈 */
    //for (int n = 0; n < t; n++)
    //	fprintf(fstack, "%d:\t %d \n", n, s[n]);
}



/* 单步解释 */
void InterpretStep()
{
    //int p = 0;						/* 指令指针 */
    //int b = 1;						/* 指令基址 */
    //int t = 0;						/* 栈顶指针 */`````
    //int s[MAX_SIZE_STACK];			/* 数据栈 */


    Instruction i;					/* 存放当前指令 */

    int d;							/* 存放数组维数 */
    int adr;						/* 数组元素的偏移量 */
    int pos;						/* 记录变量在符号表中的位置 */
    //int outputType = Int;			/* 记录栈顶元素类型以便输出 */
    //int codenNumprint = 0;			/* 记录中间代码行号 */


    if (p == 0)
    {
        printf("output of x0 program:\n");
        fprintf(fout, "output of x0 program:\n");
        s[0] = 0; /* s[0]不用 */
        s[1] = 0; /* 主程序的三个联系单元均置为0 */
        s[2] = 0;
        s[3] = 0;
    }

    //do {
    i = code[p];	/* 读当前指令 */

    p = p + 1;

    if (i.fct != opr && i.a != 14)
        outputType = Int;

    switch (i.fct)
    {
    case lit:	/* 将常量a的值取到栈顶 */
        t = t + 1;
        s[t] = i.a;
        break;
    case opr:	/* 数学、逻辑运算 */
        switch (i.a)
        {
        case 0:  /* 函数调用结束后返回 */
            t = b - 1;
            p = s[t + 3];
            b = s[t + 2];
            break;
        case 1: /* 栈顶元素取反 */
            s[t] = -s[t];
            break;
        case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
            t = t - 1;
            s[t] = s[t] + s[t + 1];
            break;
        case 3:/* 次栈顶项减去栈顶项 */
            t = t - 1;
            s[t] = s[t] - s[t + 1];
            break;
        case 4:/* 次栈顶项乘以栈顶项 */
            t = t - 1;
            s[t] = s[t] * s[t + 1];
            break;
        case 5:/* 次栈顶项除以栈顶项 */
            t = t - 1;
            s[t] = s[t] / s[t + 1];
            break;
        case 6:/* 栈顶元素的奇偶判断 */
            s[t] = s[t] % 2;
            break;
        case 7:/* 次栈顶项mod栈顶项 */
            t = t - 1;
            s[t] = s[t] % s[t + 1];
            break;
        case 8:/* 次栈顶项与栈顶项是否相等 */
            t = t - 1;
            s[t] = (s[t] == s[t + 1]);
            break;
        case 9:/* 次栈顶项与栈顶项是否不等 */
            t = t - 1;
            s[t] = (s[t] != s[t + 1]);
            break;
        case 10:/* 次栈顶项是否小于栈顶项 */
            t = t - 1;
            s[t] = (s[t] < s[t + 1]);
            break;
        case 11:/* 次栈顶项是否大于等于栈顶项 */
            t = t - 1;
            s[t] = (s[t] >= s[t + 1]);
            break;
        case 12:/* 次栈顶项是否大于栈顶项 */
            t = t - 1;
            s[t] = (s[t] > s[t + 1]);
            break;
        case 13: /* 次栈顶项是否小于等于栈顶项 */
            t = t - 1;
            s[t] = (s[t] <= s[t + 1]);
            break;
        case 14:/* 栈顶值输出 */
            if (outputType == Int)
            {
                printf("%d", s[t]);
                fprintf(fout, "%d", s[t]);
            }
            else
            {
                printf("%c", s[t]);
                fprintf(fout, "%d", s[t]);
            }

            t = t - 1;
            break;
        case 15:/* 输出换行符 */
            printf("\n");
            fprintf(fout, "\n");
            break;
        case 16:/* 读入一个输入置于栈顶 */
            t = t + 1;
            switch (i.l)
            {
            case Int:
                //scanf("%d", &(s[t]));
                fscanf(finput, "%d", &(s[t]));
                fprintf(fout, ">>%d\n", s[t]);
                break;
            case Char:
                char tmp = ' ';
                while (tmp == ' ' || tmp == '\n')
                    fscanf(finput, "%c", &tmp);
                s[t] = int(tmp);
                fprintf(fout, ">>%c\n", s[t]);
                break;
            }
            break;
        case 17:/* 次栈顶项xor栈顶项 */
            t = t - 1;
            if (s[t] == s[t + 1])
                s[t] = 0;
            else
                s[t] = 1;
            break;
        }
        break;
    case lod:	/* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
        pos = FindPos(i.a);
        d = symTable[pos].d;
        adr = 0;
        for (int i = 0; i < d; i++)
        {
            adr = adr * symTable[pos].size[i] + s[t + 1 - d + i];
        }
        s[t + 1 - d] = s[b + i.a + adr];  /* 下标出栈，栈顶为读取的元素 */
        t = t + 1 - d;
        if (symTable[pos].kind == charVar || symTable[pos].kind == charArray)
            outputType = Char;
        break;

    case sto:	/* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
        pos = FindPos(i.a);
        d = symTable[pos].d;
        adr = 0;
        for (int i = 0; i < d; i++)
        {
            adr = adr * symTable[pos].size[i] + s[t - d + i];
        }
        s[b + i.a + adr] = s[t];
        s[t - d] = s[t];  /* 下标出栈，栈顶为读取的元素 */
        t = t - d;
        break;
    case ini:	/* 在数据栈中为被调用的过程开辟a个单元的数据区 */
        t = t + i.a;
        break;
    case jmp:	/* 直接跳转 */
        p = i.a;
        break;
    case jpc:	/* 条件跳转 */
        if (s[t] == 0)
            p = i.a;
        t = t - 1;
        break;
    }
    //} while (p != 0);
    //if(p==0) printf("End x0\n");
    //fprintf(fout, "End x0.\n");


    /* 输出中间代码 */
    for (int n = 0; n < codeNum; n++)
        fprintf(fcode, "%d: %s, %d, %d\n", n, fctCodeString[code[n].fct], code[n].l, code[n].a);

    /* 输出单步中间代码 */
    fprintf(fstep, "%s, %d, %d\n", fctCodeString[i.fct], i.l, i.a);

    /* 输出符号表 */
    fprintf(ftable, "NAME\t KIND\t LEVEL\t ADR \n\n");
    for (int n = 0; n < tableSize; n++)
        fprintf(ftable, "%s\t %s\t %d\t %d \n", symTable[n].name, dataTypeString[symTable[n].kind], symTable[n].value, symTable[n].address);

    //int tempt = t;

    /* 输出栈*/
    for (int n = 0; n < t + 1; n++)
    {
        fprintf(fstack, "%d:\t%d \n", n, s[n]);
    }
}



