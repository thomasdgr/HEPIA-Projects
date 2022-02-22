"""*****************************************************************************
			____
           /____ \         | Projet : TP sur la théorie des signaux,
           | _ _`\|        | 
    .-.   `| O O |         | Auteurs : Quentin Rod et Thomas Dagier
    | |   (- /_  -)        |
    | |    |     |         | Descripition :
 __/  |    | \__/|         | => python3 TP1_Rod_Dagier.py
(___) \.  _.\__. `\___     | Programme qui permet de déchifrer un message secret
(___)  )\/  \_____/  ~\.   | dans plusieurs fichiers wav samplés à 8192 Hz
(___) . \   `         `\   | selon un bruit généré aléatoirement
 (__)-    ,/        (   |  | 
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 31/01/2020

*****************************************************************************"""

import matplotlib.pyplot as plt
import numpy
from struct import pack,unpack
import wave as w
import math

######## Transforme un objet wave_read (une seule piste mono) en liste
def file_to_array( wave_file_object ):
    length = wave_file_object.getnframes()
    list_out = []
    for t in range(length):
        aaa = unpack( 'h' , wave_file_object.readframes(1) )       
        list_out += [ int(aaa[0]) ]
    return list_out

######## Transforme une liste en un wave_write object avec par defaut un encodage sur 16 bits et un sampling a 8192Hz
######## Attention, les valeurs dans la liste doivent etre des entiers entre -32678 et 32677.
def array_to_file( liste , name , nchannels = 1 , sampwidth = 2 , framerate = 8192 ):
    f = w.open( name ,'wb')
    f.setnchannels(nchannels)
    f.setsampwidth(sampwidth)
    f.setframerate(framerate)
    f.setcomptype('NONE', 'none')
    for k in liste:
        data = pack('h',k)
        f.writeframes(data)
    return f

############# Application du programme pour trouver le message secret
############# Ouvrir les fichiers dans le dossier 'message/' et le transformer en un fichier resultat.wav contenant le message caché :

tabResult = []
for count_file in range(0,4):
    fichier_wav = w.open('message/message_cache_noised' + str(count_file) + '.wav' ,'rb')
    
    list_sampled_values = file_to_array( fichier_wav )
    dict_ak = dict()
    dict_bk = dict()

    # calcul de a0 dont nous aurons besoin pour reconstruire le signal
    a0 = 1 * list_sampled_values[0] * 1/8192

    # calcul des ak et bk
    for k in range(100, 1900):
        resultat_ak=0
        resultat_bk=0
        for i in range(len(list_sampled_values)):
            resultat_ak += math.cos(2 * math.pi * k * i * 1/8192) * list_sampled_values[i] * 1/8192
            resultat_bk += math.sin(2 * math.pi * k * i * 1/8192) * list_sampled_values[i] * 1/8192

        resultat_ak *= 2
        resultat_bk *= 2
        # permet de filtrer les sinus qui perturbent le message
        if  resultat_ak < 100 and resultat_bk < 100:
            dict_ak[k] = resultat_ak
            dict_bk[k] = resultat_bk
        else :
            dict_ak[k] = 0
            dict_bk[k] = 0

    # reconstruction du signal sans le bruit
    for i in range(0,8192):
        resultat_point=0
        for k in dict_ak:
            resultat_point += dict_ak[k] * math.cos(2 * math.pi * k * i * 1/8192) + dict_bk[k] * math.sin(2 * math.pi * k * i * 1/8192)
        resultat_point += a0     
        resultat_point *= 100
        tabResult.append(int(resultat_point))

############# Sauver le contenu de la liste tabResult qui contient les 4 morceaux de message dans le fichier 'resultat.wav' (avec taux de sample implicite de 8192Hz):
BBB_file = array_to_file( tabResult , name = 'resultat.wav' ) 
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