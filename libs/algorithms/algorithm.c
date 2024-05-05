//
//
//

#include <stdio.h>


void swap(void * a, void * b, size_t len){
    unsigned char * p = a, * q = b, tmp;
    for (size_t i = 0; i != len; ++i)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}