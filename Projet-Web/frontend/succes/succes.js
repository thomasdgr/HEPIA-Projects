let token;
let currentUser;

async function connexion(){
    currentUser = document.getElementById('user').value;
    const pass = document.getElementById('pass').value;    
    await fetch('http://localhost:8080/api/v1/succes/login',
    {
        method: 'POST',
        headers : new Headers({
            'Access-Control-Allow-Origin': 'http://localhost:8080',
            'Accept': 'application/json',
            'Content-Type': 'application/json'
        }),
        body: JSON.stringify({username:currentUser, password:pass})
    })
    .then(response => response.json() )
    .then(response => token = response);
    getSucces(currentUser);
}

async function postSucces(){
    const success = document.getElementById('addSucces').value;
    console.log(success);
    if(success !== "" && currentUser !== undefined){    
        await fetch('http://localhost:8080/api/v1/succes/add',
        {
            method: 'PUT',
            headers: new Headers({
                'Authorization': 'Bearer ' + token.accessToken,
                'Content-Type': 'application/json',
            }),
            body: JSON.stringify({'user':currentUser, 'succes':success})
        })
        .then(function(response) { // gèrer les codes de retour correctement
            if(response.status === 200){
                getSucces(currentUser);
            } else {
                alert("error while adding succes");
            }
        });
    }
}

async function getSucces(username){
    document.getElementById('mySucces').innerHTML = "";
    await fetch('http://localhost:8080/api/v1/succes/get/' + username,
    {
        method: 'GET',
        headers: new Headers({
            'Authorization': 'Bearer ' + token.accessToken,
            'Content-Type': 'application/json',
        })
    })
    .then(response => response.json())
    .then(result => {
        result.forEach(element => {
            // préciser
            var img = (Math.round(Math.random())) ? "../images/check.png" : "../images/no.png"; 
            document.getElementById('mySucces').innerHTML += '<li><div class="ligne"><img id="img1-1" src="'+ img +'"><p>'+ element.value + '</p></div></li>';
        });
    });
}

async function deconnexion(){
    token = "";
    await fetch('http://localhost:8080/api/v1/succes/logout' ,
    {
        method: 'DELETE',
        headers: new Headers({
            'Authorization': 'Bearer ' + token.accessToken,
            'Content-Type': 'application/json',
        })
    });
    document.getElementById('mySucces').innerHTML = "";
}