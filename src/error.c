#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>

void error(const compile_ctx_t *ctx, const char *msg) {
    fprintf(stderr, "line %zu: error: %s\n", ctx->lineno, msg);
}
