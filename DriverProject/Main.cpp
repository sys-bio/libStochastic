
#include <stdio.h>
#include <crtdbg.h>  

#include "gl_Stochastic.h"

void main (int argc, char* argv[]) {

	double timeEnd = 50;
	double currentTime = 0;
	int numberOfPoints = 51;

	//int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	//flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	//_CrtSetDbgFlag(flag);
	//_CrtSetBreakAlloc(352);

	printf("Starting Gillespie simulation...\n");

	gl_STOCHASTIC_OBJ *gl = gl_createStochastic();

	int x = gl_addSpecies (gl, "x", 0, true);
	int source = gl_addSpecies (gl, "source", 0, false);
	int sink = gl_addSpecies (gl, "sink", 0, false);

	int rxa = gl_addZeroOrderReaction (gl, 10.0);
	gl_addProduct (gl, rxa, x, 1);

	rxa = gl_addFirstOrderReaction (gl, x, 0.1);
	gl_addProduct (gl, rxa, sink, 1);


	gl_MATRIX *m = gl_execute (gl, 0, 50);

	// Simple Decay
	//int x1 = gl_addSpecies (gl, "X1", 10, true);
	//gl_REACTION *rxa = gl_addFirstOrderReaction(gl, x1, 0.4);

	for (int i = 0; i < m->nRows; i++) {
		for (int j = 0; j < m->nCols; j++) {
			printf("%f ", m->m[i][j]);
		}
		printf("\n");
	}

	gl_freeMatrix(m);

	gl_freeStochastic (gl);

	printf ("Finished....");
	getchar();
}