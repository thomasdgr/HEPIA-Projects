// header utilisé pour les appels vers l'api rest
const myHeader = new Headers({
    'Access-Control-Allow-Origin': 'http://localhost:8080',
    'Accept': 'application/json',
    'Content-Type': 'application/json'
});

let count = 26;

// au chargement de la page, on affiche les infos pour le premier onglet
window.onload = function(){
    update(1);
};

// dès que l'on clique sur un des onglets, on appelle la fonction update
// avec différentes valeurs d'index
async function update(index){
    let content;
    // en fonction de la valeur on récupère les infos dans la db
    // à différents endroits
    switch(index){
        case 2: 
            content = await getContentClassement2();
            break;
        case 3: 
            content = await getContentClassement3();
            break;
        case 4: 
            content = await getContentClassement4();
            break;
        default:
            content = await getContentClassement1();
            break;
    }
    // on affiche le contenu retourné sur la page
    var text1 = document.getElementById('text1');
    text1.innerHTML = content[0];
    var text2 = document.getElementById('text2');
    text2.innerHTML = content[1];
    var text3 = document.getElementById('text3');
    text3.innerHTML = content[2];
    var text4 = document.getElementById('text4');
    text4.innerHTML = content[3];
}

// Fonction permettant de récuperer les 4 meilleures entrées du classement des délais
async function getContentClassement1(){
    document.getElementById('podium1').style.display = "block";
    document.getElementById('podium2').style.display = "none";
    document.getElementById('podium3').style.display = "none";
    document.getElementById('podium4').style.display = "none";

    let array;
    // on indique vouloir faire le get sur les délais et on veut 4 valeurs
    await fetch('//localhost:8080/api/v1/classements/delay/4',
    {
        headers : myHeader,
        method: 'GET'
    })
    // gestion du code de retour
    .then(async function(response) {
        if(response.status !== 200){
            console.log("Error while getting data from delay");
        } else{
            // gestion du résultat retourné
            array = await response.json();
            var status = document.getElementById('status');
            status.innerHTML = "";
        }
    });
    // grâce au résultat, on retourne un tableau des 4 éléments à afficher
    var output = [];
    output.push("1: Le " + array[0].key + ", " + array[0].value + " heures de retard");
    output.push("2: Le " + array[1].key + ", " + array[1].value + " heures de retard");
    output.push("3: Le " + array[2].key + ", " + array[2].value + " heures de retard");
    output.push("4: Le " + array[3].key + ", " + array[3].value + " heures de retard");
    return output;
} 


// le fonctionnement est exactement le même sauf que le get est fait sur les excuses
async function getContentClassement2(){
    document.getElementById('podium1').style.display = "none";
    document.getElementById('podium2').style.display = "block";
    document.getElementById('podium3').style.display = "none";
    document.getElementById('podium4').style.display = "none";

    let array;
    await fetch('//localhost:8080/api/v1/classements/excuses/4',
    {
        headers : myHeader,
        method: 'GET'
    })
    // gestion du code de retour
    .then(async function(response) {
        if(response.status !== 200){
            console.log("Error while getting data from delay");
        } else{
            // gestion du résultat retourné
            array = await response.json();
            var status = document.getElementById('status');
            status.innerHTML = "";
        }
    });

    var output = [];
    output.push("1: " + array[0].key + ", " + array[0].value + " fois");
    output.push("2: " + array[1].key + ", " + array[1].value + " fois");
    output.push("3: " + array[2].key + ", " + array[2].value + " fois");
    output.push("4: " + array[3].key + ", " + array[3].value + " fois");
    return output;
}

// le fonctionnement est exactement le même sauf que le get est fait sur les voyages
async function getContentClassement3(){
    document.getElementById('podium1').style.display = "none";
    document.getElementById('podium2').style.display = "none";
    document.getElementById('podium3').style.display = "block";
    document.getElementById('podium4').style.display = "none";

    let array;
    await fetch('//localhost:8080/api/v1/classements/journey/4',
    {
        headers : myHeader,
        method: 'GET'
    })
    // gestion du code de retour
    .then(async function(response) {
        if(response.status !== 200){
            console.log("Error while getting data from delay");
        } else{
            // gestion du résultat retourné
            array = await response.json();
            var status = document.getElementById('status');
            status.innerHTML = "";
        }
    });

    var output = [];
    output.push("1: " + array[0].key + ", annulé " + array[0].value + " fois");
    output.push("2: " + array[1].key + ", annulé " + array[1].value + " fois");
    output.push("3: " + array[2].key + ", annulé " + array[2].value + " fois");
    output.push("4: " + array[3].key + ", annulé " + array[3].value + " fois");
    return output;
}

