#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  //cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // delete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
 // cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  //cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
	int* array = new int[length];
	for(int i = 0; i < length; ++i){
		array[i] = 0;
	}		
	
  return array;
}

void deleteSeam(int* seam) {
	delete[] seam;
	seam = NULL;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
	ifstream ifs(filename);

	if(!(ifs.is_open())){
		cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }
  char type[3];
  ifs >> type;
  if((toupper(type[0]) != 'P') || (type[1] != '3')){
	      cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }
	int w, h;
	
	ifs >> w >> h;
	/*
	if(ifs.fail()){
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	if( w!= width){
		cout << "Error: input width (" << width <<  ") does not match value in file ("<< w << ")" << endl;
		return false;
  }
	if( h!= height){
		cout << "Error: input height (" << height <<  ") does not match value in file (" << h << ")" << endl;
		return false;
  }
  */
  int colorMax = 0;
  ifs >> colorMax;
  if( colorMax != 255){
	     cout << "Error: file is not using RGB color values." << endl;
    return false;
  }
  
  
  int i, j, r , g , b;
  
  for( i = 0 ; i < height ; ++i){
	  for ( j = 0; j < width ; ++j){
		  
		  	if(ifs.eof()){
			cout << "Error: not enough color values" << endl;
			return false;
		}
		  ifs >> r;
		  
		  		/*
		  if(ifs.fail()){
			  if(ifs.eof()){
			cout << "Error: not enough color values" << endl;
			return false;
		}
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	*/
		ifs >> g;
/*
		if(ifs.fail()){
			 if(ifs.eof()){
			cout << "Error: not enough color values" << endl;
			return false;
		}
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	*/
		ifs >> b;
		/*
		if(ifs.fail()){
			 if(ifs.eof()){
			cout << "Error: not enough color values" << endl;
			return false;
		}
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	
		if( r < 0 || r > 255){
			cout << "Error: Invalid color value " << r << endl;
			return false;
		}
		if( g < 0 || g > 255){
			cout << "Error: Invalid color value " << g << endl;
			return false;
		}
		if( b < 0 || b > 255){
			cout << "Error: Invalid color value " << b << endl;
			return false;
		}
		*/
		//cout <<r<<" "<<g<<" "<<b<<endl;
		image[j][i].r = r;
		image[j][i].g = g;
		image[j][i].b = b;

	  }
  }
	  if(!ifs.eof()){
		  ifs >> r;
		  if(!ifs.fail()){
		  cout << "Error: too many color values" << endl;
	  }
	  }
  
  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
	ofstream ofs(filename);
	if (!ofs.is_open()){
		cout << "Error: failed to open output file - " << filename << endl;
		return false;
	}
	ofs << "P3" << "\n";
	ofs << width << " " << height << endl;
	ofs << 255 << endl;
	int i, j;
	for(i = 0; i < height; ++i){
		for(j=0; j < width; ++j){
			ofs << image[j][i].r << " ";
			ofs << image[j][i].g << " ";
			ofs << image [j][i].b <<endl;	
		}
	}
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
int energyx, energyy, rx , ry , gx, gy, bx , by, energy;
if( x ==0){
rx = image[x+1][y].r - image[width-1][y].r;
gx = image[x+1][y].g - image[width-1][y].g;
bx = image[x+1][y].b - image[width-1][y].b;
}
else if(x == width-1){
	rx = image[0][y].r - image[x-1][y].r;
	gx = image[0][y].g - image[x-1][y].g;
	bx = image[0][y].b - image[x-1][y].b;
}
else{
	rx = image[x+1][y].r - image[x-1][y].r;
	gx = image[x+1][y].g - image[x-1][y].g;
	bx = image[x+1][y].b - image[x-1][y].b;
}
if(y == 0){
	ry = image[x][y+1].r - image[x][height-1].r;
	gy = image[x][y+1].g - image[x][height-1].g;
	by = image[x][y+1].b - image[x][height-1].b;
}
else if(y == height-1){
	ry = image[x][0].r - image[x][y-1].r;
	gy = image[x][0].g - image[x][y-1].g;
	by = image[x][0].b - image[x][y-1].b;
}
else{
	ry = image[x][y+1].r - image[x][y-1].r;
	gy = image[x][y+1].g - image[x][y-1].g;
	by = image[x][y+1].b - image[x][y-1].b;
}

energyx = rx*rx + gx*gx + bx*bx;
energyy = ry*ry + gy*gy + by*by;
energy = energyx + energyy;
/*
energyx = pow(rx, 2) + pow(gx, 2) + pow(bx,2);
energyy = pow(ry,2) + pow(gy,2) + pow(by,2);
energy = energyx + energyy;

cout<< "x: " << x << " y: " << y << endl;
cout << "rx: "<< rx<< " gx: " << gx << " bx: " << bx << endl;
cout<< "ry: " << ry << " gy: " << gy << " by: " << by << endl;
cout << "energy: " << energy << endl << endl; 

*/
  return energy; 
}
 
