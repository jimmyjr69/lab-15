//
// 
//
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <memory.h>

#ifndef UNTITLED1_VECTORVOID_H
#define UNTITLED1_VECTORVOID_H


typedef struct vectorVoid {
    void *data;
    size_t size;
    size_t capacity;
    size_t baseTypeSize;
} vectorVoid;

vectorVoid createVectorV(size_t n, size_t baseTypeSize);

void reserveV(vectorVoid *v, size_t newCapacity);

void clearV(vectorVoid *v);

void shrinkToFitV(vectorVoid *v);

void deleteVectorV(vectorVoid *v);

bool isEmptyV(vectorVoid *v);

bool isFullV(vectorVoid *v);

void getVectorValueV(vectorVoid *v, size_t index, void *destination);

void setVectorValueV(vectorVoid *v, size_t index, void *source);

void popBackV(vectorVoid *v);

void pushBackV(vectorVoid *v, void *source);

void test1();

void test2();

#endif //UNTITLED1_VECTORVOID_H
