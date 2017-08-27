
#include <stdlib.h>

#include "gl_simpleMatrix.h"
#include "gl_utils.h"

gl_MATRIX *gl_allocateMatrix (int rows, int cols) {

	double** matrix = (double **) safe_malloc (sizeof(double*) * rows);
	for (int i = 0; i < rows; i++) {
		matrix[i] = (double *) safe_malloc(cols * sizeof(double));
	}

	gl_MATRIX *glm = (gl_MATRIX *) safe_malloc(sizeof(gl_MATRIX));
	glm->m = matrix;
	glm->nRows = rows;
	glm->nCols = cols;

	return glm;
}


void gl_addRowsToMatrix(gl_MATRIX *mat, int extraRows) {

	int currentRows = mat->nRows;
	int currentCols = mat->nCols;

	mat->m = (double **) safe_realloc(mat->m, sizeof(double *) * (currentRows + extraRows));

	for (int i = currentRows; i < currentRows + extraRows; i++)
		(mat->m)[i] = (double *) safe_malloc (sizeof(double) * currentCols);
	mat->nCols = currentCols;
	mat->nRows = currentRows + extraRows;
}


int gl_getMatrixRows(gl_MATRIX *mat) {
	return mat->nRows;
}


int gl_getMatrixCols(gl_MATRIX *mat) {
	return mat->nCols;
}


double gl_getMatrixValue(gl_MATRIX *mat, int row, int col) {
	return mat->m[row][col];
}


void gl_freeMatrix(gl_MATRIX *mat) {

	for (int i = 0; i < mat->nRows; i++)
		safe_free(mat->m[i]);
	safe_free(mat->m);
	safe_free(mat);
}


