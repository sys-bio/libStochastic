
/******************************************************
* Copyright(C) 2017 Herbert Sauro
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

// Simple appendable reactant array type
// In the current version if space runs out, the array is
// increased two fold in size. 
// The array can be acessed directly using:  x->items[index]
// x->count contains the current used size of the array

#ifndef REACTANTARRAY_H
#define REACTANTARRAY_H

#define gl_REACTANT_ARRAY_INIT_CAPACITY 10

#define gl_MAXIMUM_REACTANTS 12

typedef struct TReactant {
	int index;  // Index to list of species array
	int st;     // Stoichiometry
} gl_REACTANT;


// This could be done better, curretly thereis a meximum number of reactants
typedef struct reactantArray {
	//gl_REACTANT items[gl_MAXIMUM_REACTANTS];
	int numberOfReactants;
} gl_REACTANT_ARRAY;


//extern REACTANT *createReactant(int reactantIndex, int stoichiometry);

//extern REACTANT_ARRAY *ra_create();
//extern void ra_free();
//extern void reactant_append (REACTANT_ARRAY *ra, REACTANT *value);
//extern void ra_setValue (REACTANT_ARRAY *ra, int index, REACTANT *value);

#endif
