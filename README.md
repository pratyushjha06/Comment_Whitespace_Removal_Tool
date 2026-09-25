# Comment and Whitespace Removal Tool

Compiler Design PBL — C

## What it does
Removes `//` and `/* ... */` comments and unnecessary spaces/tabs/blank lines from C source code. It uses lexical states so comment-like text inside strings and character literals is preserved.

## States
`CODE`, `STRING`, `CHARACTER`, `LINE_COMMENT`, `BLOCK_COMMENT`

## Requirements
GCC with C11 support.

Check:
```bash
gcc --version
```

## Compile
Linux/macOS:
```bash
gcc -std=c11 -Wall -Wextra -pedantic -Iinclude src/main.c src/lexer.c src/comment_remover.c src/whitespace_remover.c -o comment_tool
```
Windows:
```bash
gcc -std=c11 -Wall -Wextra -pedantic -Iinclude src/main.c src/lexer.c src/comment_remover.c src/whitespace_remover.c -o comment_tool.exe
```

Or use:
```bash
make
```

## Run
```bash
./comment_tool
```
Windows:
```bash
comment_tool.exe
```

Select `1` for `input/sample.c`, or `2` to provide your own input/output paths.

## Example
Input:
```c
int x    =    10; // comment
printf("Hello // World");
```
Output:
```c
int x = 10;
printf("Hello // World");
```


## Important viva point
This is not simple string replacement. The tool performs character-level lexical/state processing to distinguish normal code, strings, character literals, line comments and block comments.

## Limitations
It is a preprocessing/cleaning tool, not a full C compiler. It does not build an AST or validate the complete C grammar.
