from PyQt5.QtWidgets import QWidget, QApplication, QSlider, QLabel, QVBoxLayout, QGridLayout, QPushButton, QHBoxLayout
from PyQt5.QtGui import QPixmap, QColor, QImage
from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread, QTimer
from typing import List, Tuple
import numpy as np
import matplotlib.pyplot as plt
import random
import sys
import cv2
import time
import math

# enum qui va nous permettre de placer arbitrairement les éléments dans la grille
elements = ((0, 0, 1, 1), (0, 1, 1, 1), (1, 0, 1, 1), (2, 0, 1, 1),(1, 1, 2, 1))

class App(QWidget):
    def __init__(self):
        super().__init__()
        
        glay = QGridLayout(self)
        
        # pour rafraichir la vidéo, on utilise le timer de l'app
        self.timer = QTimer(self)
        self.timer.setInterval(1)
        self.timer.timeout.connect(lambda: self.update_image(glay))
        self.timer.start()
        
        # 2 vboxs pour les sliders de chaque mask
        vb1 = QVBoxLayout()
        for i in range(0,6):
            vb1.addWidget(QLabel(d.get(i)))
            vb1.addWidget(self.create_slider(i))
        glay.addLayout(vb1,1,1,1,1)
        vb2 = QVBoxLayout()

        for i in range(0,6):
            vb2.addWidget(QLabel(d.get(i)))
            vb2.addWidget(self.create_slider(i+6))
        glay.addLayout(vb2,2,1,1,1)

        self.setLayout(glay)
        self.setWindowTitle("wheel.py")
        self.resize(700, 700)
        self.show()

    # rafraichissement de la grille {glay}
    def update_image(self, glay: QGridLayout) -> None:
        # lecture d'une frame
        ret, img = cap.read()

        # check si la vidéo est terminée
        try:
            hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        except:
            self.timer.stop()
            save_angles_and_display(angles)
            return

        # conversion d'une image en QImage
        height, width, channel = img.shape
        bytesPerLine = 3 * width
        qImg = QImage(img.data, width, height, bytesPerLine, QImage.Format_BGR888)

        # calcul du mask rouge et conversion en QImage
        red_min = np.array([ values[0], values[1], values[2] ])
        red_max = np.array([ values[3], values[4], values[5] ])
        red_mask = cv2.inRange(hsv, red_min, red_max)
        red_qImg = self.convert_grayscale_to_qImgBGR(red_mask)
        
        # calcul du mask jaune et conversion en QImage
        yellow_min = np.array([ values[6], values[7], values[8] ])
        yellow_max = np.array([ values[9], values[10], values[11] ])
        yellow_mask = cv2.inRange(hsv, yellow_min, yellow_max)
        yellow_qImg = self.convert_grayscale_to_qImgBGR(yellow_mask)
        
        # combinaison des 2 masks
        combine_make = cv2.bitwise_or(red_mask, yellow_mask)
        tmp = cv2.cvtColor(combine_make, cv2.COLOR_GRAY2BGR)

        # ajout de l'angle d'inclinaison du volant (à partir des 2 masks)
        add_line_and_angle(red_mask, yellow_mask, tmp)

        # conversion en QImage
        height, width, channel = tmp.shape
        qImg_combine = QImage(tmp.data, width, height, 3 * width, QImage.Format_BGR888)
        
        # mise à jour des QImage dans la grille
        self.update_grid(glay, qImg, red_qImg, yellow_qImg, qImg_combine)

    # rafraichissement de chaque image {qImg,red_qImg,yellow_qImg,qImg_combine} de la grille {glay}
    def update_grid(self, glay: QGridLayout, qImg: QImage, red_qImg: QImage, yellow_qImg: QImage, qImg_combine: QImage) -> None:
        for i, (row, col, row_span, col_span) in enumerate(elements):
            label = QLabel("{}".format(i))
            if row == 0 and col == 0:
                pixmap = QPixmap(qImg).scaled(350,300)
                label.setPixmap(pixmap)
                glay.addWidget(label, row, col, row_span, col_span)
            if row == 0 and col == 1:
                pixmap = QPixmap(qImg_combine).scaled(350,300)
                label.setPixmap(pixmap)
                glay.addWidget(label, row, col, row_span, col_span)
            if row == 1 and col == 0:
                pixmap = QPixmap(red_qImg).scaled(350,300)
                label.setPixmap(pixmap)
                glay.addWidget(label, row, col, row_span, col_span)
            if row == 2 and col == 0:
                pixmap = QPixmap(yellow_qImg).scaled(350,300)
                label.setPixmap(pixmap)
                glay.addWidget(label, row, col, row_span, col_span)

    # conversion d'une image en nuance de gris {img} vers une QImage pour l'afficher
    def convert_grayscale_to_qImgBGR(self, img: np.ndarray) -> QImage:
        tmp = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
        height, width, channel = tmp.shape
        return QImage(tmp.data, width, height, 3 * width, QImage.Format_BGR888)

    # création d'un QSlider avec une valeur {values[i]} par défaut
    def create_slider(self, i):
        slider = QSlider(Qt.Horizontal, self)
        slider.setRange(0, 255)
        slider.setValue(values[i])
        slider.setTickPosition(QSlider.TicksBelow)
        slider.setTickInterval(10)
        slider.setFocusPolicy(Qt.NoFocus)
        slider.setPageStep(1)
        slider.valueChanged.connect(lambda val, i=i: self.change_value(val,i))
        return slider
    
    # modification de la valeur du slider d'indice {i} dans le tableau "values"
    def change_value(self, value: int, i: int) -> None:
        values[i] = value

