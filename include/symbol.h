#ifndef SYMBOL_H
#define SYMBOL_H

#include "compiler.h"

#include <string.h>

ssize_t lookup(const compile_ctx_t *ctx, const char *s);
size_t insert(compile_ctx_t *ctx, const char *s, token_t token);

#endif