int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
	//cout << "height:" << height;
	int totenergy = 0, left = 0, right = 0, center = 0, row = 0;
	seam[0] = start_col;
	totenergy = energy(image, start_col, row, width, height);
	row += 1;
	//cout << "energy: "<<totenergy<<endl;;
	while(row <height){
	if(start_col == width-1){
		right = energy(image, start_col-1, row, width, height);
	    center = energy(image, start_col, row, width, height);
		if(center <= right){
		totenergy += center;
		seam[row] = start_col;
		//cout << "center " << center<< "row: " << row<< endl; 
		}else{
			totenergy += right;
			seam[row] = start_col -1;
			//cout << "right " << right<< "row: " << row << endl; 
			start_col -=1;
		}
	}else if(start_col == 0){
		left = energy(image, start_col+1, row, width, height);
		center = energy(image, start_col, row, width, height);
		if(center <= left){
		totenergy += center;
		seam[row] = start_col;
		}
		else{
			totenergy += left;
		    seam[row] = start_col+1;
			start_col +=1;
	}
	}else{
	left = energy(image, start_col+1, row, width, height);
	right = energy(image, start_col-1, row, width, height);
	center = energy(image, start_col, row, width, height);
	if((center <= left) && (center <= right)){
		totenergy += center;
		seam[row] = start_col;
	}else if( (left < center) && (left <= right)){
		totenergy += left;
		seam[row] = start_col+1;
		start_col +=1;
	}else if((right < center) && (right < left)){
		totenergy += right;
		seam[row] = start_col-1;
		start_col -=1;
	}
	}
	row+=1;
	//cout<< "begin";
	//cout << "energy" <<totenergy<< endl;
	}

  return totenergy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  int totenergy = 0, left = 0, right = 0, center = 0, col = 0;
  seam[0] = start_row;
  totenergy = energy(image, col, start_row, width, height);
  col +=1;
  while(col < width){
	  if( start_row == height-1){
		  center = energy(image, col, start_row, width, height);
		  left = energy(image,col, start_row-1, width, height);
		  if(left < center){
			  totenergy += left;
			  //seam[col] = start_row-1;
			  start_row -=1;
		  }else{
			  totenergy += center;
			  //seam[col] = start_row;
		  }
	  }else if(start_row == 0){
		  center = energy(image,col,start_row,width,height);
		  right = energy(image, col, start_row+1, width, height);
		  if(right < center){
			  totenergy += right;
			  //seam[col] = start_row+1;
			  start_row +=1;
		  }else{
			  totenergy += center;
			  //seam[col] = start_row;
		  }
	  }else{
		  center = energy(image,col,start_row,width,height);
		  right = energy(image, col, start_row+1, width, height);
		  left = energy(image,col, start_row-1, width, height);
		  if( center <= left){
			  totenergy += center;
			  //seam[col] = start_row;
		  }else if((left < center) && (left <= right)){
			  totenergy +=left;
			  //seam[col] = start_row-1;
			  start_row -=1;
		  }else{
			  totenergy +=right;
			  //seam[col] = start_row+1;
			  start_row +=1;
		  }
	  }
			seam[col] = start_row;
		  col +=1;
			  
  }
		
  
  return totenergy;  
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
	
	int cols = 0, value;
	int* seam1 = createSeam(height);
	int min = loadVerticalSeam(image, cols, width, height, seam1);
	int minCols = cols;
	deleteSeam(seam1);
	cols +=1 ;
	while(cols <= width-1){

	seam1 = createSeam(height);
	value = loadVerticalSeam(image, cols, width, height, seam1);
	if(value < min){
		min = value;
		minCols = cols;
	}
	deleteSeam(seam1);
	cols+=1;
	}
	seam1 = createSeam(height);
	loadVerticalSeam(image, minCols, width, height, seam1);
	
  return seam1;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
	
	int rows = 0, value;
	int* seam1 = createSeam(width);
	int min = loadHorizontalSeam(image, rows, width, height, seam1);
	int minRows = rows;
	deleteSeam(seam1);
	rows +=1 ;
	while(rows <= height-1){

	seam1 = createSeam(width);
	value = loadHorizontalSeam(image, rows, width, height, seam1);
	if(value < min){
		min = value;
		minRows = rows;
	}
	deleteSeam(seam1);
	rows+=1;
	}
	seam1 = createSeam(width);
	loadHorizontalSeam(image, minRows, width, height, seam1);
	
	
  return NULL;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
	int rows, cols;
	for(rows = 0; rows < height; ++rows){
		for(cols = verticalSeam[rows]; cols < width-1; ++cols){
			image[cols][rows] = image[cols+1][rows];
	}
}
		
	
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
	
	int rows, cols;
	for(cols = 0; cols < width; ++cols){
		for (rows = horizontalSeam[cols]; rows < height -1; ++rows){
			image[cols][rows] = image[cols][rows+1];
		}
	}
	
}


	