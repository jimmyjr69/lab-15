//
// 
//
#include "string_.h"
#include <ctype.h>
#include <assert.h>
#include <memory.h>
#include <stdbool.h>

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)

BagOfWords _bag;
BagOfWords _bag2;

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char* findNonSpace(char *begin) {
    while (isspace(*begin) && *begin != '\0') {
        begin++;
    }
    return begin;
}

char* findSpace(char *begin) {
    while (!isspace(*begin) && *begin != '\0') {
        begin++;
    }
    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && isspace(*rbegin)) {
        rbegin--;
    }
    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && !isspace(*rbegin)) {
        rbegin--;
    }
    return rbegin;
}

int strcmp_(const char *lhs, const char *rhs) {
    while (*lhs == *rhs && *lhs != '\0' && *rhs != '\0') {
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}

char* copy(const char *beginSource, const char *endSource, char *beginDestination) {
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);
    *(beginDestination + size) = '\0';

    return beginDestination + size;
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    while (beginSource != endSource) {
        if (f( *beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
    *beginDestination = '\0';

    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    char *beginDestination_ = beginDestination;
    while (rbeginSource >= rendSource) {
        if (f(*rbeginSource)) {
            *beginDestination_ = *rbeginSource;
            beginDestination_++;
        }
        rbeginSource--;
    }
    *beginDestination_ = '\0';

    return beginDestination_;
}

int is_h(char s) {
    return s == 'h' || s == 'w';
}

void test_find_1() {
    char string[] = "hello";

    assert(find(string, string + 5, 'e') == string + 1);
}

void test_find_2() {
    char string[] = "hello";

    assert(find(string, string + 5, 'h') == string);
}

void test_find_3() {
    char string[] = "hello";

    assert(find(string, string + 5, 'o') == string + 4);
}

void test_find_4() {
    char string[] = "hello";

    assert(find(string, string + 5, 'g') == string + 5);
}

void test_find_non_space_1() {
    char string[] = "hello";

    assert(findNonSpace(string) == string);
}

void test_find_non_space_2() {
    char string[] = "  llo";

    assert(findNonSpace(string) == string + 2);
}

void test_find_non_space_3() {
    char string[] = "    o";

    assert(findNonSpace(string) == string + 4);
}

void test_find_non_space_4() {
    char string[] = "     ";

    assert(findNonSpace(string) == string + 5);
}

void test_find_space_1() {
    char string[] = " ello";

    assert(findSpace(string) == string);
}

void test_find_space_2() {
    char string[] = "he lo";

    assert(findSpace(string) == string + 2);
}

void test_find_space_3() {
    char string[] = "hello";

    assert(findSpace(string) == string + 5);
}

void test_find_space_4() {
    char string[] = "hell ";

    assert(findSpace(string) == string + 4);
}

void test_find_non_space_reverse_1() {
    char string[] = "hello";

    assert(findNonSpaceReverse(string + 4, string) == string + 4);
}

void test_find_non_space_reverse_2() {
    char string[] = "hel  ";

    assert(findNonSpaceReverse(string + 4, string) == string + 2);
}

void test_find_non_space_reverse_3() {
    char string[] = "h    ";

    assert(findNonSpaceReverse(string + 4, string) == string);
}

void test_find_non_space_reverse_4() {
    char string[] = "     ";

    assert(findNonSpaceReverse(string + 4, string) == string - 1);
}

void test_find_space_reverse_1() {
    char string[] = "hello";

    assert(findSpaceReverse(string + 4, string) == string - 1);
}

void test_find_space_reverse_2() {
    char string[] = "hel  ";

    assert(findSpaceReverse(string + 4, string) == string + 4);
}

void test_find_space_reverse_3() {
    char string[] = "h   o";

    assert(findSpaceReverse(string + 4, string) == string + 3);
}

void test_find_space_reverse_4() {
    char string[] = " ello";

    assert(findSpaceReverse(string + 4, string) == string);
}

void test_is_strings_equal_1() {
    char string1[] = "Hello";
    char string2[] = "Hello";

    assert(strcmp_(string1, string2) == 0);
}

void test_is_strings_equal_2() {
    char string1[] = "Hello";
    char string2[] = "Hallo";

    assert(strcmp_(string1, string2) > 0);
}

void test_is_strings_equal_3() {
    char string1[] = "Hello";
    char string2[] = "Hellower";

    assert(strcmp_(string1, string2) < 0);
}

void test_strcmp_(){
    test_is_strings_equal_1();
    test_is_strings_equal_2();
    test_is_strings_equal_3();
}

void test_string_1(){
    test_find_1();
    test_find_2();
    test_find_3();
    test_find_4();
    test_find_non_space_1();
    test_find_non_space_2();
    test_find_non_space_3();
    test_find_non_space_4();
    test_find_space_1();
    test_find_space_2();
    test_find_space_3();
    test_find_space_4();
    test_find_non_space_reverse_1();
    test_find_non_space_reverse_2();
    test_find_non_space_reverse_3();
    test_find_non_space_reverse_4();
    test_find_space_reverse_1();
    test_find_space_reverse_2();
    test_find_space_reverse_3();
    test_find_space_reverse_4();
}

void test_copy() {
    char string[] = "hahh";
    char new_string[4];
    copy(string, string + 3, new_string);
    char result[] = "hah";

    assert(strcmp_(new_string, result) == 0);
}

void test_copyIf() {
    char string[] = "hahh";
    char new_string[4];
    copyIf(string, string + 3, new_string, (int (*)(int)) is_h);
    char result[] = "hh";

    assert(strcmp_(new_string, result) == 0);
}

void test_copyIfReverse() {
    char string[] = "haw";
    char new_string[3];
    copyIfReverse(string + 3, string, new_string, (int (*)(int)) is_h);
    char result[] = "wh";

    assert(strcmp_(new_string, result) == 0);
}

void test_copy_full(){
    test_copy();
    test_copyIf();
    test_copyIfReverse();
}

void test_string(){
    test_string_1();
    test_strcmp_();
    test_copy_full();
}

void removeNonLetters(char *s) {
    char *endSource = s + strlen_(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void test_removeNonLetters() {
    char s1[] = "hel lo";
    char s2[] = "hello";
    removeNonLetters(s1);
    ASSERT_STRING(s1, s2);
}

char* copy_if_not_extra_spaces(char *beginSource, const char *endSource, char *beginDestination) {
    *beginDestination = *beginSource;
    beginDestination++;
    beginSource++;

    while (beginSource != endSource) {
        if (!isspace(*beginSource) || (isspace(*beginSource) && !isspace(*(beginSource - 1)))) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }

    *beginDestination = '\0';

    return beginDestination;
}

void removeExtraSpaces(char *s) {
    if (strlen_(s) > 0) {
        char *endSource = s + strlen_(s);
        char *destination = copy_if_not_extra_spaces(s, endSource, s);
        *destination = '\0';
    }
}
void test_removeExtraSpaces_1() {
    char s1[] = "";
    char s2[] = "";
    removeExtraSpaces(s1);
    ASSERT_STRING(s1, s2);
}
void removeAdjacentEqualLetters(char *s) {
    if (*s != '\0') {
        s++;
    }
    char *read_buffer = s;
    while (*read_buffer != '\0') {
        if (*read_buffer != *(--s)) {
            *(++s) = *read_buffer;
        }
        s++;
        read_buffer++;
    }
    *s = '\0';
}
void test_removeAdjacentEqualLetters() {
    char s1[] = "";
    removeAdjacentEqualLetters(s1);
    ASSERT_STRING(s1, "");
    char s2[] = "zero";
    removeAdjacentEqualLetters(s2);
    ASSERT_STRING(s2, "zero");
    char s3[] = "zzeeeeroooo";
    removeAdjacentEqualLetters(s3);
    ASSERT_STRING(s3, "zero");
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}
void digitToStart(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin,
                               isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}
void digitToEnd(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin,
                               isalpha);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isdigit);
}
void digitToEndAndReverse(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin,
                               isalpha);
    copyIfReverse(endStringBuffer, _stringBuffer, recPosition, isdigit);
}
void digits_to_end(char *string) {
    WordDescriptor word;
    char *beginSearch = string;
    while (getWord(beginSearch, &word)) {
        digitToEnd(word);
        beginSearch = word.end;
    }
}
void digits_to_end_and_reverse(char *string) {
    WordDescriptor word;
    char *beginSearch = string;
    while (getWord(beginSearch, &word)) {
        digitToEndAndReverse(word);
        beginSearch = word.end;
    }
}
void letters_to_end(char *string) {
    WordDescriptor word;
    char *beginSearch = string;
    while (getWord(beginSearch, &word)) {
        digitToStart(word);
        beginSearch = word.end;
    }
}
void test_WordDescriptor() {
    char string1[] = "he13l3lo8";
    digits_to_end(string1);
    ASSERT_STRING("hello1338", string1);
    char string2[] = "he13l3lo8";
    digits_to_end_and_reverse(string2);
    ASSERT_STRING("hello8331", string2);
    char string3[] = "he13l3lo8";
    letters_to_end(string3);
    ASSERT_STRING(string3, "1338hello");
}

void replace_digits_with_spaces(char *string) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *end = string + strlen_(string);
    char *readBuffer = _stringBuffer;
    copy(string, end, readBuffer);
    while (*readBuffer != '\0') {
        if (isalpha(*readBuffer)) {
            *string++ = *readBuffer;
        } else {
            while (isdigit(*readBuffer) && *readBuffer != '0') {
                *string++ = ' ';
                (*readBuffer)--;
            }
        }
        readBuffer++;
    }
    *string = '\0';
}

void test_replace_digits_with_spaces() {
    char string_1[] = "";
    replace_digits_with_spaces(string_1);
    ASSERT_STRING("", string_1);
    char string_2[] = "hl";
    replace_digits_with_spaces(string_2);
    ASSERT_STRING("hl", string_2);
    char string_3[] = "h12l";
    replace_digits_with_spaces(string_3);
    ASSERT_STRING("h l", string_3);
}

bool are_two_words_equal(WordDescriptor a, WordDescriptor b) {
    char *readBuffer1 = a.begin;
    char *readBuffer2 = b.begin;
    while ((*readBuffer1 != ' ' || *readBuffer2 != ' ') && (*readBuffer1 !=
                                                            '\0' && *readBuffer2 != '\0')) {
        if (*readBuffer1 != *readBuffer2 != '\0') {
            return 0;
        }
        readBuffer1++;
        readBuffer2++;
    }
    return readBuffer1 == a.end && readBuffer2 == b.end;
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    WordDescriptor word;
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *readPtr, *recPtr;
    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, source + strlen_(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }
    while (getWord(readPtr, &word)) {
        WordDescriptor res = word2;
        if (!are_two_words_equal(word, word1)) {
            res = word;
        }
        for (char *cp = res.begin; cp != res.end; cp++) {
            *recPtr++ = *cp;
        }
        *recPtr++ = ' ';
        readPtr = word.end;
    }
    *(recPtr - 1) = '\0';
}

void test_replace() {
    char string[] = "0/20/0 who? -=-";
    replace(string, "who?", "Rell"); //Nice champ, but my hands out of the ass =(
    ASSERT_STRING("0/20/0 Rell -=-", string);
    char string2[] = "0/20/0 x -=- x";
    replace(string2, "x", "Rell");
    ASSERT_STRING("0/20/0 Rell -=- Rell", string2);
}

bool are_two_words_ordered(WordDescriptor word1, WordDescriptor word2) {
    char *string1 = word1.begin;
    char *string2 = word2.begin;
    while (*string1 != '\0' || *string1 != ' ') {
        if (*string2 - 'a' < *string1 - 'a' || *string2 == '\0' || *string2
                                                                   == ' ') {
            return false;
        } else if (*string2 - 'a' > *string1 - 'a') {
            return true;
        }
        string1++;
        string2++;
    }
    return true;
}

bool are_words_ordered(char *string) {
    WordDescriptor word1, word2;
    if (getWord(string, &word1)) {
        word2 = word1;
        char *string_ = word1.end;
        while (getWord(string_, &word1)) {
            if (!are_two_words_ordered(word2, word1)) {
                return false;
            }
            word2 = word1;
            string_ = word1.end;
        }
        return true;
    } else {
        return true;
    }
}

void test_are_words_ordered() {
    char string1[] = "";
    assert(are_words_ordered(string1));
    char string2[] = "zero one two";
    assert(!are_words_ordered(string2));
    char string3[] = "one two zero";
    assert(are_words_ordered(string3));
}

void getBagOfWords(BagOfWords *bag, char *s) {
    bag->size = 0;
    WordDescriptor word;
    char *beginSearch = s;
    while (getWord(beginSearch, &word)) {
        bag->words[bag->size].begin = word.begin;
        bag->words[bag->size].end = word.end;
        bag->size++;
        beginSearch = word.end;
    }
}

void print_words_in_reversed_order(char *string) {
    getBagOfWords(&_bag, string);
    char word[MAX_WORD_SIZE];
    for (size_t i = _bag.size; i > 0; i--) {
        copy(_bag.words[i - 1].begin, _bag.words[i - 1].end, word);
        printf("%s\n", word);
    }
}

void test_print_words_in_reversed_order() {
    char string_1[] = "";
    print_words_in_reversed_order(string_1);
    char string_2[] = "One Two Three";
    print_words_in_reversed_order(string_2);
}

int is_palindrome(char *begin, char *end) {
    end--;
    while (end > begin) {
        if (*begin != *end) {
            return 0;
        }
        begin++;
        end--;
    }
    return 1;
}

int count_palindromes(char *string) {
    char *begin = findNonSpace(string);
    char *end = string + strlen_(string);
    char *new_word = find(begin, end, ',');
    bool is_last_word = *new_word == '\n';
    size_t result = 0;
    while (*new_word != '\0' || is_last_word) {
        result += is_palindrome(begin, new_word);
        if (is_last_word) {
            break;
        }
        begin = findNonSpace(new_word + 1);
        new_word = find(begin, end, ',');
        is_last_word = *new_word == '\0';
    }
    return result;
}

void test_count_palindromes() {
    char string_1[] = "";
    assert(count_palindromes(string_1) == 0);
    char string_2[] = "daffs, dadad";
    assert(count_palindromes(string_2) == 1);
}

void join_strings(char *string1, char *string2, char *result) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = string1, *beginSearch2 = string2;
    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found =getWord(beginSearch2, &word2)), isW1Found || isW2Found) {
        if (isW1Found && isW2Found) {
            for (char *s = word1.begin; s != word1.end; s++) {
                *result++ = *s;
            }
            *result++ = ' ';
            for (char *s = word2.begin; s != word2.end; s++) {
                *result++ = *s;
            }
            beginSearch1 = word1.end;
            beginSearch2 = word2.end;
            if ((isW1Found = getWord(beginSearch1, &word1)),
                    (isW2Found =getWord(beginSearch2, &word2)), isW1Found || isW2Found)
            {
                *result++ = ' ';
            }
        } else if (isW1Found) {
            for (char *s = word1.begin; s != beginSearch1 + strlen_(beginSearch1); s++) {
                *result++ = *s;
            }
            return;
        } else {
            for (char *s = word2.begin; s != beginSearch2 + strlen_(beginSearch2); s++) {
                *result++ = *s;
            }
            return;
        }
    }
}

