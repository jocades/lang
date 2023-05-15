import matplotlib.pyplot as plt
import numpy as np

# Define the time complexity functions


def constant_time(n):
    return 1


def linear_time(n):
    return n


def quadratic_time(n):
    return n**2


# Generate some data to plot
n_values = np.arange(1, 11)
t_constant = [constant_time(n) for n in n_values]
t_linear = [linear_time(n) for n in n_values]
t_quadratic = [quadratic_time(n) for n in n_values]

# Plot the data
plt.plot(n_values, t_constant, label='O(1)', marker='o')
plt.plot(n_values, t_linear, label='O(n)', marker='o')
plt.plot(n_values, t_quadratic, label='O(n^2)', marker='o')
plt.legend()

plt.xlabel('n')
plt.ylabel('t')
plt.title('Time Complexity')

plt.show()
