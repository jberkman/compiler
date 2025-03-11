#include "compiler.h"

#define SYMMAX 100
#define STRMAX 999

static const entry_t keywords[] = {
    {"div", TOK_DIV},
    {"mod", TOK_MOD},
    {NULL, 0},
};

static entry_t symbols[SYMMAX] = {0};
static char lexemes[STRMAX] = {0};

void init(compiler_ctx_t *ctx) {
    ctx->lineno = 1;

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
