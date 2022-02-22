"""*****************************************************************************
		     ____
           /____ \         | Projet : TP sur le chiffrement et le déchiffrement
           | _ _`\|        |          dans le cadre du cours de sécurité
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Réalisation de l'algorithme IDEA Simplifié
 __/  |    | \__/|         |    Le contenu d'un message donné en paramètre est chiffré
(___) \.  _.\__. `\___     |    Il est ensuite déchiffré et le résultat est écrit dans le fichier souhaité
(___)  )\/  \_____/  ~\.   |
(___) . \   `         `\   | Utilisation : python3 main.py fichierInitial fichierFinal
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 26/08/2020

*****************************************************************************"""
import idea_library as idea
import sys
import os

numberArguments = len(sys.argv)
nomFichierInput =""
nomFichierOutput = ""
if numberArguments != 3:
	print("Merci de lancer le programme sous la forme : python3 main.py fichierInitial fichierFinal")
	exit(0)
else:
	nomFichierInput = sys.argv[1]
	nomFichierOutput = sys.argv[2]
	boolExistingInput = os.path.isfile(nomFichierInput)
	if not boolExistingInput:
		print("Le fichier \"" + nomFichierInput + "\" n'existe pas.")
		exit(0)


inputText = open(nomFichierInput, "r")
inputContent = inputText.read()
inputText.close()

key32 = idea.generate_pseudo_random_key32bits(32)

print("\nmessage de départ : " + inputContent)
print("clef de départ : " + key32 + "\n")

asciiTextArray = []
asciiTextBinaryArray = []
encryptedSubTextsArray = []
decryptedSubTextsArray = []

# on écrit le message dans un tableau de byte (1 octet par caractère)
for char in inputContent:
	asciiValue = ord(char)
	asciiTextArray.append(asciiValue)
	textBinaryValue= idea.convert_int_to_string_binary(asciiValue);
	asciiTextBinaryArray.append(idea.set_to_byte(textBinaryValue))

# comme le message est décomposé en paquets de 16 bits, on s'assure que
# chaque morceau sera bien sur 16 bits (donc le nombre de lettre doit être pair)
# sinon on ajoute un caractère null qui ne sera pas présent à l'écriture
if len(asciiTextBinaryArray) % 2 != 0:
	asciiTextBinaryArray.append("00000000")

# on encrypte le contenu du fichier sous-message par sous-message
for i in range(0, len(asciiTextBinaryArray) -1, 2):
	subText = asciiTextBinaryArray[i] + asciiTextBinaryArray[i+1]
	encryptedSubText = idea.encryption_idea(key32,subText)
	encryptedSubTextsArray.append(encryptedSubText)


# on décrypte le contenu encrypté sous-message par sous-message
for i in range(0,len(encryptedSubTextsArray)):
	encryptedValue= encryptedSubTextsArray[i]
	decryptedSubText = idea.decryption_idea(key32, encryptedValue)
	decryptedSubTextsArray.append(decryptedSubText[0:8])
	# on ne prend pas en compte le caractère null s'il y en a un
	if decryptedSubText[8:16] != "00000000":
		decryptedSubTextsArray.append(decryptedSubText[8:16])

# on écrit le message déchiffré dans le fichier resultat.txt
outputText = open(nomFichierOutput, "w+")
resultText=""
for binaryText in decryptedSubTextsArray:
	intValue = idea.convert_string_binary_to_int(binaryText)
	resultText= resultText + chr(intValue)
outputText.write(resultText)
outputText.close()

if inputContent == resultText:
    print("Le message de départ à été retrouvé !")
else :
    print("Le message est différent de celui de départ ...")
