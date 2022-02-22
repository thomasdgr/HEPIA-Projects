import os

P = [1,2,4,8,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256]
n = 1000
I = [100,500,1000,5000,10000,15000]
J = [100,500,1000,5000,10000,15000]
k = 4

for p in P:
    for i in range(0, len(I)):
        for _ in range(k):
            x = int(p / 18) + 1
            os.system("sbatch --ntasks=" + str(p) + " --partition=shared-cpu --nodes=" + str(x) + "-" + str(x) + " script.sh " + str(I[i]) + " " + str(J[i]) + " " + str(n))