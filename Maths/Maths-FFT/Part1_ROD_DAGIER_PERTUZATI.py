"""*****************************************************************************
			____
           /____ \         | Projet : TP sur la théorie des signaux,
           | _ _`\|        | 
    .-.   `| O O |         | Auteurs : Quentin, Thomas, Gustavo
    | |   (- /_  -)        |
    | |    |     |         | Descripition :
 __/  |    | \__/|         | => python3 Part1_ROD_DAGIER_PERTUZATI.py
(___) \.  _.\__. `\___     | Programme qui permet de déchifrer un message secret
(___)  )\/  \_____/  ~\.   | avec une fft
(___) . \   `         `\   | 
 (__)-    ,/        (   |  | 
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 27/04/2020

*****************************************************************************"""

import matplotlib.pyplot as plt
import numpy as np
from struct import pack,unpack
import wave as w
import math

######## Transforme un objet wave_read (une seule piste mono) en liste
def file_to_array( wave_file_object ):
    length = wave_file_object.getnframes()
    list_out = []
    for t in range(length):
        aaa = unpack('h', wave_file_object.readframes(1))       
        list_out += [int(aaa[0])]
    return list_out

######## Transforme une liste en un wave_write object avec par defaut un encodage sur 16 bits et un sampling a 8192Hz
######## Attention, les valeurs dans la liste doivent etre des entiers entre -32678 et 32677.
def array_to_file(liste, name, nchannels = 1, sampwidth = 2, framerate = 8192):
    f = w.open( name ,'wb')
    f.setnchannels(nchannels)
    f.setsampwidth(sampwidth)
    f.setframerate(framerate)
    f.setcomptype('NONE', 'none')
    for k in liste:
        data = pack('h',int(k))
        f.writeframes(data)
    return f

############# Application du programme pour trouver le message secret
############# Ouvrir les fichiers dans le dossier 'message/' et appliquer une fft pour trouver le message caché :

tabResult = []
for count_file in range(0,4):
    fichier_wav = w.open('message/message_cache_noised' + str(count_file) + '.wav' ,'rb')
    
    list_sampled_values = file_to_array( fichier_wav )
    list_ck_sample= np.fft.rfft(list_sampled_values)
    list_ck_sample[0:100]=0
    list_ck_sample[1901:]=0
    for i_ck in range(len(list_ck_sample)):
        if abs(list_ck_sample[i_ck]/8192)>100 :
            list_ck_sample[i_ck]=0
        list_ck_sample[i_ck] = list_ck_sample[i_ck]*100
    tabResult+= np.fft.irfft(list_ck_sample).tolist()

############# Sauver le contenu de la liste tabResult dans le fichier 'resultat_part1.wav'
BBB_file = array_to_file(tabResult , name = 'resultat_Part1.wav' )
BBB_file.close()

############# Si besoin, affichage des valeurs du dernier fichier avec puis sans le bruit dans l'intervalle des fréquences qui nous concerne
'''t = [k/8192 for k in range(1900)]
plt.figure()
plt.plot( t , list_sampled_values[:1900])
plt.show()

t = [k/8192 for k in range(1900)]
plt.figure()
plt.plot( t , tabResult[:1900])
plt.show()'''