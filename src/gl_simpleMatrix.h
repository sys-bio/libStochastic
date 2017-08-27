
/******************************************************
* Copyright(C) 2017 Herbert Sauro
* VERSION 1.0
*
* This file is part of C Stochastic library
*
* Licensed under the Apache License, Version 2.0 (the "License"); you
* may not use this file except in compliance with the License.You
* may obtain a copy of the License at
*
* http ://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
* implied.See the License for the specific language governing permissions
* and limitations under the License.
****************************************************** */

// Simple appendable two dimension array type
// In the current version if space runs out, the array is
// increased two fold in size. 
// The array can be acessed directly using:  x->items[row][col]
// x->row and cols contains the size of the matrix


#ifndef TWODIMARRAY_H
#define TWODIMARRAY_H

#include <stdlib.h>

// Very simple Matrix type.

typedef struct gl_Matrix {
	double **m;
	int nRows; int nCols;
} gl_MATRIX;


extern "C" {
	// Create a matrix with numbers of rows and columns
	__declspec(dllexport) extern gl_MATRIX *gl_allocateMatrix(int rows, int cols);

	// Add a given number of rows to the matrix 
	__declspec(dllexport) extern void gl_addRowsToMatrix(gl_MATRIX *mat, int extraRows);

	// Free a previously created matrix
	__declspec(dllexport) extern void gl_freeMatrix(gl_MATRIX *mat);

	__declspec(dllexport) extern double gl_getMatrixValue (gl_MATRIX *mat, int row, int col);

	__declspec(dllexport) extern int gl_getMatrixRows(gl_MATRIX *mat);

	__declspec(dllexport) extern int gl_getMatrixCols(gl_MATRIX *mat);
}

#endif
