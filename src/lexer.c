#include "compiler.h"

#include <ctype.h>
#include <stdio.h>

#define ID_LEN_MAX 128

int lexan(compile_ctx_t *ctx, token_val_t *val) {
    memset(val, 0, sizeof(*val));
    do {
        int t = getchar();
        switch (t) {
        case ' ':
        case '\t':
            break;

        case '\n':
            ++ctx->lineno;
            break;

        case EOF:
            return TOK_DONE;

        case ':':
            if ((t = getchar()) == '=') {
                return TOK_ASSIGN;
            }
            ungetc(t, stdin);
            return ':';

        default:
            if (isdigit(t)) {
                ungetc(t, stdin);
                scanf("%d", &val->num_val);
                return TOK_NUM;
            
            } else if (isalpha(t)) {
                char symbol_name[ID_LEN_MAX] = {0};
                size_t i = 0;
                while (isalnum(t)) {
                    symbol_name[i] = t;
                    if (++i >= ID_LEN_MAX) {
                        error(ctx, "lexer error");
                    }
                    t = getchar();
                }
                if (t != EOF) {
                    ungetc(t, stdin);
                }
                ssize_t idx = lookup(ctx, symbol_name);
                if (idx < 0) {
                    val->id_val = insert(ctx, symbol_name, TOK_ID);
                } else {
                    val->id_val = idx;
                }
                return ctx->symbols[val->id_val].token;
            }

            return t;
        }
    } while (1);
}
