
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "gl_Stochastic.h"
#include "gl_utils.h"

// Random number generator provided by:
// Christian Stigen Larsen
// http://csl.name
// https://github.com/cslarsen/mersenne-twister

#include "mersenne_twister.h"

// This is the initial number of rows in the array (called data) that stores the results
#define gl_INITIAL_SIZE 100
// This is the number of rows that the data array is 
// incresed each time its capacity is raeached
#define gl_DELTA 50


// ------------------------------------------------------------------------------------

gl_STOCHASTIC_OBJ *gl_createStochastic () {

	gl_STOCHASTIC_OBJ *gl = (gl_STOCHASTIC_OBJ *) safe_malloc (sizeof(gl_STOCHASTIC_OBJ));

	gl->propensities = da_create ();
	gl->namesOfSpecies = sa_create ();
	gl->amounts = ia_create ();
	gl->previousAmounts = ia_create();
	gl->inititalAmounts = ia_create();
	gl->speciesIsFloating = ia_create();
	gl->numberOfFloating = 0;
	gl->listOfReactions = rxa_createArray();

	gl->printInterval = 1; // Default, print every event
	gl->stopRun = false;

	// Set the random number generator seed in case users does not
	srand (gl_DEFAULT_RANDOM_SEED);

	return gl;
}

void gl_freeStochastic(gl_STOCHASTIC_OBJ *gl) {

	da_free (gl->propensities);
	sa_free(gl->namesOfSpecies);
	ia_free(gl->amounts);
	ia_free(gl->previousAmounts);
	ia_free(gl->inititalAmounts);
	ia_free(gl->speciesIsFloating);
	rxa_free(gl->listOfReactions);

	free(gl);
}


void gl_setSeed (int seed) {
	srand (seed);
}


int gl_setSeedByTime () {

	int t = time (NULL);
	srand (t);
	return t;
}

void setPrintInterval (gl_STOCHASTIC_OBJ *gl, int printInterval) {
	if (printInterval > 0)
		gl->printInterval = printInterval;
}


int getPrintInterval (gl_STOCHASTIC_OBJ *gl) {
	return gl->printInterval;
}


int gl_addSpecies (gl_STOCHASTIC_OBJ *g, char* name, int value, bool isFloating) {

	sa_append (g->namesOfSpecies, name);
	ia_append (g->amounts, value);
	ia_append (g->inititalAmounts, value);

	if (isFloating) {
		ia_append (g->speciesIsFloating, true);
		g->numberOfFloating++;
	}
	else {
		ia_append (g->speciesIsFloating, false);
	}
	return g->namesOfSpecies->count - 1;
}


// Private method
static int gl_createReaction (gl_STOCHASTIC_OBJ *g) {
	
	gl_REACTION *rxa = createReaction();
	if (rxa == NULL)
		return NULL;

	// Append reaction to the network
	int index = rxa_append (g->listOfReactions, rxa);
	// Make space for the propensity value for this reaction
    da_append  (g->propensities, 0.0);

	return index;
}


// Private method, don't allow developers access in order to prevent abuse
// Might removed at a later date
static int gl_addReactant (gl_STOCHASTIC_OBJ *g, int reactionIndex, int speciesIndex, int stoichiometry) {

	if ((reactionIndex < 0) || (reactionIndex >= g->listOfReactions->count))
		return -1;

	if ((speciesIndex < 0) || (speciesIndex >= gl_MAXIMUM_REACTANTS)) {
		return -1;
	}
	else {
		gl_REACTION *rxn = g->listOfReactions->items[reactionIndex];

		rxn->reactantArray[rxn->numberOfReactants].index = speciesIndex;
		rxn->reactantArray[rxn->numberOfReactants].st = -stoichiometry;
		rxn->numberOfReactants++;

		return 0;
	}
}


int gl_addProduct (gl_STOCHASTIC_OBJ *g, int reactionIndex, int speciesIndex, int stoichiometry) {

	if ((reactionIndex < 0) || (reactionIndex >= g->listOfReactions->count)) 
		return -1;

	if ((speciesIndex < 0) || (speciesIndex >= gl_MAXIMUM_REACTANTS)) {
		return -1;
	}
	else {

		gl_REACTION *rxn = g->listOfReactions->items[reactionIndex];
		rxn->productArray[rxn->numberOfProducts].index = speciesIndex;
		rxn->productArray[rxn->numberOfProducts].st = stoichiometry;
		rxn->numberOfProducts++;

		return 0;
	}
}


int gl_addZeroOrderReaction (gl_STOCHASTIC_OBJ *g, double rateConstant) {

	int reactionIndex = gl_createReaction(g);

	if (reactionIndex < 0)
		return -1;

	gl_REACTION *rxn = g->listOfReactions->items[reactionIndex];

	rxn->rateConstant = rateConstant;

	return reactionIndex;
}


