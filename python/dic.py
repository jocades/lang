my_dict = {'a': 1, 'b': 2, 'c': 3}

# Ways of adding new key-value pairs to a dictionary
# 1. Using the update() method, if the key already exists, it will be updated
my_dict.update({'d': 4})
print(my_dict)

# 2. Using the subscript operator, if the key already exists, it will be updated
my_dict['e'] = 5
print(my_dict)

# Unpacking a dictionary similiar to ... in JS
# 3. Using the unpacking operator, if the key already exists, it will be updated
my_dict = {**my_dict, 'f': 6}
print(my_dict)

# 4. Using the setdefault() method, if the key already exists, it will not be updated
# setdefault() returns the value of the key if it exists, else it returns None
my_dict.setdefault('g', 7)
print(my_dict)


d = {}
d.setdefault('a', 1)
print(d)
d.setdefault('a', 2)
print(d)
