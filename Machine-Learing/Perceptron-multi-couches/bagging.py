from sklearn.ensemble import RandomForestClassifier
from pmc import *

def get_sample(attributs, classes, proportion = 0.1):
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
        nb_pmc = int(sys.argv[1])
        path = sys.argv[2]

    except:
        print("Example of program use: python3 bagging.py 2 data/heart.dat") 
        sys.exit(0)

    attributs, classes = read_file(path)
    
    moyenne_bag = 0
    moyenne_skl = 0
    for i in range(10):
        attributs_train, attributs_test, classes_train, classes_test = train_test_split(attributs, classes, test_size=0.1, random_state=0)

        moyenne_bag += bagging(25, 50, attributs_train, 1000, classes_train)

        clf=RandomForestClassifier(n_estimators=1000,criterion="gini", max_features="sqrt", max_depth=100)
        clf.fit(attributs_train, classes_train)
        moyenne_skl += clf.score(attributs_test, classes_test) * 100
    
    print("BAG -> total: " + str(moyenne_bag / 10) + "%")
    print("SKL -> total: " + str(moyenne_skl / 10) + "%")