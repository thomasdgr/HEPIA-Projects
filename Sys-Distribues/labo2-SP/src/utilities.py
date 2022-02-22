from socket import socket
import yaml
import json
from threading import Thread

def readYamlFile(path_yamlFile):
    with open(path_yamlFile, "r") as stream:
        try:
            return yaml.safe_load(stream)
        except yaml.YAMLError as exc:
            print(exc)

def readJsonFile(idServer):
    with open('server' + str(idServer) + '/routing_table' + str(idServer) + '.json', "r") as stream:
        return json.load(stream)

def writeInJsonFile(routing_table, idServer):
    with open('server' + str(idServer) + '/routing_table' + str(idServer) + '.json', "w") as stream:
        json.dump(routing_table, stream)

def updateJsonFile(routing_table, update, index, idServer):
    routing_table[index] = update
    writeInJsonFile(routing_table, idServer)
  
def sendData(s, ip, port, message):
    try:
        s.sendto(json.dumps(message).encode(), (ip,port) )
    except socket.error as e:
        print("{}:{}[{}] -> {}".format(ip, port, message, e))
        
def send2Neighbours(s, reseaux, port, message):
    threads = [None]*len(reseaux['neighbours'])
    for i in range (len(threads)):
        ip = reseaux['neighbours'][i]['address']
        threads[i] = Thread(target = sendData, args = (s, ip, port, message))
        threads[i].start()

def joinThreads(threads):
    for thread in threads:
        thread.join()
