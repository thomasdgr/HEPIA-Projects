#include "test_heapsort.h"
#include "../heapsort/heapsort.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_heapsort(){
    hpq inserer_nom_ici;
    hpq_init(&inserer_nom_ici);
    hpq_push(&inserer_nom_ici, 7);
    hpq_push(&inserer_nom_ici, 2);
    hpq_push(&inserer_nom_ici, 8);
    hpq_push(&inserer_nom_ici, 5);
    hpq_push(&inserer_nom_ici, 10);
    hpq_push(&inserer_nom_ici, 3);
    hpq_push(&inserer_nom_ici, 6);
    hpq_push(&inserer_nom_ici, 4);
    hpq_push(&inserer_nom_ici, 1);
    hpq_push(&inserer_nom_ici, 9);

    heapsort(inserer_nom_ici.length, inserer_nom_ici.data);
    CU_ASSERT(inserer_nom_ici.data[0] == 1);
    CU_ASSERT(inserer_nom_ici.data[1] == 2);
    CU_ASSERT(inserer_nom_ici.data[2] == 3);
    CU_ASSERT(inserer_nom_ici.data[3] == 4);
    CU_ASSERT(inserer_nom_ici.data[4] == 5);
    CU_ASSERT(inserer_nom_ici.data[5] == 6);
    CU_ASSERT(inserer_nom_ici.data[6] == 7);
    CU_ASSERT(inserer_nom_ici.data[7] == 8);
    CU_ASSERT(inserer_nom_ici.data[8] == 9);
    CU_ASSERT(inserer_nom_ici.data[9] ==10);


    int* elem = malloc(sizeof(int));
    hpq_pop(&inserer_nom_ici, elem);
    CU_ASSERT(*elem ==10);
    CU_ASSERT(inserer_nom_ici.length == 9);

    hpq_peek(&inserer_nom_ici, elem);
    CU_ASSERT(*elem == 9);
    CU_ASSERT(inserer_nom_ici.length == 9);

    hpq_empty(&inserer_nom_ici);
    CU_ASSERT(hpq_is_empty(inserer_nom_ici) == true);
    
    hpq_free(&inserer_nom_ici);    
    free(elem);
}