void test_join_strings() {
    char result1[MAX_STRING_SIZE];
    join_strings("", "", result1);
    ASSERT_STRING(result1, "");
    char result2[MAX_STRING_SIZE];
    join_strings("one three", "two four", result2);
    ASSERT_STRING(result2, "one two three four");
    char result3[MAX_STRING_SIZE];
    join_strings("one three five", "two four", result3);
    ASSERT_STRING(result3, "one two three four five");
    char result4[MAX_STRING_SIZE];
    join_strings("one three", "two four five", result4);
    ASSERT_STRING(result4, "one two three four five");
}

void reverse_words_order(char *string) {
    getBagOfWords(&_bag, string);
    char result[MAX_STRING_SIZE + 1];
    int size = 0;
    for (int i = _bag.size; i > 0; i--) {
        for (char *s = _bag.words[i - 1].begin; s != _bag.words[i - 1].end; s++) {
            result[size++] = *s;
        }
        if (i != 1) {
            result[size++] = ' ';
        }
    }
    result[size++] = '\0';
    copy(result, result + size, string);
}

void test_reverse_words_order() {
    char string1[] = "";
    reverse_words_order(string1);
    ASSERT_STRING(string1, "");
    char string2[] = "one";
    reverse_words_order(string2);
    ASSERT_STRING(string2, "one");
    char string3[] = "one two three";
    reverse_words_order(string3);
    ASSERT_STRING(string3, "three two one");
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w) {
    if (*s == '\0') {
        return EMPTY_STRING;
    } else if (find(s, s + strlen_(s), 'A') != s + strlen_(s) || find(s, s + strlen_(s), 'a') != s + strlen_(s)) {
        char *beginSearch = s;
        getWord(beginSearch, w);
        if (find(w->begin, w->end, 'A') != w->end || find(w->begin, w->end, 'a') != w->end) {
            return FIRST_WORD_WITH_A;
        } else {
            return WORD_FOUND;
        }
    } else {
        return NOT_FOUND_A_WORD_WITH_A;
    }
}

