#include "pgm/pgm.h"
#include "gfx/gfx.h"
#include "integrales/integrales.h"

/* fonction à changer */
double f(double x){
    double function = -(2.0 * x - 1.0) / (exp(x * x - x + 2.0));
    return function;
}

// validation de l'intégration numérique
void validationPart(double a, double b, int N){
    double exactValue = exactIntegralValueWithF(a, b);
    printf("Valeure exacte: %.6f\n", exactValue);
    double rectValue = calculateIntegralLeftRectangle(a, b, N, f);
    printf("\nRectangle à gauche: %.6f", rectValue);
    printf("\tErreur: %.6f\n", errorIntegral(exactValue, rectValue));
    double trapValue = calculateIntegralTrapeze(a, b, N, f);
    printf("Trapèze: %.6f", trapValue);
    printf("\t\tErreur: %.6f\n", errorIntegral(exactValue, trapValue));
}

int main(int argc, char* argv[]){
// partie 1
    printf("partie 1: \n");
    double a, b;
    int ret, N;
    printf("/!\\ entrer la fonction à integrer dans main.c /!\\ \n");
    printf("borne inferieure: ");
    ret = scanf("%lf", &a);
    if (ret < 0)
        return EXIT_FAILURE;
    printf("borne superieure: ");
    ret = scanf("%lf", &b);
    if (ret < 0)
        return EXIT_FAILURE;
    printf("nombre d'échantillons: ");
    ret = scanf("%d", &N);
    if (ret < 0)
        return EXIT_FAILURE;

    validationPart(a, b, N);

    if (argc == 2 && strcmp(argv[1],"f") == 0){
        filterValidationS();
    }
    else if ( argc == 2 && strcmp(argv[1],"h") == 0){
        filterValidationH();
    }
    else{
        // partie 2
        printf("\npartie 2: \n");
        pgm read = pgm_read("src/images/part2.pgm");
        double data0[9] = {0, 0, 0,
                           0, 1, 0,
                           0, 0, 0};
        display(applyConvolveOnPGM(read, data0));
        double data1[25] = {1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1,
                            1, 1, 1, 1, 1};
        display(applyConvolveOnPGM(read, data1));
        double data2[25] = {1, 4, 6, 4, 1,
                            4, 16, 24, 16, 4,
                            6, 24, 36, 24, 6,
                            4, 16, 24, 16, 4,
                            1, 4, 6, 4, 1};
        display(applyConvolveOnPGM(read, data2));
        double data3[9] = {0, -1, 0,
                           -1, 5, -1,
                           0, -1, 0};
        display(applyConvolveOnPGM(read, data3));
        double data4[9] = {0, -1, 0,
                           -1, 4, -1,
                           0, -1, 0};
        display(applyConvolveOnPGM(read, data4));
        pgm_destroy(&read);

        // partie 3
        printf("\npartie 3: \n");
        pgm read2 = pgm_read("src/images/part3_9.pgm");
        double data5[9] = {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                           1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                           1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0};
        matrix res = applyConvolveOnPGM(read2, data5);
        matrix finalRes = matrix_crop(res, 8);
        matrix_destroy(&res);
        matrix_convert_in_eight_bits_in_place(finalRes);
        display(finalRes);
        pgm_destroy(&read2);
    }
    return 0;
}