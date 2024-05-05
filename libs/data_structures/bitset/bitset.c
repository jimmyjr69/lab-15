//
//
//
#include "bitset.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

bitset bitset_create(unsigned maxValue) {
    assert (maxValue < 32);
    return (bitset) {0, maxValue};
}

bool bitset_in(bitset set, unsigned int value) {
    return value <= set.maxValue && set.values & (1 << value);
}

bool bitset_isEqual(bitset set1, bitset set2) {
    return set1.values == set2.values && set1.maxValue == set2.maxValue;
}

bool bitset_isSubset(bitset subset, bitset set) {
    if (subset.values <= set.values && subset.maxValue <= set.maxValue) {
        for (int i = 0; i <= subset.maxValue; i++)
            if (bitset_in(subset, i) && !bitset_in(set, i))
                return false;
        return true;
    } else
        return false;
}

void bitset_insert(bitset *set, unsigned int value) {
    assert(value <= set->maxValue);
    set->values |= (1 << value);
}

void bitset_deleteElement(bitset *set, unsigned int value) {
    if (bitset_in(*set, value))
        set->values &= ~(1 << value);
}

bitset bitset_union(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values | set2.values, set1.maxValue};
}

bitset bitset_intersection(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & set2.values, set1.maxValue};
}

bitset bitset_difference(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & ~set2.values, set1.maxValue};
}

bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values ^ set2.values, set1.maxValue};
}

bitset bitset_complement(bitset set) {
    return (bitset) {~set.values, set.maxValue};
}

void bitset_print(bitset set) {
    printf("{");
    int is_empty = true;

    for (int i = 0; i <= set.maxValue; i++) {
        if (bitset_in(set, i)) {
            printf("%d, ", i);
            is_empty = false;
        }
    }

    if (is_empty) {
        printf("}\n");
    } else {
        printf("\b\b}\n");
    }
}