import matplotlib.pyplot
from matplotlib import ticker

with open('C:\\CLionProjects\\CacheWayMeasuring\\out') as file:
    pairs = [line.rstrip().split() for line in file]

x = []
y = []

for pair in pairs:
    x.append(int(pair[0]))
    y.append(int(pair[1]))

fig, ax = matplotlib.pyplot.subplots()

ax.plot(x, y, label=' ', linewidth=2, color='r')

ax.xaxis.set_major_locator(ticker.MultipleLocator(1))
ax.yaxis.set_major_locator(ticker.MultipleLocator(2))

ax.set_xlabel('Число фрагментов')
ax.set_ylabel('Время чтения элемента в тактах')
ax.legend()

matplotlib.pyplot.show()
