
function who_we_are() {
    var titre = document.getElementById('titre');
    titre.innerHTML = "Qui somme-nous ?";
    var res = document.getElementById('res');
    res.innerHTML = "Le groupe HESSNCF vous propose une offre complète de solutions de retard, à travers ses différents services.";
    var titre2 = document.getElementById('titre2');
    titre2.innerHTML = "La société";
    var res2 = document.getElementById('res2');
    res2.innerHTML = "Notre vocation ? Nous souhaitons faire en sorte que vos déplacements soient le plus compliqués possible pour répondre aux besoins des personnes qui souhaite développer leur immobilité.";
    res2.innerHTML += "<br/>";
    res2.innerHTML += "Pour répondre à ces enjeux nous oeuvrons à faire en sorte que votre retard soit le plus agréable possible.";
    res2.innerHTML += "<br/>";
    res2.innerHTML += "Afin de perpetuer la tradition de la célèbre société homonyme dont nous tairons volontairement le nom, notre équipe se donne à coeur joie pour vous proposer les fonctionalités les plus claquées possibles.";
    res2.innerHTML += "<br/>";
    res2.innerHTML += "<br/>";
    res2.innerHTML += "Petit jeu: Où est Dorian est un jeu très simple qui consiste à retrouver Dorian caché dans certaines images du site. Bonne chance !";
    res2.innerHTML += "<br/>";

    var img = document.getElementById('arbre').style.display = "block";
    var img2 = document.getElementById('tete').style.display = "none";
}
function our_values() {
    var titre = document.getElementById('titre');
    titre.innerHTML = "Quelles sont nos valeurs ?";
    var res = document.getElementById('res');
    res.innerHTML = "La HESSNCF est une entreprise statique. Notre mission et nos objectifs sont totalement figés dans le temps, ils n'évoluent jamais pour répondre le moins possible aux besoins de nos utilisateurs.";
    var titre2 = document.getElementById('titre2');
    titre2.innerHTML = "L'engagement";
    var res2 = document.getElementById('res2');
    res2.innerHTML = "Nous sommes fiers de contribuer à la haine générée chaque jours par nos nombreux utilisateurs, et nous souhaitons continuer sur cette voie en éspérant que vous ferez parti de cette merveilleuse aventure.";
    res2.innerHTML += "<br/>";
    res2.innerHTML += "L\'ADN de la HESSNCF et ses valeurs profondément méprisées de tous forgent l\'esprit même de notre entreprise: pourquoi changer une équipe qui gagne ?";
    
    var img = document.getElementById('arbre').style.display = "none";
    var img2 = document.getElementById('tete').style.display = "none";
    
}
function emplois() {
    var titre = document.getElementById('titre');
    titre.innerHTML = "Nous recrutons êtes-vous interessés ?";
    var res = document.getElementById('res');
    res.innerHTML = 'La HESSNCF s\'emploie à essayer de fournir un service optimal en recrutant les personnes les moins qualifiées possible.';
    var titre2 = document.getElementById('titre2');
    titre2.innerHTML = "L'equipe de la HESSNCF";
    var res2 = document.getElementById('res2');
    res2.innerHTML = "Notre équipe à la fois motivée et dynamique vous attend pour pouvoir changer la vie de millions de chômeurs. Elle est pour l'instant uniquement constitué des deux membres fondateurs.";
    res2.innerHTML += "<br/>";
    res2.innerHTML += "Dorian et Thomas seront enchantés de vous compter parmis les valeureux membre de la HESSNCF. Pour nous contacter, n'hésitez pas a appeler le standard au : 06 36 92 10 35 (disponible entre 13h28 et 14h09 uniquement les jeudis en semaines paires qui sont entre Janvier et mi-Mars)";
    
    var img = document.getElementById('arbre').style.display = "none";
    var img = document.getElementById('tete').style.display = "block";
}


window.onload = function() {
    who_we_are();
};