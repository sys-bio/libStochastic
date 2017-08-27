
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

// Simple appendable reaction array type
// In the current version if space runs out, the array is
// increased two fold in size. 
// The array can be acessed directly using:  x->items[index]
// x->count contains the current used size of the array

#ifndef REACTIONARRAY_H
#define REACTIONARRAY_H

#include <stdlib.h>

#include "gl_reactantArray.h"
#include "gl_reaction.h"

#define gl_REACTION_ARRAY_INIT_CAPACITY 20


typedef struct TReactionArray {
	gl_REACTION **items;
	int count;
	int capacity;   // Private
} gl_REACTION_ARRAY;


extern gl_REACTION_ARRAY *rxa_createArray ();
extern void rxa_free (gl_REACTION_ARRAY *rxa);
// Return index of position of appended reaction
extern int  rxa_append (gl_REACTION_ARRAY *rxa, gl_REACTION *value);

#endif

