"""
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
"""

import yaml
import sys
import socket
import json
from threading import Thread

# global for convenience
PORT= 50000 # common to every nodes
count = 0 # number of nodes that sent a message to this node (for the two algorithm)
reach = False # check if this node has aleready received a message from an other node or the client (for the two algorithm)
value_vote = 0 # number of nodes (children + this one) that contains a transaction in their db (broadcast with ack)
nodes = 1 # number of nodes (children + this one) that answer to this node (broadcast with ack) 
parent = "" # father's ip address of this node (broadcast with ack)
database = json.loads('{ "transactions": [] }') # database of this node

# BROADCAST BY WAVES algorithm
# take a content (message that contains the transaction) and the ip of the sender node
# append the transaction in his db by broadcasting the transaction through the network
def create_transaction(content, addr):
    global count
    global reach
    # check if the sender is the client or a neighbour node
    if is_neighbour(addr):
        count = count + 1
    if not reach:
        # add the transaction in his db and broadcast using threads
        reach = True
        if content["body"] not in database["transactions"]:
            database["transactions"].append(content["body"])
        send_neighbours(content)
    if count == len(server_infos["neighbours"]):
        # reset the values for an other broadcast
        reach = False
        count = 0

# BROADCAST BY WAVES WITH ACK algorithm
# take a content (message that contains the transaction) and the ip of the sender node
# spread the transaction to his neighbours and wait for an answer
# the answer is a tuple of the current nb of nodes that contains the transaction and the current nb of nodes
# those values will be increased in result_vote() and returned as a precentrage to the client by the proactive node
def vote(content, addr):
    global count
    global reach
    global parent
    global value_vote
    global nodes
    # same steps as the broadcast by waves algorithm
    if is_neighbour(addr):
        count += 1
    if not reach:
        reach = True
        parent = addr
        # broadcast message to all neighbours except the father node
        send_neighbours(content, parent)
        value_vote = 1 if content["body"] in database["transactions"] else 0
    # if the node has received from each neighbour, it sends the answer to his father node
    if count == len(server_infos["neighbours"]) and reach:
        reach = False
        count = 0
        content["job"] = "vote_answer"
        body = '{ "rate":' + str(value_vote) + ', "nodes":' + str(nodes) +'}'
        content["body"] = json.loads(body)
        send_message(content, parent)

# ACK from the BROADCAST BY WAVES WITH ACK algorithm
# take a content (message that contains the transaction) and the ip of the sender node
# spread and update the answer to his father node
# the answer is a tuple of the current nb of nodes that contains the transaction and the current nb of nodes
def result_vote(content, addr):
    global value_vote
    global parent
    global count
    global reach
    global nodes
    # update of the values
    value_vote += content["body"]["rate"]
    nodes += content["body"]["nodes"]
    if is_neighbour(addr):
        count = count + 1
    if count == len(server_infos["neighbours"]) and reach:
        reach = False
        count = 0
        # check if the father node is not the neighbour -> then its the client so we return a percentage
        if not is_neighbour(parent):
            content["body"] = (value_vote / nodes) * 100
        # otherwise this is note a proactive node so we just send the two values    
        else:
            content["body"]["rate"] = value_vote
            content["body"]["nodes"] = nodes
        send_message(content, parent)
        # reset the values for an other broadcast
        value_vote = 0
        nodes = 1

# take a content (message that contains the fake transaction) and the ip of the sender node (must be the client)
# update the transaction only in his db
def fake(content, addr):
    for i, item in enumerate(database["transactions"]):
        if item["id"] == content["body"]["id"]:
            database["transactions"][i] = content["body"]

# take a content (message with no body) and the ip of the sender node (must be the client)
# return the db to the client
def list_transaction(content, addr):
    send_message(database, addr)

# take a content (message with any body and job)
# it can also take an exception (for example if we dont wanna send the message to the father node)
def send_neighbours(content, exception = ""):
    for n in server_infos["neighbours"]:
        if n["address"] != exception:
            send_message(content, n["address"])

# take a content (message with any body and job) and the ip of the sender node
def send_message(content, addr):
    # messages are sent in "parallel" using a socket  
    thread = Thread(target = s.sendto, args = (json.dumps(content).encode(), (addr, PORT)))
    thread.start()
    # we dont expect for a return value so there is no needs to join() the thread

# take a path to a yaml config file (unique for every node) and return its content
def read_yaml_file(path):
    with open(path, "r") as f:
        try:
            data = yaml.safe_load(f)
        except yaml.YAMLError as exc:
            print(exc)
    return data

# take an ip address and check if the node is a neighbour to this node
def is_neighbour(addr):
    for n in server_infos["neighbours"]:
        if n["address"] == addr:
            return True
    return False

##### MAIN

instructions = {
    "transaction": create_transaction,
    "vote": vote,
    "vote_answer": result_vote,
    "fake": fake,
    "list": list_transaction
}

try:
    id = int(sys.argv[1])
except:
    print("Example of program use:   python3 server.py 2")
    sys.exit(0)

# yaml file content
server_infos = read_yaml_file("../server_infos/neighbour-" + str(id) + ".yaml")

# create socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

########
s.bind((server_infos["address"], PORT)) # version to use for the local dev.
#s.bind(("0.0.0.0", PORT)) # version to user for the dist dev.
########

# we never stop the server unless we press ctrl+C
while True:
    content, addr = s.recvfrom(1024) # wait unit we receive a message
    content = json.loads(content) # convert the message to json
    instructions[content["job"]](content, addr[0]) # call the function according to the job read from the message
s.close()