/*
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
*/

package mess

import (
    "fmt"
    "net"
    "app/trans"
    "encoding/json"
    "strings"
)

type Message struct {
  Job      string `json:"job"`
  Body     interface{} `json:"body"` // Any type possible
}

type VoteAnswer struct {
  Percentage      float64 `json:"percentage"`
  TotalSamples    uint32 `json:"total_samples"`
}


func Extract_transaction_from_message(mess Message) (trans.Transaction){
  var t trans.Transaction
  mapString, _ := mess.Body.(map[string]interface{}) //Convert interface to map[string]
  //fmt.Println(mapString)

  //Convert map[string] to JSON to convert it in transaction
  mapStringJsonBytes, _ := json.Marshal(mapString)
  json.Unmarshal(mapStringJsonBytes, &t)

  return t
}

func Extract_vote_answer_from_message(mess Message) (VoteAnswer){
  var answerVote VoteAnswer
  mapString, _ := mess.Body.(map[string]interface{}) //Convert interface to map[string]
  //fmt.Println(mapString)

  //Convert map[string] to JSON to convert it in transaction
  mapStringJsonBytes, _ := json.Marshal(mapString)
  json.Unmarshal(mapStringJsonBytes, &answerVote)

  return answerVote
}


//Wait a connection and a message. Return the message read
//error will be nil if the operation was successfull.
//if an error occured you must not take care of the content of message
//The last parameter is the address of the sender
func Wait_and_get_message(ln net.Listener) (Message, error, *json.Encoder, string){
  var messageInStruct Message
  conn, err := ln.Accept() //Wait a connection
  if err != nil {
     fmt.Println("Error connecting:", err.Error())
     return messageInStruct, err, nil , ""
  }
  strRemoteAddr := strings.Split(conn.RemoteAddr().String(), ":")[0]
  fmt.Println("Connection accepted from " + strRemoteAddr)

  decoderFromStream := json.NewDecoder(conn)
  encoderOnStream := json.NewEncoder(conn)

  err = decoderFromStream.Decode(&messageInStruct)  //Wait to receive the JSON
  if err != nil {
      fmt.Println("Error, impossible to decode message", err.Error())
      return messageInStruct, err, nil , ""
  }
  fmt.Printf("Message received: ")
  fmt.Println(messageInStruct)
  fmt.Println()
  return messageInStruct, err, encoderOnStream, strRemoteAddr

}