// le fonctionnement est exactement le même sauf que le get est fait sur les gares
async function getContentClassement4(){
    document.getElementById('podium1').style.display = "none";
    document.getElementById('podium2').style.display = "none";
    document.getElementById('podium3').style.display = "none";
    document.getElementById('podium4').style.display = "block";
    
    let array;
    await fetch('//localhost:8080/api/v1/classements/station/4',
    {
        headers : myHeader,
        method: 'GET'
    })
    // gestion du code de retour
    .then(async function(response) {
        if(response.status !== 200){
            console.log("Error while getting data from delay");
        } else{
            // gestion du résultat retourné
            array = await response.json();
            var status = document.getElementById('status');
            status.innerHTML = "";
        }
    });
    
    var output = [];
    output.push("1: La gare " + array[0].key + " compte " + array[0].value + " heures de retard");
    output.push("2: La gare " + array[1].key + " compte " + array[1].value + " heures de retard");
    output.push("3: La gare " + array[2].key + " compte " + array[2].value + " heures de retard");
    output.push("4: La gare " + array[3].key + " compte " + array[3].value + " heures de retard");
    return output;
}

// permet d'ajouter des données dans la base de données (pour chaque type)
async function addData(){
    // l'idée aurait été de faire un ajout quotidien des données dans la db
    // mais on sort un peu trop du backend alors on a juste mis un bouton pour ajouter en dur des infos
    let data = { 
        content : [
            {key: "nouvelle entrée", value: count},
        ],
        type: "delay"
    };
    count += Math.round(Math.random() * 7);

    fetch('//localhost:8080/api/v1/classements/add',
    {
        headers : myHeader,
        method : 'POST',
        body : JSON.stringify(data)
    })
    // gestion du code de retour
    .then(function(response) {
        if(response.status === 201){
            var status = document.getElementById('status');
            status.innerHTML = "AJOUT REUSSI DANS LA BDD";
        } else if (response.status === 202){
            var status = document.getElementById('status');
            status.innerHTML = "L'AJOUT N'EST PAS GARANTIE DANS LA BDD";
        } else {
            var status = document.getElementById('status');
            status.innerHTML = "ECHEC DE L'AJOUT DANS LA BDD";
        }
    });
}

// permet de suprimer des données dans la base de données (en fonction du type et du nombre)
// attention: on peut supprimer autant d'élément que l'on veut tant qu'il en reste minimum 4 après le delete
async function deleteData(){
    // ici on fait le delete uniquement pour les délais (le fonctionnement est le meme pour les autres)
    fetch('//localhost:8080/api/v1/classements/delete/delay/2',
    {
        headers : myHeader,
        method: 'DELETE'
    })
    // gestion du code de retour
    .then(function(response) {
        if(response.status === 200){
            var status = document.getElementById('status');
            status.innerHTML = "SUPRESSION REUSSI DANS LA BDD";
        } else if (response.status === 202){
            var status = document.getElementById('status');
            status.innerHTML = "LA SUPRESSION N'EST PAS GARANTIE DANS LA BDD";
        } else {
            var status = document.getElementById('status');
            status.innerHTML = "ECHEC DE LA SUPRESSION DANS LA BDD";
        }
    });
}

// permet de modifier des données dans la base de données (pour chaque type)
async function updateData(){
    let data = {
        content : [
            {key: "Mardi 34 Juin 2021", value: 87}, // remplace la valeur 58
            {key: "Travaux sur les voies", value: 3781}, // remplace la valeur 3721
            {key: "Geneve -> Grenoble", value: 2}, // remplace la valeur 1
            {key: "Avigon Centre", value: 23} // remplace la valeur 9
        ]
    };
    fetch('//localhost:8080/api/v1/classements/update',
    {
        headers : myHeader,
        method : 'PUT',
        body : JSON.stringify(data)
    })
    // gestion du code de retour
    .then(function(response) {
        if(response.status === 200){
            var status = document.getElementById('status');
            status.innerHTML = "UPDATE REUSSI DANS LA BDD";
        } else if (response.status === 202){
            var status = document.getElementById('status');
            status.innerHTML = "L'UPDATE N'EST PAS GARANTIE DANS LA BDD";
        } else {
            var status = document.getElementById('status');
            status.innerHTML = "ECHEC DE L'UPDATE DANS LA BDD";
        }
    });
}