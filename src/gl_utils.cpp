
#include <stdlib.h>
#include <stdio.h>

// Some safe routines for memory management

void *safe_malloc (size_t size) {

	void* result = malloc (size);
	if (result == NULL) {
		fprintf (stderr, "safe_malloc: Memory full. Couldn't allocate %lu bytes.\n", (unsigned long)size);
		exit (EXIT_FAILURE);
	}
	return result;
}

void *safe_calloc (size_t n, size_t size) {
	void* result = calloc(n, size);
	if (result == NULL) {
		fprintf (stderr, "safe_calloc: Memory full. Couldn't allocate %lu bytes.\n",	(unsigned long) (n * size));
		exit (EXIT_FAILURE);
	}
	return result;
}


void *safe_realloc (void* p, size_t size) {
	void* result = realloc (p, size);
	if (result == NULL) {
		fprintf (stderr, "safe_realloc: Memory full. Couldn't allocate %lu bytes.\n", (unsigned long)size);
		exit (EXIT_FAILURE);
	}
	return result;
}

void safe_free (void* p) {
	if (p != NULL)
	   free (p);
}