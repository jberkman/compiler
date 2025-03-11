#include "emitter.h"
#include "error.h"

#include <stdio.h>

void emit(const compile_ctx_t *ctx, instr_t instr, const token_val_t *val) {
    switch (instr) {
    case INSTR_HALT:
        printf("halt\n");
        break;
    
    case INSTR_ADD:
        printf("+\n");
        break;

    case INSTR_ASSIGN:
        printf(":=\n");
        break;

    case INSTR_COPY:
        printf("copy\n");
        break;

    case INSTR_DIV:
        printf("div\n");
        break;

    case INSTR_FDIV:
        printf("/\n");
        break;

    case INSTR_GOFALSE:
        printf("gofalse label_%zu\n", val->label_val);
        break;

    case INSTR_GOTO:
        printf("goto label_%zu\n", val->label_val);
        break;

    case INSTR_GOTRUE:
        printf("gotrue label_%zu\n", val->label_val);
        break;

    case INSTR_LABEL:
        printf("label label_%zu\n", val->label_val);
        break;

    case INSTR_LVALUE:
        printf("lvalue %s\n", ctx->symbols[val->id_val].lexptr);
        break;

    case INSTR_MOD:
        printf("mod\n");
        break;

    case INSTR_MUL:
        printf("*\n");
        break;

    case INSTR_POP:
        printf("pop\n");
        break;

    case INSTR_PUSH:
        printf("push %d\n", val->num_val);
        break;

    case INSTR_RVALUE:
        printf("rvalue %s\n", ctx->symbols[val->id_val].lexptr);
        break;

    case INSTR_SUB:
        printf("-\n");
        break;

    default:
        error(ctx, "invalid instruction");
    }
}
