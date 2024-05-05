//
//
//
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>


#ifndef LAB_ALG_H
#define LAB_ALG_H

int test123();

typedef struct subset_line{
    char *line;
    int num_operators;
} subset_line;

typedef struct PNFK{
    int *arr_constituent;
    int size_arr_c;
} PNFK;

typedef struct set_theoretic_method_result{
    int *result_arr_TMP;
    int size_res_arr;
} set_theoretic_method_result;

typedef struct set{
    subset_line term;
    PNFK perfect_form;
    set_theoretic_method_result result_STM;
} set;

bool changeBool(bool a);

#endif //LAB_ALG_H
