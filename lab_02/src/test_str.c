#include <assert.h>
#include "test_str.h"
#include "str.h"

void test_my_strcpy(void) {
    char s[6];
    my_strcpy(s, "great");
    assert(*(s + 0) == 'g');
    assert(*(s + 1) == 'r');
    assert(*(s + 2) == 'e');
    assert(*(s + 3) == 'a');
    assert(*(s + 4) == 't');
    assert(*(s + 5) == '\0');
}

void test_my_strcat(void) {
    char s1[5];
    char s2[3];
    *(s1 + 0) = 'a';
    *(s1 + 1) = 'b';
    *(s1 + 2) = '\0';
    *(s2 + 0) = 'c';
    *(s2 + 1) = 'd';    
    *(s2 + 2) = '\0';
    my_strcat(s1, s2);
    assert(*(s1 + 0) == 'a');
    assert(*(s1 + 1) == 'b');
    assert(*(s1 + 2) == 'c');
    assert(*(s1 + 3) == 'd');
    assert(*(s1 + 4) == '\0');
}

void test_my_strcmp(void) {
	assert(my_strcmp("eeeee", "fffff") < 0);
	assert(my_strcmp("eeeee", "eeeee") == 0);
	assert(my_strcmp("eeeee", "ddddd") > 0);
}

void test_my_strlen(void) {
    assert(my_strlen("milk") == 4);
    assert(my_strlen("ice-cream") == 9);
    assert(my_strlen("sugar") == 5);
}


