import ctypes

mod = ctypes.CDLL('mod.so')


add = mod.add
add.argtypes = [ctypes.c_int, ctypes.c_int]
add.restype = ctypes.c_int


fib = mod.fib
fib.argtypes = [ctypes.c_int]
fib.restype = ctypes.c_int
