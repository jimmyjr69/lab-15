#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#include "libs/algorithms/array/array.h"
#include "libs/data_structures/ordered_set/ordered_set.h"
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/vector/vectorVoid.h"
#include "libs/data_structures/matrix/matrix.h"
#include "libs/algorithms/algorithm.h"
#include "libs/algorithms/for_dm/for_dm.h"
#include "libs/string_/string_.h"
#include "libs/data_structures/bitset/bitset.h"

#define SYMMDIFF(a, b) bitset_symmetricDifference(a, b)
#define COMPL(a) bitset_complement(bitset a)
#define DIFF(a, b) bitset_difference(a, b)
#define INTERSEC(a, b) bitset_intersection(a, b)
#define UNION(a, b) bitset_union(a, b)


int main() {
    bitset universum = {2046, 10};
    bitset a = {1672, 10};
    bitset b = {1802, 10};
    bitset c = {244, 10};
    bitset zero = {0, 10};

    bitset_print(universum);
    bitset_print(a);
    bitset_print(b);
    bitset_print(c);

    bitset st1 = DIFF(a, zero);
    bitset st2 = INTERSEC(b, zero);
    bitset st3 = SYMMDIFF(st1, st2);
    st1 = bitset_complement(DIFF(a, bitset_complement(zero)));
    st2 = SYMMDIFF(st1, DIFF(c, zero));
    st3 = SYMMDIFF(st3, st2);
    bitset fi_zero = st3;

    bitset_print(fi_zero);

    st1 = SYMMDIFF(DIFF(a, universum), INTERSEC(b, universum));
    st2 = SYMMDIFF(bitset_complement(DIFF(a, bitset_complement(universum))), DIFF(c, universum));
    st3 = SYMMDIFF(st1,st2);
    bitset fi_univ = st3;
    bitset_print(bitset_complement(fi_univ));

    return 0;
}