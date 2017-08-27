
#include <stdlib.h>

#include "gl_integerArray.h"
#include "gl_utils.h"

gl_INTEGER_ARRAY *ia_create () {

	gl_INTEGER_ARRAY *ia = (gl_INTEGER_ARRAY *) safe_malloc (sizeof(gl_INTEGER_ARRAY));
	ia->capacity = gl_INTEGER_ARRAY_INIT_CAPACITY;
	ia->count = 0;
	ia->items = (int *) safe_malloc(sizeof(int) * ia->capacity);

	return ia;
}


void ia_free (gl_INTEGER_ARRAY *ia) {

	safe_free(ia->items);
	safe_free(ia);
}


static void vector_resize (gl_INTEGER_ARRAY *ia, int capacity) {

	int *items = (int *) safe_realloc (ia->items, sizeof(void *) * capacity);
	if (items) {
		ia->items = items;
		ia->capacity = capacity;
	}
}


void ia_append (gl_INTEGER_ARRAY *ia, int value) {

	if (ia->capacity == ia->count)
		vector_resize(ia, ia->capacity * 2);
	ia->items[ia->count++] = value;
}


int ia_setValue(gl_INTEGER_ARRAY *ia, int index, int value) {
	if (index >= ia->count)
		return -1;
	ia->items[index] = value;
	return 0;
}


int ia_getValue(gl_INTEGER_ARRAY *ia, int index, int *value) {
	if (index >= ia->count)
		return -1;
	*value = ia->items[index];
	return 0;
}
