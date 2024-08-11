import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load data from file
data = np.loadtxt('Ising_model.dat')

# Extract beta, h, and average values
beta = data[:, 0]
h = data[:, 1]
average = data[:, 2]

# Create a grid for plotting
beta_grid, h_grid = np.meshgrid(np.unique(beta), np.unique(h))
average_grid = np.zeros(beta_grid.shape)

# Fill the grid with average values
for i, b in enumerate(np.unique(beta)):
    for j, hh in enumerate(np.unique(h)):
        index = (beta == b) & (h == hh)
        average_grid[j, i] = average[index][0]

# Plotting
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot surface
ax.plot_surface(beta_grid, h_grid, average_grid, cmap='viridis')

# Labels and title
ax.set_xlabel(r'$\beta$')
ax.set_ylabel(r'$h$')
ax.set_zlabel('Average of $x_{500}$')
ax.set_title(r'Ising Model: Average of $x_{500}$ vs $\beta$ and $h$')

plt.savefig('IsingModel.png')
plt.show()