int gl_addFirstOrderReaction(gl_STOCHASTIC_OBJ *g, int speciesIndex, double rateConstant) {

	int reactionIndex = gl_createReaction(g);

	if (reactionIndex < 0)
		return -1;

	if (gl_addReactant(g, reactionIndex, speciesIndex, 1) == -1)
		return -1;

	g->listOfReactions->items[reactionIndex]->rateConstant = rateConstant;

	return reactionIndex;
}


int gl_addUniUniReaction (gl_STOCHASTIC_OBJ *gl, int reactantIndex, int productIndex, double rateConstant) {

	int reactionIndex = gl_addFirstOrderReaction (gl, reactantIndex, rateConstant);
	
	if (reactionIndex < 0)
		return -1;

	return gl_addProduct (gl, reactionIndex, productIndex, 1);
}



// Create a new reaction that is second order: 2X ->
int gl_addSecondOrderReaction (gl_STOCHASTIC_OBJ *gl, int speciesIndex, double rateConstant) {

	int reactionIndex = gl_createReaction (gl);

	if (reactionIndex < -1)
		return -1;

	if (gl_addReactant (gl, reactionIndex, speciesIndex, 2) < 0)
		return -1;

	gl->listOfReactions->items[reactionIndex]->rateConstant = rateConstant;

	return reactionIndex;
}


// Create a new reaction that is second order: 2X -> Y OR X1 + X2 -> Y
int gl_addBiUniReaction(gl_STOCHASTIC_OBJ *g, int reactantIndex1, int reactantIndex2, int productIndex, double rateConstant) {

	// First deal with 2X -> Y
	if (reactantIndex1 == reactantIndex2) {

		int reactionIndex = gl_addSecondOrderReaction(g, reactantIndex1, rateConstant);
		if (reactionIndex < 0)
			return -1;

		return gl_addProduct (g, reactionIndex, productIndex, 1);
	}
	else {
		int reactionIndex = gl_addBiMolecularReaction  (g, reactantIndex1, reactantIndex2, rateConstant);
		if (reactionIndex < 0)
			return -1;

		return gl_addProduct (g, reactionIndex, productIndex, 1);
	}
}


// Create a new reaction of the form X1 + X2 -> 
// Use addProduct to add products to the right hand side.
// If no product are added then the right-hand side is anonymous
int gl_addBiMolecularReaction(gl_STOCHASTIC_OBJ *g, int speciesIndex1, int speciesIndex2, double rateConstant) {

	// Only X1 + X2 -> allowed, use addSecondOrderReaction to add 2X ->
	if (speciesIndex1 != speciesIndex2) {

		int reactionIndex = gl_createReaction(g);

		if (gl_addReactant (g, reactionIndex, speciesIndex1, 1) < 0)
			return -1;

		if (gl_addReactant (g, reactionIndex, speciesIndex2, 1) < 0)
			return -1;

		g->listOfReactions->items[reactionIndex]->rateConstant = rateConstant;
		
		return reactionIndex;
	}
	else
		return -1;
}

// Create reaction of the form X1 + X2 + X3 ->
// Use addProduct to add optional product species
int gl_addTriMolecularReaction(gl_STOCHASTIC_OBJ *g, int speciesIndex1, int speciesIndex2, int speciesIndex3, double rateConstant) {

	// Only X1 + X2 + X3 -> 
	if ((speciesIndex1 != speciesIndex2) && (speciesIndex1 != speciesIndex3) && (speciesIndex2 != speciesIndex3)) {
		
		int reactionIndex = gl_createReaction(g);

		if (gl_addReactant(g, reactionIndex, speciesIndex1, 1) == -1)
			return -1;

		if (gl_addReactant(g, reactionIndex, speciesIndex2, 1) == -1)
    		return -1;

		if (gl_addReactant(g, reactionIndex, speciesIndex3, 1) == -1)
		   return -1;

		g->listOfReactions->items[reactionIndex]->rateConstant = rateConstant;
		return reactionIndex;
	}
	else
		return -1;
}


int gl_setRateConstant(gl_STOCHASTIC_OBJ *gl, int reactionIndex, double value) {

	if ((reactionIndex < 0) || (reactionIndex >= gl->listOfReactions->count)) {
		return -1;
	}
	else {
		gl->listOfReactions->items[reactionIndex]->rateConstant = value;
		return 0;
	}
}


void gl_setStopRun(gl_STOCHASTIC_OBJ *g, bool value) {
	g->stopRun = value;
}


double gl_getAmount(gl_STOCHASTIC_OBJ *gl, int speciesIndex) {

	if ((speciesIndex < 0) || (speciesIndex >= gl->namesOfSpecies->count)) {
		return -1;
	} 
	else {
		return gl->amounts->items[speciesIndex];
	}
}


