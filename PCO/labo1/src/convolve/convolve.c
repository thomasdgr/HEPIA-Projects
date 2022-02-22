#include "convolve.h"

void* convolve(void* arg){
    partial_convolution* pConv = (partial_convolution *)arg;
	img_t *img = pConv->imgSource;
	img_t *dest = pConv->imgDest;
	double* kernel = pConv->kernel;
	int ker_size = pConv->kernelSize;
	int id_thread = pConv->idThread;
	int nb_threads = pConv->numberOfThreads;

	double sommeR = 0.0;
	double sommeG = 0.0;
    double sommeB = 0.0;
    // on trouve le centre du kernel
    int Kx = ker_size / 2;
    int Ky = ker_size / 2;
    // pour chaque valeur de la matrice on veut faire un somme de multiplication de mat.nm avec kernel.nm
    for (int i = id_thread; i < img->height; i+=nb_threads){
        for (int j = 0; j < img->width; j++){
            for (int k = 0; k < ker_size; k++){
                for (int l = 0; l < ker_size; l++){
                    // on verifie que les valeurs du kernel sont superposables avec les valeurs de la matrice
                    if((i-Kx+k) < img->height && (i-Kx+k) >= 0 && (j-Ky+l) < img->width && (j-Ky+l) >= 0){
                        pixel_t current_pixel = img->data[(i - Kx + k) * img->width + (j - Ky + l)]; 
			            int pixelR = current_pixel.r;
                        int pixelG = current_pixel.g;
                        int pixelB = current_pixel.b;
			            sommeR += kernel[k * ker_size + l] * (double)pixelR;
                        sommeG += kernel[k * ker_size + l] * (double)pixelG;
                        sommeB += kernel[k * ker_size + l] * (double)pixelB;
			        }
                }
            }
	        pixel_t pixelConvolute = {sommeR, sommeG, sommeB};
	        dest->data[i * dest->width + j] = pixelConvolute;
	        sommeR = 0.0;
            sommeG = 0.0;
            sommeB = 0.0;
        }
    }
	return NULL;
}