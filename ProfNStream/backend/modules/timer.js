
const express = require('express');
const redis = require('redis')
const fs = require('fs');
const bodyParser = require('body-parser');

const cachePath = './cache.json'

// ??
var userList = { entity : [] }

// timer list
var timerList = [];


class UserStreamEntity {
    constructor(idUser, idStream,time) {
      this.idUser= idUser;
      this.idStream = idStream;
      this.time = time;
      this.timer = new timer(function() {
        console.log("FINISH");
        //call socket thing
        //socketList[this.idUser].close()
        delete timerList[timerList.findIndex(i => {return i.idUser === idUser && i.idStream == idStream})];
    }, time)
    }    
}

function timer(callback, delay) {
    var id, started, remaining = delay, running

    this.start = function() {
        running = true
        started = new Date()
        id = setTimeout(callback, remaining)
    }

    this.pause = function() {
        running = false
        clearTimeout(id)
        remaining -= new Date() - started
    }

    this.getTimeLeft = function() {
        if (running) {
            this.pause()
            this.start()
        }
        return remaining
    }

    this.getStateRunning = function() {
        return running
    }
    this.start()
    
}



app.post('/cache', async (request, response) => {
    
    if(request.query.username != undefined){
        username = request.query.username
        streamId = request.query.streamId
        time = request.query.time

        var newEntry = new UserStreamEntity(username,streamId,time)
        timerList.push(newEntry);



        //userList.entity.push(entity)
        //console.log(userList)
        writeCache(username,streamId,time)
        response.status(200).json(response.json);
    } else{
        response.status(400).end("Failed to get the ressource");
    }
});

app.get('/cache', async (request, response) => {
    if(request.query.username != undefined){
        console.log("ICI")
        username = request.query.username
        streamId = request.query.streamId



        userList.entity.forEach( el =>{ 
            console.log(el)
            if( el.userId == username) response.status(200).json(el)
            else response.status(401).json("User Or stream wrong");
        })

        response.status(200).json(response.json);
    } else{
        response.status(400).end("Failed to get the ressource");
    }
});



//function createTimer





app.listen(8080);
console.log('Server started');