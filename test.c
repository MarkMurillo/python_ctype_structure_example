//test.c
//Example C function source including python c extension wrapper code.
//This must be compiled by running the command:
//python3 setup.py install
//
//Author: Mark Murillo
#include "test.h"
#include <Python.h>


//The native routine to wrap in python.
testStruct_t *returnMe(testStruct_t *myStruct) {
    return myStruct;
}


/* AT THIS POINT, THE REST OF THE SOURCE CAN BE SEPARTED INTO ANOTHER FILE IDEALlY */

//Declare the prototype for the python wrapping function.
static PyObject *testReturnMe(PyObject *self, PyObject *args);

//Declare the python-callable methods for the module that will wrap
//the c function.
static PyMethodDef testModMethods[] = {
    {"py_returnMe", testReturnMe, METH_VARARGS, "testing C extension"},
    {NULL, NULL, 0, NULL}
};

//Declare the module containing the wrapped c function.
static struct PyModuleDef testMod = {
    PyModuleDef_HEAD_INIT,
    "testMod",
    NULL,
    -1,
    testModMethods,
    NULL, NULL, NULL, NULL
};

//Load module based on module definition.
PyMODINIT_FUNC PyInit_testMod(void) {
    PyObject *pModule = PyModule_Create(&testMod);

    if(pModule == NULL) {
        fprintf(stderr, "Failed to load testMod module\n");
    }

    return pModule;
}

//Python wrapper function implementation.
static PyObject *testReturnMe(PyObject *self, PyObject *args) {
    (void) self;

    testStruct_t *test;
    size_t size;

    //Parse the python structure as a byte buffer with
    //the same memory mapping as the C counterpart.
    if (!PyArg_ParseTuple(args, "y#", &test, &size))
        return NULL;
    if (size != sizeof(testStruct_t))
        return NULL;

    testStruct_t *result = returnMe(test);
    //We can return the structure as bytes.
    return Py_BuildValue("y#", result, size);
}
