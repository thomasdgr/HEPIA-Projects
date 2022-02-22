require('dotenv').config()

const express = require('express');
const fs = require('fs');
const bodyParser = require('body-parser');
const jwt = require('jsonwebtoken');
const { type } = require('os');
const db = require("./modules/database.js");
var cors = require('cors');
let app = express();

app.use(cors());

app.use(express.static('../frontend'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));
app.listen(8081);
console.log('Database started');



/* Route permettant de récuperer les "limit" éléments les plus intéréssant du fichier identifié par "type"
 * "limit" étant optionnel, on le remplace par 4 s'il n'est pas renseigné
 * "type" fait référence au ficher json du dossier backend/db dans lequel on veut aller chercher l'info
 * valeurs de retour: -> 200 (OK)
 *                    -> 400 (Bad Request) 
 */
app.get('/api/classements/:type/:limit?', (request, response) => {
    if(request.params.type !== undefined){
        const limit = request.params.limit ? request.params.limit : 4;
        response.status(200).json(db.get(limit, request.params.type));
    } else{
        response.status(400).end();
    }
});


/* Route permettant d'ajouter un élément pour chaque type
 * Pour chaque fichier relatifs aux données des classements (delay, excuses, station, journey), on doit ajouter une info 
 * tous les fichiers (voir au dessus) sont mis à jour par l'appel de cette route
 * valeurs de retour: -> 201 (Created) données créées
 *                    -> 202 (Accpected) valide mais pas de garantie du résultat
 *                    -> 400 (Bad Request) 
 */
//A ADAPTER
app.post('/api/classements/add', (request, response) => {
    if(request.body.content !== undefined && request.body.type){
        if(db.add(request.body.content[0].key, request.body.content[0].value, request.body.type)){
            response.status(201).end();
            return;
        } 
        response.status(202).end();
    } else{
        response.status(400).end();
    }
});



/* Route permettant de mettre à jour un élément pour chaque type
 * Pour chaque fichier relatifs aux données des classements (delay, excuses, station, journey), on doit mettre à jour une info 
 * valeurs de retour: -> 200 (OK)
 *                    -> 202 (Accpected) valide mais pas de garantie du résultat
 *                    -> 400 (Bad Request) 
 */
//A ADAPTER
app.put('/api/classements/update', (request, response) => {
    if(request.body !== undefined){
        if(db.update(request.body.content)){
            response.status(200).end();
            return;
        }
        response.status(202).end();
    } else{
        response.status(400).end();
    }
});

/* Route permettant de supprimer "limit" éléments les plus intéréssant du fichier identifié par "type"
 * "limit" étant optionnel, on le remplace par 4 s'il n'est pas renseigné
 * "type" fait référence au ficher json du dossier backend/db dans lequel on veut aller chercher l'info
 * valeurs de retour: -> 200 (OK)
 *                    -> 202 (Accpected) valide mais pas de garantie du résultat
 *                    -> 400 (Bad Request) 
 */

//A ADAPTER
app.delete('/api/classements/delete/:type/:limit?', (request, response) => {
    if(request.params.type !== undefined){
        const limit = request.params.limit ? request.params.limit : 2;
        if(db.delete(limit, request.params.type)){
            response.status(200).end();
            return;
        }
        response.status(202).send();
    }
    response.status(400).end();
});