"""*****************************************************************************
			____
           /____ \         |  Projet : TP de Télécom 1,
           | _ _`\|        | Huffman et codage de l'information
    .-.   `| O O |         |  Auteurs : Antoine Blancy et Thomas Dagier
    | |   (- /_  -)        |
    | |    |     |         |  Descripition :
 __/  |    | \__/|         | => python3 Tris_Dagier_Blancy.py input.txt
(___) \.  _.\__. `\___     | Première partie du projet qui permet de trier
(___)  )\/  \_____/  ~\.   | le texte de différentes manières (ASCII, Fréquence)
(___) . \   `         `\   | et de calculer l'entropie, le taux de bits moyen
 (__)-    ,/        (   |  | la redondance et la quantité de décision
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 22/11/2018

*****************************************************************************"""

import math
import sys

################################################################################
####             FONCTIONS                  ####################################
################################################################################

def text_sorter_ascii(inputstring) : # tri le texte dans l'ordre ASCII
    sorted_out = sorted(input_content)
    return sorted_out


# tri le texte par nombre d'apparition des caractères
def text_sorter_apparition(inputstring) :
    sorted_out = sorted(inputstring, key = inputstring.count, reverse = True)
    return sorted_out


# tri les caractères par fréquence
def text_sorter_freq(inputstring) :
    sorted_out = dict()
    for i in range(0,len(inputstring)):
		#nombre de fois que le caractère apparait / longueur du texte
        frequence = inputstring.count(inputstring[i])  / len(inputstring)
        if not inputstring[i] in sorted_out :
            sorted_out[inputstring[i]] = frequence
	# transforme en liste de tuples et tris par ordre décroissant
    sorted_out = sorted(sorted_out.items(), key=lambda kv: kv[1], reverse=True)
    return sorted_out


# calcule l'entropie
def calculate_entropy(inputdict) :
    output = 0
    for i in sorted_freq :
        output += inputdict[i] * math.log(inputdict[i],2)
    output *= -1
    return output

################################################################################
################################################################################
################################################################################

program_file = sys.argv[0]
input_text = sys.argv[1]

input_text = open(input_text, "r")
input_content = input_text.read()

sorted_ascii = text_sorter_ascii(input_content)
output_text_ascii = open("out1.txt", "w+")

sorted_apparition = text_sorter_apparition(sorted_ascii)
output_text_apparition = open("out2.txt", "w+")

sorted_freq = text_sorter_freq(sorted_apparition)
sorted_freq_output = ""

# on convertit les caractères en hexa pour les afficher
for i in sorted_freq:
        sorted_freq_output += hex(ord(i[0])) + "  :  " + str(i[1]) + " \n"

# on retransforme la liste en dictionaire pour les prochains calculs
sorted_freq = dict(sorted_freq)


quantite_decision = math.log(len(sorted_freq), 2)

entropie = calculate_entropy(sorted_freq)

redondance = quantite_decision - entropie

taux_compression = 100 - (entropie  / quantite_decision) * 100


print("###################################\n")
print("Text original:\n")
print(input_content)

print("###################################\n")
print("Text trié:")
print(sorted_ascii)

output_text_ascii.write(''.join(sorted_ascii))
print("Fichier out1.txt créé!")

print("###################################\n")
print("Text trié dans l'ordre d'apparition:")
print(sorted_apparition)
output_text_apparition.write(''.join(sorted_apparition))
print("Fichier out2.txt créé!")

print("###################################\n")
print("Caractères et leurs fréquences d'apparition:")
print(sorted_freq_output)

print("###################################\n")
print("Entropie:" + str(entropie))
print("Quantité de decision:" + str(quantite_decision))
print("Redondance:" + str(redondance))
print("Taux de compression maximal:" + str(taux_compression) + "%\n\n\n")

input_text.close()
output_text_ascii.close()
output_text_apparition.close()
