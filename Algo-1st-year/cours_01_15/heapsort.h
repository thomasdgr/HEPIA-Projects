#ifndef HEAPSORT_H
#define HEAPSORT_H

int fils_g(int i);
int fils_d(int i);
int max3(int* tab,int size,int i);
void promotion(int* tab,int size,int i);
void entassement(int* tab,int size);
void heapsort(int* tab,int size);
void print(int* tab,int size,char* str);
#endif
