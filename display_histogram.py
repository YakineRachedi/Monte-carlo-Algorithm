import matplotlib.pyplot as plt

def read_data(filename):
    x = []
    y = []
    file = open(filename, 'r')
    lines = file.readlines()
    for line in lines:
        cols = line.split()
        x.append(float(cols[0]))
        y.append(float(cols[1]))
    return x,y

# Read data from files
filename_normal_dist = "Normal_dist.dat"
filename_chi2_3 = "Chi2_first_example.dat"
filename_chi2_6 = "Chi2_second_example.dat"

x_normal_dist, y_normal_dist = read_data(filename_normal_dist)
x_chi2_3, y_chi2_3 = read_data(filename_chi2_3)
x_chi2_6, y_chi2_6 = read_data(filename_chi2_6)


# Histogram for the normal distribution
plt.bar(x_normal_dist, y_normal_dist, width=(x_normal_dist[1] - x_normal_dist[0]), align='center', edgecolor='black', color='violet')
plt.xlabel('x values')
plt.ylabel('Frequency')
plt.title(r'Histogram of the Normal Distribution $\mathcal{N}(0,1)$')
plt.savefig('Normal_distribution.png')
plt.show()

# Histogram for the Chi-Squared distribution with 3 degrees of freedom
plt.bar(x_chi2_3, y_chi2_3, width=(x_chi2_3[1] - x_chi2_3[0]), align='center', edgecolor='black', color='green', alpha=0.6, label='Chi-Squared (3 degrees)')
plt.xlabel('x values')
plt.ylabel('Frequency')
plt.title(r'Histogram of $\chi^2$ with 3 degrees of freedom')

# Histogram for the Chi-Squared distribution with 6 degrees of freedom
#ax2.bar(x_chi2_6, y_chi2_6, width=(x_chi2_6[1] - x_chi2_6[0]), align='center', edgecolor='black', color='yellow')
bar_width = (x_chi2_3[1] - x_chi2_3[0]) * 0.9  # Slightly reduce width to avoid overlap
plt.bar([xi + bar_width/2 for xi in x_chi2_6], y_chi2_6, width=bar_width, align='center', edgecolor='black', color='yellow', alpha=0.6, label='Chi-Squared (6 degrees)')
plt.xlabel('x values')
plt.ylabel('Frequency')
plt.title(r'Histogram of $\chi^2$ with 6 degrees of freedom')
plt.xlim(0,10)
plt.legend()

plt.tight_layout()
plt.savefig('Chi2_distributions.png')
plt.show()