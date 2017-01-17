
/* 
 * readf()
 *
 * readf will do the same as fread but will not return if a timeout 
 * happens like reading in from a serial port.
 *
 * We seem to be droping chars on the floor since this is reading in
 * from a tty. I need to stick some sort of buffering in here to suck in
 * as much as possible.
 *
 * Copywright 1994 Timothy Pozar
 *
 */

#include "anpa.h"

readf(fsp,buffer,len)
FILE *fsp;
char *buffer;
int len;
{
int a,n;

	for (n = 0; n < len; n++) {
		a = fread(buffer + n, 1, 1, fsp); 
		buffer[n] = buffer[n] & 0x7f;
		if ((a == 0) && feof(fsp))
			return(n);
	}

	return(n);
}

