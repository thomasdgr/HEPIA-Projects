from matplotlib import pyplot as plt
from load_vec import load_vector
import glob

type_of_data = 'curve'
listOfVectors = glob.glob("src/Python/*X.vec")

for nameVectorX in listOfVectors:
    nameVectorY = nameVectorX.replace("X","Y",1)
    description = ((nameVectorX.split('/'))[-1])[0:-5]

    X = load_vector(nameVectorX)
    Y = load_vector(nameVectorY)

    if type_of_data == 'curve':
        plt.plot(X, Y, label=description)
    else:
        plt.scatter(X, Y, marker='x', label="my points")

    plt.xlabel("X")
    plt.ylabel("Y")
    plt.legend(loc="upper right")

plt.show()
