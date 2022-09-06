const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
var cors = require('cors');
const fs = require('fs');
const bodyParser = require('body-parser');
app.use(cors());


app.use(express.static('../frontend'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));

const payment = require('./modules/payment')
var redis = require('redis');

var socketList = {};
var timerList = [];

const cachePath = './cache.json'

const { Server } = require("socket.io");
const path = require('path');
const session = require('express-session');
const bodyParse = require('body-parser');
const { features } = require('process');
const port = 8080;
const io = require("socket.io")(server, {
  cors: {
    origin: "*",
    methods: ["GET", "POST"],
    allowedHeaders: ["my-custom-header"],
  }
});

require('dotenv').config();

const LIVEGO_ADDR = process.env.LIVEGO_ADDR;
console.log("livegoADDR " + LIVEGO_ADDR );
var profStreamDict = [];

const TRIALTIMEDURATION = 5 * 60 * 1000;

const STREAMCOST = 10;

class UserStreamEntity {
  constructor(userId, streamId, time, socketId, callback) {
    this.userId = userId;
    this.streamId = streamId;
    this.time = time;
    this.timer = new timer(function () {
      callback.call()
      //eraseCache(userId,streamId)
      //delete timerList[timerList.findIndex(i => {return i.userId == userId && i.streamId == streamId})];
      //timerList = timerList.filter((a) => a)
    }, time)
  }
}

function test() {
  //console.log("EH OH")
}


function timer(callback, delay) {
  var id, started, remaining = delay, running

  this.start = function () {
    running = true
    started = new Date()
    if (delay >= 0) {
      id = setTimeout(callback, remaining)
    }
  }

  this.pause = function () {
    running = false
    clearTimeout(id)
    remaining -= new Date() - started
  }

  this.getTimeLeft = function () {
    if (running) {
      this.pause()
      this.start()
    }
    return remaining
  }

  this.getStateRunning = function () {
    return running
  }
  this.start()

}

//This is called by the frontend whenever the page is loaded
//in order to know the tie remaining
app.get('/timer/:stream/:user', (req, res) => {
  //Get the time remaining for the user.
  getRemainingTime(req.params.user, req.params.stream)
    .then(a => {
      if (a < 0) {
        a = 0;
      }
      res.json({ "timer": a });
      res.status(200).end();
    });
});


function getStreamURL(profID) {
  if (existDB(profID)) {
    let res = "def";
    profStreamDict.forEach(a => {
      if (a['key'] == profID) {
        console.log(a['key'], "and", profID, "makes", a['value']);
        res = a['value'];
    }});
    return res;
  }else{
    return "OI"
  }
}


////////////////////////////////////////////////////////

/* Route pour le front */

app.get('/stream/get/:profID/:userID', (req, res) => {
  var r = getRemainingMoney(req.params.userID)
  if (r < STREAMCOST) {
    res.status(402).end();
  }
  let a = getStreamURL(req.params.profID);
  console.log("ProfID = " + req.params.profID);
  console.log("VAL: " + a);
  if (a == null) {
    res.status(408).end();
  } else {
    res.json({ "url": a });
    res.status(200).end();
  }

});

app.get('/banned/add/:stream/:user', (req, res) => {
  payment.updateBannedUsers(parseInt(req.params.user), parseInt(req.params.stream));
  res.status(200).end();
});

app.get('/banned/check/:stream/:user', (req, res) => {
  output = payment.checkUserBanned(parseInt(req.params.user), parseInt(req.params.stream));
  if(output){
    res.json({
      "result": true
    });
    res.status(200).end();
  } else {
    res.json({
      "result": false
    });
    res.status(200).end();
  }
});

app.get('/payment/debit/:stream/:user', (req, res) => {
  // we suppose we don't need any timestamp to compute the number of credits to debit
  if(payment.debitUser(parseInt(req.params.user), payment.computeCreditsToDebit("timestamp", parseInt(req.params.user), parseInt(req.params.stream))) == 0){
    payment.updatePayment(parseInt(req.params.user), parseInt(req.params.stream));
    res.json({
      "credits": payment.getUserCredits(parseInt(req.params.user))
    });
    res.status(200).end();
  } else {
    res.json({
      "credits": -1
    });
    res.status(200).end();
  }
});

app.get('/payment/credits/:user', (req, res) => {
  // we suppose we don't need any timestamp to compute the number of credits to debit
  var credits = payment.getUserCredits(parseInt(req.params.user)); 
  if(credits >= 0){
    res.json({
      "credits": credits
    });
    res.status(200).end();
  } else {
    res.json({
      "credits": -1
    });
    res.status(200).end();
  }
});

app.get('/payment/check/:stream/:user', (req, res) => {
  // we suppose we don't need any timestamp to compute the number of credits to debit
  output = payment.checkPayment(parseInt(req.params.user), parseInt(req.params.stream));
  if(output){
    res.json({
      "credits": true
    });
    res.status(200).end();
  } else {
    res.json({
      "credits": false
    });
    res.status(200).end();
  }
});

