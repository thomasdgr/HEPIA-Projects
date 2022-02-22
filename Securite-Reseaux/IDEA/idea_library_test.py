"""*****************************************************************************
		     ____
           /____ \         | Projet : TP sur le chiffrement et le déchiffrement
           | _ _`\|        |          dans le cadre du cours de sécurité
    .-.   `| O O |         | Auteurs : Qentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : librairie de fonctions utiles pour
 __/  |    | \__/|         |    chiffrer  et déchiffre un message avec
(___) \.  _.\__. `\___     |    la méthode IDEA
(___)  )\/  \_____/  ~\.   |
(___) . \   `         `\   |
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 26/08/2020

*****************************************************************************"""
import sys
import math
import random

#Fonction de décallage des sous-clefs (on décalle de 6 bits vers la gauche)
#Argument : input: chaine de caractère contenant les clefs (à la suite)
#
#Retourne:  une chaine de caractère shiftée vers la gauche
def shift(input):
    shiftedPart = input[0:6]
    shiftedKey = input[6:]
    return shiftedKey + shiftedPart



#Fonction qui écrit un nombre binaire sous forme de demi-octet
#Argument : input: le nombre binaire (chaine de caractère) à étendre
#
#Retourne:  une chaine de caractère sous forme de demi-octet
def set_to_nibble(input):
    while len(input) < 4:
        input = "0" + input
    return input


#Fonction qui écrit un nombre binaire sous forme d'octet
#Argument : input: le nombre binaire (chaine de caractère) à étendre
#
#Retourne:  une chaine de caractère sous forme d'octet
def set_to_byte(input):
    while len(input) < 8:
        input = "0" + input
    return input


#Fonction qui additionne deux demi-octets (chaines de caractère)
#Argument : nibble1: premier nombre à additionner
#           nibble2: second nombre à additionner
#           modulo : modulo à utiliser après l'addition (par défaut, 16)
#
#Retourne:  une chaine de caractère sous forme de demi-octet
def add_nibbles(nibble1, nibble2, modulo):
    intNibble1 = convert_string_binary_to_int(nibble1)
    intNibble2= convert_string_binary_to_int(nibble2)
    result = convert_int_to_string_binary((intNibble1 + intNibble2) % modulo)
    return set_to_nibble(result)


#Fonction qui multiplie deux demi-octets (chaines de caractère)
#Argument : nibble1: premier nombre à multiplier
#           nibble2: second nombre à multiplier
#           modulo : modulo à utiliser après la multiplication (par défaut, 17)
#
#Retourne:  une chaine de caractère sous forme de demi-octet
def mult_nibbles(nibble1, nibble2, modulo):
    intNibble1= convert_string_binary_to_int(nibble1)
    intNibble2= convert_string_binary_to_int(nibble2)
    if intNibble1 == 0:
        intNibble1 = modulo - 1
    if intNibble2 == 0:
        intNibble2 = modulo - 1

    result =  (intNibble1 * intNibble2) % modulo
    #dans le cas de la multiplication 16 s'écrit ici 0b0000
    if result == 16:
        result = 0
    result = convert_int_to_string_binary(result)
    result = set_to_nibble(result)
    return result


#Fonction qui effectue un XOR entre deux demi-octets (chaines de caractère)
#Argument : number1: premier nombre
#           number2: second nombre
#
#Retourne:  une chaine de caractère
def bitwise_xor(number1, number2):
    result = ""
    if len(number1) != len(number2):
        print("error, different size for bitwise_xor")
        exit(0)
    else:
        for i in range(0, len(number1)):
            if number1[i] == number2[i]:
                result = result + "0"
            else:
                result = result + "1"
    return result


#Fonction qui convertit un nombre binaire (chaine de caractère) en entier
#Argument : numberString: nombre à convertir
#
#Retourne:  un entier
def convert_string_binary_to_int(numberString):
    lengthString = len(numberString)
    resultNumber = 0

    for i in range(0,lengthString):
        value = int(numberString[lengthString - i - 1])
        resultNumber = resultNumber + value * pow(2, i)
    return resultNumber


#Fonction qui convertit un entier en un nombre binaire (chaine de caractère)
#Argument : numberInt: nombre à convertir
#
#Retourne:  un nombre binaire (chaine de caractère)
def convert_int_to_string_binary(numberInt):
    numberConvert = numberInt
    resultString = ""

    if numberConvert > 0:
        powNumber = int(math.log(numberConvert, 2))
        for i in range(powNumber, -1, -1):
            if numberConvert >= pow(2, i):
                numberConvert = numberConvert - pow(2, i)
                resultString = resultString + "1"
            else:
                resultString = resultString + "0"
    else:
        resultString = "0"
    return resultString


