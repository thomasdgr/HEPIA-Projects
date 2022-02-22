C Project developped by Thomas Dagier from October 2, 2019 to November 29, 2019.

This librairy aims to manipulate pgm files (P2 type) applying arithmetic function (mult,add,sub,clipper...) geometric function (rotate, translate, zoom, symmetry...) and filter (sharpen, sobel, enhance, blur...)

- Only PGM files are allowed because of their structure.

After downloading the folder, in matrice-ci :

 *make clean image_transform*  

./image_transform operations (visual)*

"operations" is a .txt file which contains all commands to apply on a pgm file. To see the structure follow the markdown bellow. You must start your operations by a reading function as the end must be after a writing function. It is possible to write before or after this block but a message will appear telling you "pgm is not initialized".

"visual" is not necessary but offers you the possibility to see every steps of your command file using SDL2.   

```English
commands available (for an operation_file.txt in /matrice-ci folder) : 
    read "path/to/file.pgm"
    write "output_name.pgm"
    rotate centerX centerY angle
    photomaton
    translate factorX factoY
    # zoom can be in (positive factor) or out (negative) #
	zoom factorX factorY
    resize FactorX FactorY
    symmetry central (or) vertical (or) horizontal
    # filters #
    mult (or) add (or) sub "second/file/to/mult/with"
    #to emphasis by a number#
    mult (or) add (and) scalar
```

Do not edit anything unless you want to destroy the project

To see if I've done correctly my homework, still in matrice-ci :

 *make clean tests*  

NB : I didn't made tests for functions that were not given (6 to 10 from any file.c) 



