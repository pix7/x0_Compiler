#ifndef GLOBAL_H
#define GLOBAL_H

#endif // GLOBAL_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_LEN_FILENAME        100        /* 文件名最大长度 */
#define MAX_LEN_IDENT           20         /* 标识符最大长度 */
#define MAX_NUM_LINE            100        /* 输入文件单行最大字符个数 */
#define MAX_LEN_INT				5          /* 整数最大位数 */
#define MAX_SIZE_TABLE          100        /* 符号表最大长度 */
#define MAX_SIZE_ADDRESS        2048        /* 地址上界 */
#define MAX_NUM_TYPE            4          /* 符号表类型数 */
#define MAX_NUM_CODE            500      /* 中间代码最大行数 */
#define MAX_SIZE_STACK          10000      /* 数据栈最大格数 */
#define MAX_NUM_BACKUP          100        /* 最大备份数 */
#define MAX_DIMENSION           10         /* 最大数组维度 */
#define MAX_LEN_RESERVE_WORD    10         /* 保留字最大长度 */
#define MAX_LEN_FCTCODE         10          /* 指令码最大长度 */
#define FCTCODE_NUM             7         /* 指令码个数 */
#define TERMINAL_SYM_NUM        34         /* 终结符个数 */
#define RESERVE_WORD_NUM        12         /* 保留字个数 */
#define MAX_ERROR_NUM   30  /*最大错误数*/


/* 终结符 */
/*
 *	其它符号, 标识符, main, int, char,
 *	if,else,while,read,write,
 *  +,-,*,/,(,
 *  ),[,],{,},
 *  ;,=,>,<,>=,
 *  <=,==,!=,num,%
 * odd,xor,++,--
 */
typedef enum symbol
{
    nul, ident, mainsym, intsym, charsym,
    ifsym, elsesym, whilesym, readsym, writesym,
    plus, minus, times, slash, lparen,
    rparen, lbracket, rbracket, lbrace, rbrace,
    semic, eql, great, less, greateql,
    lesseql, eqleql, neql, intnum, modsym,
    oddsym, xorsym, incsym, decsym,
    reptsym,untlsym
}Symbol;

/* 指令码 */
typedef enum fctCode
{
    lit, opr, lod, sto, ini, jmp, jpc
}FctCode;

/* 中间代码 */
typedef struct instruction
{
    FctCode fct; /* 指令 */
    int l; /* 引用层与声明层的层次差 */
    int a; /* 根据fct的不同而不同 */

}Instruction;

/* 数据类型 */
typedef enum dataType
{
    Nul, Int, Char
}DataType;


/* 符号表中的类型 */
typedef enum objectKind
{
    intVar, intArray,
    charVar, charArray
}ObjectKind;


/* 符号表结构 */
typedef struct tableObject
{
    char name[MAX_LEN_IDENT + 1];	/* 标识符名字 */
    ObjectKind kind;				/* 标识符类型 */
    int address;						/* 地址 */
    int size[MAX_DIMENSION];	    /* 存储空间 (此处用于记录数组每一维度大小) */
    int d;							/* 数组维度 */
    int value;					/* 层差 (没有实现调用所以都为0) */
}TableObject;

extern TableObject symTable[MAX_SIZE_TABLE];  /* 符号表 */
extern int tableSize;  /* 符号表大小 */
extern char dataTypeString[4][10];  /* 数据类型字符串 */

/* 词法分析状态备份 */
typedef struct backUp
{
    FILE* backupFin;
    Symbol backupSym;
    char backupCh;
    int backupcc;
    char backupLineCache[MAX_NUM_LINE];
    int backupll;
    int backupIntNum;
    char backupId[MAX_LEN_IDENT + 1];
    int backupIterCode;
}BackUp;

/* 文件读写变量 */
extern char fileName[MAX_LEN_FILENAME + 1];     /* 文件名 */
extern FILE* fin;                               /* 输入文件指针 */
extern FILE* fout;								/* 输出文件指针 */
extern FILE* finput;							/* 用户输入文件指针 */
extern FILE* fcode;								/* 中间代码文件文件指针 */
extern FILE* fstep;								/* 单步中间代码文件指针 */
extern FILE* ftable;							/* 符号表文件指针 */
extern FILE* fstack;							/* 数据栈文件指针 */
extern long finputpos;							/* 记录指针位置 */


/* 词法分析变量 */
extern Symbol sym;                               /* 当前被getsym()获取到的符号 */
extern char ch;                                  /* 当前被getch()获取到的字符 */
extern int cc;									 /* 行中要被读取的字符位置 */
extern int ll;									 /* 行字符个数 */
extern char lineCache[MAX_NUM_LINE];             /* 读取行缓冲区 */
extern char temp[MAX_LEN_IDENT + 1];			 /*  临时符号，存放标识符或保留字的名字，多出的一个字节用于存放0 */
extern char id[MAX_LEN_IDENT + 1];               /* 当前标识符名字 */
extern int intNum;                               /* 当前数字（整数） */
extern Symbol wsym[RESERVE_WORD_NUM];            /* 保留字对应的符号值 */
extern Symbol ssym[256];						 /* 单字符的符号值 */
extern BackUp backups[MAX_NUM_BACKUP];           /* 词法分析状态备份 */
extern int backUpNum;                            /* 备份数 */
extern char reserveWord[RESERVE_WORD_NUM][MAX_LEN_RESERVE_WORD];  /* 保留字 */

/* 语句处理变量 */
extern Instruction code[MAX_NUM_CODE];						/* 中间代码 */
extern int codeNum;                                         /* 中间代码行数 */
extern char fctCodeString[FCTCODE_NUM][MAX_LEN_FCTCODE];    /* 代码指令 */

/* 词法分析函数 */
int getch();		/* 获取字符 */
int getsym();		/* 获取符号 */
void backup();     /* 备份词法分析状态 */
void recover();    /* 恢复词法分析状态 */
void init();		/* 初始化单字符符号 */

/* 语句处理函数 */
int DeclarationList(int* ptr_address);
int DeclarationStat(int* ptr_address);
int StatementList();
int statement();
DataType type();
int IfStat();
int RepeatStat();
int WhileStat();
int ReadStat();
int WriteStat();
int CompoundStat();
int ExpressionStat();
int Var(ObjectKind* ptr_kind, int* ptr_address, int* ptr_IncOrDec);
int SimpleVar(ObjectKind* ptr_kind, int* ptr_address);
int expression();
int SimpleExpr();
int term();
int factor();
int AdditiveExpr();

/* 向符号表添加新的对象 */
void EnterTable(ObjectKind k, int address, int* size, int d, int val);

/* 按标识符名称查找符号表中标识符的位置  */
int FindPos(char* identName);

/* 按标识符address查找符号表中标识符的位置 */
int FindPos(int address);

extern int errornum;//错误数

/* 出错处理 */
void ErrorHandler(int error_code);

/* 生成中间代码 */
void Gen(FctCode fct, int l, int a);

/* 编译 */
int compile();

/* 解释并执行中间代码 */
void Interpret();
void InterpretStep();


/* 解释程序变量 */
extern int p;						/* 指令指针 */
extern int b;						/* 指令基址 */
extern int t;						/* 栈顶指针 */
extern int s[MAX_SIZE_STACK];		/* 数据栈 */
extern int outputType;			/* 记录栈顶元素类型以便输出 */




///* 获取输入*/
//void obtainInput();

//extern x0compiler *mymainwindow;
