#include "compiler.h"

#include <stdio.h>

void emit(const compiler_ctx_t *ctx, token_t token, const token_val_t *val) {
    switch (token) {
        case '+':
        case '-':
        case '*':
        case '/':
            printf("%c\n", token);
            break;
        
        case TOK_DIV:
            printf("DIV\n");
            break;

        case TOK_MOD:
            printf("MOD\n");
            break;

        case TOK_NUM:
            printf("%d\n", val->num_val);
            break;

        case TOK_ID:
            printf("%s\n", ctx->symbols[val->id_val].lexptr);
            break;

        default:
            printf("token %d, tokenval %d\n", token, val->num_val);
            break;
    }
}
