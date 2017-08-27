
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

// Simple appendable double array type
// In the current version if space runs out, the array is
// increased two fold in size. 
// The array can be acessed directly using:  x->items[index]
// x->count contains the current used size of the array


#include <stdlib.h>

#include "gl_doubleArray.h"
#include "gl_utils.h"

gl_DOUBLE_ARRAY *da_create() {

	gl_DOUBLE_ARRAY *da = (gl_DOUBLE_ARRAY *) safe_malloc(sizeof(gl_DOUBLE_ARRAY));
	da->capacity = gl_DOUBLE_ARRAY_INIT_CAPACITY;
	da->count = 0;
	da->items = (double *) malloc(sizeof(double) * da->capacity);

	return da;
}


void da_free (gl_DOUBLE_ARRAY *da) {

	safe_free(da->items);
	safe_free(da);
}


static void vector_resize(gl_DOUBLE_ARRAY *da, int capacity) {

	double *items = (double *) safe_realloc(da->items, sizeof(void *) * capacity);
	if (items) {
		da->items = items;
		da->capacity = capacity;
	}
}

void da_append (gl_DOUBLE_ARRAY *da, double value) {

	if (da->capacity == da->count)
		vector_resize(da, da->capacity * 2);
	da->items[da->count++] = value;
}


int a_setValue(gl_DOUBLE_ARRAY *da, int index, int value) {
	if (index >= da->count)
		return -1;
	da->items[index] = value;
	return 0;
}