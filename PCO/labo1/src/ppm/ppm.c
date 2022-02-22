#include "ppm.h"

// Allocate the memory for an image of size width*height
img_t *alloc_img(int width, int height) {
	img_t *img = malloc(sizeof(img_t));
	img->width = width;
	img->height = height;
	img->data = malloc(sizeof(pixel_t) * width * height);	
	return img;
}

// Free an image
void free_img(img_t *img) {
	free(img->data);
	free(img);
}

// Write a 24-bit RGB PPM file.
// Return false if the image wasn't written properly.
bool write_ppm(char *filename, img_t *img) {
	FILE *f = fopen(filename, "w");
	if (f == NULL) return false;
	// Write the header
	fprintf(f, "P3\n%d %d\n255\n", img->width, img->height);
	// Write image content
	int count = 0;
	for (int i = 0; i < img->width * img->height; i++) {
		pixel_t *p = &img->data[i];
		fprintf(f, "%d %d %d ", p->r, p->g, p->b);
		if (++count % 5 == 0)  // New line every 5 pixels (max 70 characters/line)
			fprintf(f, "\n");
	}
	fclose(f);
	return true;
}

// Ajouté: Clone une img_t
img_t * img_t_clone(img_t *img){
	img_t *cloneImg = alloc_img(img->width, img->height);
	for (int i = 0; i < img->width * img->height; i++){
		cloneImg->data[i] = img->data[i];
	}
	return cloneImg;
}

// Load a 24-bit RGB PPM file and return the loaded image.
// The function takes care of allocating the memory for the image.
img_t *load_ppm(char *filename) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) return NULL;
	
	char line[128];  // The PPM format states a line is at most 70 character long
	unsigned int width, height;
	unsigned int maxval;
	
	// Reads the PPM header, making sure it's valid
	int matches;
	// Fist line should be P3
	matches = fscanf(f, "%2s", line);  // read 2 characters
	if (matches != 1 || strcmp(line, "P3") != 0) goto error;
	// Second line should be image width and height
	matches = fscanf(f, "%u %u", &width, &height);
	if (matches != 2) goto error;
	// Third line should be the maximum value per component
	matches = fscanf(f, "%u", &maxval);
	if (matches != 1) goto error;
	
	// Allocate memory for image structure and image data
	img_t *img = alloc_img(width, height);
	
	// Next, should be the image data in RGB order
	for (int i = 0; i < (int)(width * height); i++){
		unsigned r, g, b;
		matches = fscanf(f, "%u %u %u", &r, &g, &b);
		if (matches != 3) goto error;
		if (r > maxval || g > maxval || b > maxval) goto error;
		pixel_t p = { r, g, b };
		img->data[i] = p;
	}
	fclose(f);
	return img;

error:
	fclose(f);
	return NULL;
}