# ajout, sur le mask combiné de la drote entre les centres des 2 formes les plus présentes
# ajout de la droite entre les 2 centres sur le mask combiné
def add_line_and_angle(red_mask: np.ndarray, yellow_mask: np.ndarray, img: np.ndarray) -> None:
    # detection des contours sur les masks
    bin_img_red = cv2.threshold(red_mask, 127, 255, cv2.THRESH_BINARY)[1]
    contours_red, hierarchy = cv2.findContours(bin_img_red, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    bin_img_yellow = cv2.threshold(yellow_mask, 127, 255, cv2.THRESH_BINARY)[1]
    contours_yellow, hierarchy = cv2.findContours(bin_img_yellow, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    if contours_red and contours_yellow:
        contours = list()
        points = list()
        # ajout du plus grand contour présent dans chaque mask
        contours.append(max(contours_yellow, key = cv2.contourArea))
        contours.append(max(contours_red, key = cv2.contourArea))
        for c in contours:
            M = cv2.moments(c)
            try:
                cX = int(M["m10"] / M["m00"])
                cY = int(M["m01"] / M["m00"])
                points.append((cX,cY))
                cv2.circle(img, (cX,cY), 5, (0,0,255), -1)
            except Exception as ZeroDivisionError:
                pass
        if len(points) == 2:
            # ajout de la droite entre les 2 centres dans l'image combinée
            cv2.line(img, points[0], points[1], (255,0,0), 3) 
            # ajout de l'angle entre la droite et l'axe horizontal
            angles.append(np.rad2deg(-1 * math.atan2(points[1][1] - points[0][1], points[1][0] - points[0][0])))

# écriture du contenu de la liste {angles} dans un fichier
# affichage du contenu sur un graphique
def save_angles_and_display(angles: List[float]) -> None:
    f = open('labo2/angle.txt', 'w+')
    for angle in angles:
        f.write(str(angle) + ";")
    f.close()

    plt.plot(angles)
    plt.show()


##### MAIN #####

# video
cap = cv2.VideoCapture('labo2/wheel_racing.avi')

# dictionnaire pour stocker les noms des sliders
d = dict()
d[0] = "hue_min"
d[1] = "sat_min"
d[2] = "val_min"
d[3] = "hue_max"
d[4] = "sat_max"
d[5] = "val_max"

# tableaux des valeurs initiales des sliders
values = [150, 150, 200,        # red_min
          255, 255, 255,        # red_max
           20, 100, 100,        # yellow_min
           30, 255, 255]        # yellow_max

angles: List[float] = [] 

app = QApplication(sys.argv)
a = App()
sys.exit(app.exec_())
cap.release()
cv2.destroyAllWindows()