void printWordBeforeFirstWordWithA(char *s) {
    WordDescriptor word;
    WordBeforeFirstWordWithAReturnCode code = getWordBeforeFirstWordWithA(s, &word);
    if (code == EMPTY_STRING) {
        printf("The string is empty.\n");
    } else if (code == NOT_FOUND_A_WORD_WITH_A) {
        printf("The letter 'a' or 'A' was not founded.\n");
    } else if (code == FIRST_WORD_WITH_A) {
        printf("The letter 'a' or 'A' was founded in first word.\n");
    } else {
        char *beginSearch = s;
        char result[MAX_WORD_SIZE];
        while (getWord(beginSearch, &word)) {
            copy(word.begin, word.end, result);
            getWord(word.end, &word);
            if (find(word.begin, word.end, 'A') != word.end ||
                find(word.begin, word.end, 'a') != word.end) {
                printf("%s\n", result);
                return;
            }
            beginSearch = word.begin;
        }
    }
}

void test_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    printWordBeforeFirstWordWithA(s1);
    assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);
    char s2[] = "ABC";
    printWordBeforeFirstWordWithA(s2);
    assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);
    char s3[] = "BC DSS A DS AD";
    printWordBeforeFirstWordWithA(s3);
    assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);
    char s4[] = "B Q WE YR OW IUWR";
    printWordBeforeFirstWordWithA(s4);
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void wordDescriptorToString(WordDescriptor word, char *destination) {
    copy(word.begin, word.end, destination);
}

