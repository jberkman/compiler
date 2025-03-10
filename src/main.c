#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int lookahead;
} c_ctx;

static void error() {
    fprintf(stderr, "syntax error\n");
    exit(1);
}

static void match(c_ctx *ctx, int t) {
    if (ctx->lookahead == t) {
        ctx->lookahead = getchar();
    } else {
        error();
    }
}

static void term(c_ctx *ctx) {
    if (isdigit(ctx->lookahead)) {
        putchar(ctx->lookahead);
        match(ctx, ctx->lookahead);
    } else {
        error();
    }
}

static void expr(c_ctx *ctx) {
    term(ctx);
    while (1) {
        switch (ctx->lookahead) {
            case '+':
                match(ctx, '+');
                term(ctx);
                putchar('+');
                break;

            case '-':
                match(ctx, '-');
                term(ctx);
                putchar('-');
                break;

            default:
                return;
        }
    }
}

int main(int argc, char *argv[]) {
    c_ctx ctx = {0};
    ctx.lookahead = getchar();
    expr(&ctx);
    putchar('\n');
    return 0;
}
