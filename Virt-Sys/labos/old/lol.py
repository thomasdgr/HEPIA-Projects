import getpass
import os
import socket

jsonString = '{echo \'{"execute":"guest-shutdown"}\'; sleep 1; }'

sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

try:
    # Connect to server and send data
    print("Attempting connection")
    sock.connect(str("/tmp/qga.sock"))
    print("Sending json string")
    sock.sendall(jsonString.encode('utf-8'))
    print("String sent")

finally:
    sock.close()

print("Sent:     {}".format(jsonString))
#     | socat unix-connect:/tmp/qga.sock -

