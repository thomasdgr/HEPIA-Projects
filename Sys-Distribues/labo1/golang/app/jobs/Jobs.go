/*
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
*/

package jobs

import (
    "app/mess"
    "app/bd"
    "net"
    "fmt"
    "encoding/json"
    "app/node"
    "app/trans"
)

//Adds in the database the transaction of the received message. Also, sends it to all neighbours by using Broadcast by wave algorithm
//ln: the listening socket of the server
//db: the transaction database of the node
//infosNode: the node informations
//messageReceivedJSON the message received with the socket
//portString: the port of destination nodes to communicate with.
//isTransmitterAServer: is the sender a server
//Return 1 if the job was successfull. Otherwise -1
func Job_transaction(ln net.Listener, db *bd.Database, infosNode node.InfosNodeYaml, messageReceivedJSON mess.Message, portString string, isTransmitterAServer bool)(int){
  var err error
  var reach bool = false
  var count uint32 = 0

  if !isTransmitterAServer{
    reach = true
    db.Add_transaction_from_message(messageReceivedJSON)
    infosNode.Send_to_all_neighbours(messageReceivedJSON, portString)
  }

  numberOfNeighbours := infosNode.Get_number_of_neighbours()
  //fmt.Printf("count:%d, nb of neighbours: %d\n",count, numberOfNeighbours)
  for count < numberOfNeighbours {
    if (count != 0 && isTransmitterAServer) || !isTransmitterAServer {//Potential skip to avoid two consecutives waiting
      messageReceivedJSON, err, _, _ = mess.Wait_and_get_message(ln)
      if err != nil {
          fmt.Println("Error during waiting a message:", err.Error())
          return -1
      }
    }
    count++
    if reach == false{
      db.Add_transaction_from_message(messageReceivedJSON)
      //print_database(db)
      reach = true
      infosNode.Send_to_all_neighbours(messageReceivedJSON, portString)
    }
  }
  return 1
}

//Sends to the client a message containing the percentage of neighbours who have the transaction contained in a message. To do that, the Broadcast by wave with ack is used.
//ln: the listening socket of the server
//db: the transaction database of the node
//infosNode: the node informations
//messageReceivedJSON: the message containing the transaction to check. <!> Only the id needs to be specified
//encoderOnStream: The JSON encoder associated to the socket. It will be used to respond to the client
//portString: the port of destination nodes to communicate with.
//addrTransmitter: address of the sender of the message
//Return 1 if the job was successfull. Otherwise -1
func Job_vote(ln net.Listener, db *bd.Database, infosNode node.InfosNodeYaml, messageReceivedJSON mess.Message, encoderOnStream *json.Encoder, portString string, addrTransmitter string)(float64){
  var err error
  var reach bool = false
  var count uint32 = 0
  var idParent uint8 = 0
  var selfNodeAnswerVote mess.VoteAnswer = mess.VoteAnswer{100.0,1}

  var transToCheck trans.Transaction =  mess.Extract_transaction_from_message(messageReceivedJSON)
  var isTransmitterAServer bool = infosNode.Is_a_server_address(addrTransmitter)

  if !isTransmitterAServer{ //Self data is considered as correct
    messageReceivedJSON.Body, err = db.Get_transaction(transToCheck.Id) //The client only gives the transaction Id. Future root has to set the data corresponding to this Id
    if err != nil {
        fmt.Println(err.Error())
        return -1
    }
  }else{
    if(db.Is_transaction_valid(transToCheck) == -1){
        selfNodeAnswerVote.Percentage = 0.0
    }
  }

  if !isTransmitterAServer{
    reach = true
    infosNode.Send_to_all_neighbours(messageReceivedJSON, portString) //vote sent to children
  }
  numberOfNeighbours := infosNode.Get_number_of_neighbours()
  //fmt.Printf("count:%d, nb of neighbours: %d\n",count, numberOfNeighbours)
  for count < numberOfNeighbours {
    if (count != 0 && isTransmitterAServer) || !isTransmitterAServer {//Potential skip to avoid two consecutives waiting

      messageReceivedJSON, err, _, addrTransmitter = mess.Wait_and_get_message(ln)
      if err != nil {
          fmt.Println("Error during waiting a message:", err.Error())
          return -1
      }
    }

    count++
    if reach == false{
      reach = true
      idParent, err = infosNode.Get_id_of_address(addrTransmitter)
      if err != nil {
          fmt.Println(err.Error())
          return -1
      }
      infosNode.Send_to_all_neighbours_except(messageReceivedJSON, []uint8{idParent}, portString) //vote sent to children

    }else{ //It can be a message from a child or not
      if messageReceivedJSON.Job == "vote_answer"{ //It's a child
        voteAnswerReceived :=  mess.Extract_vote_answer_from_message(messageReceivedJSON)
        var nbOfTransValids float64 = selfNodeAnswerVote.Percentage * float64(selfNodeAnswerVote.TotalSamples) + voteAnswerReceived.Percentage * float64(voteAnswerReceived.TotalSamples)
        selfNodeAnswerVote.TotalSamples += voteAnswerReceived.TotalSamples
        selfNodeAnswerVote.Percentage = nbOfTransValids / float64(selfNodeAnswerVote.TotalSamples)
      }//else nothing to do

    }
  }
  //Sends the answer of the vote to the parent or client
  var answerVoteToSendJSON mess.Message
  answerVoteToSendJSON.Job = "vote_answer"
  answerVoteToSendJSON.Body= selfNodeAnswerVote

  if !isTransmitterAServer{ //The node is the root
    //Sends to the client
    err = encoderOnStream.Encode(answerVoteToSendJSON)
    if err != nil {
        fmt.Printf("Error, impossible to write the structure in JSON on the stream: ", err)
    }

  }else{
    go infosNode.Send_to_neighbour(idParent, answerVoteToSendJSON, portString)
  }
  return 1
}

//Sends to the client a message containing the database of the node
//db: the transaction database of the node
//infosNode: the node informations
//encoderOnStream: The JSON encoder associated to the socket. It will be used to respond to the client
//Return 1 if the job was successfull. Otherwise -1
func Job_list(db bd.Database, infosNode node.InfosNodeYaml, encoderOnStream *json.Encoder)(int){
  messageList := mess.Message{"list_answer", db}
  err := encoderOnStream.Encode(messageList)
  if err != nil {
      fmt.Printf("Error, impossible to write the structure in JSON on the stream: ", err)
      return -1
  }
  //db.Print()
  return 1
}

//Replaces the transaction in the database by the one in the message.
//Return 1 if the transaction existed and was successfully replaced. Otherwise -1
func Job_fake(db *bd.Database, messageReceivedJSON mess.Message) (int){
  return db.Replace_transaction_from_message(messageReceivedJSON)
}
