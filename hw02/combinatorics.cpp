#include "combinatorics.h"

int64_t factorial(int64_t val) {
    // TODO
    // if (val < 0) return 0;
    if (val == 0) return 1;
    return val * factorial(val-1);
}


int64_t permutation(int64_t val, int64_t val2) {
    // TODO
    // if (val < val2) return 0;
    return factorial(val)/ factorial(val-val2);
}


int64_t combination(int64_t val, int64_t val2) {
    // TODO
    // if (val < val2) return 0;
    return permutation(val,val2) / factorial(val2);
}