#Fonction qui crée le tableau de sous-clefs (IDEA) à partir de la clef (string)
#Argument : keyString: clef à transformer en tableau
#
#Retourne:  un tableau 2D contenant les sous-clefs
def fill_array(keyString):
    keyArrayTmp = []
    keyArrayFinal = [[0 for i in range(6)] for j in range(5)]

    for  round in range (1, 5):
        startIndex = 0
        endIndex = 4
        for i in range(0, 8):
            #print("value : "+ keyString[startIndex:endIndex] )
            keyArrayTmp.append(keyString[startIndex:endIndex])
            startIndex = startIndex + 4
            endIndex = endIndex + 4
        startIndex = 0
        endIndex = 4
        keyValue = shift(keyString)
        keyString= keyValue
    for j in range(0, 5):
        for k in range(0, 6):
            keyArrayFinal[j][k] = keyArrayTmp[k + j * 5 + j * 1]
    return keyArrayFinal


#Fonction qui donne la clef de decryption correspondante (à modifier)
#Argument : keyArray: le tableau de sous-clefs
#           i,j: coordonnées de la sous-clef (i = round et j = numéro de clef)
#
#Retourne:  la sous-clef (chaine de caractère) correspondante
def get_correspondant_key_from_encryption(keyArray, i, j):
    if j < 4:
        return keyArray[4 - i][j]
    else:
        return keyArray[4 - i - 1][j]


#Fonction qui modifie la sous-clef de décryption
#Argument : keyArray: le tableau de sous-clefs
#           i,j: coordonnées de la sous-clef (i = round et j = numéro de clef)
#           operationType: 0 = multiplication et 1 = addition
#
#Retourne:  la sous-clef (chaine de caractère) correspondante
def calculate_decryption_key(keyArray, i, j, operationType):
    keyEncryption = get_correspondant_key_from_encryption(keyArray, i, j)
    print("correspondant key: "+ keyEncryption)
    if j < 4:
        result = 0
        if operationType == 0: #multiplication
            keyEncryption = convert_string_binary_to_int(keyEncryption)
            result = extended_euclidian_algorithm(keyEncryption, 17)
            print("correspondant key 2: "+ str(result))
        else:
            result = (16 - convert_string_binary_to_int(keyEncryption)) % 16

        return set_to_nibble(convert_int_to_string_binary(result))

    else:
        return keyEncryption


#Fonction qui retourne l'inverse modulaire
#Argument : number: le nombre entier dont on doit trouver l'inverse
#           modulo: modulo à utiliser (defaut, 17)
#
#Retourne:  l'inverse modulaire en fonction du modulo donné (s'il existe)
def extended_euclidian_algorithm(number, modulo):
	
	reste = 1
	quotient = 0
	diviseur = 0
	dividende = 0

	pMoins1 = 1
	pMoins2 = 0
	quotienMoins2 = 0
	stepNumber = 0

	arrayP= []
	arrayQuotient = []
	arrayP.append(0)
	arrayP.append(1)

	while reste >0:
		if stepNumber == 0:
				dividende = modulo
				diviseur = number
		else:
			dividende = diviseur
			diviseur = reste
		quotient = int(dividende / diviseur)
		arrayQuotient.append(quotient)
		reste = dividende % diviseur
		if stepNumber>1:
			pMoins2 = arrayP[stepNumber-2]
			pMoins1 = arrayP[stepNumber-1]
			quotienMoins2 = arrayQuotient[stepNumber-2]
			arrayP.append( (pMoins2- pMoins1 * quotienMoins2) % modulo )

		stepNumber += 1;

	pMoins2 = arrayP[stepNumber-2]
	pMoins1 = arrayP[stepNumber-1]
	quotienMoins2 = arrayQuotient[stepNumber-2]
	return (pMoins2 - pMoins1 * quotienMoins2) % modulo