app.get('/credential/:user', (req, res) => {
  res.json({
    "credential": payment.isUserProf(parseInt(req.params.user))
  });
  res.status(200).end();
});

function getRemainingMoney(userID) {
  if (existDB(userID)) {
    let remainingMoney = getMoneyFromDB(userID);
    return remainingMoney;
  } else {
    return 42;
  }
}

function existDB(userID) {
  return (userID != null) ? true : false;
}

function getMoneyFromDB(userID) {
  return 15;
}


function getURLFromDB(profID) {
  return profStreamDict.forEach(a => {
    if (a['key'] == profID) {
      return a['value'];
    }
  })
}

//////////////////////////////////////////////////////

/* Route pour le liveGo */

app.post('/stream/add/:profID', (req, res) => {
  addStreamFromDB(req.params.profID, LIVEGO_ADDR + "/live/" + req.params.profID + ".m3u8")
  console.log(profStreamDict);
  res.status(200).end();
});

app.post('/stream/remove/:profID', (req, res) => {
  removeStreamFromDB(req.params.profID, req.params.URL);
  res.status(200).end();
});


function addStreamFromDB(profID, URL) {
  profStreamDict.push({ key: profID, value: URL });
}

function removeStreamFromDB(profID, URL) {
  console.log(getStreamURL(profID) );
  let obj = { key: profID, value: "hah"};
}

//////////////////////////////////////////////////////

function writeCache(userID, streamID, time) {

  var value = userID + "|" + streamID
  return add(value, time)
}

// Récupère le temps restant d'un utilisateur pour un stream donné
async function getTimeFromCache(userID, streamID) {
  var value = userID + "|" + streamID;
  return chope(value);
}

async function getRemainingTime(userID, streamID) {
  //If user-stream combo doesn´t exist in cache -> return TRIALTIMEDURATION
  return existCache(userID + "|" + streamID).then(a => {
    if (a == 1) {1
      let remainingTime = getTimeFromCache(userID, streamID);
      //console.log("remaining time = " + remainingTime);
      return remainingTime;
    } else {
      return TRIALTIMEDURATION;
    }

  });

}

async function existCache(value) {
  var client = redis.createClient();
  return client.connect().then(a => {
    return client.exists(value);
  });
}

async function add(key, timer) {

  var client = redis.createClient();
  return client.connect().then(a => {

    return client.set(key, timer).then(b =>
      client.disconnect()
    );

  });

  //console.log("heu")
}



async function chope(key) {
  var client = redis.createClient();
  return client.connect().then(a => {
    return client.get(key).then(b => {
      client.disconnect();
      return b;
    });
  });
}

function addTimer(newEntry) {
  //timerList.push(newEntry);
  return writeCache(newEntry.userId, newEntry.streamId, newEntry.timer.getTimeLeft())
}

function updateCache() {

}

io.on('connection', (socket) => {

  var roomID = "";
  var userID = "";


  socket.on('init', (args) => {
    //console.log("eheh")
    roomID = args['roomID'];
    userID = args['userID'];
    socket.join(args['roomID']);

    getRemainingTime(userID, roomID).then(a => {

      let remainingTime = a;
      console.log("remaining : " + remainingTime)

      if (remainingTime <= 0) {
        socketList[args['userID'] + "|" + args['roomID']] = new UserStreamEntity(args['userID'], args['roomID'], remainingTime, socket, i => {
          //console.log("Timer Ended");
          socket.disconnect();
        });
        console.log("Detected negative or 0 time!");
        socket.disconnect();
      } else {
        socketList[args['userID'] + "|" + args['roomID']] = new UserStreamEntity(args['userID'], args['roomID'], remainingTime, socket, i => {
          //console.log("Timer Ended");
          socket.disconnect();
        });

        /*console.log(socketList[userID + "|" +roomID]);*/
        existCache(userID + "|" + roomID).then(b => {
          if (b == 0) {
            addTimer(socketList[userID + "|" + roomID]);
          }
        });
      }

    })


    /*
    if(!existCache(userID, roomID)){
      console.log("SHIT")
      addTimer(socketList[userID + "|" +roomID]);
    }*/
  });

  socket.on('chat message', (args) => {
    console.log("RECIEVED MESSAGE");
    console.log(args);
    socket.to(args['roomID']).emit('recieve message', ({ "msg": args['msg'], "userID": args['userID'], "question": args['question'] }));
  });

  socket.on('disconnect', (reason) => {
    addTimer(socketList[userID + "|" + roomID]);
    socket.disconnect();
  });

});

app.listen(8080);
console.log('Server started');

//On connection to socket -> add the socket to the correct room

//On connection to socket -> add the socket to the correct room

server.listen(3000, () => {
  console.log('listening on *:3000');
});
////////////////////////////////