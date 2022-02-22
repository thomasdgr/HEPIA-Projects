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
            result[int(lines[1][2:-1])].append([int(lines[2][2:-1]), float(lines[3][5:])])

def calcul(result, output):
    for key in result:
        print("Avec un matrice de taille " + str(key) + "*" + str(key) + " et " + str(n) + " itérations : (moyenne sur " + str(k) + " executions)")
        result[key] = sorted(result[key], key=itemgetter(0))
        temps_sequentiel = 0
        for i in range(0, len(result[key])-1, k):
            val = 0
            for j in range(k):
                val += result[key][i+j][1]
            moyenne = round(val / k, 3)
            if i == 0:
                temps_sequentiel = moyenne
            output[key].append([result[key][i+j][0], temps_sequentiel / (val/k)])
            print("|" + str(result[key][i+j][0]) + "|" + str(round(temps_sequentiel / moyenne, 3)) + "|" + str(moyenne) + "|",  end='')
            for j in range(k):
                val += math.pow(result[key][i+j][1] / moyenne, 2)
            print(round(math.sqrt((1/k) * val), 3))

def courbe(output):
    for key in output:
        xAxis = [i[0] for i in output[key]]
        yAxis = [i[1] for i in output[key]]
        plt.plot(xAxis, yAxis, marker='o', markersize=6, label=key)
        plt.title('Speedup des matrices pour ' + str(n) + ' itérations')
        plt.xlabel('Nb. proc')
        plt.ylabel('Speedup')
        plt.legend(loc="upper right")
        plt.grid()
    plt.plot(xAxis, xAxis, '--', color='blue', label="ideal")
    plt.legend(loc="upper right")
    plt.show()

def heat_map(output):
    array = []
    for key in output:
        for i in range(0, len(output[key])):
            array.append(output[key][i][1])
    array = np.asarray(array).reshape(len(I), len(P))
    heatmap = plt.pcolor(array, cmap=plt.cm.viridis)
    plt.title('Speedup des matrices pour ' + str(n) + ' itérations')
    plt.xticks(np.arange(len(P)), P)
    plt.yticks(np.arange(len(I)), I)
    plt.colorbar(heatmap)
    plt.xlabel('Nb. proc')
    plt.ylabel('Taille du prob (Nb. lignes)')
    plt.gca().invert_yaxis()
    plt.show()

def print_matrix(path):
    mat = []
    with open(path) as f:
        lines = f.readlines()
        for item in lines:
            mat.append(list(map(float, item.split())))
    colormesh = plt.pcolormesh(mat, cmap=plt.cm.jet, shading='gouraud')
    plt.colorbar(colormesh)
    plt.title("Colormesh de la matrice après 1'000 itérations")
    plt.xlabel('Nb. lignes')
    plt.ylabel('Nb. colonnes')
    plt.style.use('classic')
    plt.show()

def theorical():
    P = [1,2,4,8,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256]
    I = [500,1000,5000,10000]
    kek = {}
    for item in I:
        kek[item] = []
        for item2 in P:
            speedup = curve(item2, item, item, 1000)
            kek[item].append([item2, speedup])
    courbe(kek)

# 0.0008
def curve(p, m, n, iterration, Ta=1, C=10):
    K = C * m * 2 # temps de comm pour échanger des données C * (2 sends) dans le cas le plus lent
    petite_matrice = n / p + 1 # pire cas possible: chaque petites matrices possède n / p + 1 lignes
    une_etape = petite_matrice * (m-2) * Ta + K # le temps pris pour faire une fois la convolution
    tp = une_etape * iterration + (C * (n-1) * 2)# le temps total en parallèle + le temps du scatterv et gatherv
    ts = (m-2) * (n-2) * Ta * iterration # le temps total en séquentiel
    return (ts / tp) 

## MAIN

#P = [1,2,4,8,16,32,64,128,256]
#n = 1000
#I = [500,1000,5000]
#J = [500,1000,5000]

#I = [100,500,1000,5000,10000,15000]
#J = [100,500,1000,5000,10000,15000]

file = input("Sur quel set faire les tests ? (Baobab ou Yggdrasil): ")

P = [1,2,4,8,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256]
n = 10000
result = {}
output = {}
I = [500,1000,5000,10000]
for i in range(0,len(I)):
    result[int(I[i])] = []
    output[int(I[i])] = []
J = [500,1000,5000,10000]
k = 4

#theorical()

read_files("../results_clusters/results" + str(file), result)
result[10000], result[5000] = result[5000], result[10000]

calcul(result, output)
courbe(output)
heat_map(output)
#print_matrix("laplace.txt")
#print_matrix("results/v2.txt")
