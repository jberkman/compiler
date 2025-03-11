#include "init.h"
#include "symbol.h"

#define SYMMAX 100
#define STRMAX 999

static const entry_t keywords[] = {
    {TOK_ASSIGN, ":="},
    {TOK_BEGIN, "begin"},
    {TOK_DIV, "div"},
    {TOK_DO, "do"},
    {TOK_END, "end"},
    {TOK_IF, "if"},
    {TOK_MOD, "mod"},
    {TOK_THEN, "then"},
    {TOK_WHILE, "while"},
    {.lexptr = NULL},
};

static entry_t symbols[SYMMAX] = {0};
static char lexemes[STRMAX] = {0};

void init(compile_ctx_t *ctx) {
    ctx->lineno = 1;
    ctx->label_count = 0;

    ctx->symbols = symbols;
    ctx->symbols_max = SYMMAX;
    ctx->symbols_len = 0;

    ctx->lexemes = lexemes;
    ctx->lexemes_max = STRMAX;
    ctx->lexemes_len = 0;

    for (const entry_t *kw = keywords; kw->lexptr; ++kw) {
        insert(ctx, kw->lexptr, kw->token);
    }
}
