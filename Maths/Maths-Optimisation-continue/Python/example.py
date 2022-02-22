from matplotlib import pyplot as plt
from load_vec import load_vector

for i in range(0,2):
    if i == 0:
        arrayPointsX = load_vector("RandomArrayPointsX.vec")
        arrayPointsY = load_vector("RandomArrayPointsY.vec")
        lineX = load_vector("RandomLineX.vec")
        lineY = load_vector("RandomLineY.vec")
        plt.title("Modelisation : Random Points")
    else:
        arrayPointsX = load_vector("TestArrayPointsX.vec")
        arrayPointsY = load_vector("TestArrayPointsY.vec")
        lineX = load_vector("TestLineX.vec")
        lineY = load_vector("TestLineY.vec")
        plt.title("Modelisation : Noise Straight Line")

    type_of_data_line = 'curve'

    if type_of_data_line == 'curve':
        plt.plot(lineX, lineY, label="my curve", color='r')
    else:
        plt.scatter(lineX, lineY, marker='x', label="my points")

    type_of_data_arrayPoints = 'scatter'

    if type_of_data_arrayPoints == 'curve':
        plt.plot(arrayPointsX, arrayPointsY, label="my curve")
    else:
        plt.scatter(arrayPointsX, arrayPointsY, marker='x', label="my points")

    plt.xlabel("arrayPointsX")
    plt.ylabel("arrayPointsY")
    plt.legend(loc="upper right")
    plt.show()
