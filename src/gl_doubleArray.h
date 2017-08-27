
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

// Simple appendable double array type
// In the current version if space runs out, the array is
// increased two fold in size. 
// The array can be acessed directly using:  x->items[index]
// x->count contains the current used size of the array

#ifndef DOUBLEARRAY_H
#define DOUBLEARRAY_H

#include <stdlib.h>

#define gl_DOUBLE_ARRAY_INIT_CAPACITY 20

typedef struct doubleArray {
	double *items;
	int count;      // Current uzed size of the array 
	int capacity;   // Priviate memeber
} gl_DOUBLE_ARRAY;


extern gl_DOUBLE_ARRAY *da_create();
extern void da_free(gl_DOUBLE_ARRAY *da);
extern void da_append (gl_DOUBLE_ARRAY *da, double value);

// Return -1 if index is out of range
extern int da_setValue (gl_DOUBLE_ARRAY *da, int index, double value);

#endif
