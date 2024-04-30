#!/usr/bin/env python3

# quick test to make sure we can call shared libraries
import ctypes

lib = ctypes.CDLL('./librge')

foo = lib.foo
foo.restype = ctypes.c_int

result = foo()
print('Result from foo():', result)
