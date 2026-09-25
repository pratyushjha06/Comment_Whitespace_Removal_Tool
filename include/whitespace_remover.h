#ifndef WHITESPACE_REMOVER_H
#define WHITESPACE_REMOVER_H
#include <stdio.h>
#include "common.h"
int remove_unnecessary_whitespace(FILE *input, FILE *output, ProcessingStats *stats);
#endif
