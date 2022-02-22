"""*****************************************************************************
			____
           /____ \         | Projet : TP sur la théorie des signaux,
           | _ _`\|        | 
    .-.   `| O O |         | Auteurs : Quentin, Thomas, Gustavo
    | |   (- /_  -)        |
    | |    |     |         | Descripition :
 __/  |    | \__/|         | => python3 Part2_ROD_DAGIER_PERTUZATI.py <filtre>
(___) \.  _.\__. `\___     | Programme qui permet de déchifrer un message secret
(___)  )\/  \_____/  ~\.   | avec une rfft / irfft
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
import sys

def file_to_array( wave_file_object ):
    length = wave_file_object.getnframes()
    list_out = []
    for t in range(length):
        aaa = unpack('h', wave_file_object.readframes(1))       
        list_out += [int(aaa[0])]
    return list_out

def array_to_file(liste, name, nchannels = 1, sampwidth = 2, framerate = 44100):
    f = w.open( name ,'wb')
    f.setnchannels(nchannels)
    f.setsampwidth(sampwidth)
    f.setframerate(framerate)
    f.setcomptype('NONE', 'none')
    for k in liste:
        data = pack('h',int(k))
        f.writeframes(data)
    return f

def normalize( lst ):
    M = max( [ abs(k) for k in lst ] )
    return [ int( K / M * 32000 ) for K in lst ] 

def miroir(list_ck_sample):
    print("voir le fichier tests.py car le mirroir ne marche pas")
    return (np.fft.irfft(list_ck_sample)).tolist()

def translation(list_ck_sample):
    list_ck_sample_result = list_ck_sample
    length_list_ck=len(list_ck_sample)
    freqSignal= 44100/(length_list_ck*2)
    for i_ck in range(length_list_ck):
        list_ck_sample_result[i_ck] = list_ck_sample[int(i_ck+(4000/freqSignal))%length_list_ck]
    return (np.fft.irfft(list_ck_sample_result)).tolist()

def echange_amp_deph(list_ck_sample,list_ck_sample_two):
    list_amp_one = 2*np.abs(list_ck_sample)
    list_amp_two = 2*np.abs(list_ck_sample_two)
    list_deph_one = np.angle(list_ck_sample)
    list_deph_two = np.angle(list_ck_sample_two)
    for i_ck in range(len(list_ck_sample)):
        list_ck_sample[i_ck] = list_amp_one[i_ck]*np.exp(1j*list_deph_two[i_ck])
        list_ck_sample_two[i_ck] = list_amp_two[i_ck]*np.exp(1j*list_deph_one[i_ck]) 
    
    list_real = np.fft.irfft(list_ck_sample)
    list_real_two = np.fft.irfft(list_ck_sample_two)
    tabResult = list_real.tolist() + list_real_two.tolist()
    return tabResult 

def saute_mouton(list_ck_sample,list_ck_sample_two): 
    compteurChoix=1
    choix=0
    list_ck_f1= []
    list_ck_f2= []
    for i in range(len(list_ck_sample)):
        if choix==0:
            list_ck_f1.append(list_ck_sample[i])
        else:
            list_ck_f1.append(list_ck_sample_two[i])
        if compteurChoix == 10:
            choix = not choix
            compteurChoix=0
        compteurChoix+=1
        
    compteurChoix=1
    choix=1
    for i in range(len(list_ck_sample)):
        if choix == 0:
            list_ck_f2.append(list_ck_sample[i])
        else:
            list_ck_f2.append(list_ck_sample_two[i])
        if compteurChoix == 10:
            choix = not choix
            compteurChoix = 0
        compteurChoix += 1
    
    list_real = (np.fft.irfft(np.asarray(list_ck_f1)).tolist())
    list_real_two = (np.fft.irfft(np.asarray(list_ck_f2)).tolist())
    tabResult = list_real_two + list_real
    return tabResult

############# Application du programme pour trouver le message secret
############# Ouvrir les fichiers et le transformer en un fichier resultat.wav contenant le message caché :

tabResult = []
filtre = sys.argv[1]

fichier_wav = w.open('message/message_part_1.wav', 'rb')
list_sampled_values = file_to_array(fichier_wav)
list_ck_sample = np.fft.rfft(list_sampled_values)

fichier_wav_two = w.open('message/message_part_2.wav', 'rb')
list_sampled_values_two = file_to_array(fichier_wav_two)
list_ck_sample_two = np.fft.rfft(list_sampled_values_two)

#Pour les autres transformations, tester avec les exemples dans le dossier message/<file>
if filtre == "miroir":
    tabResult = miroir(list_ck_sample) + miroir(list_ck_sample_two)
elif filtre == "echange_amp_deph":
    tabResult = echange_amp_deph(list_ck_sample,list_ck_sample_two)
elif filtre == "translation":
    tabResult = translation(list_ck_sample) + translation(list_ck_sample_two)
elif filtre == "saute_mouton":
    tabResult = saute_mouton(list_ck_sample,list_ck_sample_two)
else:
    print("erreur d'argument")
    exit(0)
############# Sauver le contenu de la liste tabResult dans le fichier 'resultat.wav'
BBB_file = array_to_file(normalize(tabResult) , name ='resultat_Part2.wav')
BBB_file.close()

############# Si besoin, affichage des valeurs du dernier fichier avec puis sans le bruit
'''t = [k/8192 for k in range(1900)]
plt.figure()
plt.plot( t , list_sampled_values[:1900])
plt.show()

t = [k/8192 for k in range(1900)]
plt.figure()
plt.plot( t , tabResult[:1900])
plt.show()'''