char* getLastWordInFirstStringInSecondString(char *s1, char *s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    char result[MAX_WORD_SIZE + 1];
    for (int i = _bag.size; i > 0; i--) {
        for (int j = _bag2.size; j > 0; j--) {
            if (are_two_words_equal(_bag.words[i - 1], _bag2.words[j - 1])) {
                wordDescriptorToString(_bag.words[i - 1], result);
                return result;
            }
        }
    }
    return "";
}

void test_getLastWordInFirstStringInSecondString() {
    char s1_1[] = "";
    char s1_2[] = "";
    ASSERT_STRING(getLastWordInFirstStringInSecondString(s1_1, s1_2), "");
    char s2_1[] = "One Two Zero Three";
    char s2_2[] = "One Zero Five";
    ASSERT_STRING(getLastWordInFirstStringInSecondString(s2_1, s2_2), "Zero");
    char s3_1[] = "One Three Five";
    char s3_2[] = "Two Four";
    ASSERT_STRING(getLastWordInFirstStringInSecondString(s3_1, s3_2), "");
}

bool has_same_words(char *string) {
    getBagOfWords(&_bag, string);
    for (int i = 0; i < _bag.size; i++) {
        for (int j = i + 1; j < _bag.size; j++) {
            if (are_two_words_equal(_bag.words[i], _bag.words[j])) {
                return 1;
            }
        }
    }
    return 0;
}

