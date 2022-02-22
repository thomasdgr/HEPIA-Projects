import matplotlib.pyplot as plt
import numpy as np
import PIL
import sys
import math
from PIL import Image
from typing import List, Tuple


# convolution d'une image {img} à partir d'un kernel {ker}
# retourne le résultat {res} de la convolution
def linear_ker(img: np.ndarray, ker: np.ndarray) -> np.ndarray:
    # res est une matrice de la même taille que img mais remplit de 0
    res = img * 0
    # déterminer le milleu du kernel
    x, y = ker.shape
    kx = int(x / 2)
    ky = int(y / 2)
    # application de la convolution
    for i in range(-kx, kx + 1):
        # on fait un shift sur l'image (décallage des éléments du tableau)
        img_right = np.roll(img, i, axis=0)
        for j in range(-ky, ky + 1):
            # puis un shift dans le sens opposé
            img_right_left = np.roll(img_right, j, axis=1)
            res = res + ker[i + kx, j + ky] * img_right_left
    return res


# filtre moyenneur sur une image {img} avec un kernel de taille {k}
# retourne la nouvelle image floutée {res}
def kernel_average(img: np.ndarray, k: int) -> np.ndarray:
    blur = [1 / (k * k)] * k * k
    ker = np.asarray(blur).reshape((k, k))
    res = linear_ker(img, ker)
    return res


# application du filtre de sobel sur une image {img}
# retourne la nouvelle image {res}, binarisée avec la détéction des contours
# selon un seuil {threshold}
def sobel(img: np.ndarray, threshold: float = 0.1) -> np.ndarray:
    # création des filtres horizontaux et verticaux
    hor = [-1, 0, 1, -2, 0, 2, -1, 0, 1]
    ker_h = np.array(hor).reshape((3, 3))
    ver = [-1, -2, -1, 0, 0, 0, 1, 2, 1]
    ker_v = np.array(ver).reshape((3, 3))
    # application du filtre moyenneur
    img = kernel_average(img, 3)
    # convolutions sur les filtres horizontaux et verticaux
    new_img_h = linear_ker(img, ker_h)
    new_img_v = linear_ker(img, ker_v)
    # application de sobel
    sobel_img = np.sqrt(np.square(new_img_h) + np.square(new_img_v))
    sobel_img *= 255.0 / sobel_img.max()
    # binarisation du résultat (plus simple pour hough)
    seuil = np.average(sobel_img) + np.max(sobel_img) * threshold
    res = np.where(sobel_img > seuil, 1, 0)
    return res


# algorithme de hough sur une image {img}
# retourne l'accumulateur de hough et une liste des "bonnes" droites de l'image
# selon un seuil de séléction {seuil_accumulateur}
def hough_lines(img: np.ndarray, angle_step: int = 1, seuil_accumulateur: float = 0.5) -> Tuple[np.ndarray, List[Tuple[int, int]]]:
    # tableau de tous les thetas en fonction de {angle_step}
    thetas = np.deg2rad(np.arange(0, 360, angle_step))
    width, height = img.shape
    lines_eq = list()
    # calcul de la diagonale (le rho maximum dans l'image)
    diag = np.ceil(np.sqrt(width * width + height * height))
    # création de l'accumulateur
    accumulator = np.zeros((int(diag), len(thetas)), dtype=int)
    # parcours de la matrice
    it = np.nditer(img, flags=["multi_index"])
    while not it.finished:
        x, y = it.multi_index
        # si le pixel courrant est blanc
        if img[x][y] == 1:
            # on calcul toutes les equations de droites autour de ce point
            for i in range(0, 360, angle_step):
                theta = i * (math.pi / 180)
                rho = round(y * math.cos(theta) + x * math.sin(theta))
                # on met a jour l'accumulateur
                accumulator[rho, i] += 1
        it.iternext()

    # parcours de l'accumulateur
    it = np.nditer(accumulator, flags=["multi_index"])
    # seuil de conservation de l'équation de droite
    seuil = np.average(accumulator) + (np.max(accumulator) * seuil_accumulateur)
    while not it.finished:
        rho, angle = it.multi_index
        # si le nombre stocké dépasse le seuil
        if accumulator[rho, angle] > seuil:
            tup = (rho, int(angle))
            # on ajoute l'equation de droite dans la liste
            lines_eq.append(tup)
        it.iternext()
    return accumulator, lines_eq


# affiche avec matplotlib l'image originale, l'image binarisée après sobel,
# l'accumulateur de hough et les droites qui ont été détéctées
def show_hough(img: np.ndarray, img_processed: np.ndarray, accumulator: np.ndarray, lines_eq: List[Tuple[int, int]],) -> None:
    w = 20
    h = 20
    fig = plt.figure(figsize=(8, 8))
    columns = 2
    rows = 2
    # affichage des 4 subplots
    for i in range(1, columns * rows + 1):
        fig.add_subplot(rows, columns, i)
        if i == 1:
            plt.imshow(img)
            plt.axis("off")
            plt.title("Image originale")
        if i == 2:
            plt.imshow(img_processed, cmap=plt.cm.gray)
            plt.axis("off")
            plt.title("Image binarisée")
        if i == 3:
            plt.imshow(accumulator)
            plt.title("Accumulateur de hough")
        if i == 4:
            # conversion des equations de droites
            lines_keq = transform_lines_eq(lines_eq)
            # les rhos et thetas deviennent les A et B
            height, width = img_processed.shape
            x = np.linspace(0, width)
            for igrek in lines_keq:
                if igrek[0] == 1000000:
                    plt.vlines(x=igrek[1], ymin=height, color="blue", ymax=0)
                else:
                    plt.plot(x, x * igrek[0] + igrek[1], color="blue", linewidth=1)
            plt.axis("off")
            plt.title("Résultat")
            plt.imshow(img)
    plt.show()


# modifie les coefficients dans la liste des droite (et évite les divisons par 0)
# retourne la même liste des equations de droites mais avec les nouveaux coefficients (A et B)
def transform_lines_eq(lines_eq: List[Tuple[int, int]]) -> List[Tuple[float, float]]:
    lines_keq = list()  # type: List[Tuple[float, float]]
    for i in range(0, len(lines_eq)):
        rho, theta = lines_eq[i]
        angle = theta * (math.pi / 180)
        # on vérifie la valeur du sin avant de faire la division
        if math.sin(angle) != 0:
            a = (math.cos(angle) / math.sin(angle)) * -1
            b = rho / math.sin(angle)
        # si le sin vaut 0 c'est une droite verticale
        else:
            # on abuse le coefficient pour se raprocher d'une droite verticale
            a = 1000000
            b = rho
        # remplace le couple de coefficients dans la lsite
        tup = (a, b)
        lines_keq.append(tup)
    return lines_keq




##### MAIN #####

# lecture de l'argument
try:
    input_img = Image.open(sys.argv[1])
    img = np.array(input_img)
    seuil_binaire = float(sys.argv[2])
    seuil_accumulateur = float(sys.argv[3])
except:
    print("\nExemple d'utilisation du programme:\n poetry run python3 labo1/hough.py labo1/chess.py 0.1 0.5")
    sys.exit(0)

# image en nuances de gris
rgb_weights = [0.2989, 0.5870, 0.1140]
grey_img = np.dot(img[..., :3], rgb_weights)

# application du filtre sobel + binarisation
new_img = sobel(grey_img, seuil_binaire)

# obtention des droites et de l'accumulateur
accumulator, lines_eq = hough_lines(new_img, 1, seuil_accumulateur)

# Affichage des images et des résultats
show_hough(img, new_img, accumulator, lines_eq)