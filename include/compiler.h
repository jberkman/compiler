#ifndef COMPILER_H
#define COMPILER_H

#include <string.h>

enum {
    TOK_NUM = 0x100,
    TOK_DIV,
    TOK_MOD,
    TOK_ID,
    TOK_DONE,
};

typedef int token_t;

typedef union {
    int num_val;
    size_t id_val;
} token_val_t;

typedef struct {
    char *lexptr;
    int token;
} entry_t;

#define CTX_BUFFER(n, t) \
    t *n; \
    size_t n##_max; \
    size_t n##_len

typedef struct {
    size_t lineno;

    CTX_BUFFER(symbols, entry_t);
    CTX_BUFFER(lexemes, char);
} compiler_ctx_t;

#undef CTX_BUFFER

void init(compiler_ctx_t *ctx);

void emit(const compiler_ctx_t *ctx, token_t token, const token_val_t *val);

ssize_t lookup(const compiler_ctx_t *ctx, const char *s);
size_t insert(compiler_ctx_t *ctx, const char *s, token_t token);

token_t lexan(compiler_ctx_t *ctx, token_val_t *val);

void parse(compiler_ctx_t *ctx);

void error(const compiler_ctx_t *ctx, const char *msg);

#endif
