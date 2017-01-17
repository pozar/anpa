/* 
 * readrec()
 *
 * read a line of text in to a buffer
 *
 * Copyright 1994 Timothy Pozar
 *
 */

#include "anpa.h"

readrec(fsp)
FILE *fsp;
{
char ch;
int  n=0;
	memset(recbuf,'\0',RECSIZE);
	if (fread(&ch, 1, 1, fsp) == NUL)
		return(NUL);
	while ((ch != NUL) && (ch != LF) && (ch != CR) && (n < RECSIZE)){
		recbuf[n]=ch;
		n++;
		if (fread(&ch, 1, 1, fsp) == NUL)
			return(NUL);
	}
	return(n);
}

