/*
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
*/

package main

import (
    "app/mess"
    "app/bd"
    "net"
    "fmt"
    "app/node"
    "os"
    "app/jobs"
)

//TODO: Give port as parameter in node, Send_to_neighbour not public, functions in struct for node,
var PORT_TO_USE_STRING string = "50000"
var PATH_TO_NODES_INFOS_YAML = "../../server_infos/"

func main() {
  if(len(os.Args) < 2 || len(os.Args) > 2){
    fmt.Println("Please use:  go run server.go ID")
    os.Exit(1)
  }

  idServer:= os.Args[1][0:1]

  var db bd.Database
  infosNode, err := node.Get_infos_from_yaml_file(PATH_TO_NODES_INFOS_YAML + "neighbour" + "-" + idServer + ".yaml")
   if err != nil {
     fmt.Println("Error, impossible to read the YAML file:", err.Error())
     os.Exit(1)
   }

   fmt.Println("Starting the server : " + idServer + " on " + infosNode.Address)
   //fmt.Println("Infos YAML: %v", infosNode)

  // listen on a port
  ln, error := net.Listen("tcp", ":" + PORT_TO_USE_STRING)
  if error != nil {
      fmt.Println("Error listening:", error.Error())
      os.Exit(1)
  }
  
  for{

    messageReceivedJSON, err, encoderOnStream, addrTransmitter := mess.Wait_and_get_message(ln)

    if err != nil {
        fmt.Println("Error during waiting a message:", err.Error())
        os.Exit(1)
    }

    isEmitterAServer := infosNode.Is_a_server_address(addrTransmitter)

    if messageReceivedJSON.Job == "transaction"{
      jobs.Job_transaction(ln, &db, infosNode, messageReceivedJSON, PORT_TO_USE_STRING, isEmitterAServer)
    }else if messageReceivedJSON.Job == "list" && !isEmitterAServer {
      jobs.Job_list(db, infosNode, encoderOnStream)
    }else if messageReceivedJSON.Job == "fake" && !isEmitterAServer {
      jobs.Job_fake(&db, messageReceivedJSON)
    }else if messageReceivedJSON.Job == "vote" {
      jobs.Job_vote(ln, &db, infosNode, messageReceivedJSON, encoderOnStream, PORT_TO_USE_STRING, addrTransmitter)
    }
    fmt.Println("Job is finished!")
  }

}
