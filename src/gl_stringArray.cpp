

#include <stdlib.h>

#include "gl_stringArray.h"
#include "gl_utils.h"

gl_STRING_ARRAY *sa_create () {

	gl_STRING_ARRAY *sa = (gl_STRING_ARRAY *) safe_malloc(sizeof(gl_STRING_ARRAY));
	sa->capacity = gl_STRING_ARRAY_INIT_CAPACITY;
	sa->count = 0;
	sa->items = (char **) safe_calloc (sa->capacity, sizeof(char *));

	return sa;
}


void sa_free (gl_STRING_ARRAY *ia) {

	safe_free(ia->items);
	safe_free(ia);
}


static void vector_resize (gl_STRING_ARRAY *ia, int capacity) {

	char **items = (char **) safe_realloc(ia->items, sizeof(char *) * capacity);
	if (items) {
		ia->items = items;
		ia->capacity = capacity;
	}
}

void sa_append (gl_STRING_ARRAY *sa, char* value) {

	if (sa->capacity == sa->count)
		vector_resize(sa, sa->capacity * 2);
	sa->items[sa->count++] = value;
}


int sa_setValue (gl_STRING_ARRAY *sa, int index, char *value) {
	if (index >= sa->count)
		return -1;
	sa->items[index] = value;
	return 0;
}