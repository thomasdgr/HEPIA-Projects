import os

k = 1
T = [10000,1000000]

I = [1000]
J = [1000]

for t in T:
    for i in range(0, len(I)):
        for _ in range(k):
            os.system("sbatch ../src/script.sh " + str(I[i]) + " " + str(J[i]) + " " + str(t) + " " + str(1110) + " " + str(1100) + " " + str(32) + " " + str(32))
