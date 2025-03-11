#ifndef COMPILER_H
#define COMPILER_H

#include <stdlib.h>

enum {
    TOK_255 = 0xff,
    
    TOK_ASSIGN,
    TOK_BEGIN,
    TOK_DIV,
    TOK_DO,
    TOK_DONE,
    TOK_END,
    TOK_ID,
    TOK_IF,
    TOK_MOD,
    TOK_NUM,
    TOK_THEN,
    TOK_WHILE,
};

typedef int token_t;

typedef union {
    int num_val;
    size_t id_val;
    size_t label_val;
} token_val_t;

typedef struct {
    int token;
    char *lexptr;
} entry_t;

#define CTX_BUFFER(n, t) \
    t *n; \
    size_t n##_max; \
    size_t n##_len

typedef struct {
    size_t lineno;
    size_t label_count;

    CTX_BUFFER(symbols, entry_t);
    CTX_BUFFER(lexemes, char);
} compile_ctx_t;

#undef CTX_BUFFER

#endif
