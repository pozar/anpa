/* 
 * getheader()
 *
 * The purpose is just to load up the message header struct. Then, later
 * on in another function compare against the tables and see what we need
 * to do with the story.
 *
 * Copywrite 1994 Timothy Pozar
 *
 */

#include "anpa.h"

getheader()
{
bzero(&hdr,sizeof(hdr));
/* if (readf(fspi, &hdr, sizeof(hdr.somh)+sizeof(hdr.sld)+sizeof(hdr.snum)-1) == NULL ) */
if (readf(fspi, &hdr, sizeof(hdr.somh)+sizeof(hdr.sld)+sizeof(hdr.snum)-1) == 0 )
	fin(0);

/* Skip past UPI's special field */
if (readf(fspi, &c, 1) == NUL)
	fin(0);
while (c != TFI){
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
}

hdr.eofd1 = c;

if (readf(fspi, &hdr.selc, sizeof(hdr.selc)+sizeof(hdr.eofd2)+\
 sizeof(hdr.priority)+sizeof(hdr.eofd3)+sizeof(hdr.cat)+\
 sizeof(hdr.format)+sizeof(hdr.eofd4))== NUL)
	fin(0);
hdr.eofd2 = '\0';

/* The keyword field is varible up to 24 chars. */
bzero(buf,BUFSIZE);
i = 0;
if (readf(fspi, &c, 1) == NUL)
	fin(0);
while ((i<BUFSIZE) && (c != SP)){	/* Load up buf to end of field */
	buf[i] = c;
	i++;
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
}
strcpy(hdr.keyword,buf);
strcpy(hdr.subject,buf);

/* The version field is varible length. */
bzero(buf,BUFSIZE);
i = 0;
if (readf(fspi, &c, 1) == NUL)
	fin(0);
while ((i<BUFSIZE) && (c != SP)){	/* Load up buf to end of field */
	buf[i] = c;
	i++;
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
}
if (buf[0]=='\0'){	/* Was a null field so go past EOF */
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
}else{
	strcpy(hdr.vers,buf);
}

/* The reference field is varible length. */
bzero(buf,BUFSIZE);
i = 0;
if (readf(fspi, &c, 1) == NUL)
	fin(0);
while ((i<BUFSIZE) && (c != SP)){	/* Load up buf to end of field */
	buf[i] = c;
	i++;
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
}
if (buf[0]=='\0'){	/* Was a null field so go past EOF */
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
}else{
	strcpy(hdr.ref,buf);
}

/* The date field is varible length. */
bzero(buf,BUFSIZE);
i = 0;
if (readf(fspi, &c, 1) == NUL)
	fin(0);
while ((i<BUFSIZE) && (c != SP)){	/* Load up buf to end of field */
	buf[i] = c;
	i++;
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
}
strcpy(hdr.date,buf);

bzero(buf,BUFSIZE);
if (readf(fspi, &buf, 4) == NUL)
	fin(0);
strcpy(hdr.wordcnt,buf);


if (readf(fspi, &buf, 2) == NUL)
	fin(0);
if (readf(fspi, &c, 1) == NUL)
	fin(0);

if (flg_bay == TRUE){	/* Bay City adds three spaces before the STX. Go pass it. */
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
}

if (c == STX){

	if (flg_bay == TRUE){	/* Bay City adds a LF/CR after the STX. Go pass it. */
		if (readf(fspi, &c, 1) == NUL)
			fin(0);
		if (readf(fspi, &c, 1) == NUL)
			fin(0);
	}

	if (readf(fspi, &c, 1) == NUL)	/* One more byte... */
		fin(0);
	/* This is the "subject" field and it is varible length. */
	bzero(buf,BUFSIZE);
	i = 0;
	if (readf(fspi, &c, 1) == NUL)
		fin(0);
	while ((i<BUFSIZE) && ((c != '<') && (c != '\n') && (c != '\r'))){
		buf[i] = c;
		i++;
		if (readf(fspi, &c, 1) == NUL)
			fin(0);
	}
	if (buf[0] != '\0'){
		/* Go past the '<' and the '\n' */
		if (readf(fspi, &c, 1) == NUL)
			fin(0);
		if (readf(fspi, &c, 1) == NUL)
			fin(0);
		if (readf(fspi, &c, 1) == NUL)
			fin(0);
	}
	strcpy(hdr.subject,buf);
}
} /* EOF getheader.c */
