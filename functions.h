#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "functions.h"

struct Pixel {
  int r = 0; // red
  int g = 0; // green
  int b = 0; // blue
};

// Implemented for you

Pixel** createImage(int width, int height);
void deleteImage(Pixel** image, int width);


// Implement for part 1

int* createSeam(int length);
void deleteSeam(int* seam);
bool loadImage(std::string filename, Pixel** image, int width, int height);
bool outputImage(std::string filename, Pixel** image, int width, int height);
int energy(Pixel** image, int x, int y, int width, int height);


// Implement for part 2

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam);

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam);
int* findMinVerticalSeam(Pixel** image, int width, int height);
int* findMinHorizontalSeam(Pixel** image, int width, int height);
void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam);
void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam);


#endif