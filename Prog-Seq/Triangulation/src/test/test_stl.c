#include "test_stl.h"
#include "../stl/stl.h"
#include "../geom/triangle.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_stl_file_create(){
    stl_file mon_fichier_test = stl_file_create("create_test.stl", "test_function_stl_create");

    CU_ASSERT(strcmp(mon_fichier_test.name,"test_function_stl_create") == 0);
    CU_ASSERT(mon_fichier_test.file != NULL);

    stl_file_close(&mon_fichier_test);

    CU_ASSERT(remove("create_test.stl") == 0);

}

void test_stl_file_close(){
    // tested above
}

void test_stl_file_write_triangle(){
    point_3d point1 = point_3d_create(1,2,3);
    point_3d point2 = point_3d_create(4,5,6);
    point_3d point3 = point_3d_create(7,8,9);

    triangle mon_triangle = triangle_create(point1, point2, point3);

    stl_file mon_fichier_triangle = stl_file_create("triangle_test.stl", "mon_fichier_triangle");

    stl_file_write_triangle(&mon_fichier_triangle, &mon_triangle);
    stl_file_close(&mon_fichier_triangle);

    CU_ASSERT(remove("triangle_test.stl") == 0);
}

void test_stl_file_create_and_write(){
    point_3d pA = point_3d_create(0,0,0);
    point_3d pB = point_3d_create(1,0,0);
    point_3d pC = point_3d_create(1,0,1);
    point_3d pD = point_3d_create(0,0,1);
    point_3d pE = point_3d_create(0,1,0);
    point_3d pF = point_3d_create(1,1,0);
    point_3d pG = point_3d_create(1,1,1);
    point_3d pH = point_3d_create(0,1,1);

    triangle tab[12];

    triangle t_AFB = triangle_create(pA,pF,pB);
    tab[0] = t_AFB;
    triangle t_AEF = triangle_create(pA,pE,pF);
    tab[1] = t_AEF;

    triangle t_DCG = triangle_create(pD,pC,pG);
    tab[2] = t_DCG;
    triangle t_DGH = triangle_create(pD,pG,pH);
    tab[3] = t_DGH;

    triangle t_ABC = triangle_create(pA,pB,pC);
    tab[4] = t_ABC;
    triangle t_ACD = triangle_create(pA,pC,pD);
    tab[5] = t_ACD;

    triangle t_EGF = triangle_create(pE,pG,pF);
    tab[6] = t_EGF;
    triangle t_EHG = triangle_create(pE,pH,pG);
    tab[7] = t_EHG;

    triangle t_AHE = triangle_create(pA,pH,pE);
    tab[8] = t_AHE;
    triangle t_ADH = triangle_create(pA,pD,pH);
    tab[9] = t_ADH;

    triangle t_BFG = triangle_create(pB,pF,pG);
    tab[10] = t_BFG;
    triangle t_BGC = triangle_create(pB,pG,pC);
    tab[11] = t_BGC;

    stl_file_create_and_write("resultat_cube.stl", "reference_cube", tab, 12);
}
