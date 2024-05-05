//
//
//
#include <assert.h>
#include <stdbool.h>
#include <malloc.h>
#include "../../algorithms/array/array.h"
#include "ordered_set.h"

static void ordered_array_set_shrinkToFit(ordered_array_set *a) {
    if (a->size < a->capacity / 4) {
        a->data = (int*)realloc(a->data, sizeof(int)*a->capacity / 2);
        a->capacity /= 2;
    }
}

static void ordered_array_set_give_more_memory(ordered_array_set *a){
    if (a->size == a->capacity){
        a->data = (int*)realloc(a->data, sizeof(int)*a->capacity * 2);
        a->capacity *= 2;
    }
}

ordered_array_set ordered_array_set_create(size_t capacity) {
    return (ordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    ordered_array_set result = ordered_array_set_create(size);

    for (size_t i = 0; i < size; i++) {
        ordered_array_set_insert(&result, a[i]);
    }

    return result;
}

size_t ordered_array_set_in(ordered_array_set *set, int value) {
    size_t x = binarySearch_(set->data, set->size, value);
    return x != SIZE_MAX ? x : set->size;
}

bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }
    return !memcmp(set1.data, set2.data, set1.size * sizeof(int));
}

bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set) {
    if (subset.size > set.size)
        return false;
    int counter = 0;
    size_t read_subset = 0;
    size_t read_set = 0;

    while (read_subset < subset.size && read_set < set.size){
        if (subset.data[read_subset] == set.data[read_set]){
            read_subset++;
            read_set++;
            counter++;
        } else if (subset.data[read_subset] < set.data[read_set])
            read_subset++;
        else if (subset.data[read_subset] > set.data[read_set])
            read_set++;
    }
    return counter == subset.size;
}

void ordered_array_set_isAbleAppend(ordered_array_set *set) {
    assert(set->size < set->capacity);
}

void ordered_array_set_insert(ordered_array_set *set, int value) {
    if (ordered_array_set_in(set, value) == set->size) {
        ordered_array_set_give_more_memory(set);
        ordered_array_set_isAbleAppend(set);
        insert_(set->data, &set->size, binarySearchMoreOrEqual_(set->data, set->size, value), value);

    }
}

void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    size_t index = ordered_array_set_in(set, value);
    if (index != set->size)
        deleteByPosSaveOrder_(set->data, &set->size, index);
}

ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.size + set2.size);
    int read_set1 = 0;
    int read_set2 = 0;
    while (!(read_set1 >= set1.size && read_set2 >= set2.size)){
        if ((set1.data[read_set1] < set2.data[read_set2] || read_set2 == set2.size) && read_set1 < set1.size)
            result.data[result.size++] = set1.data[read_set1++];
        else if ((set1.data[read_set1] > set2.data[read_set2] || read_set1 == set1.size) && read_set2 < set2.size)
            result.data[result.size++] = set2.data[read_set2++];
        else if (set1.data[read_set1] == set2.data[read_set2]){
            result.data[result.size++] = set1.data[read_set1++];
            read_set2++;
        }
    }
    return result;
}

ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    size_t size = set1.size < set2.size ? set1.size : set2.size;
    ordered_array_set result = ordered_array_set_create(size);

    for (size_t i = 0; i < size; i++) {
        if (ordered_array_set_in(&set2, set1.data[i]) != set2.size) {
            ordered_array_set_insert(&result, set1.data[i]);
        }
    }

    ordered_array_set_shrinkToFit(&result);

    return result;
}

ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result = ordered_array_set_create(set1.size);

    for (size_t i = 0; i < set1.size; i++) {
        if (ordered_array_set_in(&set2, set1.data[i]) == set2.size) {
            ordered_array_set_insert(&result, set1.data[i]);
        }
    }

    ordered_array_set_shrinkToFit(&result);

    return result;
}

ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set difference1 = ordered_array_set_difference(set1, set2);
    ordered_array_set_print(difference1);
    ordered_array_set difference2 = ordered_array_set_difference(set2, set1);
    ordered_array_set_print(difference2);
    ordered_array_set result = ordered_array_set_union(difference1, difference2);
    ordered_array_set_delete(&difference1);
    ordered_array_set_delete(&difference2);
    return result;
}

ordered_array_set unordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet) {
    ordered_array_set result = ordered_array_set_create(universumSet.size);

    for (size_t i = 0; i < universumSet.size; i++) {
        if (ordered_array_set_in(&set, universumSet.data[i]) == set.size) {
            ordered_array_set_insert(&result, universumSet.data[i]);
        }
    }

    ordered_array_set_shrinkToFit(&result);

    return result;
}

void ordered_array_set_print(ordered_array_set set) {
    outputArray_(set.data, set.size);
}

void ordered_array_set_delete(ordered_array_set *set) {
    free(set->data);
    set->size = 0;
    set->capacity = 0;
}