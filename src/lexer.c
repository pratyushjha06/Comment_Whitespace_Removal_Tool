#include "lexer.h"
#include <stdio.h>
int lexer_validate_source(FILE *input, ProcessingStats *stats)
{
    int c, next, escaped = 0;
    LexerState state = STATE_CODE;
    if (!input || !stats)
        return 0;
    while ((c = fgetc(input)) != EOF)
    {
        stats->input_characters++;
        if (c == '\n')
            stats->lines++;
        switch (state)
        {
        case STATE_CODE:
            if (c == '"')
            {
                state = STATE_STRING;
                escaped = 0;
            }
            else if (c == '\'')
            {
                state = STATE_CHARACTER;
                escaped = 0;
            }
            else if (c == '/')
            {
                next = fgetc(input);
                if (next == '/')
                {
                    state = STATE_LINE_COMMENT;
                    stats->line_comments_removed++;
                }
                else if (next == '*')
                {
                    state = STATE_BLOCK_COMMENT;
                    stats->block_comments_removed++;
                }
                else if (next != EOF)
                    ungetc(next, input);
            }
            break;
        case STATE_STRING:
            if (escaped)
                escaped = 0;
            else if (c == '\\')
                escaped = 1;
            else if (c == '"')
                state = STATE_CODE;
            break;
        case STATE_CHARACTER:
            if (escaped)
                escaped = 0;
            else if (c == '\\')
                escaped = 1;
            else if (c == '\'')
                state = STATE_CODE;
            break;
        case STATE_LINE_COMMENT:
            if (c == '\n')
                state = STATE_CODE;
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
            break;
        }
    }
    if (state == STATE_BLOCK_COMMENT)
        stats->unterminated_block_comment = 1;
    if (state == STATE_STRING)
        stats->unterminated_string = 1;
    if (state == STATE_CHARACTER)
        stats->unterminated_character = 1;
    rewind(input);
    return !(stats->unterminated_block_comment || stats->unterminated_string || stats->unterminated_character);
}
