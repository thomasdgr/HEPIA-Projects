"""*******************************************************************************
			____
           /____ \         | Projet : TP sur le chiffrement et le hachage dans
           | _ _`\|        |          le cadre du cours sur la blockchain
    .-.   `| O O |         | Auteurs : Antoine BLANCY, Thomas DAGIER 
    | |   (- /_  -)        |
    | |    |     |         | Descripition :
 __/  |    | \__/|         | python blockchain_DAGIER_BLANCY.py <path_to_block_0>
(___) \.  _.\__. `\___     | 
(___)  )\/  \_____/  ~\.   | 
(___) . \   `         `\   | 
 (__)-    ,/        (   |  | 
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 5/06/2020

******************************************************************************"""

from datetime import datetime
import hashlib
from string import digits
import sys

class Block:


    #Fonction d'initialisation de l'objet
    #Arguments: timestamp: date d'ajout du block
    #           header_hash: hash de l'en-tête (sha256)
    #           content_hash: hash du contenu (sha256)
    #           nonce_len: nombre d'octets pour écrire le nonce
    #           nonce: preuve de travail
    #           content: contenu du fichier stocké dans le block 
    #
    #Retourne:  un objet pouvant être rempli
    def __init__(self, timestamp, header_hash, content_hash, nonce_len, nonce, content):
        self.timestamp = timestamp
        self.header_hash = header_hash
        self.content_hash = content_hash
        self.nonce_len = nonce_len
        self.nonce = nonce
        self.content = content
    

    #Fonction de lecture d'un byte array pour stocker le contenu dans un block
    #Arguments: self: l'objet à remplir
    #           input_block: byte array récupéré lors de la lecture du fichier
    #
    #Retourne:  un objet contenant toutes les informations nécéssaires pour valider la blockchain
    def Block_read(self, input_block):
        start_index = 0
        end_index = 4
        #On lit les octets de l'input allant de start_index à end_index à chaque fois
        self.timestamp = input_block[start_index:end_index]
        #La longeur du timestamp
        start_index += 4
        #la longueur de la partie d'après
        end_index += 32
        #On refait la même chose
        self.header_hash = input_block[start_index:end_index]
        start_index += 32
        end_index += 32
        self.content_hash = input_block[start_index:end_index]
        start_index += 32
        end_index += 1
        self.nonce_len = input_block[start_index:end_index]
        start_index += 1
        end_index += int.from_bytes(self.nonce_len, byteorder='big')
        self.nonce = input_block[start_index:end_index]
        start_index += int.from_bytes(self.nonce_len, byteorder='big')
        self.content = input_block[start_index:]


    #Fonction de copie d'un objet dans un nouveau pour éviter une deepcopy
    #Arguments: self: l'objet à remplir (initialisé plus tôt)
    #           block_precedent: block que l'on veut copier dans self
    #
    #Retourne:  une copie de l'objet 
    def Block_copy(self, block_precedent):
        self.timestamp = block_precedent.timestamp
        self.header_hash = block_precedent.header_hash
        self.content_hash = block_precedent.content_hash
        self.nonce_len = block_precedent.nonce_len
        self.nonce = block_precedent.nonce
        self.content = block_precedent.content


    #Fonction de hashage du header du block
    #Argument: self: l'objet qui contient le header à hasher
    #
    #Retourne:  le hash en format hexadécimal
    def header_hasher(self):
        h = hashlib.sha256(bytes(self.timestamp))
        h.update(self.header_hash)
        h.update(self.content_hash)
        h.update(self.nonce_len)
        h.update(self.nonce)
        h = h.hexdigest()
        return hex(int(h, 16))


    #Fonction de hashage du contenu du block
    #Argument: self: l'objet qui contient le contenu à hasher
    #
    #Retourne:  le hash en format hexadécimal
    def content_hasher(self):
        h = hashlib.sha256(bytes(self.content))
        h = h.hexdigest()
        return hex(int(h,16))


    #Fonction d'affichage du block
    #Argument: self: l'objet qui contient toutes les données à afficher
    #
    #Retourne:  l'affichage complet du block dans le terminal
    def Block_print(self):
        print("Le timestamp du block: " 
        + str(datetime.fromtimestamp(int.from_bytes(self.timestamp, byteorder='big'))))
        print("Le hash du header du block précédent: " 
        + str(hex(int.from_bytes(self.header_hash, byteorder='big'))))
        print("Le hash du contenu du block: " 
        + str(hex(int.from_bytes(self.content_hash, byteorder='little'))))
        nonce_len = str(int.from_bytes(self.nonce_len, byteorder='big'))
        print("Le nonce: " 
        + str(int.from_bytes(self.nonce, byteorder='big')) + " écrit sur "+ nonce_len + " octets")
        print("Le hash de l'entête actuelle: " 
        + self.header_hasher())
        print("Les premiers 128 octets du contenu: " 
        + str(hex(int.from_bytes(self.content[:128], byteorder='little'))))


    #Fonction de verification de la validité de toute la blockchain
    #Argument: self: l'objet actuel (le plus recement lu)
    #          block_precedent: le block avec lequel comparer l'objet actuel
    #          num_block: le numero du block par raport à toute la blockchain lue
    #
    #Retourne:  true si la blockchain est intègre et false si la blockchain est corrompue 
    def blockchain_is_valid(self, block_precedent, num_block):
        if not self.timestamp_is_valid(block_precedent):
            print("Invalide: le timestamp du block " + str(num_block) +" est incorrect.\n")
            return False
        if not self.content_hash_is_valid():
            print("Invalide: le block " + str(num_block) +" ne contient pas le hash de son contenu.\n")
            return False
        if not self.header_previous_hash_is_valid(block_precedent):
            print("Invalide: le block " + str(num_block) + " ne contient pas le hash du block"+ str(num_block-1) +".\n")
            return False
        if not self.header_previous_header_is_valid():
            print("Invalide: le hash de l'en-tête du block " + str(num_block -1) + " ne commence pas par " + str(nb_0_in_header) + " bits à '0'\n")
            return False
        return True

    #Fonction de verification de la validité du timestamp
    #Argument: self: l'objet à verifier
    #          block_precedent: le block avec lequel comparer le timestamp actuel
    #
    #Retourne:  true si le timestamp est acceptable et false s'il existe déjà un timestamp plus recent
    def timestamp_is_valid(self, block_precedent):
        time_1 = datetime.fromtimestamp(int.from_bytes(self.timestamp, byteorder='big'))
        time_2 = datetime.fromtimestamp(int.from_bytes(block_precedent.timestamp, byteorder='big'))
        return time_1 >= time_2


    #Fonction de verification de la validité du contenu
    #Argument: self: l'objet à verifier
    #
    #Retourne:  true si le hash fait à partir du contenu est le même que le hash stocké dans l'objet
    def content_hash_is_valid(self):
        new_hash = self.content_hasher()
        content = "0x" + ''.join('{:02x}'.format(x) for x in self.content_hash)
        return new_hash == content


    #Fonction de verification de la validité du header
    #Argument: self: l'objet à verifier
    #
    #Retourne:  true si le hash fait à partir du contenu est le même que le hash stocké dans l'objet
    def header_previous_hash_is_valid(self, block_precedent):
        content = ''.join('{:02x}'.format(x) for x in self.header_hash)
        content = hex(int(content, 16))
        return content == str(block_precedent.header_hasher())
    

    #Fonction de verification du nombre de 0 dans le header
    #Argument: self: l'objet à verifier
    #
    #Retourne:  true si le header contient le bon nombre de 0 et false si ce n'est pas le cas
    def header_previous_header_is_valid(self):
        content = ''.join('{:02x}'.format(x) for x in self.header_hash)
        content = bin(int(content,16))[2:]
        return 32*8 - len(content) >= nb_0_in_header
    

