#include "whitespace_remover.h"
#include <ctype.h>
#include <stdio.h>
static int word(int c) { return isalnum((unsigned char)c) || c == '_'; }
int remove_unnecessary_whitespace(FILE *in, FILE *out, ProcessingStats *s)
{
    int c, prev = EOF, pending = 0, line_has = 0, at_start = 1, in_string = 0, in_char = 0, escaped = 0;
    while ((c = fgetc(in)) != EOF)
    {
        if (in_string || in_char)
        {
            fputc(c, out);
            line_has = 1;
            if (escaped)
                escaped = 0;
            else if (c == '\\')
                escaped = 1;
            else if ((in_string && c == '"') || (in_char && c == '\''))
            {
                in_string = 0;
                in_char = 0;
            }
            if (c == '\n')
            {
                at_start = 1;
                line_has = 0;
                prev = EOF;
            }
            else
            {
                at_start = 0;
                prev = c;
            }
            continue;
        }
        if (c == '"' || c == '\'')
        {
            if (pending && !at_start && word(prev) && word(c))
                fputc(' ', out);
            pending = 0;
            fputc(c, out);
            line_has = 1;
            at_start = 0;
            prev = c;
            if (c == '"')
                in_string = 1;
            else
                in_char = 1;
            continue;
        }
        if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f')
        {
            pending = 1;
            s->whitespace_characters_removed++;
            continue;
        }
        if (c == '\n')
        {
            pending = 0;
            if (!line_has)
            {
                s->blank_lines_removed++;
                at_start = 1;
                prev = EOF;
                continue;
            }
            fputc('\n', out);
            at_start = 1;
            line_has = 0;
            prev = EOF;
            continue;
        }
        if (pending)
        {
            if (!at_start && word(prev) && word(c))
                fputc(' ', out);
            pending = 0;
        }
        fputc(c, out);
        line_has = 1;
        at_start = 0;
        prev = c;
    }
    return !(in_string || in_char);
}
