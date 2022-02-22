from sklearn.ensemble import RandomForestClassifier
from pmc_test import *

def get_sample(attributs, classes, proportion = 0.2):
    output_attributs = []
    output_classes = []
    for _ in range(int(len(attributs) * proportion)):
        k = int(random.random() * len(attributs))
        output_attributs.append(attributs[k].tolist())
        output_classes.append(classes[k].tolist())
    return output_attributs, output_classes

def bagging(nb_pmc, neurons, attributs, iter, classes):
    array_weights = []
    hidden_layer_result = []
    weights = []
    for _ in range(nb_pmc):
        new_attributs, new_classes = get_sample(attributs, classes)
        a1, a2, a3 = train(neurons, new_attributs, iter, new_classes)
        array_weights.append(a1)
        hidden_layer_result.append(a2)
        weights.append(a3)
    count = 0
    for k in range(len(attributs)):
        h = 0
        for i in range(nb_pmc):
            for j in range(neurons):
                hidden_layer_result[i][j] = sigmoid(sum(attributs[k], array_weights[i][j]))
            h += 1 if (sigmoid(sum(hidden_layer_result[i], weights[i])) > 0.5) else 0
        if round(h / nb_pmc) == classes[k]:
            count += 1
    return (count / len(attributs)) * 100

if __name__ == "__main__" :
    try:
        path = sys.argv[1]
    except:
        print("Example of program use: python3 bagging.py data/heart.dat") 
        sys.exit(0)

    attributs, classes = read_file(path)
    
    neurons = [1, 10, 20, 50, 100]
    iters = [100, 500, 1000, 5000]

    with open('res_bag_australian.txt', 'w') as f:
        for n in neurons:
            for i in iters:
                res_mlp = []
                res_skl = []
                for _ in range(10):
                    attributs_train, attributs_test, classes_train, classes_test = train_test_split(attributs, classes, test_size=0.1, random_state=0)

                    res_mlp.append(bagging(25, n, attributs_train, i, classes_train))

                    #clf=RandomForestClassifier(n_estimators=n,criterion="gini", max_features="sqrt", max_depth=i)
                    #clf.fit(attributs_train, classes_train)
                    #res_skl.append(clf.score(attributs_test, classes_test) * 100)

                print(n, ",", i,",","{:.2f}".format(np.average(res_mlp)), ",","{:.2f}".format(np.std(res_mlp)), "\n", file=f)
