//
//

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "../../algorithms/array/array.h"
#include "matrix.h"
#include "../../algorithms/algorithm.h"
#include <assert.h>
#include <string.h>

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m){
    for(int row = 0; row < m->nRows; row++){
        free(m->values[row]);
        m->values[row] = NULL;
    }
    free(m->values);
    m->nRows = 0;
    m->nCols = 0;
    m->values = NULL;
}

void freeMemMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(&ms[i]);
    free(ms);
}

void inputMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i++){
        inputArray_(m->values[i], m->nCols);
    }
    printf("Matrix hax been created\n");
}

void inputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++){
        printf("Enter the matrix N %d\n", i+1);
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m){
    for (int i = 0; i < m.nRows; i++){
        outputArray_(m.values[i], m.nCols);
    }
    printf("\n");
}

void outputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++){
        printf("Matrix N %d\n", i+1);
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix *m, int i1, int i2){
    assert(i1 < m->nRows && i2 < m->nRows && i1 >= 0 && i2 >= 0);
    swap(&m->values[i1], &m->values[i2], sizeof(m->values[i1]));
}

void swapColumns(matrix m, int j1, int j2){
    assert(j1 < m.nCols && j2 < m.nCols && j1 >= 0 && j2 >= 0);
    for (int i = 0; i < m.nRows; i++){
        swap(&m.values[i][j1], &m.values[i][j2], sizeof(m.values[i][j1]));
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)){
    int *rowsValues = (int*)malloc(sizeof(int)*m.nRows);
    rowsValues[0] = criteria(m.values[0], m.nCols);
    for (int row = 1; row < m.nRows; row++){
        rowsValues[row] = criteria(m.values[row], m.nCols);
        int temp = rowsValues[row];
        int j = row;
        while (j > 0 && rowsValues[j - 1] > temp) {
            rowsValues[j] = rowsValues[j - 1];
            m.values[j] = m.values[j-1];
            j--;
        }
        rowsValues[j] = temp;
        m.values[j] = m.values[row];
    }
    free(rowsValues);
} // Функция может не работать из-за идеи одного for

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)){
    int *colsValues = (int*)malloc(sizeof(int)*m.nCols);
    for (int col = 0; col < m.nCols; col++) {
        int *temp_arr_col = (int*)malloc(sizeof(int)*m.nRows);
        for (int row = 0; row < m.nRows; row++)
            temp_arr_col[row] = m.values[row][col];
        colsValues[col] = criteria(temp_arr_col, m.nRows);
        free(temp_arr_col);
    }

    for (int col = 0; col < m.nCols; col++) {
        int minCol = col;
        for (int j = col + 1; j < m.nCols; j++)
            if (colsValues[j] < colsValues[minCol])
                minCol = j;
        swap(&colsValues[col], &colsValues[minCol], sizeof(int));
        swapColumns(m, col, minCol);
    }
    free(colsValues);
}

bool isSquareMatrix(matrix *m){
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if (m1->nRows == m2->nRows && m1->nCols == m2->nCols){
        for(int row = 0; row < m1->nRows; row++)
            if (memcmp(m1->values[row], m2->values[row], sizeof(int) * m1->nCols) != 0)
                return false;
        return true;
    } else
        return false;
}

bool isEMatrix(matrix *m){
    if (isSquareMatrix(m)){
        for (int i = 0; i < m->nRows; i++)
            for(int j = 0; j< m->nRows; j++)
                if (i != j && m->values[i][j] != 0)
                    return false;
        return true;
    } else
        return false;
}

bool isSymmetricMatrix(matrix *m){
    if (isSquareMatrix(m)){
        for (int i = 0; i < m->nRows; i++)
            for(int j = m->nRows - 1; j >= 0; j--)
                if (m->values[i][j] != m->values[j][i])
                    return false;
        return true;
    } else
        return false;
}

void transposeSquareMatrix(matrix *m){
    assert(isSquareMatrix(m));

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}

void transposeMatrix(matrix *m) {
    matrix result = getMemMatrix(m->nCols, m->nRows);
    for (int i = 0; i < m->nCols; i++) {
        for (int j = 0; j < m->nRows; j++) {
            result.values[i][j] = m->values[j][i];
        }
    }
    memcpy(m, &result, sizeof(matrix));
}

