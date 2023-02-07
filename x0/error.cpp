#include "global.h"

/* 出错处理 */
void ErrorHandler(int error_code)
{
    char errspace[81];
    memset(errspace, 32, sizeof(errspace));

    /* 记录出错位置 */
    if (cc - 2 >= 0)
    {
        errspace[cc - 2] = '\0';
    }
    else
    {
        errspace[0] = '\0';
    }

    printf("%s^", errspace);
    fprintf(fout, "%s^", errspace);

    switch (error_code)
    {
    case 1:
        printf("line is too long\n");
        fprintf(fout, "Error %d: line is too long\n", error_code);
        break;
    case 2:
        printf("comments doesn't have an end symbol!\n");
        fprintf(fout, "Error %d: comments doesn't have an end symbol!\n", error_code);
        break;
    case 3:
        printf("identifier is too long!\n");
        fprintf(fout, "Error %d: identifier is too long!\n", error_code);
        break;
    case 4:
        printf("number is too long(should less than 9)!\n");
        fprintf(fout, "Error %d: number is too long(should less than 9)!\n", error_code);
        break;
    case 5:
        printf("lack of '}' !\n");
        fprintf(fout, "Error %d: lack of '}' !\n", error_code);
        break;
    case 6:
        printf("lack of '{' !\n");
        fprintf(fout, "Error %d: lack of '{' !\n", error_code);
        break;
    case 7:
        printf("lack of 'main' !\n");
        fprintf(fout, "Error %d: lack of 'main' !\n", error_code);
        break;
    case 8:
        printf("lack of ';' !\n");
        fprintf(fout, "Error %d: lack of ';' !\n", error_code);
        break;
    case 9:
        printf("lack of ')' !\n");
        fprintf(fout, "Error %d: lack of ')' !\n", error_code);
        break;
    case 10:
        printf("syntax of factor error!\n");
        fprintf(fout, "Error %d:  syntax of factor error!\n", error_code);
        break;
    case 11:
        printf("the program is too long !\n");
        fprintf(fout, "Error %d: the program is too long !\n", error_code);
        break;
    case 12:
        printf("lack of '(' !\n");
        fprintf(fout, "Error %d: lack of '(' !\n", error_code);
        break;
    case 13:
        printf("lack of 'if' !\n");
        fprintf(fout, "Error %d: lack of 'if' !\n", error_code);
        break;
    case 14:
        printf("lack of 'while' !\n");
        fprintf(fout, "Error %d: lack of 'while' !\n", error_code);
        break;
    case 15:
        printf("incsym or decsym in read state!\n");
        fprintf(fout, "Error %d: incsym or decsym in read state!\n", error_code);
        break;
    case 16:
        printf("lack of 'read' !\n");
        fprintf(fout, "Error %d: lack of 'read' !\n", error_code);
        break;
    case 17:
        printf("lack of 'write' !\n");
        fprintf(fout, "Error %d: lack of 'write' !\n", error_code);
        break;
    case 18:
        printf("lack of ']'!\n");
        fprintf(fout, "Error %d: lack of ']'!\n", error_code);
        break;
    case 19:
        printf("lack of integer in definition of array !\n");
        fprintf(fout, "Error %d: lack of integer in definition of array !\n", error_code);
        break;
    case 20:
        printf("lack of identifier !\n");
        fprintf(fout, "Error %d: lack of identifier !\n", error_code);
        break;
    case 21:
        printf("fail declare identifier !\n");
        fprintf(fout, "Error %d: fail declare identifier!\n", error_code);
        break;
    case 22:
        printf("identifier isn't array !\n");
        fprintf(fout, "Error %d: identifier isn't array !\n", error_code);
        break;
    case 23:
        printf("subscript is out of bound !\n");
        fprintf(fout, "Error %d: subscript is out of bound !\n", error_code);
        break;
    case 24:
        printf("illegal operator!\n");
        fprintf(fout, "Error %d: illegal operator !\n", error_code);
        break;
    case 25:
        printf("illegal data type!\n");
        fprintf(fout, "Error %d: illegal data type!\n", error_code);
        break;
    case 26:
        printf("displacement address is too big!\n");
        fprintf(fout, "Error %d: displacement address is too big !\n", error_code);
        break;
        //case 28:
        //	printf ("illegal function code !\n");
        //	break;
    case 27:
        printf("lack of 'repeat' !\n");
        fprintf(fout, "Error %d: lack of 'repeat'!\n", error_code);
        break;
    case 28:
        printf("lack of 'until' !\n");
        fprintf(fout, "Error %d: lack of 'until'!\n", error_code);
        break;
    default:
        printf("illegal return ErrorHandler code !\n");
    }
    errornum++;
    if(errornum>MAX_ERROR_NUM){
        printf("error is too much!\n");
        fprintf(fout, "error is too much!\n");
        exit(1);
    }
    //exit (0);
    //return 0;
}
