import os
import time
import sys

for i in range(1 , len(sys.argv)):
    print("scp -o StrictHostKeyChecking=no -i ~/.ssh/gussSShAWS.pem -r ./ressources/server" + str(i) + " src/ ec2-user@" + sys.argv[i] + ":")
    os.system("scp -o StrictHostKeyChecking=no -i ~/.ssh/trung.pem -r ./ressources/server" + str(i) + " src/ ec2-user@" + sys.argv[i] + ":")

for i in range(1, len(sys.argv)):
    print("ssh -o StrictHostKeyChecking=no -i ~/.ssh/trung.pem ec2-user@" + sys.argv[i] + " &")
    os.system("xterm -hold -e ssh -o StrictHostKeyChecking=no -i ~/.ssh/trung.pem  ec2-user@" + sys.argv[i] + " &")

