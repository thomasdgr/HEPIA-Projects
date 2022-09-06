
const express = require('express');
const redis = require('redis')
const fs = require('fs');
const bodyParser = require('body-parser');


let app = express();
app.use(express.static('../frontend'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));


var socketList = {};

const cachePath = './cache.json'

// ??
var userList = { entity : [] }

// timer list
var timerList = [];


class UserStreamEntity {
    constructor(userId, streamId,time, callback) {
      this.userId= userId;
      this.streamId = streamId;
      this.time = time;
      this.timer = new timer(function() {
        console.log("FINISH");
        callback.call()
        eraseCache(userId,streamId)
        console.log(timerList)
        delete timerList[timerList.findIndex(i => {return i.userId == userId && i.streamId == streamId})];
        timerList = timerList.filter((a) => a)
        console.log(timerList)
    }, time)
    }    
}

function test(){
    console.log("EH OH")
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
    
    if(request.query.userId != undefined){
        userId = request.query.userId
        streamId = request.query.streamId
        time = request.query.time

        var newEntry = new UserStreamEntity(userId,streamId,time,test)
        timerList.push(newEntry);



        //userList.entity.push(entity)
        //console.log(userList)
        writeCache(userId,streamId,time)
        response.status(200).json(response.json);
    } else{
        response.status(400).end("Failed to get the ressource");
    }
});

app.get('/cache', async (request, response) => {
    
    if(request.query.userId != undefined){
        console.log("ICI")
        userId = request.query.userId
        streamId = request.query.streamId



        userList.entity.forEach( el =>{ 
            console.log(el)
            if( el.userId == userId) response.status(200).json(el)
            else response.status(401).json("User Or stream wrong");
        })

        response.status(200).json(response.json);
    } else{
        response.status(400).end("Failed to get the ressource");
    }
});
/*
function updateCache(){
    
    f.readFile(cachePath, 'utf8', function readFileCallback(err, data){
      if (err){
          console.log(err);
      } 
      else {
            timerList.forEach(element => {
            
        })
    }});

}*/

function eraseCache(userId,streamId){

    fs.readFile(cachePath, 'utf8', function readFileCallback(err, data){
        if (err){
            console.log(err);
        } else {
        obj = JSON.parse(data); //now it an object


        if(obj.table.length <= 1 ){
            try {
                fs.unlinkSync('cache.json');
            
                console.log("File is deleted.");
            } catch (error) {
                console.log(error);
            }
        }
        else{
            //console.log(obj.table)
            delete obj.table[obj.table.findIndex(i => {return i.userId == userId && i.streamId == streamId})]; //del some data
            obj.table = obj.table.filter((a) => a)
            json = JSON.stringify(obj); //convert it back to json
            fs.writeFile(cachePath, json, 'utf8', function(error) {
                console.log("File has been erased");
              }); // write it back 
        }


    }});
}

function writeCache(userId,streamId,time) {

    var entity = {
        "userId": userId,
        "streamId": streamId,
        "time": time
    }

    var obj = {
        table: []
     };
    
    try {
        var fs = require('fs');
        if (fs.existsSync(cachePath)) {
            fs.readFile(cachePath, 'utf8', function readFileCallback(err, data){
                if (err){
                    console.log(err);
                } else {
                    obj = JSON.parse(data); //now it an object
                    obj.table.push(entity); //add some data
                    json = JSON.stringify(obj); //convert it back to json
                    fs.writeFile(cachePath, json, 'utf8', function(error) {
                    console.log("File has been updated");
                  }); // write it back 
            }});

        }else{          


            obj.table.push(entity)
            var json = JSON.stringify(obj);
            fs.writeFile(cachePath, json, 'utf8', function(error) {
                console.log("File has been created");
              })
        }
    } catch(err) {
        console.error(err)
    }
}

app.listen(8080);
console.log('Server started');