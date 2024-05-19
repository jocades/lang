import matplotlib.pyplot as plt
import numpy as np


def constant_time(n):
    return 1


def linear_time(n):
    return n


def quadratic_time(n):
    return n**2


n_values = np.arange(1, 21)
t_constant = [constant_time(n) for n in n_values]
t_linear = [linear_time(n) for n in n_values]
t_quadratic = list(map(quadratic_time, n_values))

plt.plot(n_values, t_constant, label='O(1)', marker='o')
plt.plot(n_values, t_linear, label='O(n)', marker='o')
plt.plot(n_values, t_quadratic, label='O(n^2)', marker='o')
plt.legend()

plt.xlabel('n')
plt.ylabel('t')
plt.title('Time Complexity')

plt.show()
