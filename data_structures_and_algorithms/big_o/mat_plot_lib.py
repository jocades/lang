import matplotlib.pyplot as plt
import numpy as np


x_points = np.array([1, 6])
y_points = np.array([0, 250])


# how to change the line color
plt.plot(x_points, y_points, marker='o', color='r')


# plot another line in green dot
x_points = np.array([1, 2, 6])
y_points = np.array([3, 8, 1])
plt.plot(x_points, y_points, marker='o', color='g')
plt.show()

# this will plot a line graph with the x and y values
