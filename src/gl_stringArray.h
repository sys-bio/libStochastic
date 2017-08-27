

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

// Simple appendable string array type
// In the current version if space runs out, the array is
// increased two fold in size. 
// The array can be acessed directly using:  x->items[index]
// x->count contains the current used size of the array

#ifndef STRINGARRAY_H
#define STRINGARRAY_H

#define gl_STRING_ARRAY_INIT_CAPACITY 20

typedef struct stringArray {
	char **items;
	int count;     // Size of current used space of the array
	int capacity;  // Priviate variable
} gl_STRING_ARRAY;


extern gl_STRING_ARRAY *sa_create();
extern void sa_free (gl_STRING_ARRAY *sa);
extern void sa_append (gl_STRING_ARRAY *sa, char *value);

// Returns -1 if index is out of range
extern int sa_setValue (gl_STRING_ARRAY *sa, int index, char *value);

#endif