#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;


int main() {
  string filename;
  int width = 0;
  int height = 0;
 // int originalWidth = 0;
  int originalHeight = 0;
  int targetWidth = 0;
  int targetHeight = 0;
  
//  cout << "Input filename: ";
  cin >> filename;
  
  // add error checking for width, height, targetWidth, and targetHeight
//  cout << "Input width and height: ";
  cin >> width >> height;
  //cout << "Input target width and height: ";
  cin >> targetWidth >> targetHeight;
  
  // save originalWidth since width will change with carving
  int originalWidth = width; 
  // save originalHeight since height will change with carving
  originalHeight = height;
  
  Pixel** image = createImage(width, height);
  if (image != nullptr) { // new returns nullptr if it fails to allocate array

    if (loadImage(filename, image, width, height)) {
      

      while ((width - targetWidth > 0) /*|| (height - targetHeight > 0)*/) {
        if (width - targetWidth > 0) {
          int* verticalSeam = findMinVerticalSeam(image, width, height);
          removeVerticalSeam(image, width, height, verticalSeam);
          deleteSeam(verticalSeam);
          width = width - 1;
        }
        /*
        // this is for the extra credit
        if (height - targetHeight > 0) {
          int* horizontalSeam = findMinHorizontalSeam(image, width, height);
          removeHorizontalSeam(image, width, height, horizontalSeam);
          deleteSeam(horizontalSeam);
          height--;
        }
		*/
		cout << width;
      }
      
      
      stringstream ss;
      ss << "carved" << targetWidth << "X" << targetHeight << "." << filename;
      outputImage(ss.str().c_str(), image, width, height);
    }
  }
  
  // call last to remove the memory from the heap
  deleteImage(image, originalWidth);
}