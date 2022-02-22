import os
import sys
import time
import subprocess

# script is using xterm to run terminals
# to install xterm:
#   sudo apt-get update -y
#   sudo apt-get install -y xterm

FOLDER = "big_network"
PORT = 50000
NAME_ALGO_FILE = "distributed_alg"

try:
    id = int(sys.argv[1])
    size = 0
    if FOLDER == "small_network":
        size = 7
    elif FOLDER == "medium_network":
        size = 18
    elif FOLDER == "big_network":
        size = 37
    else:
        print("folder \"" + FOLDER + "\" not found")
        sys.exit(0)
except:
    print("Command: python3 script.py X\n  |___  with X, the index of the proactive node between 1 and " + str(size))
    sys.exit(0)

for i in range(1,size):
    if i != id:
        subprocess.Popen(["xterm -hold -e ./"  + NAME_ALGO_FILE + " " +  str(PORT) + " neighbour-" + str(i) + ".yaml" + " WAIT &"], shell=True)
        time.sleep(0.2)

subprocess.Popen(["xterm -hold -e ./"  + NAME_ALGO_FILE + " " +  str(PORT) + " neighbour-" + str(id) + ".yaml" + " INIT &"], shell=True)
sys.exit(0)
