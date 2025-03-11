#include "emitter.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"

#include <stdio.h>

typedef struct {
    compile_ctx_t *parent;
    token_t lookahead;
    value_t val;
} parse_ctx_t;

static void expr(parse_ctx_t *ctx);

static void match(parse_ctx_t *ctx, token_t t) {
    if (ctx->lookahead != t) {
        fprintf(stderr, "expected token %d (%c), got %d\n", t, t, ctx->lookahead);
        error(ctx->parent, "parser error");
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
        emit(ctx->parent, INSTR_PUSH, &ctx->val);
        match(ctx, TOK_NUM);
        break;

    case TOK_ID:
        emit(ctx->parent, INSTR_RVALUE, &ctx->val);
        match(ctx, TOK_ID);
        break;

    default:
        error(ctx->parent, "parser error");
    }
}

static void term(parse_ctx_t *ctx) {
    factor(ctx);
    while (1) {
        instr_t instr = -1;

        switch (ctx->lookahead) {
        case '*':
            instr = INSTR_MUL;
            break;

        case '/':
            instr = INSTR_FDIV;
            break;

        case TOK_DIV:
            instr = INSTR_DIV;
            break;

        case TOK_MOD:
            instr = INSTR_MOD;
            break;

        default:
            return;
        }

        match(ctx, ctx->lookahead);
        factor(ctx);
        emit(ctx->parent, instr, NULL);
    }
}

static void expr(parse_ctx_t *ctx) {
    term(ctx);
    while (1) {
        instr_t instr = -1;

        switch (ctx->lookahead) {
        case '+':
            instr = INSTR_ADD;
            break;
        case '-':
            instr = INSTR_SUB;
            break;

        default:
            return;
        }

        match(ctx, ctx->lookahead);
        term(ctx);
        emit(ctx->parent, instr, NULL);
    }
}

void stmt(parse_ctx_t *ctx) {
    switch (ctx->lookahead) {
    case TOK_ID:
        emit(ctx->parent, INSTR_LVALUE, &ctx->val);
        match(ctx, TOK_ID);
        match(ctx, TOK_ASSIGN);
        expr(ctx);
        emit(ctx->parent, INSTR_ASSIGN, NULL);
        return;

    case TOK_IF: {
        value_t out_val = {
            .size_t_val = ctx->parent->label_count++,
        };
        match(ctx, TOK_IF);
        expr(ctx);
        emit(ctx->parent, INSTR_GOFALSE, &out_val);
        match(ctx, TOK_THEN);
        stmt(ctx);
        emit(ctx->parent, INSTR_LABEL, &out_val);
        break;
    }

    case TOK_WHILE: {
        value_t test_val = {
            .size_t_val = ctx->parent->label_count++,
        };
        value_t out_val = {
            .size_t_val = ctx->parent->label_count++,
        };
        emit(ctx->parent, INSTR_LABEL, &test_val);
        match(ctx, TOK_WHILE);
        expr(ctx);
        emit(ctx->parent, INSTR_GOFALSE, &out_val);
        match(ctx, TOK_DO);
        stmt(ctx);
        emit(ctx->parent, INSTR_GOTO, &test_val);
        emit(ctx->parent, INSTR_LABEL, &out_val);
        break;
    }

    case TOK_BEGIN:
        match(ctx, TOK_BEGIN);
        while (ctx->lookahead != TOK_END) {
            stmt(ctx);
            if (ctx->lookahead != ';') {
                break;
            }
            match(ctx, ';');
        }
        match(ctx, TOK_END);
        break;

    default:
        break;
    }
}

void parse(compile_ctx_t *ctx) {
    parse_ctx_t pctx = {
        .parent = ctx,
    };
    pctx.lookahead = lexan(ctx, &pctx.val);

    while (pctx.lookahead != TOK_DONE) {
        stmt(&pctx);
        match(&pctx, ';');
    }
}
