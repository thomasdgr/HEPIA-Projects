/*
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
*/

package bd

import (
    "fmt"
    "errors"
    "reflect"
    "app/mess"
    "app/trans"
    "encoding/json"
)

type Database struct{
  Transactions []trans.Transaction `json:"database"`
}

//Add a transaction t in the database
//Return 1 if the transaction was added. -1 otherwise (already exists).
func (db *Database) Add_transaction(transToAdd trans.Transaction)(int){
  for _, transCheck := range db.Transactions {
    if transToAdd.Id == transCheck.Id{
        return -1
      }
    }

  db.Transactions = append(db.Transactions, transToAdd)
  return 1
}

//Return the transaction which has the id transId
//If an error occured, the transaction returned will not be vaild
func (db *Database) Get_transaction(transId uint32)(trans.Transaction, error){
  for _, trans := range db.Transactions {
    if trans.Id == transId{
      return trans, nil
    }
  }
  var t trans.Transaction = trans.Transaction{0, "", "", 0}
  return t, errors.New("The transaction doesn't exist")

}

//Return 1 if the transaction transToCheck exists and is valid. Otherwise, -1. -2 if not exists
func (db *Database) Is_transaction_valid(transToCheck trans.Transaction)(int){
  fmt.Println(transToCheck)
  for _, trans := range db.Transactions {
    if transToCheck.Id == trans.Id{
        if(reflect.DeepEqual(transToCheck, trans)){
          fmt.Println(trans)
          return 1
        }else{
          return -1
        }
      }
  }
  return -2
}

//Return 1 if the transaction existed and was successfully replaced. Otherwise -1
func (db *Database) Replace_transaction(transToAdd trans.Transaction) (int){
  for iTrans, transCheck := range db.Transactions {
    if transToAdd.Id == transCheck.Id{
        db.Transactions[iTrans] = transToAdd
        return 1
    }
  }
  return -1
}

//Print the transactions contained in the database
func (db *Database) Print(){
  fmt.Println("-----Transactions------")
  for _, t := range db.Transactions {
    fmt.Printf("id:%d, sender:%s, receiver:%s, amount:%d\n", t.Id, t.Sender, t.Receiver, t.Amount)
  }
  fmt.Println("-----------------------")
}

//Add in the database the transaction contained in the message m
func (db *Database) Add_transaction_from_message(m mess.Message){
  transaction := mess.Extract_transaction_from_message(m)
  db.Add_transaction(transaction)
}

//Replace a transaction in the database by the one contained in the message m.
//The transaction replaced is the one with the id of the transaction in the message m
//Return 1 if the transaction existed and was successfully replaced. Otherwise -1
func (db *Database) Replace_transaction_from_message(m mess.Message)(int){
  transaction := mess.Extract_transaction_from_message(m)
  return db.Replace_transaction(transaction)
}

//Return the database presents in the Body of the message
func Extract_database_from_message(m mess.Message) (Database){
  var answerDb Database
  mapString, _ := m.Body.(map[string]interface{}) //Convert interface to map[string]

  //Convert map[string] to JSON to convert it in transaction
  mapStringJsonBytes, _ := json.Marshal(mapString)
  json.Unmarshal(mapStringJsonBytes, &answerDb)

  return answerDb
}
