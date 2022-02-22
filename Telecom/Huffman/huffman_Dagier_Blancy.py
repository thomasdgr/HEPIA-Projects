"""*****************************************************************************
 |\_________/|		                                               |\_________/|
 |           |		 							                   |           |
 | [°] [°]   |      									           |   [°] [°] |
 |    V      |      Nom du Programme: Encodeur Huffman             |      V    |
 |  -----    |		          				                       |    -----  |
 | |     |   |								                       |   |     | |
 | |     |   |		   						                       |   |     | |
 -ooo---ooo---											           ---ooo---ooo-
 |\_________/|          Nom du Créateur: Thomas Dagier	           |\_________/|
 |           |		 			et Antoine Blancy		           |           |
 |   [°] [°] | 		 		  							           | [°] [°]   |
 |      V    |	                Version: 1.0	    		       |    V      |
 |    -----  |										               |  -----    |
 |   |     | |										               | |     |   |
 |   |     | |	        Date de Création: 20.12.2019               | |     |   |
 ---ooo---ooo-								                       -ooo---ooo---
*****************************************************************************"""

import math
import sys
import struct
import collections

program_file = sys.argv[0]
input_text = sys.argv[1]
output_bin = sys.argv[2]

################################################################################
####             FONCTIONS                  ####################################
################################################################################

#Tri du texte dans l'ordre ASCII
def text_sorter_ascii(inputstring) :
    sorted_out = sorted(input_content)
    return sorted_out

#Tri du texte par la fréquence d'apparition
def text_sorter_apparition(inputstring) :
    sorted_out = sorted(inputstring, key = inputstring.count, reverse = True)
    return sorted_out

#Tri des caractères par la fréquence d'apparition
def text_sorter_freq(inputstring) :
    sorted_out = dict()
    for i in range(0,len(inputstring)):
        frequence = inputstring.count(inputstring[i])  / len(sorted_apparition)
        if not inputstring[i] in sorted_out :
            sorted_out[inputstring[i]] = frequence

    sorted_out = sorted(sorted_out.items(), key = lambda kv: kv[1])
    return sorted_out

#Calcul de l'entropie
def calculate_entropy(inputdict) :
    output = 0
    for i in sorted_freq :
        output += inputdict[i] * math.log(inputdict[i],2)
    output *= -1
    return output

#Trieur de dictionnaire
def dict_sorter(inputdict) :
    dictout = collections.OrderedDict(sorted(inputdict.items(),key=lambda kv:kv[1]))
    return dictout


################################################################################
################################################################################
################################################################################

alter = True

input_text = open(input_text, encoding = 'utf8')
input_content = input_text.read()

output_text = open(output_bin, "wb+")
output_content = ""

#Trié par ASCII
sorted_ascii = text_sorter_ascii(input_content)

#Trié par apparition
sorted_apparition = text_sorter_apparition(sorted_ascii)

#Trié par fréquence d'apparition (sort une liste de tuples)
sorted_freq = text_sorter_freq(sorted_apparition)

#Transformation en dictionnaire
sorted_freq = dict(sorted_freq)

#Liste de tout les caractères
sorted_keys = list(sorted_freq.keys())

#Dictionnaire qui va stocker les codes binaires des caractères
dichuffman = dict()

#Le string qui va contenir l'input encodé
huffman_output = ""

#Une copie de la liste triée par frequence dans laquelle on va faire les
#manipulation
sorted_copy = sorted_freq.copy()

#Une copie de la liste pour garder l'original pour plus tard pour calculer
#la moyenne
dic_copy = sorted_freq.copy()

#La valeur qui va stocker la moyenne
moyenne = 0

#Inistialisation du dictionnaire en y ajoutant les caractère
#en clé et des strings en valeur
for i in sorted_keys :
    dichuffman[i] = ""


#Calcule de l'entropie
entropie = calculate_entropy(sorted_freq)


#Valeurs pour les nodes combinées
tmp = ""

node1 = ""

node2= ""

while len(list(sorted_freq.keys())) > 1:
    #Tri du dictionnaire
    sorted_freq = dict_sorter(sorted_freq)

    #Attribution des valeurs des nodes
    node1 = list(sorted_freq.keys())[0]
    node2 = list(sorted_freq.keys())[1]


    #On test pour voir si les nodes contienne un des caractère
    for i in dichuffman :

        #Si on est sur la "branche" droite on attribue un 1
        if i in node1 :
            dichuffman[i] = "1" + dichuffman[i]

        #Si on est sur la "branche" gauche on attribue un 0 v
        if i in node2 :
            dichuffman[i] = "0" + dichuffman[i]
    #Fin de boucle

    #On prends le 0ème et 1er element des clés pour les concatener et créer
    #la node combinée en l'ajoutant dans le dictionnaire
    sorted_copy[list(sorted_freq.keys())[0] + list(sorted_freq.keys())[1]] = sorted_freq[list(sorted_freq.keys())[0]] + sorted_freq[list(sorted_freq.keys())[1]]

    #Combinaison des nodes
    tmp = list(sorted_freq.keys())[0] + list(sorted_freq.keys())[1]

    #Effacer les éléments qu'on a déjà pris en compte
    del sorted_freq[list(sorted_freq.keys())[1]]
    del sorted_freq[list(sorted_freq.keys())[0]]

    #On ajoute les nodes combinées pour refaire la manipulation
    sorted_freq[tmp] = sorted_copy[tmp]
#Fin de Boucle


#Impréssion des ASCII  :  Codes
for i in dichuffman:
        huffman_output += hex(ord(i)) + "  :  " + str(dichuffman[i]) + " \n"
print(huffman_output)

#Calcule de la moyenne
for i in dichuffman :
    moyenne += (len(dichuffman[i]) * dic_copy[i])
print("Taux moyen de bits par char : " + str(moyenne))


print("Entropie : " + str(entropie))
print("L'entropie doit etre inferieure ou egale au taux moyen")
print("Plus le taux moyen tend vers l'entropie, plus le codage est optimal")





for i in input_content :
    for j in list(dichuffman.keys()) :
        if i == j :
            output_content += dichuffman[j]


#Les octets qu'on va écrire dans le fichier
output_bytes = bytearray()

#La valeur des Octets qu'on va ajouter à output_bytes
byte = 0


while len(output_content) > 0 :

    #Boucle allant de 7 à 0 pour bien prendre seulement 8 valeur pour les octets
    for i in range(7, 0, -1) :
        if len(output_content) > 0 :
            #Conversion en binaire en multiplant par la puissance de i vue qu'on
            #décremente
            byte+= (int(output_content[0])) *pow(2, i)
            #On coupe les caractères déjà pris en compte
            output_content = output_content[1:]
    #On ajoute la valeur des octets
    output_bytes.append(byte)
    #On remet à Zéro avant de refaire la boucle comme il s'agit de "+="
    byte = 0

output_text.write(output_bytes)
