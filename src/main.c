#include <stdio.h>
#include <string.h>
#include "common.h"
#include "lexer.h"
#include "comment_remover.h"
#include "whitespace_remover.h"
#define PATH_SIZE 512
static void stats(const ProcessingStats *s) { printf("\n--- Statistics ---\nInput characters: %zu\nLines: %zu\nLine comments: %zu\nBlock comments: %zu\nBlank lines removed: %zu\nWhitespace characters reduced: %zu\n", s->input_characters, s->lines, s->line_comments_removed, s->block_comments_removed, s->blank_lines_removed, s->whitespace_characters_removed); }
static int process(const char *inpath, const char *outpath)
{
    FILE *in = fopen(inpath, "rb"), *tmp = NULL, *out = NULL;
    ProcessingStats s = {0};
    int ok;
    if (!in)
    {
        perror("Input file");
        return 0;
    }
    ok = lexer_validate_source(in, &s);
    if (!ok)
    {
        printf("Invalid input: unterminated string/character/block comment.\n");
        fclose(in);
        return 0;
    }
    tmp = tmpfile();
    if (!tmp)
    {
        fclose(in);
        return 0;
    }
    if (!remove_comments(in, tmp, &s))
    {
        printf("Comment removal failed.\n");
        fclose(in);
        fclose(tmp);
        return 0;
    }
    rewind(tmp);
    out = fopen(outpath, "wb");
    if (!out)
    {
        perror("Output file");
        fclose(in);
        fclose(tmp);
        return 0;
    }
    if (!remove_unnecessary_whitespace(tmp, out, &s))
    {
        printf("Whitespace processing failed.\n");
        fclose(in);
        fclose(tmp);
        fclose(out);
        return 0;
    }
    fclose(in);
    fclose(tmp);
    fclose(out);
    printf("\nSuccess!\nInput : %s\nOutput: %s\n", inpath, outpath);
    stats(&s);
    return 1;
}
int main(void)
{
    int ch;
    char in[PATH_SIZE], out[PATH_SIZE];
    for (;;)
    {
        printf("\n========================================\n COMMENT AND WHITESPACE REMOVAL TOOL\n Compiler Design PBL - C\n========================================\n1. Process sample input\n2. Process custom C file\n3. Exit\nChoice: ");
        if (scanf("%d", &ch) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }
        while (getchar() != '\n')
            ;
        if (ch == 1)
            process("input/sample.c", "output/cleaned.c");
        else if (ch == 2)
        {
            printf("Input file: ");
            if (!fgets(in, sizeof in, stdin))
                continue;
            printf("Output file: ");
            if (!fgets(out, sizeof out, stdin))
                continue;
            in[strcspn(in, "\r\n")] = 0;
            out[strcspn(out, "\r\n")] = 0;
            process(in, out);
        }
        else if (ch == 3)
            break;
        else
            printf("Invalid choice.\n");
    }
    return 0;
}
