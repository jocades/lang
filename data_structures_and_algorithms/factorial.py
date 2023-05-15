# Consider the following numbers (where n! is factorial(n)):

# u1 = (1 / 1!) * (1!)
# u2 = (1 / 2!) * (1! + 2!)
# u3 = (1 / 3!) * (1! + 2! + 3!)
# ...
# un = (1 / n!) * (1! + 2! + 3! + ... + n!)
# Which will win: 1 / n! or (1! + 2! + 3! + ... + n!)?

# Are these numbers going to 0 because of 1/n! or to infinity due to the sum of factorials or to another number?

# Task
# Calculate (1 / n!) * (1! + 2! + 3! + ... + n!) for a given n, where n is an integer greater or equal to 1.

# To avoid discussions about rounding, return the result truncated to 6 decimal places, for example:

# 1.0000989217538616 will be truncated to 1.000098
# 1.2125000000000001 will be truncated to 1.2125

def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)


def going(n):
    sum = 0
    for i in range(1, n+1):
        sum += factorial(i)
    return round(sum / factorial(n), 6)


print(going(5))
print(going(6))
print(going(7))

assert going(5) == 1.275
assert going(6) == 1.2125
assert going(7) == 1.173214

# getting some erros in some cases
# when using 6 decmals it rounds up to the 6th decimal
# how to fix this?
#
# 1.146652 should equal 1.146651
# 1.052787 should equal 1.052786
