

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


#ifndef REACTION_H
#define REACTION_H

#define gl_MAXIMUM_REACTANTS 12

#include "gl_reactantArray.h"

// A reaction is a list of reactants and a list of products
// aswell as the value for the rate constant

// This could be done better, current there is a max number of reactants 
// SHould be made dynamic in the future
typedef struct TReaction {
	gl_REACTANT reactantArray[gl_MAXIMUM_REACTANTS];
	int numberOfReactants;

	gl_REACTANT productArray[gl_MAXIMUM_REACTANTS];
	int numberOfProducts;
	double rateConstant;
} gl_REACTION;


extern gl_REACTION *createReaction();


#endif