# Nombre de 0 dans l'en-tête -> variable à modifer pour la blockchain 0
nb_0_in_header = 13


try:
    input_name = sys.argv[1]
except:
    print("Veuillez donner le chemin en argument!.\n")
    exit()

# test de la lecture du fichier (block_0 d'une blockchain)
try:
    input_file = open(input_name, 'rb')
except:
    print("Le fichier spécifié n'existe pas, ou n'est pas accessible.\n")
    exit()

# on conserve le chemin vers les blocks à l'exception du numéro de block
for i in range(len(input_name) -1, 0, -1):
    if input_name[i].isdigit():
        input_name = input_name[:-1]
    elif input_name[i] == '_':
        break

validation_flag = True
file_flag = True
block_number = 1
block = Block(0,0,0,0,0,0)
tmp_block = Block(0,0,0,0,0,0)

#convertion du contenu du premier block en byte array
input_bytes = bytes(input_file.read())
input_file.close()

#remplissage et vérification du block
tmp_block.Block_read(input_bytes)
validation_flag = tmp_block.content_hash_is_valid()


#gestion d'erreurs
if not validation_flag:
    print("Invalide: Le hash du premier bloc ne correspond pas à son contenu\n")
    print("La blockchain n'est pas valide.\n")
    exit()

#vérification pour tous les blocks suivants le premier
while file_flag and validation_flag:
    try: 
        input_file = open(input_name + str(block_number), 'rb')
        input_bytes = bytes(input_file.read())
        block.Block_read(input_bytes)
        input_file.close()
        validation_flag = block.blockchain_is_valid(tmp_block, block_number)
        tmp_block.Block_copy(block)
        block_number +=1
    except:
        file_flag = False

# extraction d'un block si la blockchain est valide
if  validation_flag:
    print("Toute la blockchain est valide.\n")
    nb_block = input("Veuillez entrer le numéro du block à extraire: ")
    input_name = sys.argv[1]
    input_name = input_name[:-1]
    input_name += nb_block

# test de la lecture du fichier à extraire
    try:
        input_file = open(input_name, 'rb')
    except:
        print("Le fichier spécifié n'existe pas, ou n'est pas accessible.\n")
        exit()

    input_bytes = bytes(input_file.read())
    input_file.close()

#stockage du contenu dans un block pour afficher les données
    block.Block_read(input_bytes)
    block.Block_print()
    path_extract = input("Veuillez entrer l'endroit où extraire le fichier: ")
    output_file = open(path_extract, 'wb+')
    output_file.write(block.content)
    output_file.close()

#gestion d'erreurs
else:
    print("La blockchain n'est pas valide.\n")
    exit()