from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn import datasets, preprocessing
import numpy as np
import random
import math
import sys

def read_file(path): 
    data = np.asarray(np.loadtxt(path, delimiter=','),dtype=np.float32)
    data = preprocessing.MinMaxScaler().fit(data).transform(data)
    attributs = np.delete(data, len(data[0]) - 1, axis=1)
    classes = np.array([row[len(data[0]) - 1].astype(np.int64) for row in data])
    return attributs, classes

def sigmoid(x):
    return 1 / (1 + math.exp(-x))

def sum(x, w):
    result = 1 * w[0]
    for i in range(len(x)):
        result += x[i] * w[i+1]
    return result

def train(neurons, attributs, iter, classes):
    array_weights = []
    hidden_layer = [0] * neurons
    weights = []
    weights.append(random.random() - 0.5)
    for _ in range(neurons):
        neurons_weights = []
        for _ in range(len(attributs[0]) + 1):
            neurons_weights.append(random.random() - 0.5)
        array_weights.append(neurons_weights)
        weights.append(random.random() - 0.5)
    for _ in range(iter):
        k = int(random.random() * len(attributs))        
        for i in range(neurons):
            hidden_layer[i] = sigmoid(sum(attributs[k], array_weights[i]))
        y = sigmoid(sum(hidden_layer, weights))        
        for i in range(len(weights)):
            weights[i] += 0.1 * (classes[k] - y) * ((1 if i == 0 else hidden_layer[i - 1]) * (1 - y))
    return array_weights, hidden_layer, weights

def test(neurons, attributs, weight_input, hidden_layer, weight_hidden, classes):
    count = 0
    for i in range(len(attributs)):
        for index_hidden_cell in range(neurons):
            hidden_layer[index_hidden_cell] = sigmoid(sum(attributs[i], weight_input[index_hidden_cell]))
        h = 1 if (sigmoid(sum(hidden_layer, weight_hidden)) > 0.5) else 0
        if h == classes[i]:
            count += 1
    return (count / len(attributs)) * 100

if __name__ == "__main__" :
    try:
        path = sys.argv[1]
    except:
        print("Example of program use: python3 pmc_plot.py data/heart.dat")
        sys.exit(0)

    attributs, classes = read_file(path)

    neurons = [10, 50, 100, 200, 500, 1000]
    iters = [100, 500, 1000, 2000, 5000]

    with open('res_mlp_australian.txt', 'w') as f:
        for n in neurons:
            for i in iters:
                res_mlp = []
                res_skl = []
                for _ in range(10):
                    attributs_train, attributs_test, classes_train, classes_test = train_test_split(attributs, classes, test_size=0.1, random_state=0)

                    array_weights, hidden_layer, weights = train(n, attributs_train, i, classes_train)
                    res_mlp.append(test(n, attributs_test, array_weights, hidden_layer, weights, classes_test))

                    #clf = MLPClassifier(solver='sgd', activation='logistic', max_iter=i, hidden_layer_sizes=n, learning_rate_init=0.1)
                    #clf.fit(attributs_train, classes_train)
                    #res_skl.append(clf.score(attributs_test, classes_test) * 100)

                print("Pour", n, "neurones et", i, "itérations:\n  moyenne:", "{:.2f}".format(np.average(res_mlp)), "\n  ecart-type:", "{:.2f}".format(np.std(res_mlp)), "\n", file=f)
