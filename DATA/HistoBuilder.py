
import numpy as np
import scipy as sp
import pandas as pd
import scipy.optimize as op
import matplotlib.pyplot as plt


if __name__ == "__main__":

    plt.rcParams['figure.dpi'] = 150
    data = pd.read_csv('DATA/HashTestData.csv')

    plt.plot(data)
    # plt.bar(data.x, data.y, align='center', width=1)

    plt.show ()


    # plt.savefig('DATA/words_5000.png')

#
#     data = pd.read_csv('DATA/HashTestData.csv', header=0)
#
#     plt.bar(data.x, data.y, align='center', width=1)
#
#     plt.grid(True)
#     plt.xlim(xmin = 0, xmax = 5000)

