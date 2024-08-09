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

filename = "Normal_dist.dat"
x, y = read_data(filename)

plt.bar(x, y, width=(x[1] - x[0]), align='center', edgecolor='black', color='violet')
plt.xlabel('x values')
plt.ylabel('Frequency')
plt.title(r'Histogram of the Normal Distribution $\mathcal{N}(0,1)$')

plt.show()