position getMinValuePos(matrix m) {
    position result = {0, 0};
    int min_value = m.values[0][0];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min_value) {
                min_value = m.values[i][j];
                result.rowIndex = i;
                result.colIndex = j;
            }
        }
    }
    return result;
}

position getMaxValuePos(matrix m) {
    position result = {0, 0};
    int max_value = m.values[0][0];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max_value) {
                max_value = m.values[i][j];
                result.rowIndex = i;
                result.colIndex = j;
            }
        }
    }
    return result;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}

void test_swap_rows() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},3, 3);
    matrix result = createMatrixFromArray((int[]) {4, 5, 6,
                                                   1, 2, 3,
                                                   7, 8, 9},3, 3);

    swapRows(&m, 0, 1);

    assert(areTwoMatricesEqual(&m, &result));

    freeMemMatrix(&m);
    freeMemMatrix(&result);
}

void test_swap_columns() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},3, 3);
    matrix result = createMatrixFromArray((int[]) {2, 1, 3,
                                                   5, 4, 6,
                                                   8, 7, 9},3, 3);

    swapColumns(m, 0, 1);

    assert(areTwoMatricesEqual(&m, &result));

    freeMemMatrix(&m);
    freeMemMatrix(&result);
}

void test_is_square_matrix_true() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},3, 3);

    assert(isSquareMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_square_matrix_false() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              4, 5,
                                              7, 8},3, 2);

    assert(!isSquareMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_e_matrix_true() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1},3, 3);

    assert(isEMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_e_matrix_false() {
    matrix m = createMatrixFromArray((int[]) {2, 4, 0,
                                              0, 3, 5,
                                              8, 1, 1},3, 3);

    assert(!isEMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_symmetric_matrix_true() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              2, 5, 6,
                                              3, 6, 9},3, 3);

    assert(isSymmetricMatrix(&m));

    freeMemMatrix(&m);
}

void test_is_symmetric_matrix_false() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},3, 3);

    assert(!isSymmetricMatrix(&m));

    freeMemMatrix(&m);
}

void test_transpose_square_matrix() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},3, 3);
    matrix result = createMatrixFromArray((int[]) {1, 4, 7,
                                                   2, 5, 8,
                                                   3, 6, 9},3, 3);

    transposeSquareMatrix(&m);

    assert(areTwoMatricesEqual(&m, &result));

    freeMemMatrix(&m);
    freeMemMatrix(&result);
}

void test_transpose_matrix() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              3, 4,
                                              5, 6},3, 2);
    matrix result = createMatrixFromArray((int[]) {1, 3, 5,
                                                   2, 4, 6},2, 3);

    transposeMatrix(&m);

    assert(areTwoMatricesEqual(&m, &result));

    freeMemMatrix(&m);
    freeMemMatrix(&result);
}

void test_get_min_value_pos() {
    matrix m = createMatrixFromArray((int[]) {2, 4, 3,
                                              5, 1, 6,
                                              7, 8, 9},3, 3);
    position result = {1, 1};

    position pos = getMinValuePos(m);

    assert(pos.colIndex == result.colIndex);
    assert(pos.rowIndex == result.rowIndex);

    freeMemMatrix(&m);
}

void test_get_max_value_pos() {
    matrix m = createMatrixFromArray((int[]) {2, 4, 3,
                                              5, 9, 6,
                                              7, 8, 1},3, 3);
    position result = {1, 1};

    position pos = getMaxValuePos(m);

    assert(pos.colIndex == result.colIndex);
    assert(pos.rowIndex == result.rowIndex);

    freeMemMatrix(&m);
}

matrix mulMatrices(matrix m1, matrix m2) {
    int rows = m1.nRows;
    int cols = m1.nCols;
    matrix result = getMemMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sum = 0;
            for (int g = 0; g < rows; g++) {
                sum += m1.values[i][g] * m2.values[g][j];
            }
            result.values[i][j] = sum;
        }
    }
    return result;
}

void test_matrix() {
    test_swap_rows();
    test_swap_columns();
    test_is_square_matrix_true();
    test_is_square_matrix_false();
    test_is_e_matrix_true();
    test_is_e_matrix_false();
    test_is_symmetric_matrix_true();
    test_is_symmetric_matrix_false();
    test_transpose_square_matrix();
    test_transpose_matrix();
    test_get_min_value_pos();
    test_get_max_value_pos();
}