void test_has_same_words() {
    char s1[] = "";
    assert(!has_same_words(s1));
    char s2[] = "one two three";
    assert(!has_same_words(s2));
    char s3[] = "one two one";
    assert(has_same_words(s3));
}

bool are_two_words_with_similar_characters(char *s1, char *s2) {
    int symbols1[26] = {0};
    int symbols2[26] = {0};
    for (int i = 0; i < strlen_(s1); i++) {
        symbols1[s1[i] - 'a'] = 1;
    }
    for (int i = 0; i < strlen_(s2); i++) {
        symbols2[s2[i] - 'a'] = 1;
    }
    for (int i = 0; i < 26; i++) {
        if (symbols1[i] != symbols2[i]) {
            return 0;
        }
    }
    return 1;
}

bool has_words_with_similar_characters(char *string) {
    getBagOfWords(&_bag, string);
    for (int i = 0; i < _bag.size; i++) {
        for (int j = i + 1; j < _bag.size; j++) {
            char word1[MAX_WORD_SIZE + 1];
            char word2[MAX_WORD_SIZE + 1];
            wordDescriptorToString(_bag.words[i], word1);
            wordDescriptorToString(_bag.words[j], word2);
            if (are_two_words_with_similar_characters(word1, word2)) {
                return 1;
            }
        }
    }
    return 0;
}

