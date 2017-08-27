

#include <stdlib.h>

#include "gl_reaction.h"
#include "gl_utils.h"

gl_REACTION *createReaction() {

	gl_REACTION *rxa = (gl_REACTION *) safe_calloc (1, sizeof(gl_REACTION));

	return rxa;

}