#include "stdio.h"

typedef unsigned long long ULL;

ULL message = 0b10100100;

int hammingErrorIdx(ULL code) {
    ULL errorPos = 0;
    int idx = 0;
    ULL mask = 0b1;
    int parity = 0;     // First bit is an overall parity check
    do {
        if (code & mask) {
            errorPos ^= idx;
            parity = !parity;
        }
        mask <<= 1;
        idx++;
    } while (mask >> 1 <= code);

    if (errorPos == 0 && parity == 0) return 0; // Zero means no error
    if (errorPos != 0 && parity == 0) return -1; // -1 means unkown error
    return errorPos + 1; // positive number n means error in nth bit (1-indexed)
}

int main() {
    int error = hammingErrorIdx(message);
    if (error == 0) return printf("No error.\n");
    if (error == -1) return printf("Error found. Cannot correct.\n");
    printf("Error found in %d-th bit. Corrected to: %llu\n", error, message ^ (error-1));
}

