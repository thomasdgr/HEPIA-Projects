function eraseCache(userId,streamId,time){
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