void test_has_words_with_similar_characters() {
    char s1[] = "";
    assert(!has_words_with_similar_characters(s1));
    char s2[] = "one two three";
    assert(!has_words_with_similar_characters(s2));
    char s3[] = "one two eno";
    assert(has_words_with_similar_characters(s3));
}

void get_string_without_words_like_last_word(char *string, char *result) {
    getBagOfWords(&_bag, string);
    int size = 0;
    if (_bag.size == 0) {
        return;
    } else {
        for (int i = 0; i < _bag.size - 1; i++) {
            if (!are_two_words_equal(_bag.words[i], _bag.words[_bag.size -
                                                               1])) {
                for (char *s = _bag.words[i].begin; s != _bag.words[i].end;
                     s++) {
                    result[size++] = *s;
                }
                result[size++] = ' ';
            }
        }
        result[size--] = '\0';
    }
}

void test_get_string_without_words_like_last_word() {
    char s1[] = "";
    char res1[MAX_STRING_SIZE + 1];
    get_string_without_words_like_last_word(s1, res1);
    ASSERT_STRING(res1, "");
    char s2[] = "one one one";
    char res2[MAX_STRING_SIZE];
    get_string_without_words_like_last_word(s2, res2);
    ASSERT_STRING(res2, "");
    char s3[] = "one zero one";
    char res3[MAX_STRING_SIZE + 1];
    get_string_without_words_like_last_word(s3, res3);
    ASSERT_STRING(res3, "zero");
    char s4[] = "two dva zero one";
    char res4[MAX_STRING_SIZE + 1];
    get_string_without_words_like_last_word(s4, res4);
    ASSERT_STRING(res4, "two dva zero");
}

WordPrecedingFirstCommonWordReturnCode get_word_preceding_first_common_word(char *s1, char *s2, WordDescriptor *word) {
    if (*s1 == '\0' || *s2 == '\0') {
        return WORD_PRECEDING_EMPTY_STRING;
    }
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    for (int i = 0; i < _bag.size; i++) {
        for (int j = 0; j < _bag2.size; j++) {
            if (are_two_words_equal(_bag.words[i], _bag2.words[j])) {
                if (i > 0) {
                    word->begin = _bag.words[i - 1].begin;
                    word->end = _bag.words[i - 1].end;
                    return WORD_PRECEDING_WORD_FOUND;
                } else {
                    return WORD_PRECEDING_FIRST_WORDS_IS_COMMON;
                }
            }
        }
    }
    return WORD_PRECEDING_NOT_FOUND_COMMON_WORD;
}

void test_get_word_preceding_first_common_word() {
    char s1_1[] = "";
    char s1_2[] = "";
    WordDescriptor w1;
    assert(get_word_preceding_first_common_word(s1_1, s1_2, &w1) ==
           WORD_PRECEDING_EMPTY_STRING);
    char s2_1[] = "one three five";
    char s2_2[] = "zero two four";
    WordDescriptor w2;
    assert(get_word_preceding_first_common_word(s2_1, s2_2, &w2) ==
           WORD_PRECEDING_NOT_FOUND_COMMON_WORD);
    char s3_1[] = "zero one five";
    char s3_2[] = "five three zero";
    WordDescriptor w3;
    assert(get_word_preceding_first_common_word(s3_1, s3_2, &w3) ==
           WORD_PRECEDING_FIRST_WORDS_IS_COMMON);
    char s4_1[] = "zero one five";
    char s4_2[] = "one five";
    WordDescriptor w4;
    assert(get_word_preceding_first_common_word(s4_1, s4_2, &w4) ==
           WORD_PRECEDING_WORD_FOUND);
    char word[MAX_WORD_SIZE + 1];
    copy(w4.begin, w4.end, word);
    ASSERT_STRING(word, "zero");
}

