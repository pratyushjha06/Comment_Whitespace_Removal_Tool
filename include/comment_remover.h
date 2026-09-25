#ifndef COMMENT_REMOVER_H
#define COMMENT_REMOVER_H
#include <stdio.h>
#include "common.h"
int remove_comments(FILE *input, FILE *output, ProcessingStats *stats);
#endif
