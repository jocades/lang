from timeit import timeit
from pathlib import Path


def fib_with_cache(n: int) -> int:
    cache = [0, 1]
    for i in range(2, n + 1):
        cache.append(cache[i - 1] + cache[i - 2])

    return cache[n]


def fib(n: int) -> int:
    if n < 2:
        return n
    return fib(n - 1) + fib(n - 2)


def setup(fn): return f'from __main__ import {fn}'


x = 10
repeat = 1_000_000

t1 = timeit(
    'fib(x)',
    setup=setup('fib'),
    globals={'x': x},
    number=repeat
)

t2 = timeit(
    'fib_with_cache(x)',
    setup=setup('fib_with_cache'),
    globals={'x': x},
    number=repeat
)

t3 = timeit(
    'fib(x)',
    setup=Path('main.py').read_text(),
    globals={'x': x},
    number=repeat
)

print(f'PYTHON fib({x}): {t1:.6f} seconds')
print(f'PYTHON fib_with_cache({x}): {t2:.6f} seconds')
print(f'CYTHON fib({x}): {t3:.6f} seconds')
