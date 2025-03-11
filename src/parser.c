#include "compiler.h"

typedef struct {
    compiler_ctx_t *parent;
    token_t lookahead;
    token_val_t val;
} parse_ctx_t;

static void expr(parse_ctx_t *ctx);

static void match(parse_ctx_t *ctx, token_t t) {
    if (ctx->lookahead != t) {
        error(ctx->parent, "syntax error");
    }

    ctx->lookahead = lexan(ctx->parent, &ctx->val);
}

static void factor(parse_ctx_t *ctx) {
    switch (ctx->lookahead) {
    case '(':
        match(ctx, '(');
        expr(ctx);
        match(ctx, ')');
        break;

    case TOK_NUM:
        emit(ctx->parent, TOK_NUM, &ctx->val);
        match(ctx, TOK_NUM);
        break;

    case TOK_ID:
        emit(ctx->parent, TOK_ID, &ctx->val);
        match(ctx, TOK_ID);
        break;

    default:
        error(ctx->parent, "syntax error");
    }
}

static void term(parse_ctx_t *ctx) {
    factor(ctx);
    while (1) {
        switch (ctx->lookahead) {
        case '*':
        case '/':
        case TOK_DIV:
        case TOK_MOD: {
            token_t t = ctx->lookahead;
            match(ctx, ctx->lookahead);
            factor(ctx);
            emit(ctx->parent, t, NULL);
            continue;
        }

        default:
            return;
        }
    }
}

static void expr(parse_ctx_t *ctx) {
    term(ctx);
    while (1) {
        switch (ctx->lookahead) {
        case '+':
        case '-': {
            token_t t = ctx->lookahead;
            match(ctx, ctx->lookahead);
            term(ctx);
            emit(ctx->parent, t, NULL);
            continue;
        }

        default:
            return;
        }
    }
}

void parse(compiler_ctx_t *ctx) {
    parse_ctx_t pctx = {
        .parent = ctx,
    };
    pctx.lookahead = lexan(ctx, &pctx.val);

    while (pctx.lookahead != TOK_DONE) {
        expr(&pctx);
        match(&pctx, ';');
    }
}
