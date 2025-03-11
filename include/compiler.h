#ifndef COMPILER_H
#define COMPILER_H

#include <string.h>

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

typedef enum {
    INSTR_HALT,
    
    INSTR_ADD,
    INSTR_ASSIGN,
    INSTR_COPY,
    INSTR_DIV,
    INSTR_FDIV,
    INSTR_GOFALSE,
    INSTR_GOTO,
    INSTR_GOTRUE,
    INSTR_LABEL,
    INSTR_LVALUE,
    INSTR_MOD,
    INSTR_MUL,
    INSTR_POP,
    INSTR_PUSH,
    INSTR_RVALUE,
    INSTR_SUB,
} instr_t;

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

void init(compile_ctx_t *ctx);

void emit(const compile_ctx_t *ctx, instr_t instr, const token_val_t *val);

ssize_t lookup(const compile_ctx_t *ctx, const char *s);
size_t insert(compile_ctx_t *ctx, const char *s, token_t token);

token_t lexan(compile_ctx_t *ctx, token_val_t *val);

void parse(compile_ctx_t *ctx);

void error(const compile_ctx_t *ctx, const char *msg);

#endif
