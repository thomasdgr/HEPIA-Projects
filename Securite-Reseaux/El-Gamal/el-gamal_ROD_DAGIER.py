"""*****************************************************************************
		     ____
           /____ \         | Projet : TP sur la signature El-Gamal
           | _ _`\|        |          dans le cadre du cours de sécurité
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Librairie de fonctions utiles pour
 __/  |    | \__/|         |    la signature du message et sa vérification.
(___) \.  _.\__. `\___     |
(___)  )\/  \_____/  ~\.   |
(___) . \   `         `\   |
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 01/10/2020

*****************************************************************************"""
import sys
import math
import random
import os.path
from os import path

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


#Fonction qui retourne l'inverse modulaire
#Argument : number: le nombre entier dont on doit trouver l'inverse
#           moduloNumber: modulo à utiliser (defaut, 17)
#
#Retourne:  l'inverse modulaire en fonction du modulo donné (s'il existe)
def extended_euclidian_algorithm(number, moduloNumber):
    if number == 0:
        return 0
    reste = 1
    quotient = 0
    diviseur = 0
    dividende = 0

    pMoins1 = 1
    pMoins2 = 0
    quotienMoins2 = 0
    stepNumber = 0

    arrayP = []
    arrayQuotient = []
    arrayP.append(0)
    arrayP.append(1)

    while reste > 0:
        if stepNumber == 0:
            dividende = moduloNumber
            diviseur = number
        else:
            dividende = diviseur
            diviseur = reste
        quotient = int(dividende / diviseur)
        arrayQuotient.append(quotient)
        reste = modulo(dividende, diviseur)
        if stepNumber > 1:
            pMoins2 = arrayP[stepNumber - 2]
            pMoins1 = arrayP[stepNumber - 1]
            quotienMoins2 = arrayQuotient[stepNumber - 2]
            arrayP.append(modulo((pMoins2 - pMoins1 * quotienMoins2), moduloNumber))

        stepNumber += 1

    pMoins2 = arrayP[stepNumber - 2]
    pMoins1 = arrayP[stepNumber - 1]
    quotienMoins2 = arrayQuotient[stepNumber - 2]
    return modulo((pMoins2 - pMoins1 * quotienMoins2), moduloNumber)


#Fonction qui retourne le PGCD entre deux nombres
#Argument : number1: première composante du PGCD
#           number2: seconde composante du PGCD
#
#Retourne:  le PGCD des deux nombres
def euclidian_algorithm_pgcd(number1, number2):
    dividende = number2 if (number1 < number2) else number1
    diviseur = number1 if (number1 < number2) else number2
    reste = 1
    while modulo(dividende, diviseur) != 0:
        reste = modulo(dividende, diviseur)
        dividende = diviseur
        diviseur = reste

    return reste


#Fonction qui retourne le PGCD entre deux nombres de manière récursive
#Argument : number1: première composante du PGCD
#           number2: seconde composante du PGCD
#
#Retourne:  le PGCD des deux nombres
def recursive_pgcd(number1, number2):
    if number2 == 0:
        return number1
    else:
        return recursive_pgcd(number2, modulo(number1, number2))


#Fonction qui applique l'exponentiation modulaire sur un nombre
#Argument : number: nombre sur lequel appliquer l'exponentiation
#           exponent: exposant de "number"
#           mod: exponentiation à appliquer sur "number" modulo "mod"
#
#Retourne:  le résultat de l'exponentiation modulaire
def modular_exponentiation(number, exponent, mod):
    valueInBinaryString = convert_int_to_string_binary(exponent)
    result = 1
    tmp = number
    for i in range(len(valueInBinaryString)-1, -1, -1):
        bitValue =int(valueInBinaryString[i])
        if bitValue == 1:
            result = modulo((result * tmp), mod)
        tmp = modulo((tmp * tmp), mod)
    result = modulo(result, mod)
    return result


#Fonction qui remplace l'oppérateur modulo
#Argument : number1: première composante du modulo
#           number2: seconde composante du modulo
#
#Retourne:  le résultat du modulo
def modulo(number1, number2):
    if number1 < 0:
        resteNumber1 = -1 * number1
        while resteNumber1 >= number2:
            resteNumber1 = resteNumber1 - number2
        return number2 - resteNumber1
    result = number1 - number2
    if result < 0:
        return number1
    else:
        while result >= number2:
            result = result - number2
        return result

