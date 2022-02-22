// token utilisé pour l'authentification
let token = "3875f1e7-0db3-40f4-9cfc-220cbad4b6e3";

// variables globales -> permet de faire les requêtes une seule fois au chargement de la page
let delay_stacked = 0;
let trains_number = 0;
let delayed_trains_number = 0;
let deleted_trains_number = 0;

// execution des requêtes
window.onload = async function(){

    var since = getNewDate(0);
    var until = getNewDate(1);

    let disruption = await getDisruptions(since, until);
    
    delay_stacked = await getStackDelay(disruption);
    delay_total();
    
    let content = await getNumberTrains(since, until);
    trains_number = await content.json();
    trains_number = trains_number.pagination.total_result;

    delayed_trains_number = await getDelayedTrains(disruption);
    
    deleted_trains_number = await getDeletedTrains(disruption);
};

function getNewDate(index){
    var date = new Date();
    date.setDate(date.getDate() + index);
    var dd = String(date.getDate()).padStart(2, '0');
    var mm = String(date.getMonth() + 1).padStart(2, '0');
    var yyyy = date.getFullYear();
    var hour = "000000";
    return (yyyy + mm + dd + "T" + hour);
}

async function getNumberTrains(since, until){
    var kek = await fetch("https://api.sncf.com/v1/coverage/sncf/vehicle_journeys//?since=" + since + "&until=" + until + "&count=1", 
    { method : "GET", 
        headers : {
            "Authorization": token
        }
    });
    return kek;
}

async function getDisruptions(since, until){
    var kek = await fetch("https://api.sncf.com/v1/coverage/sncf/disruptions//?since=" + since + "&until=" + until + "&count=5000&start_page=0&", 
    { method : "GET", 
        headers : {
            "Authorization": token
        }
    });
    var tmp = await kek.json();
    return tmp.disruptions;
}

async function getStackDelay(disruptions){    
    var complete_delay = 0;
    for (let i = 0; i < disruptions.length; i++){
        if(disruptions[i].severity.name.localeCompare("trip canceled")){
            var lengthImpactedStop = disruptions[i].impacted_objects[0].impacted_stops.length;
            if(lengthImpactedStop > 0){
                if(!(disruptions[i].impacted_objects[0].impacted_stops[lengthImpactedStop - 1].arrival_status.localeCompare("delayed"))){
                    var new_arrival = disruptions[i].impacted_objects[0].impacted_stops[lengthImpactedStop - 1].amended_arrival_time;
                    var old_arrival = disruptions[i].impacted_objects[0].impacted_stops[lengthImpactedStop - 1].base_arrival_time;
                    if(new_arrival != undefined && old_arrival != undefined){
                        var new_delay = new_arrival - old_arrival;
                        complete_delay += convertDelay(padLeadingZeros(new_delay,6));
                    }
                }                        
            }
        }
    }
    return complete_delay;
}

function padLeadingZeros(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}

function convertDelay(test) {
    let total_sec = 0;
    
    let hours = test.substring(0,test.length - 4);
    let min = test.substring(2,test.length - 2);
    let sec = test.substring(4,0);

    total_sec = (parseInt(hours) * 60 * 60) + (parseInt(min) * 60) + parseInt(sec);
    return total_sec;
}

async function getDelayedTrains(disruptions){
    let numberTrainDelayed = 0;    
    for (let i = 0; i < disruptions.length; i++){
        let status = disruptions[i].severity.name
        if( !(status.localeCompare("trip delayed"))){
            numberTrainDelayed ++;
        }
    }
    return numberTrainDelayed;
}

async function getDeletedTrains(disruptions){
    let numberTrainDeleted = 0;
    for (let i = 0; i < disruptions.length; i++){
        let status = disruptions[i].severity.name
        if( !(status.localeCompare("trip canceled"))){
            numberTrainDeleted ++;
        }
    }
    return numberTrainDeleted;
}




function delay_total(){
    var d = Math.floor(delay_stacked / (3600*24));
    var h = Math.floor(delay_stacked % (3600*24) / 3600);
    var m = Math.floor(delay_stacked % 3600 / 60);
    var s = Math.floor(delay_stacked % 60);

    var ptag = document.getElementById('res');
    ptag.innerHTML = "Le retard cumulé est de " + d + "jours, " + h + "h " + m + "m " + s + "s";
}

function number_trains(){
    var ptag = document.getElementById('res');
    ptag.innerHTML = trains_number + " trains ont circulé sur nos lignes aujourd\'hui";
}

function delayed_trains(){
    var ptag = document.getElementById('res');
    ptag.innerHTML = delayed_trains_number + " trains sont arrivés en retard aujourd\'hui";
}

function deleted_trains(){
    var ptag = document.getElementById('res');
    ptag.innerHTML = deleted_trains_number + " trains ont été supprimés aujourd\'hui";
}