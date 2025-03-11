#include "init.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    compile_ctx_t ctx;
    
    (void)argc;
    (void)argv;
    
    init(&ctx);
    parse(&ctx);
    return 0;
}
