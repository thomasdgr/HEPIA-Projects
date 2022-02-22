"""*****************************************************************************
		     ____
           /____ \         | Projet : TP sur le chiffrement et le déchiffrement
           | _ _`\|        |          dans le cadre du cours de sécurité
    .-.   `| O O |         | Auteurs : Qentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : à partir d'une clef 32 bits, on
 __/  |    | \__/|         |    chiffre un message sur 16 bits que l'on doit
(___) \.  _.\__. `\___     |    déchiffrer en utilisant la clef de départ
(___)  )\/  \_____/  ~\.   |
(___) . \   `         `\   | Utilisation : python3 main.py
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 26/08/2020

*****************************************************************************"""
import idea_library_test as idea

inputText = open("message.txt", "r")
inputContent = inputText.read()
inputText.close()
#inputText= "1001110010101100"
outputText = open("resultat.txt", "w+")

#key32 = idea.generate_pseudo_random_key32bits(32)
#key32="11011100011011110011111101011001"
#Mytest
key32 = "11100001101101001100010001111110"

print("\nmessage de départ : " + inputContent)
print("clef de départ : " + key32 + "\n")
'''text = "1001110010101100"
key = "11011100011011110011111101011001"
encryptedSubText = idea.encryption_idea(key,text)
decryptedSubText = idea.decryption_idea(key, encryptedSubText)
print("decrypted= " +decryptedSubText)'''

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

print(asciiTextBinaryArray)

# on encrypte le contenu du fichier sous-message par sous-message
for i in range(0, len(asciiTextBinaryArray) -1, 2):
	subText = asciiTextBinaryArray[i] + asciiTextBinaryArray[i+1]
	encryptedSubText = idea.encryption_idea(key32,subText)
	encryptedSubTextsArray.append(encryptedSubText)

# on encrypte le contenu encrypté sous-message par sous-message
for i in range(0,len(encryptedSubTextsArray)):
	encryptedValue= encryptedSubTextsArray[i]
	decryptedSubText = idea.decryption_idea(key32, encryptedValue)
	decryptedSubTextsArray.append(decryptedSubText[0:8])
	# on ne prend pas en compte le caractère null s'il y en a un
	if decryptedSubText[8:16] !="00000000":
		decryptedSubTextsArray.append(decryptedSubText[8:16])
print(decryptedSubTextsArray)

# on écrit le message déchiffré dans le fichier resultat.txt
resultText=""
for binaryText in decryptedSubTextsArray:
	intValue = idea.convert_string_binary_to_int(binaryText)
	resultText= resultText + chr(intValue)
outputText.write(resultText)

if inputContent == resultText:
    print("le message de départ à été retrouvé !")
else :
    print("le message est différent de celui de départ ...")

outputText.close()
