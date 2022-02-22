#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void swap(int *first_item, int *second_item)
{
    int tmp = *first_item;
    *first_item = *second_item;
    *second_item = tmp;
}

int partition(int A[], int p, int q)
{
    swap(&A[p + (rand() % (q - p + 1))], &A[q]);

    int i = p - 1;
    for (int j = p; j <= q; j++)
    {
        if (&A[j] <= &A[q]){
            swap(&A[++i], &A[j]);
        }
    }
    return i;
}

void quicksort(int A[], int p, int q){
    if(p < q){
        int pivotIndx = partition(A, p, q);

        quicksort(A, p, pivotIndx-1);
        quicksort(A, pivotIndx + 1, q);
    }
}

int main()
{

    int size = 7;
    int lst[7];
    srand(142);

    for (int i = 0; i < size; i++)
    {
        lst[i] = rand();
        printf(" %d,", lst[i]);
    }

    quicksort(lst, 0, size);

    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf(" %d,", lst[i]);
    }
}