#include "error.h"
#include "symbol.h"

#include <stdio.h>

ssize_t lookup(const compile_ctx_t *ctx, const char *s) {
    for (size_t i = 0; i < ctx->symbols_len; ++i) {
        if (strcmp(ctx->symbols[i].lexptr, s) == 0) {
            return i;
        }
    }

    return -1;
}

size_t insert(compile_ctx_t *ctx, const char *s, token_t token) {
    if (ctx->symbols_len + 1 >= ctx->symbols_max) {
        error(ctx, "symbol table full");
    }
    
    size_t len = strlen(s);
    if (ctx->lexemes_len + len + 1 >= ctx->lexemes_max) {
        error(ctx, "lexemes buffer full");
    }

    ctx->symbols[ctx->symbols_len].token = token;
    ctx->symbols[ctx->symbols_len].lexptr = &ctx->lexemes[ctx->lexemes_len];
    strcpy(ctx->symbols[ctx->symbols_len].lexptr, s);
    ctx->lexemes_len += len + 1;
    return ctx->symbols_len++;
}
