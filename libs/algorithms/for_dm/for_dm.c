//
//
//
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "for_dm.h"
#include "../array/array.h"

bool changeBool(bool a){
    return a ? 0 : 1;
}

bool dif(bool a, bool b){
    if (a - b == true) return true;
    return false;
}

bool un(bool a, bool b){
    return a | b;
}

bool intersec(bool a, bool b){
    return a & b;
}

bool sim_dif(bool a, bool b){
    return a ^ b;
}

bool get_condition_subset(int num_c, char lit){
    return num_c & (1 << ((int)lit - 65));
}

void ungettok(int op, const char **p)
{
    (*p)--;
}

void skipwhite(const char **p)
{
    while(isspace(**p))
        (*p)++;
}

int gettok(const char **p, int num_c, bool *vp)
{
    skipwhite(p);
    //printf("%c %d\n", **p, **p);
    char c = **p;
    if(isalpha(c)) {
        int v = get_condition_subset(num_c, c);
        if(vp) *vp = v;
        (*p)++;
        return '1';
    }
    (*p)++;
    return c;
}

bool evalpri(const char **p, int );

bool evalterm(const char **p, int num_c){
    //printf("in 3\n");
    bool r = evalpri(p, num_c);
    while(1) {
        int op = gettok(p, num_c, NULL);
        if (op == '&') r = intersec(r, evalpri(p, num_c));
        else {ungettok(op, p); return r;}
    }
}

bool evalexpr(const char **p, int num_c){
    bool r = evalterm(p, num_c);
    while(1) {
        int op = gettok(p, num_c, NULL);
        switch(op) {
            case '|': r = un(r, evalterm(p, num_c)); break;
            case '-': r = dif(r, evalterm(p, num_c)); break;
            case '^': r = sim_dif(r, evalterm(p, num_c)); break;
            default: ungettok(op, p); return r;
        }
    }
}

bool evalpri(const char **p, int num_c){
    bool v;
    int op = gettok(p, num_c, &v);
    switch(op) {
        case '1': return v;
        case '~': return changeBool(evalpri(p, num_c));
        case '(':
            v = evalexpr(p, num_c);
            op = gettok(p, num_c, NULL);
            if(op != ')') {
                fprintf(stderr, "missing ')'\n");
                ungettok(op, p);
            }
            return v;
    }
}

/*int eval(const char *expr)
{
    return evalexpr(&expr);
}*/

bool is_constituent_in_PNFK(const char *expr, int num_c){
    return evalexpr(&expr, num_c);
}

subset_line input_subset_line(int amount_subset){
    char *line = (char*)malloc(sizeof(char) * 100);
    printf("Enter expression: ");
    assert(fgets(line, sizeof(char) * 100, stdin) != NULL);
    puts(line);
    return (subset_line){line, amount_subset};
}

PNFK get_arr_num_constituents(subset_line subset){
    int max_size = pow(2, subset.num_operators);
    int *arr = malloc(sizeof(int) * subset.num_operators);
    int size = 0;
    for(int i = 0; i < max_size; i++){
        if(is_constituent_in_PNFK(subset.line, i)){
            //printf("%d\n", i);
            arr[size] = i;
            size++;
        }
    }
    //printf("%d\n", arr[0]);
    arr = (int*)realloc(arr, sizeof(int) * size);

    return (PNFK){arr, size};
}

int test123()
{
    while(1) {
        subset_line subset = input_subset_line(3);
        puts(subset.line);
        PNFK perfect_form = get_arr_num_constituents(subset);
        outputArray_(perfect_form.arr_constituent, perfect_form.size_arr_c);

    }
}