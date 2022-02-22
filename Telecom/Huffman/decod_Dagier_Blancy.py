"""*****************************************************************************
 |\_________/|		                                               |\_________/|
 |           |		 							                   |           |
 | [°] [°]   |      									           |   [°] [°] |
 |    V      |      Nom du Programme: Décodeur Huffman             |      V    |
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
import codecs
import json

#program_file = sys.argv[0]
input_text = "output2.bin"#sys.argv[1]

################################################################################
####             FONCTIONS                  ####################################
################################################################################

def decode_char(inputstring, inputdict) :
    output_string = ""
    string_tmp = ""
    for c in inputstring:
        string_tmp += c
        if string_tmp in list(inputdict.values()):
            indeks = list(inputdict.values()).index(string_tmp)
            output_string += list(inputdict.keys())[indeks]
            string_tmp =""

    return output_string
################################################################################
################################################################################
################################################################################

strval = ""
barry = bytearray()
lines = list()

input_file= open(input_text, "rb")

byte = input_file.read(1)
while byte != b"":
    #Try except car un char utf-8 peut etre entre 1 et 3 octets
    try :
        strval += byte.decode('utf8')
    except:
        barry.append(ord(byte))
        byte = input_file.read(1)
        barry.append(ord(byte))
        strval += barry.decode('utf8')
        barry.clear()
    if strval[-3:] == "$$\n" :
        break
    byte = input_file.read(1)
#On enleve le $$$\n (délimiteur)
strval = strval[:-4]

#Pour utiliser plus tard
barry.clear()
deco_dict = dict()
key = 0
val = 0

for string in strval.splitlines():
    #le char \n se fait filtrer
    try:
        key,val = string.split(':')
    except:
        val = string
        key = '\n'
    deco_dict[key] = val

#La clé du code de '\n' est remplacé par ''
deco_dict['\n'] = deco_dict['']
del deco_dict['']

#Le padding
extra = input_file.read(1)

byte = input_file.read(1)
while byte!=b"":
    barry.append(ord(byte))
    byte = 0xFF
    byte = input_file.read(1)

coded_text = ""

for b in barry:
    coded_text += format(b, '#010b')[2:]

#On décode en enlevant le padding
print(decode_char(coded_text[:-ord(extra)], deco_dict))
