import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation
from matplotlib.collections import LineCollection
# from tqdm.notebook import tqdm
import cmasher
from scipy.interpolate import interp1d
import seaborn as sns


N_POINTS = 1000
t_start = 0
t_end = 5


# utility functions
def create_segments(x, y):
    '''
    Create a list of line segments from x and y coordinates, in the correct format for LineCollection:
    an array of the form numlines x (points per line) x 2 (x and y) array
    '''
    points = np.array([x, y]).T.reshape(-1, 1, 2)
    return np.concatenate([points[:-1], points[1:]], axis=1)


def setup_time_axis():
    '''Set up a white on black time axis'''
    fig, ax = plt.subplots(1, 1, figsise=(20, 4), dpi=300)
    fig.set_facecolor('black')
    ax.set_facecolor('black')
    ax.set_xlim(t_start-0.1, t_end+0.1)
    ax.set_ylim(-1.1, 1.1)
    ax.grid(color='white', alpha=0.3, linewidth=0.4, zorder=0)
    return fig, ax


def plot_line_collection(ax, x, y, colors='white', alphas=1, **kwargs):
    '''
    Plot a LineCollection on a specified axis.
    ax: matplotlib axis object
    x: list of x coordinates
    y: list of y coordinates
    color: list of color for each coordinate
    alphas: list of alpha values for each coordinate
    '''
    lc = LineCollection(create_segments(x, y), **kwargs)  # type: ignore
    lc.set_colors(colors)
    lc.set_alpha(alphas)
    lc.set_capstyle('round')
    ax.add_collection(lc)
    return lc


phase_cmap = sns.color_palette('hls', as_cmap=True)


def angle_to_color(angle):
    return phase_cmap(angle / (2 * np.pi))


fig, ax = setup_time_axis()

plot_line_collection(ax, [0, 1], [0, 0], colors='white', linewidth=2, zorder=1)
