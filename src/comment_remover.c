#include "comment_remover.h"
#include <stdio.h>
int remove_comments(FILE *input, FILE *output, ProcessingStats *stats)
{
    int c, next, escaped = 0;
    LexerState state = STATE_CODE;
    if (!input || !output || !stats)
        return 0;
    while ((c = fgetc(input)) != EOF)
    {
        switch (state)
        {
        case STATE_CODE:
            if (c == '"')
            {
                fputc(c, output);
                state = STATE_STRING;
                escaped = 0;
            }
            else if (c == '\'')
            {
                fputc(c, output);
                state = STATE_CHARACTER;
                escaped = 0;
            }
            else if (c == '/')
            {
                next = fgetc(input);
                if (next == '/')
                {
                    state = STATE_LINE_COMMENT;
                }
                else if (next == '*')
                {
                    state = STATE_BLOCK_COMMENT;
                }
                else
                {
                    fputc(c, output);
                    if (next != EOF)
                        ungetc(next, input);
                }
            }
            else
                fputc(c, output);
            break;
        case STATE_STRING:
            fputc(c, output);
            if (escaped)
                escaped = 0;
            else if (c == '\\')
                escaped = 1;
            else if (c == '"')
                state = STATE_CODE;
            break;
        case STATE_CHARACTER:
            fputc(c, output);
            if (escaped)
                escaped = 0;
            else if (c == '\\')
                escaped = 1;
            else if (c == '\'')
                state = STATE_CODE;
            break;
        case STATE_LINE_COMMENT:
            if (c == '\n')
            {
                fputc('\n', output);
                state = STATE_CODE;
            }
            break;
        case STATE_BLOCK_COMMENT:
            if (c == '*')
            {
                next = fgetc(input);
                if (next == '/')
                    state = STATE_CODE;
                else if (next != EOF)
                    ungetc(next, input);
            }
            else if (c == '\n')
                fputc('\n', output);
            break;
        }
    }
    return state == STATE_CODE;
}
