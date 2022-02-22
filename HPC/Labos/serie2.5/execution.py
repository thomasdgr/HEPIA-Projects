import os


def execution(P, N, k):
    for p in P:
        for n in N:
            for _ in range(k):
                os.system("sbatch --ntasks=" + str(p) + " --partition=shared-cpu script.sh " + str(n))

## MAIN

P = input("Slectionner les différentes valeurs de p:").split(",")
for i in range(0,len(P)):
    P[i] = int(P[i])

N = input("Slectionner les différentes valeurs de n:").split(",")
result = {}
output = {}
for i in range(0,len(N)):
    N[i] = int(N[i])
    result[int(N[i])] = []
    output[int(N[i])] = []

k = int(input("Slectionner la valeur de k:"))

execution(P,N,k)
