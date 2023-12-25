#include <stdio.h>

void callLogger(const char *funcName, const char *calleeName) {
    printf("[LOG PASS] \"%s\": CALL \"%s\"\n", funcName, calleeName);
}

void retLogger(const char *funcName) {
    printf("[LOG PASS] \"%s\": RET\n", funcName);
}

void nonPhiNodeLogger(const char *funcName, const char *opcodeName) {
    printf("[LOG PASS] \"%s\": RUN \"%s\"\n", funcName, opcodeName);
}