void delete_palindromes(char *string) {
    getBagOfWords(&_bag, string);
    char result[MAX_STRING_SIZE + 1];
    size_t size = 0;
    for (int i = 0; i < _bag.size; i++) {
        if (!is_palindrome(_bag.words[i].begin, _bag.words[i].end)) {
            for (char *s = _bag.words[i].begin; s != _bag.words[i].end; s++) {
                result[size++] = *s;
            }
            result[size++] = ' ';
        }
    }
    result[size--] = '\0';
    copy(result, result + strlen_(result), string);
}

void test_delete_palindromes() {
    char s1[] = "";
    delete_palindromes(s1);
    ASSERT_STRING(s1, "");
    char s2[] = "ada dafd";
    delete_palindromes(s2);
    ASSERT_STRING(s2, "dafd");
    char s3[] = "affs sdaa";
    delete_palindromes(s3);
    ASSERT_STRING(s3, "affs sdaa");
    char s4[] = "ada affa";
    delete_palindromes(s4);
    ASSERT_STRING(s4, "");
}

void complement_smaller_string(char *string1, char *string2) {
    getBagOfWords(&_bag, string1);
    getBagOfWords(&_bag2, string2);
    if (_bag.size > _bag2.size) {
        char stringBuffer[MAX_STRING_SIZE + 1];
        int size = 0;
        for (size_t i = _bag2.size; i < _bag.size; i++) {
            stringBuffer[size++] = ' ';
            for (char *s = _bag.words[i].begin; s != _bag.words[i].end; s++)
            {
                stringBuffer[size++] = *s;
            }
        }
        copy(stringBuffer, stringBuffer + size, string2 + strlen_(string2));
    } else if (_bag2.size > _bag.size) {
        char stringBuffer[MAX_STRING_SIZE + 1];
        int size = 0;
        for (size_t i = _bag.size; i < _bag2.size; i++) {
            stringBuffer[size++] = ' ';
            for (char *s = _bag2.words[i].begin; s != _bag2.words[i].end;
                 s++) {
                stringBuffer[size++] = *s;
            }
        }
        copy(stringBuffer, stringBuffer + size, string1 + strlen_(string1));
    }
}

void test_complement_smaller_string() {
    char s1_1[] = "";
    char s1_2[] = "";
    complement_smaller_string(s1_1, s1_2);
    ASSERT_STRING(s1_1, "");
    ASSERT_STRING(s1_2, "");
    char s2_1[] = "zero one two";
    char s2_2[] = "three five four";
    complement_smaller_string(s2_1, s2_2);
    ASSERT_STRING(s2_1, "zero one two");
    ASSERT_STRING(s2_2, "three five four");
    char s3_1[] = "zero one two";
    char s3_2[] = "three";
    complement_smaller_string(s3_1, s3_2);
    ASSERT_STRING(s3_2, "three one two");
    char s4_1[] = "zero";
    char s4_2[] = "five one two";
    complement_smaller_string(s4_1, s4_2);
    ASSERT_STRING(s4_1, "zero one two");
}

bool is_string_contain_all_letter(char *string, char *word) {
    if (strlen_(word) == 0) {
        return false;
    }
    size_t string_size = strlen_(string);
    size_t word_size = strlen_(word);
    for (char *s = word; s != word + word_size; s++) {
        if (find(string, string + string_size, *s) == string + string_size) {
            return false;
        }
    }
    return true;
}

void test_is_string_contain_all_letter() {
    char s1[] = "";
    char w1[] = "";
    assert(!is_string_contain_all_letter(s1, w1));
    char s2[] = "zero one five";
    char w2[] = "zeone";
    assert(is_string_contain_all_letter(s2, w2));
    char s3[] = "zero one five";
    char w3[] = "zed";
    assert(!is_string_contain_all_letter(s3, w3));
}