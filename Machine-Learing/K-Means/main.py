
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
            ____
           /____ \         | Projet :  Clustering, K-Means
           | _ _`\|        |        
    .-.   `| O O |         | Auteurs : Thomas DAGIER, Gustavo PERTUZATI
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Utiliser les notions abordées en
(___)  )\/  \_____/  ~\.   |                cours pour implémenter la méthode
(___) . \   `         `\   |                de clustering k-means
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 07/10/2021
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

import matplotlib.pyplot as plt
import numpy as np
import sys
import math
import random
from typing import List, Tuple

# retourne un nuage de "size" points compris entre 0 et "max"
def generate_cloud(max, size):
    return np.random.randint(max, size = (size, 2)) 

# affichage du nuage de points en fonction des clusters
# met aussi en évidence les différents barycentres
def show_clusters(clusters, bary):
    colors = {0:'red',1:'green',2:'blue', 3:'yellow', 4:'purple'}
    index = 0
    # nuages de points
    for key in clusters:
        array = clusters.get(key)
        for data in array:
            x, y = data
            plt.scatter(x, y, color = colors.get(index, 'black'))
        index += 1
    # barycentres
    for data in bary:
        x, y = data
        plt.scatter(x, y, color = 'black')
    plt.show()

# si "iter" = false, les barycentres sont des points du nuage choisis aléatoirements
# si "iter" = true, les coordonnées des points sont les moyennes de ceux des clusters en x et en y
def barycentre(points, nb_clusters, iter = False):
    bary = []
    for i in range(nb_clusters):
        bary.append(np.average(clusters[i], axis=0) if iter else random.choice(points))
    return bary

# application du clustering k-means en fonction du nuage et des barycentres
# retourne un dictionnaire de clusters
def sort_points(points, bary):
    clusters = {}
    for i in range(nb_clusters):
        clusters[i] = []
    for data in points:
        euc_dist = []
        for i in range(len(clusters)):
            x1, y1 = data
            x2, y2 = bary[i]
            euc_dist.append(np.linalg.norm(x1 - x2) + np.linalg.norm(y1 - y2))
        clusters[euc_dist.index(min(euc_dist))].append(data)
    return clusters

# retourne false si les clusters sont égaux, true sinon
def compare_cluster(clusters, tmp, nb_clusters):
    for index in clusters:
        array1 = clusters.get(index)
        array2 = tmp.get(index)
        if len(array1) == len(array2):
            for i in range(len(array1)):
                if not (array1[i] == array2[i]).all():
                    return True
        else:
            return True
    return False

def variance(clusters, bary, nb_points):
    L = 0
    for index in clusters:
        array = clusters.get(index)
        for value in array:
            x1, y1 = value
            x2, y2 = bary[index]
            L += math.pow(np.linalg.norm(x1 - x2) + np.linalg.norm(y1 - y2), 2)
    return L / nb_points

##### MAIN #####
try:
    nb_clusters = int(sys.argv[1])
except:
    print("\nExemple d'utilisation du programme:\n python3 main.py 2")
    sys.exit(0)

nb_points = 1000
cloud = generate_cloud(100, nb_points)
bary = barycentre(cloud, nb_clusters)
clusters = sort_points(cloud, bary)
bary = barycentre(clusters, nb_clusters, True)
show_clusters(clusters, bary)
test = True
# si le clustering n'a rien changé à l'étape X, on considère que l'alogrithme est terminé et on quitte
while test:
    tmp = clusters
    clusters = sort_points(cloud, bary)
    bary = barycentre(clusters, nb_clusters, True)
    test = compare_cluster(clusters, tmp, nb_clusters)
    show_clusters(clusters, bary)
print("variance : " + str(variance(clusters, bary, nb_points)))