import os
import matplotlib.pyplot as plt
from operator import itemgetter
import numpy as np
import math

def read_files(directory, result):
    for name in os.listdir(directory):
        print(name)
        with open(str(directory) + "/" + str(name)) as f:
            lines = f.readlines()
            print(int(lines[1][2:-1]))
            print(int(lines[2][2:-1]))
            print(float(lines[3][5:]))

            result[int(lines[1][2:-1])].append([int(lines[2][2:-1]), float(lines[3][5:])])

def calcul(result, output):
    for key in result:
        print("Avec n=" + str(key) + " et k=" + str(k) + " :")
        result[key] = sorted(result[key], key=itemgetter(0))
        for i in range(0, len(result[key]), k):
            val = 0
            for j in range(k):
                val += result[key][i+j][1]
            moyenne = round(val / k, 3)
            output[key].append([result[key][i+j][0], result[key][0][1] / (val/k)])
            print("  pour p=" + str(result[key][i+j][0]) + ", le speedup est de " + str(round(result[key][0][1] / moyenne, 3)) + ", avec un temps moyen de " + str(moyenne) + " et un écart-type de ",  end='')
            for j in range(k):
                val += math.pow(result[key][i+j][1] / moyenne, 2)
            print(round(math.sqrt((1/k) * val), 3))

def courbe(output):
    for key in output:
        xAxis = [i[0] for i in output[key]]
        yAxis = [i[1] for i in output[key]]
        #plt.plot(xAxis, xAxis, '--', color='blue', label="ideal")
        plt.plot(xAxis, yAxis, color='red', marker='o', markerfacecolor='blue', markersize=6, label="measures")
        plt.title('Speedup pour n=' + str(key))
        plt.xlabel('Nb. proc')
        plt.ylabel('Speedup')
        plt.legend(loc="upper right")
        plt.grid()
        plt.show()

def heat_map(output):
    array = []
    for key in output:
        for i in range(0, len(output[key])):
            array.append(output[key][i][1])
    array = np.asarray(array).reshape(len(N), len(P))
    heatmap = plt.pcolor(array, cmap=plt.cm.viridis)
    plt.title("Mesure de speedup")
    plt.xticks(np.arange(len(P)), P)
    plt.yticks(np.arange(len(N)), N)
    plt.colorbar(heatmap)
    plt.xlabel('Nb. proc')
    plt.ylabel('Taille du prob')
    plt.gca().invert_yaxis()
    plt.show()

P = input("Sélectionner les différentes valeurs de p:").split(",")  
N = input("Slectionner les différentes valeurs de n:").split(",")
k = int(input("Slectionner la valeur de k:"))

result = {}
output = {}
for i in range(0,len(N)):
    N[i] = int(N[i])
    result[int(N[i])] = []
    output[int(N[i])] = []

read_files("results", result)
calcul(result, output)
courbe(output)
heat_map(output)