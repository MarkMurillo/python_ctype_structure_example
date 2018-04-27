"""test.py
Python3
Test script that demonstrates the passing of an
initialized python structure to C and retrieving
the structure back.
"""
import testMod
from ctypes import *

class TESTSTRUCT(Structure):
    pass

TESTSTRUCT._fields_ = [
        ("name", c_char_p),
        ("next", POINTER(TESTSTRUCT), #We can use a structure pointer for a linked list.
        ("next2", c_void_p) #We can use void pointers for structures as well!
    ]

struct1 = TESTSTRUCT(c_char_p("Hello!".encode()), None, None)
struct2 = TESTSTRUCT(c_char_p("Goodbye!".encode()), None, None)
struct22 = TESTSTRUCT(c_char_p("My Love!".encode()), None, None)

struct1.next = pointer(struct2)

#Must cast lp to void p before assigning it or it will complain...
struct1.next2 = cast(pointer(struct22), c_void_p)

outbytes = testMod.py_returnMe(struct1)

#Must cast outbytes back into pointer for a struct and retrieve contents.
struct3 = cast(outbytes, POINTER(TESTSTRUCT)).contents

#Next is already a pointer so all we need are just the contents.
nextStruct = struct3.next.contents

#Next2 is a void p so we need to cast it back to TESTSTRUCT pointer and get
#the contents.
next2Struct = cast(struct3.next2, POINTER(TESTSTRUCT)).contents

print ("Result: {}, {}, {}".format(struct3.name, nextStrut.name, next2Struct.name)
