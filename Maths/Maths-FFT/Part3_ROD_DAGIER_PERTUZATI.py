"""*****************************************************************************
			____
           /____ \         | Projet : TP sur la théorie des signaux
           | _ _`\|        | 
    .-.   `| O O |         | Auteurs : Quentin, Thomas, Gustavo
    | |   (- /_  -)        | 
    | |    |     |         | Descripition :
 __/  |    | \__/|         | => python3 Part3_ROD_DAGIER_PERTUZATI.py <filtre>
(___) \.  _.\__. `\___     | Programme qui permet de déchifrer un message secret
(___)  )\/  \_____/  ~\.   | avec une ifft / fft
(___) . \   `         `\   | 
 (__)-    ,/        (   |  | 
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 27/04/2020

*****************************************************************************"""

import matplotlib.pyplot as plt
import numpy as np
from struct import pack,unpack
from copy import deepcopy
import wave as w
import math
import pickle
import sys

def normalize( lst ):
    M = max( [ abs(k) for k in lst ] )
    return [ int( K / M * 32000 ) for K in lst ] 

def miroir(list_ck_sample):
    indiceMoitie=int(len(list_ck_sample)/2)
    list_ck_sample_result = deepcopy(list_ck_sample)
    i_milieu_pos = int(len(list_ck_sample)/4)
    for i_ck in range(1, indiceMoitie-1):
        list_ck_sample_result[i_ck] = list_ck_sample[i_milieu_pos+(i_milieu_pos-i_ck)]
    i_milieu_pos= len(list_ck_sample)-i_milieu_pos
    for i_ck in range(indiceMoitie, len(list_ck_sample)):
        if(i_milieu_pos+(i_milieu_pos-i_ck)<len(list_ck_sample) and i_milieu_pos+(i_milieu_pos-i_ck)>=indiceMoitie):
            list_ck_sample_result[i_ck] = list_ck_sample[i_milieu_pos+(i_milieu_pos-i_ck)]
    return (np.fft.ifft(list_ck_sample_result)).tolist()
    
def translation(list_ck_sample):
    print("voir le fichier tests.py car la translation ne marche pas")
    return (np.fft.ifft(list_ck_sample)).tolist()

def filtre_passe_haut(list_ck_sample):
    print("voir le fichier tests.py car le filtre passe-haut ne marche pas")
    return (np.fft.ifft(list_ck_sample)).tolist()

def racinateur_amplitude(list_ck_sample):    
    for i_ck in range(0, len(list_ck_sample)):
        list_ck_sample[i_ck] = list_ck_sample[i_ck] * np.abs(list_ck_sample[i_ck])
    return (np.fft.ifft(list_ck_sample)).tolist() 

def diviseur_phase(list_ck_sample): 
    for i_ck in range(0, len(list_ck_sample)):
        list_ck_sample[i_ck] = list_ck_sample[i_ck] * np.exp(1j * (np.angle(list_ck_sample[i_ck])))
    return (np.fft.ifft(list_ck_sample)).tolist()

############# Application du programme pour trouver le message secret
############# Ouvrir le fichier et le transformer en une image contenant le message caché :

tabResult = []
filtre = sys.argv[1]
fig = plt.figure()

with open('data/donnees.data', 'rb') as filehandle:
    message_cache = pickle.load(filehandle)
list_ck_sample = np.fft.fft(message_cache)

if filtre == "miroir":
    tabResult = miroir(list_ck_sample)
elif filtre == "racinateur_amplitude":
    tabResult = racinateur_amplitude(list_ck_sample)
elif filtre == "passe_haut":
    tabResult = filtre_passe_haut(list_ck_sample)
elif filtre == "translation":
    tabResult = translation(list_ck_sample)
elif filtre == "diviseur_phase":
    tabResult = diviseur_phase(list_ck_sample)
else:
    print("erreur d'argument")
    tabResult = list_ck_sample

plt.plot( np.real(tabResult) , np.imag(tabResult) , '-' , color = 'r' , lw = 2 )
plt.show()
