import time
from typing import Callable

module_variable = "hello"


def module_function():
    print("module_function")


# Testing callbacks
def callback_function():
    # Simulate a long running process
    time.sleep(2)
    print("callback_function")


def fn_with_callback(callback: Callable):
    print("fn_with_callback")
    callback()


# test
fn_with_callback(callback_function)


# Testing closures
def outer_function():
    message = "hi"

    def inner_function():
        print(message)

    return inner_function


def outer_function_with_args(message):
    def inner_function():
        print(message)

    return inner_function
