#ifndef COMMON_H
#define COMMON_H
#include <stddef.h>
typedef enum { STATE_CODE, STATE_STRING, STATE_CHARACTER, STATE_LINE_COMMENT, STATE_BLOCK_COMMENT } LexerState;
typedef struct { size_t input_characters, lines, line_comments_removed, block_comments_removed, blank_lines_removed, whitespace_characters_removed; int unterminated_block_comment, unterminated_string, unterminated_character; } ProcessingStats;
#endif
