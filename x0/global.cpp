#include "global.h"


/* 数据类型 */
char dataTypeString[MAX_NUM_TYPE][10] = { "int","intArr","char","charArr" };

/* 保留字 */
char reserveWord[RESERVE_WORD_NUM][MAX_LEN_RESERVE_WORD] = { "char", "else", "if", "int","main",
                                                             "odd", "read","repeat", "until","while", "write", "xor" };


/* 代码指令 */
char fctCodeString[FCTCODE_NUM][MAX_LEN_FCTCODE] = { "lit", "opr", "lod", "sto", "ini", "jmp", "jpc" };


/* 保留字对应的符号值 */
Symbol wsym[RESERVE_WORD_NUM] = { charsym, elsesym, ifsym, intsym, mainsym,
                                  oddsym, readsym,reptsym,untlsym, whilesym, writesym, xorsym };

Symbol ssym[256];



/* 符号表变量 */
TableObject symTable[MAX_SIZE_TABLE];    /* 符号表*/
int tableSize;							 /* 符号表大小 */

/* 文件操作用变量 */
char fileName[MAX_LEN_FILENAME + 1];     /* 文件名*/
FILE* fin;                               /* 输入文件指针 */
FILE* fout;								 /* 输出文件指针 */
FILE* finput;							 /* 用户输入文件指针 */
FILE* fcode;							 /* 中间代码文件文件指针 */
FILE* fstep;							 /* 单步中间代码文件指针 */
FILE* ftable;							 /* 符号表文件指针 */
FILE* fstack;							 /* 数据栈文件指针 */
long finputpos = 0;						 /* 记录指针位置 */

/* 词法分析变量 */
BackUp backups[MAX_NUM_BACKUP];		     /* 词法分析状态备份 */
int backUpNum = 0;                       /* 备份数 */
Symbol sym;                              /* 当前获取到的符号 */
char ch = ' ';                           /* 当前获取到的字符 */
int cc;									 /* 行中要被读取的字符位置 */
char lineCache[MAX_NUM_LINE];            /* 读取行缓冲区 */
char temp[MAX_LEN_IDENT + 1];			 /*  临时符号，存放标识符或保留字的名字，多出的一个字节用于存放0 */
int ll;									 /* 行字符个数 */
int intNum;                              /* 当前数字 */
char id[MAX_LEN_IDENT + 1];              /* 当前标识符名字 */



/* 语句处理变量 */
Instruction code[MAX_NUM_CODE];						      /* 中间代码 */
int codeNum = 0;										  /* 中间代码行数 */

int p = 0;						/* 指令指针 */
int b = 1;						/* 指令基址 */
int t = 0;						/* 栈顶指针 */
int s[MAX_SIZE_STACK];			/* 数据栈 */
int outputType = Int;			/* 记录栈顶元素类型以便输出 */

/*错误数*/
int errornum=0;



void init()
{
    /* 初始化全局变量 */
    codeNum = 0;
    ch = ' ';
    cc = 0;
    ll = 0;
    tableSize = 0;
    backUpNum = 0;
    p = 0;						/* 指令指针 */
    b = 1;						/* 指令基址 */
    t = 0;						/* 栈顶指针 */
    memset(s, 0, sizeof(s));
    finputpos = 0;
    outputType = Int;			/* 记录栈顶元素类型以便输出 */

    /* 初始化单字符符号 */
    for (int i = 0; i <= 255; i++)
    {
        ssym[i] = nul;
    }
    ssym['+'] = plus;
    ssym['-'] = minus;
    ssym['*'] = times;
    ssym['/'] = slash;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['['] = lbracket;
    ssym[']'] = rbracket;
    ssym['{'] = lbrace;
    ssym['}'] = rbrace;
    ssym['='] = eql;
    ssym[';'] = semic;
    ssym['%'] = modsym;
}
