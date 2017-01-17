/* 
 * action()
 *
 * Preform any action that is needed with this article
 *
 * Copywright 1994 Timothy Pozar
 *
 */

#include "anpa.h"

char doit[BUFSIZE];

action()
{
	sprintf(doit,act,tmpfnp,tmpfnp,tmpfnp);
	if(debug_level > 4)
		printf("Running: %s\n",doit);
	system(doit);
	return(TRUE);
}
