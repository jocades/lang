import time
import sys


def debug_decorator(func):
    def wrapper(*args, **kwargs):
        print(f"Calling function {func.__name__} with args: {args} and kwargs: {kwargs}")
        result = func(*args, **kwargs)
        print(f"Function {func.__name__} returned: {result}")
        return result
    return wrapper


def timing_decorator(max=None):
    def decorator(func):
        def wrapper(*args, **kwargs):
            start_time = time.time()
            result = func(*args, **kwargs)
            end_time = time.time()
            elapsed_time = end_time - start_time
            if max is not None and elapsed_time > max:
                raise TimeoutError(
                    f"Warning: Function {func.__name__} took {elapsed_time:.4f} seconds, which exceeds the maximum allowed time of {max} second{'s' if max > 1 else ''}")
            else:
                print(f"Function {func.__name__} took {elapsed_time:.4f} seconds")
            return result
        return wrapper
    return decorator


@timing_decorator(max=1)
@debug_decorator
def my_function(a, b, kw1=None, kw2=None):
    # time.sleep(2)
    for _ in range(10 ** 6):  # 1M
        pass


my_function(1, 2, kw1=3, kw2=4)

# Playground
ls = [[1, 9], [-1, 4], [3, 5], [2, 3]]
print(ls)
ls.sort(key=lambda x: sum(x), reverse=True)
print(ls)


# Iterators / Generators
string_ls = ['1', '2', '3', '4', '5']

int_ls_iter = map(int, string_ls)  # -> iterator (not created in memory)
print(list(int_ls_iter))
# or
int_ls_mem = [int(x) for x in string_ls]  # -> list (created in memory)
print(int_ls_mem)

print('iter', sys.getsizeof(int_ls_iter))
print('mem', sys.getsizeof(int_ls_mem))

plus_one = list(map(lambda x: int(x) + 1, string_ls))
print(plus_one)
