
let token = "3875f1e7-0db3-40f4-9cfc-220cbad4b6e3";
let cities = [];
let indexes = [];

window.onload = async function(){
    getTrainStations();
}

async function rechercher() {
    var source = document.getElementById("source").value;
    var destination = document.getElementById("destination").value;
    var time = document.querySelector('input[type="time"]').value;
    var date = document.querySelector('input[type="date"]').value;

    var ptag_res = document.getElementById("info_res");
    var ptag_departure = document.getElementById("departure_time");
    var ptag_arrival = document.getElementById("arrival_time");

    if(source === "" || destination === "" || time === "" || date === ""){
        ptag_res.innerHTML = "Impossible de trouver un trajet, tous les champs n'ont pas été correctement remplis";
        ptag_departure.innerHTML = "";
        ptag_arrival.innerHTML = "";
        return;
    }
    
    var id_source = await getIdTrainStation(source);
    if(id_source.localeCompare("error")  == 0){
        ptag_res.innerHTML = "La ville source n'existe pas ou n'est pas disponible dans le réseau hessncf";
        ptag_departure.innerHTML = "";
        ptag_arrival.innerHTML = "";
        return;
    }
    console.log(id_source);

    var id_destination = await getIdTrainStation(destination);
    if(id_destination.localeCompare("error") == 0){
        ptag_res.innerHTML = "La ville de destination n'existe pas ou n'est pas disponible dans le réseau hessncf";
        ptag_departure.innerHTML = "";
        ptag_arrival.innerHTML = "";
        return;
    }
    console.log(id_destination);

    index_time = date.substring(0,4) + date.substring(5,7) + date.substring(8,10) + "T" + time.substring(0,2) + time.substring(3,5) + "00";
    
    let journey = await getJourneys(id_source, id_destination, index_time);

    let departure = getDeparture(journey);
    let arrival = getArrival(journey);
 
    let departure_date = getDate(departure);
    let arrival_date = getDate(arrival);

    ptag_res.innerHTML = "Horaire trouvé: ";

    ptag_departure.innerHTML = "Le train part le " + departure_date[2] + "/" + departure_date[1] + "/" + departure_date[0] + "<br/>";
    ptag_departure.innerHTML += "à " + departure_date[3] + "h " + departure_date[4] + "m<br/>";

    ptag_arrival.innerHTML = "Le train arrive le " + arrival_date[2] + "/" + arrival_date[1] + "/" + arrival_date[0] + "<br/>";
    ptag_arrival.innerHTML += "à " + arrival_date[3] + "h " + arrival_date[4] + "m<br/>";
}


function getDate(time){
    let date = [];
    date[0] = time.substring(0,4);
    date[1] = time.substring(4,6);
    date[2] = time.substring(6,8);
    date[3] = time.substring(9,11);
    date[4] = time.substring(11,13);
    return date;
}

async function getIdTrainStation(city){
    switch((city.toLowerCase())){
        case "bellegarde":
            return "stop_area:SNCF:87745000";
        case "lyon":
            return "stop_area:SNCF:87697128";
        case "geneve":
            return "stop_area:SNCF:85010082";
        case "marseille":
            return "stop_area:SNCF:87751602";
        case "bordeaux":
            return "stop_area:SNCF:87581009";
        case "lille":
            return "stop_area:SNCF:87223263";
        case "strasbourg":
            return "stop_area:SNCF:87212027";
        case "tourcoing":
            return "stop_area:SNCF:87286542";
        case "culoz":
            return "stop_area:SNCF:87741074";
        case "montpellier":
            return "stop_area:SNCF:87688887";
        case "dijon":
            return "stop_area:SNCF:87713040";
        case "grenoble":
            return "stop_area:SNCF:87747006";
        default:
            for (let i = 0; i < cities.length; i++){
                if (cities[i].includes(city.toLowerCase())){
                    return "stop_area:SNCF:" + indexes[i].substring(2, indexes[i].length);
                }
            }
            return "error";
    }
}

async function getTrainStations(){
    var kek = await fetch("https://ressources.data.sncf.com/api/records/1.0/search/?dataset=referentiel-gares-voyageurs&q=&rows=10000&sort=gare_alias_libelle_noncontraint&facet=departement_libellemin&facet=segmentdrg_libelle&facet=gare_agencegc_libelle&facet=gare_regionsncf_libelle&facet=gare_ug_libelle");
    let r = await kek.json();
    let records = r.records;
    let content = {};
    for (let i = 0; i < records.length; i++){
        cities[i] = records[i].fields.commune_libellemin.toLowerCase();
        indexes[i] = records[i].fields.uic_code;
    }
}

async function getJourneys(departure, arrival, datetime){
    var kek = await fetch("https://api.sncf.com/v1/coverage/sncf/journeys//?from=" + departure + "&to=" + arrival + "&datetime=" + datetime +"&count=1", 
    { method : "GET", 
        headers : {
            "Authorization": token
        }
    });
    let r = await kek.json();
    return r;
}

function getDeparture(r) {
    let departure = r.journeys[0].departure_date_time;
    return departure;
}

function getArrival(r) {
    let arrival = r.journeys[0].arrival_date_time;
    return arrival;
}