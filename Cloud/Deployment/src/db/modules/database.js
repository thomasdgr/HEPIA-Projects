const fs = require('fs');

const fileDelay = 'db/delay.json';
const fileStation = 'db/station.json';
const fileJourney = 'db/journey.json';
const fileExcuses = 'db/excuses.json';

/* En fonction de "type", permet de determiner sur quel fichier lire et écire dans la db */
function getFile(type){
    switch (type){
        case "delay":
            return 'db/delay.json';
        case "station":
            return 'db/station.json';
        case "journey":
            return 'db/journey.json';
        case "excuses":
            return 'db/excuses.json';
        default:
            return;
    }
}

/* En fonction de "type", on ajoute l'entrée {key:k, value:v}
 * dans un des 4 fichiers relatifs aux classements
 * retourne "true" si tout s'est bien passé pour addapter le code http de retour de la route 
 */
exports.add = function(k, v, type){
    let file = getFile(type);
    // ouverture du ficher
    fs.readFile(file, function (err, data){
        if(err) throw err;
        // parsing json
        obj = JSON.parse(data);
        // ajout de la valeur dans l'objet
        obj.content.push({key:k, value:v});
        // écriture du nouvel objet
        fs.writeFile(file, JSON.stringify(obj), (err) => {
            if(err) throw err;
        });
    });
    return true;
}

/* En fonction de "type", on ajoute retourne "limit" éléments
 * les éléments sont triés par leur valeur (comme ce sont des retards, des nombre d'excuses utilisés...
 * et que nous faisons des classements, nous ne voulons que les éléments avec la valeur la plus grande)
 * retourne la liste des éléments qui sont retournés ou une erreur 
 */
exports.get = function(limit, type){
    let file = getFile(type);
    // ouverture du fichier
    var kek = fs.readFileSync(file, `utf-8`);
    // parsing json
    let obj = JSON.parse(kek);
    // on trie l'objet par l'attribut "value"
    return obj.content.sort(function(a, b){
            return b.value - a.value;
    // et on retourne un objet contenant les éléments de 0 (le plus haut) à "limit" 
    // (ou 4 si "limit" n'est pas renseigné dans la route)
    }).slice(0,limit);
}

/* En fonction de "type", on supprime "limit" éléments
 * les éléments sont triés par leur valeur (comme ce sont des retards, des nombre d'excuses utilisés...
 * et que nous faisons des classements, nous voulons supprimer les éléments avec la valeur la plus petite)
 * retourne "true" si tout s'est bien passé pour addapter le code http de retour de la route 
 */
exports.delete = function(limit, type){
    let file = getFile(type);
    // lecture du fichier
    fs.readFile(file, function (err, data){
        if(err) throw err;
        // parsing json
        let obj = JSON.parse(data);
        // on trie l'objet par l'attribut "value"
        obj.content.sort(function(a, b){
            return b.value - a.value;
        });
        // on fait un classement d'au moins 4 éléments dans le frontend -> on veut donc s'assurer qu'il reste
        // toujours au moins 4 éléments dans le fichier (si ce n'est pas le cas on adapte le nombre d'objet à enlever)
        // ex: on a 6 éléments et on veut en enlever 5 -> c'est pas possible, on en enlèvera que 2 pour qu'il en reste 4 
        while(obj.content.length - limit < 4){
            limit--;
            if(limit <= 0){
                break;
            }
        }
        // on retire les éléments souhaités (avec les valeurs les plus petites)
        for(let i = 0; i < limit; i++){
            obj.content.splice(obj.content.length-1, 1);
        }
        // écriture du nouvel objet
        fs.writeFile(file, JSON.stringify(obj), (err) => {
            if(err) throw err;
        });
    });
    return true;
}

/* Fait un update de chacun des fichiers (delay, journey, excuses, station)
 * retourne "true" si tout s'est bien passé pour addapter le code http de retour de la route 
 */
exports.update = function(array){
    // on itere sur chaque fichier
    for(let i = 0; i < array.length; i++){    
        let file = "";
        switch(i){
            case 0:
                file = 'db/delay.json';
                break;
            case 1:
                file = 'db/excuses.json';
                break;
                case 2:
                file = 'db/journey.json';
                break;
            case 3:
                file = 'db/station.json';
                break;
        }
        // lecture du fichier
        fs.readFile(file, function (err, data){
            if(err) throw err;
            // parsing json
            obj = JSON.parse(data);
            // pour chaque entrée, on regarde si elle correspond à une entrée du tableau donné en paramètre
            for(let j = 0; j < obj.content.length; j++){
                if(obj.content[j].key == array[i].key){
                    // dans ce cas, on veut mettre à jour l'entrée avec la nouvelle valeur
                    obj.content[j].value = array[i].value;
                }
            }
            // écriture du nouvel objet puis passage au fichier suivant
            fs.writeFile(file, JSON.stringify(obj), (err) => {
                if(err) throw err;
            });
        });
    }
    return true;
}