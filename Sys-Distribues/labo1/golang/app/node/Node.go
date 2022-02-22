/*
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
*/

package node

import (
    "fmt"
    "net"
    "errors"
    "app/mess"
    "io/ioutil"
    "gopkg.in/yaml.v3"
    "encoding/json"
)

type InfosNeighbours struct{
  Id            uint8
  Address       string
  Edge_weight   int32
}

type InfosNodeYaml struct {
  Id      uint8
  Address string
  Neighbours []InfosNeighbours
}

//Extracts the informations of a yaml file in a infosNodeYaml structure
//yamlFile: Path to the file
//error will be nil if the operation was successfull.
//if an error occured you must not take care of the infos of the node
func Get_infos_from_yaml_file(yamlFile string) (InfosNodeYaml, error) {

    var infosNode InfosNodeYaml

    buf, err := ioutil.ReadFile(yamlFile)
    if err != nil { //An error occured
        return infosNode, err
    }

    err = yaml.Unmarshal(buf, &infosNode)
    if err != nil {
        return infosNode, fmt.Errorf("Errror during parsing YAML file %q: %v", yamlFile, err)
    }

    return infosNode, nil
}

//Returns true if the node with the address addr is a server. If a node is neighbour it's obligatory a server
//addr has to have the format: ex: "127.0.0.3"
func (infosSelfNode InfosNodeYaml) Is_a_server_address(addr string) (bool){
  for _, neighbour := range infosSelfNode.Neighbours {
    if addr == neighbour.Address {
      return true
    }
  }
  return false
}

//Returns the id if a neighbour exists with this address. Otherwise, an error is returned
func (infosSelfNode InfosNodeYaml) Get_id_of_address(addr string) (uint8, error){
  for _, neighbour := range infosSelfNode.Neighbours {
    if addr == neighbour.Address {
      return neighbour.Id, nil
    }
  }
  return 0, errors.New("Address not found. The node searched is not a neighbour")
}


//Sends the message messageToSend to the neighbour of of the node who has the id idNodeNeighbourDest.
//The node will contact his neighbours on the port portString
//Returns -1 if an error occured, otherwise 1
func (infosSelfNode InfosNodeYaml) Send_to_neighbour(idNodeNeighbourDest uint8, messageToSend mess.Message, portString string ) (int8){

  var addrNeighbourDest string = ""
  //Get the address of the node which has the id given in parameter
  for _, neighbourData := range infosSelfNode.Neighbours {
    if neighbourData.Id == idNodeNeighbourDest{
      addrNeighbourDest = neighbourData.Address
    }
	}
  if addrNeighbourDest == ""{ //String not modified -> Id doesn't exist and address not found
    return -1
  }

  //fmt.Println("addr found, send to " + addrNeighbourDest)
  conn, err := net.Dial("tcp", addrNeighbourDest + ":" + portString)
  if err != nil {
    fmt.Println("Impossible to contact host:", err)
    return -1
  }
  encoderOnStream := json.NewEncoder(conn)
  err = encoderOnStream.Encode(messageToSend)
  if err != nil {
      fmt.Printf("Error, impossible to write the structure in JSON on the stream:", err)
  }
  //fmt.Printf("Structure sent: ")
  //fmt.Println(messageToSend)

  conn.Close()
  return 1
}
//Send the message messageToSend to all neighbours of the node
//The node will contact his neighbours on the port portString
func (infosSelfNode InfosNodeYaml) Send_to_all_neighbours(messageToSend mess.Message, portString string){

  //Get the address of the node which has the id given in parameter
  for _, neighbourData := range infosSelfNode.Neighbours {
    go infosSelfNode.Send_to_neighbour(neighbourData.Id , messageToSend, portString)
	}
}

//Send the message messageToSend to all neighbours of the node except the nodes which have the id specified in the array idNodeExcludedArray
//The node will contact his neighbours on the port portString
func (infosSelfNode InfosNodeYaml) Send_to_all_neighbours_except(messageToSend mess.Message, idNodeExcludedArray []uint8, portString string){
  for _, neighbourData := range infosSelfNode.Neighbours {
    var isExcluded bool = false
    for _, iNodeExcluded := range idNodeExcludedArray{
      if neighbourData.Id == iNodeExcluded{
        isExcluded = true
      }
    }
    if !isExcluded{
      go infosSelfNode.Send_to_neighbour(neighbourData.Id , messageToSend, portString)
    }

  }
}

//Return the number of neighbours of the node
func (infosSelfNode InfosNodeYaml) Get_number_of_neighbours() (uint32){
  return uint32(len(infosSelfNode.Neighbours)) //length is always positive

}
