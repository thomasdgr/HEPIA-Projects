//Imports

require('dotenv').config()

const express = require('express');
const db = require('./modules/database');
const fs = require('fs');
const bodyParser = require('body-parser');
const jwt = require('jsonwebtoken');
const { type } = require('os');
var cors = require('cors')

let app = express();

app.use(cors());

app.use(express.static('../frontend'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));
app.listen(8080);
console.log('Server started');

app.get('/api', function(request, response) {
    response.setHeader('Content-Type', 'text/plain');
    response.send(`
    Voici l'API REST CRUD de Dorian et Thomas exposée par le backend sur /api/v1/
    
    | Verbe HTTP | Endpoint                           | Données | Description                                                          |
    |:-----------|:-----------------------------------|:--------|:---------------------------------------------------------------------|
    | GET        | classements/*:type*/:limit?        |  type   | Retourne une liste de "limit" éléments (ou 4) en fonction de "type"  |
    | POST       | classements/add                    |         | Ajoute des informations dans la base de données                      |
    | PUT        | classements/update                 |         | Modifie des informations de la base de données                       |
    | DELELTE    | classements/delete/*:type*/:limit? |  type   | Retire les "limit" derniers éléments présents dans le fichier "type" |
    |:-----------|:-----------------------------------|:--------|:---------------------------------------------------------------------|
    | GET        | succes/get/*:user*                 |  user   | Retourne un succes en fonction du "user"                             |
    | POST       | succes/login                       |         | Permet de se connecter sur le site(sous reserve d'etre dans la liste)|
    | PUT        | succes/add                         |         | Ajoute un succès dans la base de données (voir "user" du body)       |
    | DELETE     | succes/logout                      |         | Permet de se deconnecter du site                                     |
    `);
});

/* NOTES SUR LE PROJET:
 *   n'ayant pas fait de login pour la partie front, on a improvisé quelque chose en vitesse donc il n'est pas possible d'ajouter des utilisateurs
 *   les parties du frontend qui communiquent avec le backend sont les fichiers classement.js et succes.js
 *   la base de données est composée de fichiers json (voir backend/db) sur lesquels on peut appliquer toutes les propriétés CRUD
 *   le code qui permet d'interagir avec la base de données se situe dans backend/modules/database.js
 */



/* Route permettant de récuperer les "limit" éléments les plus intéréssant du fichier identifié par "type"
 * "limit" étant optionnel, on le remplace par 4 s'il n'est pas renseigné
 * "type" fait référence au ficher json du dossier backend/db dans lequel on veut aller chercher l'info
 * valeurs de retour: -> 200 (OK)
 *                    -> 400 (Bad Request) 
 */
app.get('/api/v1/classements/:type/:limit?', (request, response) => {
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
app.post('/api/v1/classements/add', (request, response) => {
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
app.put('/api/v1/classements/update', (request, response) => {
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
app.delete('/api/v1/classements/delete/:type/:limit?', (request, response) => {
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

// A TON TOUR DORIAN LA ZONE
// commentaires dans ce fichier + dans le fichier succes.js + readme (ligne 124)
// ajouter la gestion des code de retour comme dans le fichier classements.js
// touche pas trop aux classements stp ou en tout cas appuie pas sur supprimer
let users = {
    content:[
        {username:"Thomas", password:"1234"},
        {username:"Dorian", password:"prout"}
    ]
}

//permet d'avoir plusieurs utilisateur en simultané mais cela n'est pas utilisé
let tokenSave;

/* Lorsque que une route est appellée cette fonction permet de vérifier que 
 * la requête contient un token et que celui est valide 
 * valeurs de retour: -> next() (OK)
 *                    -> 401 (Unauthorized) 
 *                    -> 400 (Bad Request) 
 */
function authJwtToken(req, res, next){
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
    
    if(token == null || token != tokenSave) return res.sendStatus(401);
    jwt.verify(token, process.env.ACCESS_TOKEN_SECRET, (err, user) => {
        if(err) return res.sendStatus(403);
        req.user = user;
        
        next();
    });
}

/* Permet d'ajouter un succes dans la liste correspondante à l'utilisateur
 * valeurs de retour: -> next() (OK)
 *                    -> 401 (Unauthorized) 
 *                    -> 400 (Bad Request) 
 */
app.put('/api/v1/succes/add', authJwtToken ,(request, response) => {
    if(request.body !== undefined){
        if(db.addSucces(request.body.user, request.body.succes)){
            response.status(200).end();
            return;
        }
        response.status(404).end();
    } else{
        response.status(400).end();
    }
});

/* Permet d'obtenir les succes correspondant à l'utilisateur 
 * valeurs de retour: -> 200 (OK)
 *                    -> 400 (Bad Request) 
 */
app.get('/api/v1/succes/get/:user', authJwtToken, (request, response) => {
    if(request.params.user !== undefined){
        response.status(200).json(db.getSucces(request.params.user));
    } else{
        response.status(400).end();
    }
});

/* Permet de se deconnecter du serveur et donc empêche l'envoie de succès
 * si le token envoyé ne correspond pas à celui enregistré on ne fait rien
 * valeurs de retour: -> 204 (OK)
 *                    -> 405 (Method not allow) 
 */
app.delete('/api/v1/succes/logout', (request, response) => {
    tokenSave = ''
    response.sendStatus(204);
})

/* Permet de se connecter au serveur si les identifiants envoyé par le client
 * corresponde à ceux enregistrer dans la base de données
 * valeurs de retour: -> 204 (OK)
 *                    -> 403 (Forbidden) Le client n'a pas les droits d'accès 
 */
app.post('/api/v1/succes/login', (request, response) => {

    for(let i = 0; i < users.content.length; i++){
        if(request.body.username == users.content[i].username && request.body.password == users.content[i].password){
            const username = request.body.username;
            const user = {name: username};
            // Le token exprire dans 5 minutes
            const accessToken = jwt.sign(user, process.env.ACCESS_TOKEN_SECRET, {expiresIn: '5m'});
            tokenSave = accessToken
            response.status(200).json({accessToken: accessToken}).end();
            
        }
    }
    response.status(403).end()

});