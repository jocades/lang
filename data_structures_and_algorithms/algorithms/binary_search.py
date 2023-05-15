from math import log, log2


# Binary Search Algorithm

arr = [-2, 3, 4, 7, 8, 9, 11, 13]
target = 11

# search(arr, target) -> index if found, else -1

# Linear Search
# O(n) time complexity


def linear_search(arr, target):
    for i in arr:
        if i == target:
            print(i)
            break
    else:
        print(-1)


linear_search(arr, target)


# Binary Search

# O(log n) time complexity
#
# 40 -> 20 -> 10 -> ... -> 1
# n -> n/2 -> n/4 -> n/8 -> ... -> 1
# n -> n/2 -> n/2^2 -> n/2^3 -> ... -> n/2^k roughly = 1 (where k = log(n))
# n/2^k = 1
# n = 2^k
# log(n) = k

# Lets say n = 8
# log(8) = 3
# 8/2^3 = 1
# so to find 1 element in a list of 8 elements, we need to do 3 operations
# to find 1 element in a list of 16 elements, we need to do 4 operations
# to find an element in a list of n elements, we need to do log(n) operations
print(log2(8))
print(log2(10000000))  # 10M -> only 24 operations!


def binary_search(arr, target):
    left = 0
    right = len(arr) - 1
    operation = 0

    while left <= right:
        mid = (left + right) // 2
        # mid = left + (right - left) // 2

        operation += 1
        print('Operation:', operation, 'Left:', left, 'Right:', right, 'Mid:', mid)

        if arr[mid] == target:
            print(mid)
            break
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    else:
        print(-1)


binary_search(arr, 3)

# l = 0
# r = len(arr) - 1
# m = l + r // 2
#
# print(l, r, m)
