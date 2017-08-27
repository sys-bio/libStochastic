
#include <stdlib.h>

#include "gl_reaction.h"
#include "gl_reactionArray.h"
#include "gl_utils.h"

gl_REACTION_ARRAY *rxa_createArray () {

	gl_REACTION_ARRAY *result = (gl_REACTION_ARRAY *) safe_malloc(sizeof(gl_REACTION_ARRAY));
	result->count = 0;
	result->capacity = gl_REACTION_ARRAY_INIT_CAPACITY;
	result->items = (gl_REACTION **) safe_calloc (result->capacity, sizeof(gl_REACTION *));

	return result;
}


void rxa_free (gl_REACTION_ARRAY *rl) {

	for (int i = 0; i < rl->capacity; i++)
		if (rl->items[i] != NULL)
			free(rl->items[i]);
	free (rl->items);
	free (rl);
}


static void vector_resize (gl_REACTION_ARRAY *rxa, int capacity) {

	gl_REACTION **items = (gl_REACTION **) safe_realloc(rxa->items, sizeof(gl_REACTION *) * capacity);
	if (items) {
		rxa->items = items;
		rxa->capacity = capacity;
	}
}


int rxa_append (gl_REACTION_ARRAY *rxa, gl_REACTION *value) {

	if (rxa->capacity == rxa->count)
		vector_resize (rxa, rxa->capacity * 2);
	rxa->items[rxa->count++] = value;

	return rxa->count-1;
}

