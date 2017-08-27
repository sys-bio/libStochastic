
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

/* Utilties */

#ifndef gl_UTILS_H
#define gl_UTILES_H

extern void *safe_malloc (size_t size);
extern void *safe_calloc (size_t n, size_t size);
extern void *safe_realloc (void* p, size_t size);
extern void safe_free (void* p);

#endif


