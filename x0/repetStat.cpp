#include "global.h"

// RepeatStat 语句处理
//repeat="repeat" "{" statementlist "}" "until" "(" expression ")"";"

int RepeatStat()
{

    if (sym == reptsym)
    {
        if (!getsym()) return 0;
        if (sym == lbrace)
        {
            if (!getsym()) return 0;
            int pos = codeNum; //回填
            StatementList();


            if (sym == rbrace) //'}'
            {
                if (!getsym()) return 0;
                if (sym == untlsym) //"until"
                {
                    if (!getsym()) return 0;
                    if (sym == lparen)
                    {
                        if (!getsym()) return 0;
                        if (!expression()) return 0;
                        Gen(jpc, 0, pos);
                        if (sym == rparen)
                        {
                            if (!getsym()) return 0;
                            if (sym == semic)
                            {
                                if (!getsym()) return 0;
                            }
                            else /* the lack of ';' */
                            {
                                ErrorHandler(8);
                            }
                        }
                        else /* the lack of ')' */
                        {
                             ErrorHandler(9);
                        }
                    }
                    else /* the lack of '(' */
                    {
                          ErrorHandler(12);
                    }
                }
                else /* the lack of 'until' */
                {
                     ErrorHandler(28);
                }
            }
            else /* the lack of '}' */
            {
                  ErrorHandler(5);
            }
        }
        else /* the lack of '{' */
        {
              ErrorHandler(6);
        }
    }
    else /* the lack of 'repeat' */
    {
          ErrorHandler(27);
    }
    return 1;
}
