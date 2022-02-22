#include "convolve/convolve.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv) {
	if (argc < 4 || atoi(argv[3]) == 0) {
		fprintf(stderr, "usage: %s input output nb_threads\n"\
		"where input and output are PPM files and nb_threads is an u_int\n", argv[0]);	
		return EXIT_FAILURE;
	}

	char *input = argv[1];
	char *output = argv[2];
	int numberOfThreads = atoi(argv[3]);
	struct timespec start, finish;
    
	img_t *imgSource = load_ppm(input);
    if (imgSource == NULL) {
		fprintf(stderr, "Failed loading %s!\n", input);
		return EXIT_FAILURE;
    }

	/*double kernelIdentity[] = {0.0, 0.0, 0.0,
						       0.0, 1.0, 0.0,
						       0.0, 0.0, 0.0};

	double kernelSharpen[] ={0.0,-1.0, 0.0,
						    -1.0, 5.0,-1.0,
						     0.0,-1.0, 0.0};

	double kernelEdge[] ={-1.0,-1.0,-1.0,
						  -1.0, 8.0,-1.0,
						  -1.0,-1.0,-1.0};*/

	double kernelBlur[] ={0.111, 0.111, 0.111,
						  0.111, 0.111,-0.111,
						  0.111, 0.111, 0.111};
						  

    img_t* imgDest = img_t_clone(imgSource);
	pthread_t allThreads[numberOfThreads];
	partial_convolution allConvolutions[numberOfThreads];


	// le temps est calculé uniquement pour la "partie" convolution
	if (clock_gettime(CLOCK_MONOTONIC, &start) != 0){
		return EXIT_FAILURE;
	}
	for (int i = 0; i < numberOfThreads; i++){
		partial_convolution newConvolution = {i, numberOfThreads, imgSource, imgDest, kernelBlur, 3};
		allConvolutions[i] = newConvolution;
		if (pthread_create(&allThreads[i], NULL, convolve, &allConvolutions[i])){
			fprintf(stderr, "convolution failed!\n");
        	return EXIT_FAILURE;
		}
	}

	for(int i = 0; i< numberOfThreads; i+= 1){
     	if(pthread_join(allThreads[i], NULL) != 0){
       		perror("pthread_join");
       		return EXIT_FAILURE;
     	}
	}
	if(clock_gettime(CLOCK_MONOTONIC, &finish) != 0){
		return EXIT_FAILURE;
	}
	double elapsed_ms = 1000 * (finish.tv_sec - start.tv_sec); 
	elapsed_ms += (finish.tv_nsec - start.tv_nsec) / 1000000.0;
	printf("time elapsed: %.4fms\n", elapsed_ms);

	if(!write_ppm(argv[2], imgDest)){
		fprintf(stderr, "Failed writing %s!\n", output);
		free_img(imgDest);
		return EXIT_FAILURE;
	}
	
	free_img(imgDest);
	free_img(imgSource);
	return EXIT_SUCCESS;
}