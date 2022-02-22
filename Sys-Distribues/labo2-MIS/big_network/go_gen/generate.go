// socket client for golang
// https://golangr.com
//Labo1 broadcast 
//author: Kirill Goundiaev

package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"strconv"

	"gopkg.in/yaml.v2"
)

type Node struct {
	Id     int    `yaml:"id"`
	Addrs  string `yaml:"address"`
	Weight int    `yaml:"edge_weight"`
}
type Link struct {
	Id int `yaml:"id"`
}
type Connection struct {
	Node       int    `yaml:"node"`
	Neighbours []Link `yaml:"neighbours"`
}

type NetworkData struct {
	Name        string       `yaml:"name"`
	Nodes       []Node       `yaml:"nodes"`
	Connections []Connection `yaml:"connections"`
}

type WriteNeighbour struct {
	Id      int    `yaml:"id"`
	Address string `yaml:"address"`
	Weight  int    `yaml:"edge_weight"`
}
type WriteData struct {
	MyId       int              `yaml:"id"`
	MyAddrs    string           `yaml:"address"`
	Neighbours []WriteNeighbour `yaml:"neighbours"`
}

const PrintRed = "\033[31m"
const PrintNorm = "\033[0m"

func askEntry(str string, reader *bufio.Reader) string {
	fmt.Print(str + " ")
	text, _ := reader.ReadString('\n')
	text = text[:len(text)-1] //remove '\n'
	return text
}

func checkEmpty(str string) bool {
	if len(str) < 1 {
		fmt.Println("Entry is empty")
		return true
	}
	return false
}

func readConf(fileName string) NetworkData {
	fmt.Println("Read file: " + fileName)
	yamlFile, err := ioutil.ReadFile(fileName)
	if err != nil {
		fmt.Printf("yamlFile.Get err   #%v ", err)
	}

	var c NetworkData
	err = yaml.Unmarshal(yamlFile, &c)
	if err != nil {
		log.Fatalf("Unmarshal: %v", err)
	}
	return c
}

func writeToFile(nodeId int, nodeData WriteData) {
	filename := "neighbour-" + strconv.Itoa(nodeId) + ".yaml"

	data, err := yaml.Marshal(&nodeData)
	if err != nil {
		log.Fatal(err)
	}
	err2 := ioutil.WriteFile(filename, data, 0664)
	if err2 != nil {
		log.Fatal(err2)
	}

}

func main() {
	reader := bufio.NewReader(os.Stdin)
	fileName := askEntry("name of network structure file", reader)
	if checkEmpty(fileName) {
		return
	}

	data := readConf(fileName)

	for j := 0; j < len(data.Nodes); j++ {
		var wrNode WriteData
		nodeId := j
		wrNode.MyAddrs = data.Nodes[nodeId].Addrs
		wrNode.MyId = data.Nodes[nodeId].Id

		for i := 0; i < len(data.Connections[nodeId].Neighbours); i++ {
			nd := data.Nodes[data.Connections[nodeId].Neighbours[i].Id-1]
			var neigh WriteNeighbour
			neigh.Id = nd.Id
			neigh.Address = nd.Addrs
			neigh.Weight = nd.Weight
			wrNode.Neighbours = append(wrNode.Neighbours, neigh)
		}
		writeToFile(nodeId+1, wrNode)
	}
}
