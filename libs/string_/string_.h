//
// 
//

#ifndef UNTITLED1_STRING__H
#define UNTITLED1_STRING__H

#include "string_.h"
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <memory.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

typedef struct WordDescriptor {
    char *begin;
    char *end;
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

typedef enum WordPrecedingFirstCommonWordReturnCode {
    WORD_PRECEDING_EMPTY_STRING,
    WORD_PRECEDING_FIRST_WORDS_IS_COMMON,
    WORD_PRECEDING_WORD_FOUND,
    WORD_PRECEDING_NOT_FOUND_COMMON_WORD
} WordPrecedingFirstCommonWordReturnCode;

size_t strlen_(const char *begin);

char* find(char *begin, char *end, int ch);

char* findNonSpace(char *begin);

char* findSpace(char *begin);

char *findNonSpaceReverse(char *rbegin, const char *rend);

char *findSpaceReverse(char *rbegin, const char *rend);

int strcmp_(const char *lhs, const char *rhs);

char* copy(const char *beginSource, const char *endSource, char *beginDestination);

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));

void test_string();

void removeNonLetters(char *s);

void removeExtraSpaces(char *s);

void removeAdjacentEqualLetters(char *s);

void test_removeAdjacentEqualLetters();

void test_removeExtraSpaces_1();

int getWord(char *beginSearch, WordDescriptor *word);

void digitToStart(WordDescriptor word);

void digitToEnd(WordDescriptor word);

void digitToEndAndReverse(WordDescriptor word);

void digits_to_end(char *string);

void digits_to_end_and_reverse(char *string);

void letters_to_end(char *string);

void test_WordDescriptor();

void replace_digits_with_spaces(char *string);

void test_replace_digits_with_spaces();

bool are_two_words_equal(WordDescriptor a, WordDescriptor b);

void replace(char *source, char *w1, char *w2);

void test_replace();

bool are_two_words_ordered(WordDescriptor word1, WordDescriptor word2);

bool are_words_ordered(char *string);

void test_are_words_ordered();

void getBagOfWords(BagOfWords *bag, char *s);

void print_words_in_reversed_order(char *string);

void test_print_words_in_reversed_order();

int is_palindrome(char *begin, char *end);

int count_palindromes(char *string);

void test_count_palindromes();

void join_strings(char *string1, char *string2, char *result);

void test_join_strings();

void reverse_words_order(char *string);

void test_reverse_words_order();

void wordDescriptorToString(WordDescriptor word, char *destination);

char* getLastWordInFirstStringInSecondString(char *s1, char *s2);

void test_getLastWordInFirstStringInSecondString();

bool has_same_words(char *string);

void test_has_same_words();

bool are_two_words_with_similar_characters(char *s1, char *s2);

bool has_words_with_similar_characters(char *string);

void test_has_words_with_similar_characters();

void get_string_without_words_like_last_word(char *string, char *result);

void test_get_string_without_words_like_last_word();

WordPrecedingFirstCommonWordReturnCode get_word_preceding_first_common_word(char *s1, char *s2, WordDescriptor *word);

void test_get_word_preceding_first_common_word();

void delete_palindromes(char *string);

void test_delete_palindromes();

void complement_smaller_string(char *string1, char *string2);

void test_complement_smaller_string();

bool is_string_contain_all_letter(char *string, char *word);

void test_is_string_contain_all_letter();

#endif //UNTITLED1_STRING__H
