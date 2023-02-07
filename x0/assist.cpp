#include "global.h"

//backup()
//recover()
//enterTable()
//findPos()

// 备份词法分析状态
void backup()
{
    backups[backUpNum].backupFin = fin;
    backups[backUpNum].backupSym = sym;
    backups[backUpNum].backupCh = ch;
    backups[backUpNum].backupcc = cc;
    backups[backUpNum].backupll = ll;
    backups[backUpNum].backupIntNum = intNum;
    backups[backUpNum].backupIterCode = codeNum;
    strcpy(backups[backUpNum].backupId, id);

    for (int i = 0; i < MAX_NUM_LINE; i++)
    {
        backups[backUpNum].backupLineCache[i] = lineCache[i];
    }

    backUpNum++;
}

// 恢复词法分析状态
void recover()
{
    backUpNum--;
    fin = backups[backUpNum].backupFin;
    sym = backups[backUpNum].backupSym;
    ch = backups[backUpNum].backupCh;
    cc = backups[backUpNum].backupcc;
    ll = backups[backUpNum].backupll;
    intNum = backups[backUpNum].backupIntNum;
    codeNum = backups[backUpNum].backupIterCode;
    strcpy(id, backups[backUpNum].backupId);

    for (int i = 0; i < MAX_NUM_LINE; i++)
    {
        lineCache[i] = backups[backUpNum].backupLineCache[i];
    }
}

// 向符号表添加新的对象
void EnterTable(ObjectKind k, int address, int* size, int d, int val)
{
    int& tSize = tableSize;
    TableObject(&table)[MAX_SIZE_TABLE] = symTable;

    strcpy(table[tSize].name, id);
    table[tSize].kind = k;
    table[tSize].address = address;
    for (int i = 0; i < d; i++)
    {
        table[tSize].size[i] = size[i];
    }
    table[tSize].d = d;
    table[tSize].value = val;
    tableSize++;
}

// 根据标识符地址查找符号表中标识符的位置
int FindPos(char* idName)
{
    for (int i = 0; i < tableSize; i++)
    {
        if (strcmp(symTable[i].name, idName) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 根据标识符名字查找标识符在符号表中的位置
int FindPos(int adr)
{
    for (int i = 0; i < tableSize; i++)
    {
        if (symTable[i].address == adr)
        {
            return i;
        }
    }
    return -1;
}


