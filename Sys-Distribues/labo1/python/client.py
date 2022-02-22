"""
Dagier Thomas, Rod Quentin 3ème ISC
Lab 1: Developing and deploying a broadcast algorithm for a blockchain system. Broadcast by wave with and without ack are implemented.
"""

import sys
import socket
import json
import os

PORT = 50000 # common to every nodes

# take a message and the ip of a node
# send the message through a socket (we assume the port of the server node is the same as the client node)
def send_message(message, ip):
    server_info = (ip, PORT)
    s.sendto(json.dumps(message).encode(), server_info)
    # no needs to send message in "parallel"

# return the content of the message received by the client
def listen_message():
    content, addr = s.recvfrom(1024)
    return json.loads(content)

# take a transaction (created by the user) and send it to a server node (after asking for a node id)
# the transaction will be broadcast through the network for each node
def create_transaction(transaction):
    if transaction != None:
        message = json.loads('{ "job":"transaction", "body":""}')
        message["body"] = transaction
        send_message(message, get_ip())

# take a transaction (created by the user) and ask for the percentage of nodes from the network that have the transaction in their db
# return the precentage (nb of nodes that contains the transaction in their db / nb of nodes in the network)
def vote(transaction):
    if transaction != None:
        message = json.loads('{ "job":"vote", "body":""}')
        message["body"] = transaction
        send_message(message, get_ip())
        return listen_message()["body"]

# take a fake transaction (created by the user) and send it to only one server node (after asking for a node ip)
# the transaction will override one that aleready exists
def fake(fake_trans):
    if transaction != None:
        message = json.loads('{ "job":"fake", "body":""}')
        message["body"] = fake_trans
        send_message(message, get_ip())

# take a node id and ask a node for its db
# return the db in json format
def list_transaction(ip):
    message = json.loads('{ "job":"list", "body":""}')
    send_message(message, ip)
    return json.dumps(listen_message(), indent=4)

# ask for a node ip to the user
def get_ip():
    return str(input("Select the ip of the node to contact: "))

# ask for a transaction to the user and check if its values are acceptable
def get_transaction():
    id = 0
    try:
        id = int(input("Select the id of the transaction: "))
    except:
        print("Please select any number")
        return
    sender = input("Select the sender: ")
    receiver = input("Select the receiver: ")
    try:
        amount = int(input("Select the amount: "))
    except:
        print("Please select any number")
        return
    
    transaction = '{ "id":' + str(id) + ', "sender":"' + str(sender) + '", "receiver":"' + str(receiver) + '", "amount":' + str(amount) + '}'
    return json.loads(transaction)

### MAIN

# create a socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

########
s.bind(("127.0.0.10", PORT)) # version to use for the local dev.
#s.bind(("0.0.0.0", PORT)) # version to user for the dist dev.
########

while True:
    print("Please select an option:")
    print("[1] Insert a transaction")
    print("[2] Vote for a transaction")
    print("[3] Fake a transaction")
    print("[4] List all transactions")
    print("[0] Quit")

    try:
        option = int(input("Option: "))
    except:
        print("Please select a number between 0 and 4")
        sys.exit(0)
    if option < 0 or option > 4 :
        print("Please select a number between 0 and 4")
        sys.exit(0)

    if option == 0:
        s.close()
        sys.exit(0)
    elif option == 1:
        transaction = get_transaction()
        create_transaction(transaction)
    elif option == 2:
        transaction = get_transaction()
        print("Pourcentage de noeuds qui possèdent cette transaction: " + str(vote(transaction)) + "%")
    elif option == 3:
        transaction = get_transaction()
        fake(transaction)
    elif option == 4:
        print(list_transaction(get_ip()))
    
    input("\nPresse enter to continue...")
    os.system('clear')