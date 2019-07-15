#ifndef STEADYTEST_HPP
#define STEADYTEST_HPP

#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>

#define CROW  12		// number of rows in core composition matrix
#define CCOL  12		// number of columns in core composition matrix
#define XROW  04		// number of rows in cross-section input composition matrix
#define XCOL  07		// number of rows in cross-section input composition matrix
#define ss    60		// format setting for demarkation
#define F_max        1e5	 //maximum iteration
#define K_max        1e5	 //maximum iteration
#define epsilon      1e-6 // relative error limit
#define Kepsilon     1e-5 // relative error limit

char disc1,disc2,disc3,disc4;
int out1(int){
  int ab,cd;
  FILE *fp = fopen("ccomp","r");
  fscanf(fp,"%s %d %s %d", &disc1, &ab, &disc2, &cd);
  return ab;
}
int out2(int){
  int ab,cd;
  FILE *fp = fopen("ccomp","r");
  fscanf(fp,"%s %d %s %d", &disc1, &ab, &disc2, &cd);
  return cd;
}
int out3(int){
  int ab,cd;
  FILE *fp = fopen("xsec","r");
  fscanf(fp,"%s %d %s %d", &disc1, &ab, &disc2, &cd);
  return ab;
}
int out4(int){
  int ab,cd;
  FILE *fp = fopen("xsec","r");
  fscanf(fp,"%s %d %s %d", &disc1, &ab, &disc2, &cd);
  return cd;
}

// Function to find max element mat[][] : 2D array to find max element 
double findMax(double mat[CROW][CCOL]) 
{ 
    // Initializing max element as INT_MIN 
    double maxElement = 0; 
  
    // checking each element of matrix 
    // if it is greater than maxElement, 
    // update maxElement 
    for (int i = 0; i < CROW-1; i++) { 
      for (int j = 0; j < CCOL-1; j++) { 
	if (mat[i][j] > maxElement) { 
	  maxElement = mat[i][j]; 
	} 
      } 
    } 
    // finally return maxElement 
    return maxElement; 
} 

#endif
