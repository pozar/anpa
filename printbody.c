
/*
 *	ANPA wire feed parser.
 *
 *	Copyright 1994 Tim Pozar
 *
 */

#include "anpa.h"

printbody()
{
	while((c != FF) && (c != EOT)){
		if (readf(fspi, &c, 1) == NUL)
			fin(0);
		switch(c) {
		case ETX:	/* ^C */
		case EOT:	/* ^D */
		case TLI:	/* ^H */
		case VT:	/* ^K - Used for '~' in the Spanish feeds */
		case CR:	/* ^M */
		case NUL:	/* ^@ - Garbage that pops up in the Bay City 
					feed and screws up the gopher indexing. */
			break;
		case LF:
			fputc('\n',fspo);
			break;
		default:
			fputc(c,fspo);
		}
	}
	fputc('\n',fspo);
	fputc('\n',fspo);
	return;

}	/* EOF printbody() */

