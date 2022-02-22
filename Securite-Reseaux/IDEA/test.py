
number = 1
modulo = 17

#if number == 0:

reste = 1
quotient = 0

Pmoins1 = 1
Pmoins2 = 0
Ptmp = 0
stepNumber = 0

arrayP= []
arrayP.append(0)
arrayP.append(1)
arrayQuotient = []
diviseur = 0
dividende = 0

while reste >0:
    if stepNumber == 0:
        dividende = modulo
        diviseur = number
    else:
        dividende = diviseur
        diviseur = reste

    quotient = int(dividende / diviseur)
    arrayQuotient.append(quotient)
    reste = dividende % diviseur
    if stepNumber>1:
        arrayP.append((arrayP[stepNumber-2] - arrayP[stepNumber-1] * arrayQuotient[stepNumber-2])%modulo)

    stepNumber+=1;

print((arrayP[stepNumber-2] - arrayP[stepNumber-1] * arrayQuotient[stepNumber-2])%modulo)
