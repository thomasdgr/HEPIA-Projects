from keras.models import Sequential
from keras.layers.core import Dense, Flatten
from keras.layers import ReLU
from keras.layers.convolutional import Conv2D, MaxPooling2D
import numpy as np 
import matplotlib.pyplot as plt

ROWS = COLS = 28

if __name__ == "__main__" :

    X_train = np.loadtxt("./data/trainMnist").reshape((-1, ROWS, COLS, 1))
    X_test = np.loadtxt("./data/testMnist").reshape((-1, ROWS, COLS, 1))
    Y_train = np.loadtxt("./data/mnistTrainClass")
    Y_test = np.loadtxt("./data/mnistTestClass")

    model = Sequential()
    model.add(Conv2D(32, (3,3), padding='same', input_shape=(ROWS, COLS, 1)))
    model.add(ReLU())
    model.add(MaxPooling2D(pool_size=(2, 2)))

    #model.add(Conv2D(32, (3,3), padding='same', input_shape=(ROWS, COLS, 1)))
    #model.add(ReLU())
    #model.add(MaxPooling2D(pool_size=(2, 2)))

    model.add(Flatten())
    model.add(Dense(10, activation=("softmax")))
    model.summary()

    model.compile(loss='categorical_crossentropy', metrics=['accuracy'])
    res = model.fit(X_train, Y_train, batch_size=128, epochs=20, validation_split=0.2)

    score = model.evaluate(X_test, Y_test, batch_size=128)
    print("Score: ", (score[0] * 100), "%")
    print("Précision: ", (score[1] * 100), "%")
    for i in range(2):
        t = "accuracy" if i == 0 else "loss"
        plt.plot(res.history[t])
        plt.plot(res.history["val_" + t])
        plt.title("model " + t)
        plt.ylabel(t)
        plt.xlabel('epoch')
        plt.legend(['train', 'test'], loc='upper left')
        plt.show()