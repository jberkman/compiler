#ifndef EMITTER_H
#define EMITTER_H

#include "compiler.h"

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

void emit(const compile_ctx_t *ctx, instr_t instr, const token_val_t *val);

#endif
