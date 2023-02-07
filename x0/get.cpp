#include "global.h"

/*
 * 过滤空格，读取一个字符
 * 每次读一行，存入line缓冲区，line被getsym取空后再读一行
 * 被函数getsym调用
 * 去除注释
 */
int getch()
{
    if (cc == ll)	/* 判断缓冲区中是否有字符，若无字符，则读入下一行字符到缓冲区中 */
    {
        if (feof(fin))
        {
            printf("\nProgram end!\n");
            fprintf(fout, "\nProgram end!\n");
            return 1;
        }
        ll = 0;
        cc = 0;
        ch = ' ';
        while (ch != 10) /* 非换行符 */
        {
            char pre = ch;
            if (ll >= MAX_NUM_LINE)	/* 单行字符个数超出lineCache长度 */
            {
                 ErrorHandler(1);
            }
            if (EOF == fscanf(fin, "%c", &ch))
            {
                lineCache[ll] = 0;
                break;
            }
            if (pre == '/' && ch == '*')
            {
                lineCache[ll] = 0;
                bool isEnter = false; /*注释内有换行符*/
                fscanf(fin, "%c", &pre);
                fscanf(fin, "%c", &ch);
                if (pre == '\n')
                    isEnter = true;
                while (pre != '*' || ch != '/')
                {
                    pre = ch;
                    if (pre == '\n')
                    {
                        printf("\n");
                        fprintf(fout, "\n");
                    }
                    if (EOF == fscanf(fin, "%c", &ch))
                    {
                         ErrorHandler(2);/*注释缺少结束符号*/
                    }
                }
                if (ll == 0) /* 行中前两个字符为注释开始符号 */
                {
                    ch = ' ';
                    continue;

                }
                if (isEnter == true)
                {
                    printf("\n");
                    fprintf(fout, "\n");
                }

                break;
            }
            if (pre == '/') /*若/非用于注释则输出*/
            {
                printf("%c", pre);
                fprintf(fout, "%c", pre);
                lineCache[ll] = pre;
                ll++;
            }
            if (ch != '/')
            {
                printf("%c", ch);                   /* 当前字符不为/则输出, 否则下一循环继续判断 */
                fprintf(fout, "%c", ch);
                lineCache[ll] = ch;
                ll++;
            }
        }
    }
    ch = lineCache[cc];
    cc++;
    return 1;
}

/*
 * 词法分析，获取一个符号
 */
int getsym()
{
    int i, j, k;

    while (ch == ' ' || ch == '\n' || ch == 9)	/* 过滤空格、换行和制表符 */
    {
        if (!getch())
            return 0;
    }
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))	/* 当前的单词是标识符或是保留字 */
    {
        k = 0;
        do
        {
            if (k < MAX_LEN_IDENT)
            {
                temp[k++] = ch;
            }
            else /* 标识符名字过长 */
            {
                  ErrorHandler(3);
            }
            if (!getch()) return 0;
        } while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'));

        temp[k] = 0;

        strcpy(id, temp);	/* 在id存放标识符或保留字的名字 */

        i = 0;
        j = RESERVE_WORD_NUM - 1;
        do  /* 搜索当前单词是否为保留字，使用二分法查找 */
        {
            k = (i + j) / 2;
            if (strcmp(id, reserveWord[k]) <= 0)
            {
                j = k - 1;
            }
            if (strcmp(id, reserveWord[k]) >= 0)
            {
                i = k + 1;
            }
        } while (i <= j);
        if (i - 1 > j) /* 当前的单词是保留字 */
        {
            sym = wsym[k];
        }
        else /* 当前的单词是标识符 */
        {
            sym = ident;
        }
    }
    else if (ch >= '0' && ch <= '9')	/* 当前的单词是数字 */
    {
        k = 0;
        intNum = 0;
        sym = intnum;

        /* 读入数字 */
        do
        {
            intNum = 10 * intNum + ch - '0';
            k++;

            if (k > MAX_LEN_INT) /* 整数超过9位 */
            {
                 ErrorHandler(4);
            }
            if (!getch()) return 0;
        } while (ch >= '0' && ch <= '9');
    }
    else
    {
        switch (ch)
        {
        case '=':
            if (!getch()) return 0;
            if (ch == '=')  /* 检测==符号 */
            {
                sym = eqleql;
                if (!getch()) return 0;
            }
            else
            {
                sym = eql;  /* 检测=符号 */
            }
            break;
        case '<':
            if (!getch()) return 0;
            if (ch == '=')  /* 检测<=符号 */
            {
                sym = lesseql;
                if (!getch()) return 0;
            }
            else
            {
                sym = less;  /* 检测<符号 */
            }
            break;
        case '>':
            if (!getch()) return 0;
            if (ch == '=')  /* 检测>=符号 */
            {
                sym = greateql;
                if (!getch()) return 0;
            }
            else
            {
                sym = great;  /* 检测>符号 */
            }
            break;
        case '+':
            if (!getch()) return 0;
            if (ch == '+')  /* 检测++符号 */
            {
                sym = incsym;
                if (!getch()) return 0;
            }
            else
            {
                sym = plus;  /* 检测+符号 */
            }
            break;
        case '-':
            if (!getch()) return 0;
            if (ch == '-')  /* 检测--符号 */
            {
                sym = decsym;
                if (!getch()) return 0;
            }
            else
            {
                sym = minus;  /* 检测-符号 */
            }
            break;
        case '!':
            if (!getch()) return 0;
            if (ch == '=')  /* 检测!=符号 */
            {
                sym = neql;
                if (!getch()) return 0;
            }
            //else
            //{
            //	sym = incsym;  /*用！代替++*/
            //}
            break;
        default:
            sym = ssym[ch];
            if (!getch()) return 0;
        }
    }
    return 1;
}
