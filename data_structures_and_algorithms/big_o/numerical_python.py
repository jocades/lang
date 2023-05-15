import numpy as np

arr = np.array([1, 2, 3, 4, 5])
print(arr)
print(type(arr))

# Create a 2D array (matrix)
arr = np.array([['a', 'b', 'c'], ['d', 'e', 'f']])
print('2nd element in 1st row: ', arr[0, 1])
print('3rd element in 2nd row: ', arr[1, 2])

# The NumPy array object has a property called shape that returns a tuple with each index having the number of corresponding elements.
# (rows, columns)
print('Shape of array: ', arr.shape)


# list indexing, slicing, etc work the same way as a regular list except for multidimensional arrays
# from both elements return index 2
# usaully to access a value in a 2d array would be arr[0][2]
print(arr[0:2, 2])
print(arr[0][2], arr[1][2])

# from both elements return index 1 and 2
print(arr[0:2, 1:3])  # -> 2d array

# Array iterators
# Usually to iterate over the values (scalars) of a multidimensional array,
# we need as many nested loops as dimensions.
# NumPy provides an iterator object, nditer, that can be used to iterate over the array values directly.

# Iterate over the values of a 3-D array with nditer.
three = np.array([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])
print(three)

# regular
for x in three:
    for y in x:
        for z in y:
            print(z)

# nditer
for x in np.nditer(three):
    print(x)

# or a 2d array
for x in np.nditer(arr):
    print(x)


# Iterate with different data types
# i.e iter over the array as a string
nums = np.array([1, 2, 3, 4, 5])
for x in np.nditer(nums, flags=['buffered'], op_dtypes=['S']):
    print(x)
