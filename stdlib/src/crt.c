extern int main();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

/**
 * Actual entry point for each program linked with
 * the standard library.
 */
void _start() {
    main();
}

#pragma clang diagnostic pop