#Fonction qui fait la vérification d'une signature El Gamal caractère par caractère
#Argument : p: nombre premier pour lequel le problème du logarithme discret est dificile dans Zp*
#           alpha: générateur dans Zp*
#           beta: élément public
#           gamma: première partie de la signature
#           deltaArray: tableau des delta (seconde partie de la signature)
#           asciiTextArray: tableau contenant la chaine de caractères
#
#Retourne:  True si la signature de chaque caracctère est bonne, False si une des signatures est fausse
def verification_el_gamal(p, alpha, beta, gamma, deltaArray, asciiTextArray):
    checkSignature = True
    for index in range(len(asciiTextArray)):
        part1 = modular_exponentiation(beta,gamma,p)* modular_exponentiation(gamma,deltaArray[index],p)
        part2 = modular_exponentiation(alpha,asciiTextArray[index],p)
        result = part1 - part2
        result = modulo(result,p)
        if result != 0:
            checkSignature = False
            break

    return checkSignature


#Fonction qui signe un messsage avec El Gamal ,caractère par caractère
#Argument : filename: fichier contenant le message à signer
#           deltaArray: tableau des delta (seconde partie de la signature)
#           asciiTextArray: tableau contenant la chaine de caractères
#
#Retourne: Un tableau contenant la chaine de caractère du fichier donné en paramètre
#          Un tableau contenant la seconde partie de la signature (delta) pour chaque caractère
def signature_el_gamal(a, p, k, filename, asciiTextArray, deltaArray):
    inputText = open(filename, "r")
    inputContent = inputText.read()
    inputText.close()
    inverseK = extended_euclidian_algorithm(k, p-1)

    #Create an array of all chars in ascii value
    for char in inputContent:
        asciiValue = ord(char)
        asciiTextArray.append(asciiValue)



    #Create an array of deltas
    for m in asciiTextArray:
        Delta = modulo(((m - a * Gamma) * inverseK) , (p-1))
        deltaArray.append(Delta)


#Fonction qui signe un messsage avec El Gamal ,caractère par caractère
#Argument : filename: fichier contenant le message à signer
#           deltaArray: tableau des delta (seconde partie de la signature)
#           asciiTextArray: tableau contenant la chaine de caractères
#
#Retourne: Un tableau contenant la chaine de caractère du fichier donné en paramètre
#          Un tableau contenant la seconde partie de la signature (delta) pour chaque caractère
def getStringFromSign(deltaArray, Gamma):
    result = ""
    for delta in deltaArray:
        result += str(delta) + "," + str(Gamma) + " "
    return result

# /// MAIN ///
if len(sys.argv) != 2:
	print("Merci de lancer le programme sous la forme:\n")
	print("python3 el-gamal_ROD_DAGIER.py fileName")
	exit(0)
else:
	if not path.exists(sys.argv[1]):
		print("Merci d'entrer le nom d'un fichier valide")
		exit(0)

deltaArray = []
asciiTextArray = []
filename = sys.argv[1]

P = 787 # choisit

#Code permettant de trouver un générateur de P
'''arrayGenerator = []
for Alpha in range(1, P):
    for i in range(0, P):
        tmp = modular_exponentiation(Alpha,i,P)
        if tmp in arrayGenerator:
            break
        else:
            arrayGenerator.append(tmp)

        if i == 785:
            print(Alpha) # affiche dans le terminal tout les générateurs de P
            break

    arrayGenerator = []'''

Alpha = 235 # choisit parmis la liste des générateurs
A = 555    # choisit

K = random.randrange(1, P-1)
while euclidian_algorithm_pgcd(K, P-1) != 1:
    K = random.randrange(1, P-1)

Gamma = modular_exponentiation(Alpha, K, P)
Beta = modular_exponentiation(Alpha, A, P)


print("Signature du fichier " + filename + ": ")
signature_el_gamal(A, P, K, filename, asciiTextArray, deltaArray)
print(getStringFromSign(deltaArray, Gamma))
print()

check = verification_el_gamal(P,Alpha,Beta,Gamma, deltaArray,asciiTextArray)
resultVerif = "la signature est correcte" if check else "la signature n'est pas correcte"
print("Vérification de la signature du fichier " + filename + ": " + resultVerif)
