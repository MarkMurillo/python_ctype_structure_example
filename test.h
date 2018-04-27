//test.h
//Example c struct that can be used on the python side.
//Contains a method that just returns the given struct.
//Author: Mark Murillo
#include <stddef.h>

//Simple test structure linked list.
typedef struct testStruct {
    char *name;
    struct testStruct *next;
    struct testStruct *next2;
} testStruct_t;

/**
 * Function that returns back a given structure.
 *
 * @param myStruct - Pointer to a testStruct_t which will be returned.
 * @returns - The same testStruct_t pointer that was given as a parameter.
 */
testStruct_t *returnMe(testStruct_t *myStruct);
