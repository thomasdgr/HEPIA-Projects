/*
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
*/

package main
import (
    "fmt"
    "net"
    "encoding/json"
    "os"
    "app/mess"
    "app/trans"
    "app/bd"
    "strconv"
)

var PORT_TO_USE_STRING string = "50000"
var IP_CLIENT string = "127.0.0.10"

func main() {
  if len(os.Args) < 3{
    fmt.Println("Create transaction: Please use ./client -t ip idTrans sender receiver amount")
    fmt.Println("Fake transaction: Please use ./client -f ip idTrans sender receiver amount")
    fmt.Println("Vote: Please use ./client -v ip idTrans")
    fmt.Println("List: Please use ./client -l ip")
    os.Exit(1)
  }

  jobName:= os.Args[1]
  addrServer:= os.Args[2]

  var messToSend mess.Message
  var transToSend trans.Transaction
  var err error
  if jobName == "-t" || jobName == "-f"{
    if len(os.Args) < 7{
        fmt.Println("Please use ./client -t/-f ip idTrans sender receiver amount")
        os.Exit(1)
    }
    // connect to server
    intValue, err := strconv.Atoi(os.Args[3])
    if err != nil{
      fmt.Println("Error during parsing of idTrans:", err.Error())
      os.Exit(1)
    }
    transToSend.Id = uint32(intValue)

    intValue, err = strconv.Atoi(os.Args[6])
    if err != nil{
      fmt.Println("Error during parsing of idTrans:", err.Error())
      os.Exit(1)
    }
    transToSend.Amount = int32(intValue)

    transToSend.Sender = os.Args[4]
    transToSend.Receiver = os.Args[5]

    if jobName == "-t"{
      messToSend.Job = "transaction"
    }else if jobName == "-f"{
      messToSend.Job = "fake"
    }
    messToSend.Body= transToSend

  } else if jobName == "-v"{
    if len(os.Args) < 4{
        fmt.Println("Please use ./client -v ip idTrans")
        os.Exit(1)
    }
    intValue, err := strconv.Atoi(os.Args[3])
    if err != nil{
      fmt.Println("Error during parsing of idTrans:", err.Error())
      os.Exit(1)
    }
    transToSend.Id = uint32(intValue) //Only the id is used
    messToSend.Job = "vote"
    messToSend.Body= transToSend

  }else if jobName == "-l"{
    messToSend.Job = "list"
    messToSend.Body= nil

  }

  conn, err := net.Dial("tcp", addrServer + ":" + PORT_TO_USE_STRING)
  if err != nil {
      fmt.Printf("Error, impossible to contact the server: ", err.Error())
      os.Exit(1)
  }

  encoderOnStream := json.NewEncoder(conn)
  err = encoderOnStream.Encode(messToSend)
  //fmt.Printf("Structure sent to the server: ")
  //fmt.Println(messToSend)

   if err != nil {
       fmt.Printf("Error, impossible to write the structure in JSON on the stream:", err.Error())
       os.Exit(1)
   }else{
     fmt.Println("Message sent with success !")
   }
   //Wait an answer from the server
  if jobName == "-v" || jobName == "-l"{
    var messageReceivedInStruct mess.Message
    decoderFromStream := json.NewDecoder(conn)
    err = decoderFromStream.Decode(&messageReceivedInStruct)  //Wait to receive the JSON
    if err != nil {
        fmt.Println("Error, impossible to decode message:", err.Error())
        os.Exit(1)
    }
    //fmt.Printf("Message received: ")
    //fmt.Println(messageReceivedInStruct)

    if jobName == "-v"{
      answerVote := mess.Extract_vote_answer_from_message(messageReceivedInStruct)
      fmt.Printf("La transaction %d est correcte à %.2f%%\r\n", transToSend.Id, answerVote.Percentage)

    }else if jobName == "-l"{
      answerdb := bd.Extract_database_from_message(messageReceivedInStruct)
      answerdb.Print()
    }
  }

  conn.Close()

}