int gl_setAmount(gl_STOCHASTIC_OBJ *gl, int speciesIndex, int value) {

	if ((speciesIndex < 0) || (speciesIndex >= gl->namesOfSpecies->count)) {
	   return -1;
	} else {
		gl->amounts->items[speciesIndex] = value;
		return 0;
	}
}


int gl_setInitialAmount(gl_STOCHASTIC_OBJ *gl, int speciesIndex, int value) {
	if ((speciesIndex < 0) || (speciesIndex >= gl->namesOfSpecies->count)) {
		return -1;
	}
	else {
		gl->inititalAmounts->items[speciesIndex] = value;
		return 0;
	}
}


void gl_reset(gl_STOCHASTIC_OBJ *gl) {

	// Only reset floating species
	for (int i = 0; i < gl->amounts->count; i++)
		if (gl->speciesIsFloating->items[i])
		   gl->amounts->items[i] = gl->inititalAmounts->items[i];
}


double gl_moveOneStep (gl_STOCHASTIC_OBJ *gl, double currentTime)  {

	double totalPropensity = 0.0;
	int stoichiometry;
	int speciesindex;

	for (int j = 0; j < gl->listOfReactions->count; j++) {
		double a1 = 1.0; 
		gl_REACTION *rxa = gl->listOfReactions->items[j];

		switch (rxa->numberOfReactants) {
			// Zero-Order
		case 0:
			a1 = 1;
			break;

			// Single reactant
			// Applies to X -> *AND* 2 X -> 
		case 1:
			speciesindex = rxa->reactantArray[0].index; // Species Index for X
			stoichiometry = rxa->reactantArray[0].st;
			if (stoichiometry == -1)
				a1 = gl->amounts->items[speciesindex];
			else
				a1 = gl->amounts->items[speciesindex] * (gl->amounts->items[speciesindex] - 1) / 2;
			break;

			// Two reactants
			// Applies to X1 + X2 ->
		case 2:
			a1 = gl->amounts->items[rxa->reactantArray[0].index] * gl->amounts->items[rxa->reactantArray[1].index];
			break;

			// Three reactants
			// Applies to X1 + X2 + X3 ->
		case 3:
			a1 = gl->amounts->items[rxa->reactantArray[0].index] * gl->amounts->items[rxa->reactantArray[1].index] * gl->amounts->items[rxa->reactantArray[2].index];
			break;
		}

	    // Compute propensity for reaction j
		gl->propensities->items[j] = gl->listOfReactions->items[j]->rateConstant*a1;
		totalPropensity = totalPropensity + gl->propensities->items[j];
	}  // end reaction loop

	 if (totalPropensity == 0.0) {
    	 return -1;
	 }

	// Generate random numbers r1 and r2
	// Use the Mersenne-Twister 
	// Uncomment if you wish to use the C lib rnd
	double r1 = randf_cc();  // (double)rand() / (double)RAND_MAX ;  <-- Uses standard C lib rand
	double r2 = randf_cc();  // (double)rand() / (double)RAND_MAX ;  <-- Uses standard C lib rand

	// Compute amount of time to advance:
	double tau = -log(r1) / totalPropensity;

	//  use random number r2 to determine which reaction has occurred:
	//  if 0 < r2 <= (a1/atot) then choose reaction 1;
	//  if (a1/atot) < r2 <= ((a1+a2)/atot) then choose reaction 2;
	//    .. etc. ..
	//  Also, update molecule numbers.

	double selector = totalPropensity * r2;
	int selectedReaction = 0;
	for (int j = 0; j < gl->listOfReactions->count; j++) {
	selector = selector - gl->propensities->items[j];
		if (selector <= 0) {
			selectedReaction = j;
			break;
		}
	}

	gl_REACTION *rxa = gl->listOfReactions->items[selectedReaction];
	int reactantIndex;
	for (int i = 0; i < rxa->numberOfReactants; i++) {
		reactantIndex = rxa->reactantArray[i].index;
		if (gl->speciesIsFloating->items[reactantIndex])
			gl->amounts->items[reactantIndex] = gl->amounts->items[reactantIndex] + rxa->reactantArray[i].st;
	}

	// Change product numbers by the value of the stoichiometry matrix
	int productIndex;
	for (int i = 0; i<rxa->numberOfProducts; i++) {
		productIndex = rxa->productArray[i].index;
		 if (gl->speciesIsFloating->items[productIndex])
		    gl->amounts->items[productIndex] = gl->amounts->items[productIndex] + rxa->productArray[i].st;
	 }

	//  advance time by tau:
	currentTime = currentTime + tau;
	return currentTime;
}


void copyAmountsToMatrix (gl_STOCHASTIC_OBJ *gl, gl_MATRIX *result, int row) {
	int count = 0;
	for (int k = 0; k < gl->namesOfSpecies->count; k++)
		if (gl->speciesIsFloating->items[k]) {  // only copy over the floating species
			// count + 1 because column zero is already occupied
			result->m[row][count + 1] = gl->amounts->items[k];
			count++;
		}
}


