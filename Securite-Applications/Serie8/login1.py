import os
import re
import bcrypt
from pynput import keyboard
from pynput.keyboard import Key, Controller

def login(d):
    print()
    
    id = input("Enter Login ID:")
    passwd = input("Enter Password:")
    if id in d.keys():       
        if bcrypt.checkpw(passwd.encode('utf-8'), d[id].encode('utf-8')):
            print("welcome " + str(id) + " !")
            return 0

    print("wrong credentials...")


def signup(d):
    print()
    while True:
        id = input("Welcome, please enter your new login ID: ")
        if id in d.keys():
            print("\n/!\ this id already exists, please choose an other one")
            continue
        hashed = bcrypt.hashpw(input("Enter your new password: ").encode('utf-8'), bcrypt.gensalt())
        if bcrypt.checkpw(input("Verify your password: ").encode('utf-8'), hashed):
            print("you've been added, Thanks !")
            if not bool(d):
                return (str(id) + " - " + str(hashed))
            else:
                return ("\n" + str(id) + " - " + hashed.decode('utf-8'))
        else:
            print("passwords does not match")

f = open('admin.txt','r+')
d = dict([ re.match(r'(.+?)\ \-\ (.+$)', line).groups() for line in f ])

res = input("\nHello sir, sign up or log in ? [s/l] : ")

while True:
    if res == 's':
        f.write(signup(d))
        break
    elif res == 'l':
        login(d)
        break
    else:
        print("\n/!\ please answer s or l :")
        res = input("create new user ? [s/l] : ")

f.close()




