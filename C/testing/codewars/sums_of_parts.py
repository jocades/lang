# Let us consider this example (array written in general format):
#
# ls = [0, 1, 3, 6, 10]
#
# Its following parts:
#
# ls = [0, 1, 3, 6, 10]
# ls = [1, 3, 6, 10]
# ls = [3, 6, 10]
# ls = [6, 10]
# ls = [10]
# ls = []
# The corresponding sums are (put together in a list): [20, 20, 19, 16, 10, 0]

# Notes
# Take a look at performance: some lists have thousands of elements.

def parts_sums(ls):
    # your code
    # O(n^2) time complexity
    # result = []
    # for i in range(len(ls) + 1):
    #     result.append(sum(ls[i:]))
    # return result

    # O(n) time complexity
    # result = [0] * (len(ls) + 1)
    # for i in range(len(ls) - 1, -1, -1):
    #     result[i] = result[i + 1] + ls[i]
    # return result

    # O(n) time complexity
    result = [sum(ls)]
    for n in ls:
        result.append(result[-1] - n)
    return result


parts_sums([])  # [0]
parts_sums([0, 1, 3, 6, 10])  # , [20, 20, 19, 16, 10, 0])
parts_sums([1, 2, 3, 4, 5, 6])  # , [21, 20, 18, 15, 11, 6, 0])
# [10037855, 9293730, 9292795, 9292388, 9291934, 9291504, 9291414, 9291270, 2581057, 2580168, 2579358, 0])
parts_sums([744125, 935, 407, 454, 430, 90, 144, 6710213, 889, 810, 2579358])
