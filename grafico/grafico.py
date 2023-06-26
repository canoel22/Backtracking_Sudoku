import csv
from matplotlib import pyplot as plt
from matplotlib.ticker import ScalarFormatter


def plot_graph(title, file, types):
    x_points = []
    y_points = []
    x_label = ''
    y_label = ''

    with open(file) as file:
        csv_reader = csv.reader(file, delimiter=',')
        line = 0

        for row in csv_reader:
            if line == 0:
                x_label = row[0]
                y_label = row[1]
            else:
                x_points.append(types[0](row[0]))
                y_points.append(types[1](row[1]))
            line += 1

    plt.bar(x_points, y_points, color ='pink', width = 0.4, log=True)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(title)
    plt.show()


def plot_exec_time_per_instance_graph():
   plot_graph('Execution Time x Instance', './exec_time.csv', [str, float])


def plot_operations_per_instance_graph():
    plot_graph('Operation x Instance', './operations.csv', [str, int])
    

if __name__ == '__main__':
    plot_exec_time_per_instance_graph()
    plot_operations_per_instance_graph()