#Fonction qui encrypte un message avec la methode IDEA
#Argument : key32bits: clef à utiliser pour chiffrer
#           text16bits: texte à chiffrer (chaine de caractère binaire)
#
#Retourne:  une chaine de caractère binaire correspondant au message chiffré
def encryption_idea(key32bits, text16bits):
	keyArray = fill_array(key32bits)
	print("Encryption:")
	print(keyArray)
	print(text16bits)
	textInUse = text16bits

	for round in range (0,5):
		textArray = []
		startIndex = 0
		endIndex = 4

	    # ajout des sous-messages actuel dans le tableau
		for i in range(0,4):
			textArray.append(textInUse[startIndex:endIndex])
			startIndex = startIndex + 4
			endIndex = endIndex + 4

		print("round: " + str(round))
			    # les étapes à faire pour chaque round
		result1 = mult_nibbles(textArray[0], keyArray[round][0], 17)     #step1
		print(str(textArray[0]), str(keyArray[round][0]),"etape 1: " + result1)
		result2 = add_nibbles(textArray[1], keyArray[round][1], 16)      #step2
		print(str(textArray[1]), str(keyArray[round][1]),"etape 2: " +result2)
		result3 = add_nibbles(textArray[2], keyArray[round][2], 16)      #step3
		print(str(textArray[2]), str(keyArray[round][2]),"etape 3: " +result3)
		result4 = mult_nibbles(textArray[3], keyArray[round][3], 17)     #step4
		print(str(textArray[3]), str(keyArray[round][3]),"etape 4: " +result4)

		if round < 4:
			        #  étapes à ne pas faire pour le dernier round
			result5 = bitwise_xor(result1, result3)                      #step5
			print(result1, result3,"etape 5: " + result5)
			result6 = bitwise_xor(result2, result4)                      #step6
			print(result2,result4, "etape 6: " +result6)
			result7 = mult_nibbles(result5, keyArray[round][4], 17)      #step7
			print(result5,keyArray[round][4],"etape 7: " +result7)
			result8 = add_nibbles(result6, result7, 16)                  #step8
			print(result6,result7,"etape 8: " + result8)
			result9 = mult_nibbles(result8, keyArray[round][5], 17)      #step9
			print(result8, keyArray[round][5], "etape 9: " + result9)
			result10 = add_nibbles(result7, result9, 16)                 #step10
			print(result7, result9, "etape 10: " + result10)
			result11 = bitwise_xor(result1, result9)                     #step11
			print(result1, result9, "etape 11: " + result11)
			result12 = bitwise_xor(result3, result9)                     #step12
			print(result3, result9, "etape 12: " +result12)
			result13 = bitwise_xor(result2, result10)                    #step13
			print(result2, result10,"etape 13: " +result13)
			result14 = bitwise_xor(result4, result10)                    #step14
			print(result4, result10, "etape 14: " +result14)

			textInUse = result11 + result13 + result12 + result14
			print("resultat round " + str(round)+ " :" + textInUse)

		else:
			textInUse = result1 + result2 + result3 + result4
			print("resultat round " + str(round)+ " :" + textInUse)

	return textInUse


#Fonction qui décrypte un message avec la methode IDEA
#Argument : key32bits: clef à utiliser pour déchiffrer
#           text16bits: texte à déchiffrer (chaine de caractère binaire)
#
#Retourne:  une chaine de caractère binaire correspondant au message déchiffré
def decryption_idea(key32bits, cypher16bits):
	print("Decryption:")
	keyArray = fill_array(key32bits)
	print(keyArray)
	print("Cypher: " + cypher16bits)
	textInUse = cypher16bits
	for  round in range (0,5):
		textArray = []
		startIndex = 0
		endIndex = 4

# ajout des sous-messages actuel dans le tableau
		for i in range(0,4):
			textArray.append(textInUse[startIndex:endIndex])
			startIndex = startIndex + 4
			endIndex = endIndex + 4

		key = calculate_decryption_key(keyArray, round, 0, 0)
		print("K : " + str(round)+ "," + '0', key )
		result1 = mult_nibbles(textArray[0], key, 17)
		key =  calculate_decryption_key(keyArray, round, 1, 1)
		print("K : " + str(round)+ "," +'1', key )          #step2
		result2 = add_nibbles(textArray[1], key, 16)
		key = calculate_decryption_key(keyArray, round, 2, 1)
		print("K : " + str(round)+ "," +'2', key )         #step3
		result3 = add_nibbles(textArray[2], key, 16)
		key = calculate_decryption_key(keyArray, round, 3, 0)
		print("K : " + str(round)+ "," +'3', key )          #step4
		result4 = mult_nibbles(textArray[3], key, 17)

		if round < 4:
			result5 = bitwise_xor(result1, result3)                      #step5
			result6 = bitwise_xor(result2, result4)                      #step6
			key = calculate_decryption_key(keyArray, round, 4, 0)        #step7
			print("K : " + str(round)+ "," +'4', key )
			result7 = mult_nibbles(result5, key, 17)
			result8 = add_nibbles(result6, result7, 16)                  #step8
			key = calculate_decryption_key(keyArray, round, 5, 0)        #step9
			print("K : " + str(round)+ "," +'5', key )
			result9 = mult_nibbles(result8, key, 17)
			result10 = add_nibbles(result7, result9, 16)                 #step10
			result11 = bitwise_xor(result1, result9)                     #step11
			result12 = bitwise_xor(result3, result9)                     #step12
			result13 = bitwise_xor(result2, result10)                    #step13
			result14 = bitwise_xor(result4, result10)                    #step14
			textInUse = result11 + result13 + result12 + result14
			print("resultat round " + str(round)+ " :" + textInUse)
		else:
			textInUse = result1 + result2 + result3 + result4
			print("resultat round " + str(round)+ " :" + textInUse)

	return textInUse


#Fonction qui génère un nombre àléatoire sur 32bits et le convertit en binaire
#Argument : bitSize : nombre de bit sur lequel le nombre est genéré
#
#Retourne:  une chaine de caractère binaire correspondant à la clef à utiliser
def generate_pseudo_random_key32bits(bitSize):
    number = int(random.random() * pow(2, bitSize))
    return convert_int_to_string_binary(number)
