let array_points;

window.addEventListener("load", () => {
    const canvas = document.querySelector("#canvas");
    canvas.width = 700;
    canvas.height = canvas.width;
    
    const context = canvas.getContext('2d');
    
    nb_pixels = 20;
    array_points = new Array(nb_pixels * nb_pixels);
    let size_pixel = canvas.width / nb_pixels;
    let draw = false;
    // appel de la fonction pour initialiser l'affichage
    setGrid();

    // création du tableau en fonction de la taille du canvas
    // (c'est un carré) et du nombre de pixel par ligne
    function setGrid(e){
        for (let i = 0; i < canvas.width ; i += size_pixel){
            // construction du carré pixel par pixel
            context.moveTo(i, 0);
            context.lineTo(i, canvas.width);
            context.stroke();
    
            context.moveTo(0, i);
            context.lineTo(canvas.height, i);
            context.stroke();
        }
        // remplissage de 0 dans le tableau à envoyer
        for (let i = 0; i < nb_pixels; i++){
            for(let j = 0; j < nb_pixels; j++){
                array_points[j * nb_pixels + i] = 0;
            }
        }
    }

    // action à faire quand on appuie sur left-click
    canvas.addEventListener("mousedown", e => {
        // on passe le flag à true pour signifier que l'on veut dessiner
        draw = true;
    });
    
    // action à faire quand on relache left-click
    canvas.addEventListener("mouseup", e => {
        // on passe le flag à true pour signifier que l'on ne veut plus dessiner
        draw = false;
        context.beginPath();
    });

    // action à faire quand on déplace la souris
    canvas.addEventListener("mousemove", e => {
        if(draw){
            // si on déplace et qu'on appuie sur left-click
            context.lineCap = "round";    
            context.fillStyle = 'black';
            // on remplie d'un pixel le canvas à la position de la souris
            context.fillRect( (Math.round((e.clientX - 30) / size_pixel) * size_pixel),
                              (Math.round((e.clientY - 30) / size_pixel) * size_pixel),
                              size_pixel, size_pixel);
            // le tableau qui représente le canvas est modifié à l'index correspondant
            array_points[(Math.round((e.clientY - 30) / size_pixel) * nb_pixels) +  Math.round((e.clientX - 30) / size_pixel)] = 1;
        }
    });
    
    // action à faire quand on presse le bouton "clear"
    btnClear = document.getElementById('btnClear');
    btnClear.addEventListener('click', (e) => {
        // on vide le canvas et on réinitialise l'affichage + le tableau
        context.clearRect(0, 0, canvas.width, canvas.height);
        setGrid();
    });

    // action à faire quand on presse le bouton "send"
    //    on veut envoyer le tableau pour qu'il soit écrit
    //    ainsi que le nombre auquel il fait référence
    btnSend = document.getElementById('btnSend');
    btnSend.addEventListener('click', (e) => {
        // récuperation du nombre séléctionné
        var e = document.getElementById("number_ref");
        // appel vers la route "stocker" dans le fichier labo3/main.py
        fetch("//localhost:8000/stocker/", 
        { method : 'POST',
          // on lui envoie le tableau et le nombre qu'il est censé représenter
          // pour stocker les données dans un fichier
          body : JSON.stringify({data:array_points, number_ref:e.value})
        }).then(response => {
            return response.json(); 
        });
    });

    // action à faire quand on presse le bouton "train ia"
    //    on veut que l'ia s'entraine pour pouvoir deviner par la suite
    btnTrain = document.getElementById('btnTrain');
    btnTrain.addEventListener('click', (e) => {
        // appel vers la route "entrainer" -> simple signal pour lui
        // dire de s'entrainer à partir des données qui sont stockées
        fetch("//localhost:8000/entrainer/", 
        { method : 'GET',
        }).then(response => {
            return response.json(); 
        });
    });

    // action à faire quand on presse le bouton "guess number"
    //    on veut envoyer le tableau pour que le backend devine
    //    quel nombre est déssiné
    btnGuess = document.getElementById('btnGuess');
    btnGuess.addEventListener('click', (e) => {
        // appel vers la route "deviner" qui nous retourne le nombre
        // qui semble etre dessiné
        fetch("//localhost:8000/deviner/", 
        { method : 'POST',
          body : JSON.stringify({data:array_points, number_ref:-1})
        }).then(async function(response){
            // on recupère le tableau des probabilités
            var result = await response.json();
            // index de la valeur la plus haute dans le tableau
            var max = result[0].indexOf(Math.max.apply(null, result[0]));
            for(let i = 0; i < result[0].length; i++){
                // si on est sur la barre qui correspond à l'index max, on l'affiche en rouge
                (i == max) ? document.getElementById("bar"+i).style.background = "red" :
                             document.getElementById("bar"+i).style.background = "gray";
                // on affiche les probabilités avec un offset pour voir le numéro correspondant
                document.getElementById("bar"+i).style.maxWidth = 3+result[0][i]*100+"%";
            }
        });
    });
});