import sys
import socket
from threading import Thread, Barrier, Lock, Semaphore
import json

from numpy.core.defchararray import add
import utilities as utils
import shortest_path as func
import numpy as np

port = int(sys.argv[1])
reseaux = utils.readYamlFile(sys.argv[2])
lock = Lock()
barrier = Barrier(len(reseaux['neighbours']))

status = sys.argv[3]

def main():
    
    table_routage = utils.readJsonFile(reseaux['id'])   
    nNoeud = len(table_routage)
    print("Start server " + reseaux['address'] + ":" + str(port) + " with " + status)
    allThread = []
    setT = []
    
    ordrerTraitement = []
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind(("", port))

        if (status == "INIT"):
            setINIT = func.determineSet(table_routage, 0)
            message2send = {"id" : reseaux['id'],"t": 0, "noeud_kDis" : setINIT}
            utils.send2Neighbours(s=s, reseaux=reseaux, port=port, message=message2send)
        
        for t in range(1, nNoeud):
            print("t" +str(t))
            countMesage = 0
            
            if ordrerTraitement:
                for data2Treat in ordrerTraitement:
                    if (data2Treat.get("t") == t - 1):
                        threadConn = Thread(target=func.handle_Conn, args=(data, t, table_routage, setT))
                        threadConn.start()
                        allThread.append(threadConn)
                        countMesage += 1
                        
            while countMesage < len(reseaux['neighbours']):                
                print("wait for message at t" + str(t) + " as countmessage: " + str(countMesage))
                conn, _ = s.recvfrom(1024)
                data = json.loads(conn.decode()) 
                
                if((t - 1) == 0 and status != "INIT" and countMesage == 0):
                    setINIT = func.determineSet(table_routage , 0)
                    message2send = {"id" : reseaux['id'], "t": 0,"noeud_kDis" : setINIT}
                    utils.send2Neighbours(s=s, reseaux=reseaux, port=port, message=message2send)
                
                if (data.get("t") == t - 1):
                    threadConn = Thread(target=func.handle_Conn, args=(data, t, table_routage, setT))
                    threadConn.start()
                    allThread.append(threadConn)
                    countMesage += 1
                else :
                    ordrerTraitement.append(data)
                    
            utils.joinThreads(allThread)
            if (t < nNoeud - 1):
                message2send = {"id" : reseaux['id'],"t": t, "noeud_kDis" : setT}
                print("message2sended")
                print(message2send)
                utils.send2Neighbours(s=s, reseaux=reseaux, port=port, message=message2send)
            allThread.clear()
            setT.clear()
            
        s.close()
    
    print("finale table routage")
    print("Server " + reseaux['address'] + ":" + str(port))
    print(table_routage)
    #utils.writeInJsonFile(table_routage, reseaux['id'])
            
if __name__ == "__main__":
    main()