import os
import matplotlib.pyplot as plt
from operator import itemgetter
import numpy as np
import math
import sys

def read_files(directory, result):
    for name in os.listdir(directory):
        with open(str(directory) + "/" + str(name)) as f:
            lines = f.readlines()
            k = int(lines[2][2:-1])
            if k not in result:
                result[k] = []
            result[k].append([int(lines[0][2:-1]), int(lines[1][2:-1]), float(lines[3][5:])])


def calcul(result, ecart_type):
    k = 5
    j = 0
    for key in result:
        result[key] = sorted(result[key], key=itemgetter(1))
        for i in range(0,len(result[key]),5):
            #print(result[key][i][2], ",", result[key][i+1][2], ",", result[key][i+2][2], ",", result[key][i+3][2], ",", result[key][i+4][2])
            moyenne = (result[key][i][2] + result[key][i+1][2] + result[key][i+2][2] + result[key][i+3][2] + result[key][i+4][2]) / k
            print("| ", key, " | ", result[key][i][0], "*", result[key][i][1], " | ", round(moyenne,4), " | ", ecart_type[j])
            j+=1


def print_matrix(path):
    mat = []
    with open(path) as f:
        lines = f.readlines()
        for item in lines:
            mat.append(list(map(float, item.split())))
    colormesh = plt.pcolormesh(mat, cmap=plt.cm.jet, shading='gouraud')
    plt.colorbar(colormesh)
    plt.title("Colormesh de la matrice après 1'000'000 itérations")
    plt.xlabel('Nb. lignes')
    plt.ylabel('Nb. colonnes')
    plt.style.use('classic')
    plt.show()


results = {}
#ecart_type = [0.03, 0.16, 0.38, 1.10, 0.06, 0.17, 0.48, 0.12, 0.13, 0.27, 0.23, 0.58]
#read_files("results", results)
#calcul(results, ecart_type)

print_matrix("results/" + sys.argv[1])