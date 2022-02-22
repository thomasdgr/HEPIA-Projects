"""*****************************************************************************
			____
           /____ \         | Projet : TP sur le chiffrement et le hachage dans
           | _ _`\|        |          le cadre du cours sur la blockchain
    .-.   `| O O |         | Auteurs : Antoine BLANCY, Thomas DAGIER 
    | |   (- /_  -)        |
    | |    |     |         | Descripition :
 __/  |    | \__/|         | python myencry_DAGIER_BLANCY.py -c in_file.bin
(___) \.  _.\__. `\___     | ou
(___)  )\/  \_____/  ~\.   | python myencry_DAGIER_BLANCY.py -d in_file.bin.en
(___) . \   `         `\   | 
 (__)-    ,/        (   |  | 
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 8/05/2020

*****************************************************************************"""

from cryptography.fernet import Fernet as fernet
import hashlib
import sys


#Fonction de chiffrement
#Arguments: cle: Une clé comme: "b'...'", 
#           input_data: des données en bytes
#
#Retourne:  des données (bytes) chiffrées avec la clé
def chiffrer (cle, input_data): 
    cle_fernet = fernet(cle)
    fernet.__init__(cle_fernet, cle)
    return fernet.encrypt(cle_fernet, input_data)


#Fonction de déchiffrement
#Arguments: cle: Une clé comme: "b'...'", 
#           input_data: des données chiffrées (en bytes)
#
#Retourne:  des données (bytes) déchiffrées avec la clé
def dechiffrer (cle, input_data):
    cle_fernet = fernet(cle)
    fernet.__init__(cle_fernet, cle)
    return fernet.decrypt(cle_fernet, input_data)


#Fonction de hashage
#Arguments: data: des données à hasher (en bytes)
#
#Retourne:  Le Hash des données en Hexadécimal
def hashage(data):
    h = hashlib.sha224(bytes(data)).hexdigest()
    return hex(int(h, 16))


#Clé fournie dans l'énoncée
KEY = b'HehUbvgn6GrbwyVEc2mgT8FoAXlrwGUHMOpeIu9R0jY='


#Gestion des fichiers
try:
    input_file = open(sys.argv[2], 'rb')
except:
    print("Le fichier spécifié n'existe pas, ou n'est pas accessible.\n")
    exit()
input_bytes = bytes(input_file.read())
input_file.close()
output_name = str(sys.argv[2])

if sys.argv[1] == "-c":
    #Chiffrement
    print("Hash du fichier non-chiffré: " + str(hashage(input_bytes)))
    output_bytes = chiffrer(KEY, input_bytes)
    output_name +=".en"
elif sys.argv[1] == "-d":
    #Déchiffrement
    output_bytes = dechiffrer(KEY, input_bytes)
    output_name = output_name[:-3]

    #Lecture du hash donné pas l'utilisateur
    user_input = input("Veuillez entrer le hash en hexadécimal: ")
    user_hash = hex(int(user_input, 16))

    #Comparaison des hash
    if hashage(output_bytes) == user_hash:
        print("Le hash correspond à celui du fichier décrypté.\n")
    else:
        print("Le fichier décrypté n'a pas le bon hash.\n")
else:
    print("Erreur d'argument, utilisez -c ou -d")
    exit()


output_file = open(output_name, 'wb+')
output_file.write(output_bytes)
output_file.close()