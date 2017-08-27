
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

// Simple appendable integer array type
// In the current version if space runs out, the array is
// increased two fold in size. 
// The array can be acessed directly using:  x->items[index]
// x->count contains the current used size of the array

#ifndef INTEGERARRAY_H
#define INTEGERARRAY_H

#include <stdlib.h>

#define gl_INTEGER_ARRAY_INIT_CAPACITY 20

typedef struct integerArray {
	int *items;
	int count;     // Current used elements in the array
	int capacity;  // private variable
} gl_INTEGER_ARRAY;


extern gl_INTEGER_ARRAY *ia_create ();
extern void ia_free (gl_INTEGER_ARRAY *ia);
extern void ia_append (gl_INTEGER_ARRAY *ia, int value);

// Return -1 if index is out of range
extern int  ia_setValue (gl_INTEGER_ARRAY *ia, int index, int value);

// Returns -1 if index is out of range
extern int  ia_getValue(gl_INTEGER_ARRAY *ia, int index, int *value);

#endif
