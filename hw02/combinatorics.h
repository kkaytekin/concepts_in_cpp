#pragma once

#include <cstdint>

/**
 * computes the factorial.
 */
int64_t factorial(int64_t val);

/**
 * Return the number of ways to choose k items from n items
 * without repetition and with order.
 */
int64_t permutation(int64_t val, int64_t val2);

/**
 * Return the number of ways to choose k items from n items
 * without repetition and without order.
 */
int64_t combination(int64_t val, int64_t val2);