void makeACopyOfCurrentAmounts (gl_STOCHASTIC_OBJ *gl) {
	for (int k = 0; k < gl->namesOfSpecies->count; k++)
		gl->previousAmounts->items[k] = gl->amounts->items[k];
}


gl_MATRIX *gl_executeOnGrid (gl_STOCHASTIC_OBJ *gl, double timeStart, double timeEnd, int numberOfPoints) {


	double dt = (timeEnd - timeStart) / (numberOfPoints - 1);
	int numberOfColumns = gl->numberOfFloating + 1;

	gl->currentTime = timeStart;

	gl_MATRIX *result = gl_allocateMatrix (numberOfPoints, numberOfColumns);

	double gridTime = timeStart;
	int currentRow = 1;

	// Record the first data point at timeStart
	result->m[0][0] = timeStart;
	copyAmountsToMatrix(gl, result, 0);
	
	gridTime = gridTime + dt; // Make way for the second time point
	while ((gl->currentTime < timeEnd) && (!gl->stopRun) && (currentRow <= numberOfPoints - 1)) {

		makeACopyOfCurrentAmounts (gl);  // We might need access to the previous event

		gl->currentTime = gl_moveOneStep (gl, gl->currentTime);

		if (gl->currentTime < 0) { // Means all propensities were zero, so we stop	
			gl->currentTime = timeEnd;
			
			// Fill up the remaining slots with the last point including
			// the last data point and get out
			// 
			for (int s = currentRow; s < numberOfPoints; s++) {
				result->m[s][0] = gridTime;
				copyAmountsToMatrix(gl, result, s);

				gridTime = gridTime + dt;
			}
			return result;
		}

		while ((gl->currentTime >= gridTime) && (currentRow <= numberOfPoints - 1))  {
			result->m[currentRow][0] = gridTime;
			// We need to copy the amounts from the previous time step.
			int count = 0;
			for (int k = 0; k < gl->namesOfSpecies->count; k++)
				if (gl->speciesIsFloating->items[k]) {  // only copy over the floating species
					result->m[currentRow][count + 1] = gl->previousAmounts->items[k];
					count++;
				}

			currentRow++;
			gridTime = gridTime + dt;
			// It's possible for the current time to exceed the grid time twice in which case it will 
			// loop around too many times. Hence we need to check on the while loop that we've not
			// exceeded the number fo points we're collecting. 
			if (currentRow > numberOfPoints - 1)
				break;
		}
	}
	return result;
}


gl_MATRIX *gl_execute (gl_STOCHASTIC_OBJ *gl, double timeStart, double timeEnd) {

	gl->currentTime = timeStart;
	int numberOfRowsAvailable = gl_INITIAL_SIZE;
	int outputCount = 1; // Counts numnber actual events

	gl_MATRIX *data = gl_allocateMatrix(numberOfRowsAvailable, gl->numberOfFloating + 1); // +1 to include a column for time

    int currentRow = 0;
	// Add time zero points
	data->m[currentRow][0] = timeStart;
    int count = 0;
	for (int i = 0; i<gl->namesOfSpecies->count; i++) // Remaning columns contain species concentration
		if (gl->speciesIsFloating->items[i]) {
		   data->m[currentRow][count + 1] = gl->amounts->items[i];
		   count++;
		}

	while ((gl->currentTime < timeEnd) && (!gl->stopRun)) {
		gl->currentTime = gl_moveOneStep(gl, gl->currentTime);
		if (gl->currentTime < 0)  // Means all propensities were zero, so we stop
			gl->currentTime = timeEnd;

		if ((outputCount % gl->printInterval) == 0) {
			currentRow++;
			// Do we need more space?
			if (currentRow == numberOfRowsAvailable) {
				gl_addRowsToMatrix(data, gl_DELTA);
				numberOfRowsAvailable = numberOfRowsAvailable + gl_DELTA;
			}

			data->m[currentRow][0] = gl->currentTime; // Time is always in the first column

			// Remaining columns contain species concentration
			count = 0;
			for (int i = 0; i < gl->namesOfSpecies->count; i++)
				if (gl->speciesIsFloating->items[i]) {
					data->m[currentRow][count + 1] = gl->amounts->items[i];
					count++;
				}
		}
		outputCount++; 
	}

	// Create a matrix that actually fits the size of the generated data
	gl_MATRIX *result = gl_allocateMatrix(currentRow, data->nCols); 
	for (int i = 0; i < currentRow; i++)
		for (int j = 0; j < data->nCols; j++) {
            result->m[i][j] = data->m[i][j];
		}
	gl_freeMatrix(data);

	return result;
}
