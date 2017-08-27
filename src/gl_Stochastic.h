
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

// This is the exported API for the stochastic library

#ifndef gl_STOCHASTIC_H
#define gl_STOCHASTIC_H

#include "gl_integerArray.h"
#include "gl_stringArray.h"
#include "gl_doubleArray.h"
#include "gl_reactionArray.h"
#include "gl_reactantArray.h"
#include "gl_simpleMatrix.h"

#define gl_DEFAULT_RANDOM_SEED 6845231

typedef struct gl_StochasticObj {
	int printInterval;  
	bool stopRun;                         // Set to true to stop a long run
	gl_DOUBLE_ARRAY *propensities;        // 'Reaction' rates, aray of double
    double currentTime;

	gl_REACTION_ARRAY *listOfReactions;   // List of pointers to gl_REACTION

	gl_STRING_ARRAY *namesOfSpecies;      // Names of species
	int numberOfFloating;
	gl_INTEGER_ARRAY *amounts;            // Array of number of molecules of species
	gl_INTEGER_ARRAY *previousAmounts;    // Array of number of molecules of species one event back (used by executeOnGrid)
	gl_INTEGER_ARRAY *inititalAmounts;    // Array of initial number of molecules of species
	gl_INTEGER_ARRAY *speciesIsFloating;  // Element true if species is floating

} gl_STOCHASTIC_OBJ;


// Random number generator provided by:
// Christian Stigen Larsen
// http://csl.name
// https://github.com/cslarsen/mersenne-twister



extern "C" {

	// Create an instance of the Stochastic object, returns handle to object
	__declspec(dllexport) extern gl_STOCHASTIC_OBJ *gl_createStochastic ();

	// Frees the Stochastic object
	__declspec(dllexport) extern void gl_freeStochastic (gl_STOCHASTIC_OBJ *gl);

	// Set the random number generator seed. By default the seed is set to gl_DEFAULT_RANDOM_SEED
	__declspec(dllexport) extern void gl_setSeed (int seed);

	// Set the seed using the current time - time (NULL). Return the seed that was used
	__declspec(dllexport) extern int gl_setSeedByTime ();

	// Set the printInterval. Store results every printInterval_Th event, 1 means keep every simulaton event
	__declspec(dllexport) extern void setPrintInterval (int printInterval);

	// Set this to true if the execute loop needs to be terminated early
	__declspec(dllexport) extern void gl_setStopRun (gl_STOCHASTIC_OBJ *gl, bool value);

	// Returns the current value for the print interval
	__declspec(dllexport) extern int getPrintInterval (gl_STOCHASTIC_OBJ *gl);

	// Add a species to the model. Set isFloating to true if the species is expected
	// to change during the simulation. value is the initial number of molecules and
	// name is the name of the species. Returns the species index (see addReactant//addProduct)
	__declspec(dllexport) extern int gl_addSpecies (gl_STOCHASTIC_OBJ *gl, char* name, int value, bool isFloating);

	// Create a new reaction that is zero order:  ->
	// Returns -1 if it fails, else index to reaction list
	__declspec(dllexport) extern int gl_addZeroOrderReaction (gl_STOCHASTIC_OBJ *gl, double rateConstant);

	// Create a new reaction that is first order: X ->
	// Returns -1 if it fails, else index to reaction list
	__declspec(dllexport) extern int gl_addFirstOrderReaction (gl_STOCHASTIC_OBJ *gl, int speciesIndex, double rateConstant);

	// Create a new reaction that is first order: X1 -> X2
	// Returns -1 if it fails, else index to reaction list
	__declspec(dllexport) extern int gl_addUniUniReaction (gl_STOCHASTIC_OBJ *gl, int reactantIndex, int productIndex, double rateConstant);

	// Create a new reaction that is second order: 2X ->
	// Returns -1 if it fails, else index to reaction list
	__declspec(dllexport) extern int gl_addSecondOrderReaction (gl_STOCHASTIC_OBJ *gl, int speciesIndex, double rateConstant);

	// Create a new reaction that is second order: 2X -> Y OR X1 + X2 -> Y
	// Returns -1 if it fails, else index to reaction list
	__declspec(dllexport) extern int gl_addBiUniReaction (gl_STOCHASTIC_OBJ *gl, int reactantIndex1, int reactantIndex2, int productIndex, double rateConstant);

	// Create a new reaction that is bimo;ecular: X1 + X2 ->
	// X1 and X2 must be different species
	// Returns -1 if it fails, else index to reaction list
	__declspec(dllexport) extern int gl_addBiMolecularReaction (gl_STOCHASTIC_OBJ *gl, int speciesIndex1, int speciesIndex2, double rateConstant);

	// Create a new reaction that is bimo;ecular: X1 + X2  + X3 ->
	// The three species must all be different, ie not allowed X1 + X1 + X1, X1 + X2 + X2 etc
	// Returns -1 if it fails, else index to reaction list
	__declspec(dllexport) extern int gl_addTriMolecularReaction (gl_STOCHASTIC_OBJ *g, int speciesIndex1, int speciesIndex2, int speciesIndex3, double rateConstant);

	// Add a product to the reaction given by the handle rxa.  speciesindex is the handle
	// returned by addSpecies. stoichiometry is the stoichimetric coefficient, always positive
	// Returns -1 if unsuccessful
	// Any number of products can be added to a reaction
	__declspec(dllexport) extern int gl_addProduct (gl_STOCHASTIC_OBJ *gl, int reactionIndex, int speciesIndex, int stoichiometry);

	// Set the value for the rate constant given the reaction handle rxa
	// Return -1 if it fails, eg because rxn is null
	__declspec(dllexport) extern int gl_setRateConstant (gl_REACTION *rxn, double value);

	// Run a Gillespie simulation, starting at timeStart and ending at timeEnd.
	__declspec(dllexport) extern  gl_MATRIX *gl_execute (gl_STOCHASTIC_OBJ *gl, double timeStart, double timeEnd);

	// Run a Gillespie simulation, starting at timeStart and ending at timeEnd. Output numberOfPoints evenly spaced.
	__declspec(dllexport) extern gl_MATRIX *gl_executeOnGrid (gl_STOCHASTIC_OBJ *gl, double timeStart, double timeEnd, int numberOfPoints);

	// Run a Gillespie simulation for a single step, returns the new time
	__declspec(dllexport) extern double gl_moveOneStep (gl_STOCHASTIC_OBJ *gl, double currentTime);

	// Returns the amount for the species indicated by speciesIndex. 
	// Return -1 if it fails, eg because index is out of range
	__declspec(dllexport) extern double gl_getAmount (gl_STOCHASTIC_OBJ *gl, int speciesIndex);

	// Set the current amount for the species indicated by speciesIndex
	// Useful when using moveOneStep.
	// Return -1 if it fails, eg because index is out of range
	__declspec(dllexport) extern int gl_setAmount (gl_STOCHASTIC_OBJ *gl, int speciesIndex, int value);

	// Change the initial conditions for the species indicated by speciesIndex
	// This only affects gl_execute not gl_moveOneStep. 
	// Return -1 if it fails, eg because index is out of range
	__declspec(dllexport) extern int gl_setInitialAmount (gl_STOCHASTIC_OBJ *gl, int speciesIndex, int value);

	// Resent the current species amounts back to their initial conditions
	__declspec(dllexport) extern void gl_reset (gl_STOCHASTIC_OBJ *gl);

}
#endif

