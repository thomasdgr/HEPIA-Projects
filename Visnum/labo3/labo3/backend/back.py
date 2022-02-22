import numpy as np
from typing import List
import tensorflow as tf
from os import path, write
import json
import random

def stocker(t: List[int], i: int) -> None:
    with open ("../backend/numbers.json", "r+") as f:
        # récuperation du content et transformation en json
        content = json.load(f)
        # ajout du nouveau tableau et du nombre correspondant
        content["numbers"].append({"tab":t,"number_ref":i})        
        # on append au contenu lu donc on doit écrire par dessus l'existant
        f.seek(0)
        # ajout du nouvel objet json dans le fichier
        json.dump(content,f,indent= 4)
        f.close()

def entrainer() ->  None:
    if(path.exists("../backend/kekas.h5") == False):
        # création du modele s'il n'existe pas
        kekas = tf.keras.Sequential()
        # 20x20 -> taille du tableau
        kekas.add(tf.keras.layers.Input(shape=(20*20)))
        # 120 trouvé par tatonement
        kekas.add(tf.keras.layers.Dense(120, activation="relu",input_shape=(400,)))
        # on peut choisir parmis 10 nombres -> la somme des probas vaut 1 (d'où le "softmax")
        kekas.add(tf.keras.layers.Dense(10, activation="softmax"))
        kekas.compile(optimizer='rmsprop', loss="categorical_crossentropy")
    else:
        # on réuitilise le modele existant
        kekas = tf.keras.models.load_model("../backend/kekas.h5")

    # on entraine à partir du fichier qui contient les tableaux
    with open ("../backend/numbers.json", "r+") as f:
        content = json.load(f)
        content = content["numbers"]
        # il faut lire les valeurs de manière aléatoire donc on mélange le tableau
        random.shuffle(content)
        for i in range(0,len(content)-1):
            # pour chaque element du fichier, on recupère le tableau et le nombre correspondant
            # pour les donner à keras et entrainer notre modele
            number_ref = content[i]["number_ref"] 
            tab = content[i]["tab"]
            # pas le choix de faire comme ca pour que la structure attendue soit la bonne                     
            tab4train = []
            tab4train.append(tab)
            options = np.array([0,0,0,0,0,0,0,0,0,0])
            options[number_ref] = 1
            # pas le choix de faire comme ca pour que la structure attendue soit la bonne                     
            options_tab = []
            options_tab.append(options)
            # batch_size -> 1 (taille de tab4train)
            # epoch -> 1 on utilise le fichier une seule fois pour entrainer
            kekas.fit(x=np.array(tab4train), y=np.array(options_tab), batch_size=1, epochs=2, shuffle=True)

    kekas.save("../backend/kekas.h5", kekas)

def deviner(tab: List[int]) -> None:
    kekas = tf.keras.models.load_model("../backend/kekas.h5")
    # pas le choix de faire comme ca pour que la structure attendue soit la bonne                     
    draw2guess = []
    draw2guess.append(tab)
    training_result = np.array(draw2guess)
    return kekas.predict(training_result)