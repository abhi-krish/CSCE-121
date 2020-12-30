#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;

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
    delete [] image; // dlete array of pointers
    return nullptr;
  }

  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row].r = 0;
      image[col][row].g = 0;
      image[col][row].b = 0;
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
  int* array;
  array = new int [length];
  for (int i = 0; i<length; i++)	{
  	array[i] = 0;
  }
  return array;
}

void deleteSeam(int* seam) {
  delete [] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  ifstream inFS (filename);

  if (!inFS.is_open())	{
  	cout << "Error: failed to open input file - " << filename <<endl;
  	return false;
  }
  char type[3];
  inFS >> type; 
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { 
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }


  int w = 0, h = 0;
  inFS >> w;
  if (inFS.fail())	{
  	cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (w != width) { 
  	cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
    return false;
  }
  inFS >> h;
  if (inFS.fail())	{
  	cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (h != height) { 
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;
    return false;
  }

  
  int colorMaxval = 0;
  inFS >> colorMaxval;
  if (colorMaxval != 255) {
    cout << "Error: file is not using RGB color values." << endl;
    return false;
  }

  
  for (int i = 0; i<height; i++) {
    for (int x = 0; x<width; x++)  {
      inFS >> image[x][i].r;
      if (inFS.eof() && inFS.fail())	{
      	cout << "Error: not enough ior values" << endl;
      	return false;
      }
      if (inFS.fail())	{
      	cout << "Error: read non-integer value" << endl;
      	return false;
      }
      if (image[x][i].r < 0 || image[x][i].r > 255)	{
      	cout << "Error: invalid color value " << image[x][i].r << endl;
      	return false;
      }
      inFS >> image[x][i].g;
      if (inFS.eof() && inFS.fail())	{
      	cout << "Error: not enough color values" << endl;
      	return false;
      }
      if (inFS.fail())	{
      	cout << "Error: read non-integer value" << endl;
      	return false;
      }
      if (image[x][i].g < 0 || image[x][i].g > 255)	{
      	cout << "Error: invalid color value " << image[x][i].g << endl;
      	return false;
      }
      inFS >> image[x][i].b;
      if (inFS.eof() && inFS.fail())	{
      	cout << "Error: not enough color values" << endl;
      	return false;
      }
      if (inFS.fail())	{
      	cout << "Error: read non-integer value" << endl;
      	return false;
      }
      if (image[x][i].b < 0 || image[x][i].b > 255)	{
      	cout << "Error: invalid color value " << image[x][i].b << endl;
      	return false;
      }
      //

    }


  }
  int endof;
  inFS >> endof;

  if (!inFS.eof())	{
  	cout << "Error: too many color values" << endl;
  	return false;
  }

  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
  cout << "Outputting image..." << endl;
  ofstream outFS (filename);

  if (!outFS.is_open()) {
    cout << "Error: failed to open output file <filename>" << filename << endl;
    return false;
  }


  outFS << "P3 ";
  outFS << width << " ";
  outFS << height << " ";
  outFS << "255 ";


  for (int i = 0; i<height; i++) {
    for (int x = 0; x<width; x++)  {
      outFS << image[x][i].r << " ";
      outFS << image[x][i].g << " ";
      outFS << image[x][i].b << " ";
    }
  }
  return true;

}

int energy(Pixel** image, int x, int y, int width, int height) {
  int calcr = 0;
  int calcg = 0;
  int calcb = 0;
  int calcx = 0;
  int calcy = 0;
  int hi = 0;


  if (x==0 && y ==0)	{
  	calcr = image[x][height-1].r - image[x][y+1].r;
  	calcg = image[x][height-1].g - image[x][y+1].g;
  	calcb = image[x][height-1].b - image[x][y+1].b;
  	calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  	calcr = image[x+1][y].r - image[width-1][y].r;
  	calcg = image[x+1][y].g - image[width-1][y].g;
  	calcb = image[x+1][y].b - image[width-1][y].b;
  	calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  	return (hi + (calcy+calcx) - hi);
  }

  if (x==0 && y ==height-1)	{

  	calcr = image[x][y-1].r - image[x][0].r;
  	calcg = image[x][y-1].g - image[x][0].g;
  	calcb = image[x][y-1].b - image[x][0].b;
  	calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  	calcr = image[x+1][y].r - image[width-1][y].r;
  	calcg = image[x+1][y].g - image[width-1][y].g;
  	calcb = image[x+1][y].b - image[width-1][y].b;
  	calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  	return (hi + (calcy+calcx) - hi);
  }

  if (x==width-1 && y==0)	{
  	calcr = image[x][height-1].r - image[x][y+1].r;
  	calcg = image[x][height-1].g - image[x][y+1].g;
  	calcb = image[x][height-1].b - image[x][y+1].b;
  	calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  	calcr = image[0][y].r - image[x-1][y].r;
  	calcg = image[0][y].g - image[x-1][y].g;
  	calcb = image[0][y].b - image[x-1][y].b;
  	calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  	return (hi + (calcy+calcx) - hi);
  }

  if (x==width-1 && y==height-1)	{
  	calcr = image[x][y-1].r - image[x][0].r;
  	calcg = image[x][y-1].g - image[x][0].g;
  	calcb = image[x][y-1].b - image[x][0].b;
  	calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  	calcr = image[0][y].r - image[x-1][y].r;
  	calcg = image[0][y].g - image[x-1][y].g;
  	calcb = image[0][y].b - image[x-1][y].b;
  	calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  	return (hi + (calcy+calcx) - hi);
  }

  if (x==0)	{
	calcr = image[x][y-1].r - image[x][y+1].r;
  	calcg = image[x][y-1].g - image[x][y+1].g;
  	calcb = image[x][y-1].b - image[x][y+1].b;
  	calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  	calcr = image[x+1][y].r - image[width-1][y].r;
  	calcg = image[x+1][y].g - image[width-1][y].g;
  	calcb = image[x+1][y].b - image[width-1][y].b;
  	calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  	return (hi + (calcy+calcx) - hi);

  }
  if (x==width-1)	{
  	calcr = image[x][y-1].r - image[x][y+1].r;
  	calcg = image[x][y-1].g - image[x][y+1].g;
  	calcb = image[x][y-1].b - image[x][y+1].b;
  	calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  	calcr = image[0][y].r - image[x-1][y].r;
  	calcg = image[0][y].g - image[x-1][y].g;
  	calcb = image[0][y].b - image[x-1][y].b;
  	calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  	return (hi + (calcy+calcx) - hi);
  }
  if (y==0)	{
  	calcr = image[x][height-1].r - image[x][y+1].r;
  	calcg = image[x][height-1].g - image[x][y+1].g;
  	calcb = image[x][height-1].b - image[x][y+1].b;
  	calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  	calcr = image[x+1][y].r - image[x-1][y].r;
  	calcg = image[x+1][y].g - image[x-1][y].g;
  	calcb = image[x+1][y].b - image[x-1][y].b;
  	calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  	return (hi + (calcy+calcx) - hi);
  }
  if (y==height-1)	{
  	calcr = image[x][y-1].r - image[x][0].r;
  	calcg = image[x][y-1].g - image[x][0].g;
  	calcb = image[x][y-1].b - image[x][0].b;
  	calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  	calcr = image[x+1][y].r - image[x-1][y].r;
  	calcg = image[x+1][y].g - image[x-1][y].g;
  	calcb = image[x+1][y].b - image[x-1][y].b;
  	calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  	return (hi + (calcy+calcx) - hi);
  }

  calcr = image[x][y-1].r - image[x][y+1].r;
  calcg = image[x][y-1].g - image[x][y+1].g;
  calcb = image[x][y-1].b - image[x][y+1].b;
  calcx = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);

  calcr = image[x+1][y].r - image[x-1][y].r;
  calcg = image[x+1][y].g - image[x-1][y].g;
  calcb = image[x+1][y].b - image[x-1][y].b;
  calcy = (calcr * calcr) + (calcg * calcg) + (calcb * calcb);
  return (calcy+calcx);
}
int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  seam[0] = start_col;
  int total = energy(image, start_col, 0, width, height);
  int nrg1 = 0;
  int nrg2 = 0;
  int nrg3 = 0;
  int newcol = start_col;
  for (int i = 1; i < height; i++)  {
    if (newcol == 0) {
      nrg1 = energy(image, 0, i, width, height);
      nrg2 = energy(image, 1, i, width, height);
      if (nrg1 == nrg2 || nrg1 < nrg2)  {
        seam[i] = 0;
        total += nrg1;
        newcol = 0;
      }
      else if (nrg2 < nrg1)  {
        seam[i] = 1;
        total += nrg2;
        newcol = 1;
      }
    }
    else if (newcol == (width-1)) {
      nrg1 = energy(image, (width-1), i, width, height);
      nrg2 = energy(image, (width-2), i, width, height);
      if (nrg1 == nrg2 || nrg1 < nrg2)  {
        seam[i] = width-1;
        total += nrg1;
        newcol = width-1;
      }
      else if (nrg2 < nrg1)  {
        seam[i] = width-2;
        total += nrg2;
        newcol = width-2;
      }
    }
    else  {
      nrg1 = energy(image, newcol-1, i, width, height);
      nrg2 = energy(image, newcol, i, width, height);
      nrg3 = energy(image, newcol+1, i, width, height);
      if (nrg2 == nrg1 && nrg2 < nrg3) {
        seam[i] = newcol;
        total += nrg2;
      }
      else if (nrg2 == nrg3 && nrg2 < nrg1)  {
        seam[i] = newcol;
        total += nrg2;
      }
      else if (nrg2 == nrg3 && nrg2 == nrg1)  {
        seam[i] = newcol;
        total += nrg2;
      }
      else if (nrg1 == nrg3 && nrg1 < nrg2)  {
        seam[i] = newcol+1;
        total += nrg1;
        newcol = newcol+1;
      }
      else if (nrg2 < nrg3 && nrg2 < nrg1)  {
        seam[i] = newcol;
        total += nrg2;
      }
      else if (nrg1 < nrg2 && nrg1 < nrg3)  {
        seam[i] = newcol-1;
        total += nrg1;
        newcol = newcol-1;
      }
      else if (nrg3 < nrg2 && nrg3 < nrg1) {
        seam[i] = newcol+1;
        total += nrg3;
        newcol = newcol + 1;
      }
    }
  }
  return total;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  seam[0] = start_row;
  int total = energy(image, 0, start_row, width, height);
  int nrg1 = 0;
  int nrg2 = 0;
  int nrg3 = 0;
  int newrow = start_row;
  for (int i = 1; i < width; i++)  {
    if (newrow == 0) {
      nrg1 = energy(image, i, 0, width, height);
      nrg2 = energy(image, i, 1, width, height);
      if (nrg1 == nrg2 || nrg1 < nrg2)  {
        seam[i] = 0;
        total += nrg1;
        newrow = 0;
      }
      else if (nrg2 < nrg1)  {
        seam[i] = 1;
        total += nrg2;
        newrow = 1;
      }
    }
    else if (newrow == (height-1)) {
      nrg1 = energy(image, i, (height-1), width, height);
      nrg2 = energy(image, i, (height-2), width, height);
      if (nrg1 == nrg2 || nrg1 < nrg2)  {
        seam[i] = height-1;
        total += nrg1;
        newrow = height-1;
      }
      else if (nrg2 < nrg1)  {
        seam[i] = height-2;
        total += nrg2;
        newrow = height-2;
      }
    }
    else  {
      nrg1 = energy(image, i, newrow-1, width, height);
      nrg2 = energy(image, i, newrow, width, height);
      nrg3 = energy(image, i, newrow+1, width, height);
      if (nrg2 == nrg1 && nrg2 < nrg3) {
        seam[i] = newrow;
        total += nrg2;
      }
      else if (nrg2 == nrg3 && nrg2 < nrg1)  {
        seam[i] = newrow;
        total += nrg2;
      }
      else if (nrg2 == nrg3 && nrg2 == nrg1)  {
        seam[i] = newrow;
        total += nrg2;
      }
      else if (nrg1 == nrg3 && nrg1 < nrg2)  {
        seam[i] = newrow-1;
        total += nrg1;
        newrow = newrow-1;
      }
      else if (nrg2 < nrg3 && nrg2 < nrg1)  {
        seam[i] = newrow;
        total += nrg2;
      }
      else if (nrg1 < nrg2 && nrg1 < nrg3)  {
        seam[i] = newrow-1;
        total += nrg1;
        newrow = newrow-1;
      }
      else if (nrg3 < nrg2 && nrg3 < nrg1) {
        seam[i] = newrow+1;
        total += nrg3;
        newrow = newrow + 1;
      }
    }
  }
  return total;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int * tempvert = new int [height];
  int * minvert = new int [height];
  int minseam = loadVerticalSeam(image, 0, width, height, minvert);
  int tempval = loadVerticalSeam(image, 0, width, height, tempvert);
  for (int i = 1; i<width; i++) {
    tempval = loadVerticalSeam(image, i, width, height, tempvert);
    if (tempval < minseam)  {
      minseam = tempval;
      for (int k=0; k<height; k++)  {
        minvert[k] = tempvert[k];
      }
    }
  }
  delete [] tempvert;
  return minvert;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  int * temphoriz = new int [width];
  int * minhoriz = new int [width];
  int minseam = loadHorizontalSeam(image, 0, width, height, minhoriz);
  int tempval = loadHorizontalSeam(image, 0, width, height, temphoriz);
  for (int i = 1; i<height; i++) {
    tempval = loadHorizontalSeam(image, i, width, height, temphoriz);
    if (tempval < minseam)  {
      minseam = tempval;
      for (int j=0; j < width; j++)  {
        minhoriz[j] = temphoriz[j];
      }
    }
  }
  delete [] temphoriz;
  return minhoriz;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  for (int i=0; i<height; i++)  {
    for (int j=verticalSeam[i]; j<width-1; j++) {
      image[j][i].r = image[j+1][i].r;
      image[j][i].g = image[j+1][i].g;
      image[j][i].b = image[j+1][i].b;
    }
  }
  width = width - 1;
}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  for (int i=0; i<width; i++)  {
    for (int j=horizontalSeam[i]; j<height-1; j++)  {
      image[i][j].r = image[i][j+1].r;
      image[i][j].g = image[i][j+1].g;
      image[i][j].b = image[i][j+1].b;
    }
  }
  height = height - 1;
}