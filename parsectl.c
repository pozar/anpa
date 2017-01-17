/* 
 * parsectl()
 *
 * Parses the anpa ctl file and fills up the tables.
 *
 * Copyright 1994 Timothy Pozar
 *
 */

#include "anpa.h"
#define MAXARGS	64

parsectl()
{
FILE *fspc;
char *toks[MAXARGS], *cp, *acp;
int n, nt, t=0, x;

if ((fspc = fopen(cntlfile, "r")) == NULL) {
	perror(cntlfile);
	fin(1);
}

readrec(fspc);
printf("Got ... \"%s\"\n",recbuf);
while (!feof(fspc)){
cp = recbuf;

for(n = 0; n < MAXARGS; n++){
	toks[n] = strsep(&cp, " \t");
	if (toks[n] == NULL) break;
}

nt = n;

for(n = 0; n < nt ; n++){
	if(toks[n][0] == '#') break;

	if(strncasecmp(toks[n],"SID1",4) == 0) {
		n++;
		strcpy(sid1,toks[n]);
		if (debug_level >= 8)
			printf("SID1	%s\n", sid1);
		break;
	}
	if(strncasecmp(toks[n],"SID2",4) == 0) {
		n++;
		strcpy(sid2,toks[n]);
		if (debug_level >= 8)
			printf("SID2	%s\n", sid2);
		break;
	}
	if(strncasecmp(toks[n],"URGENT",6) == 0) {
		n++;
		strcpy(urgent,toks[n]);
		if (debug_level >= 8)
			printf("URGENT	%s\n", sid2);
		break;
	}
	if(strncasecmp(toks[n],"BULLETIN",8) == 0) {
		n++;
		strcpy(bulletin,toks[n]);
		if (debug_level >= 8)
			printf("BULLETIN	%s\n", sid2);
		break;
	}
	if(strncasecmp(toks[n],"DEFACT",6) == 0) {
		n++;
		bzero(defact,BUFSIZE);
		for(x=0; toks[n] != NULL; n++){
			strcat(defact,toks[n]);
			strcat(defact," \0");
			x++;
		}
		if (debug_level >= 8)
			printf("DEFACT	%s\n\n", defact);
		break;
	}
	if(strncasecmp(toks[n],"TABLE",5) == 0) {
		n++;
		toupper(toks[n][0]);
		t = toks[n][0] - 'A';
		if (debug_level >= 8)
			printf("TABLE	%c\n", toks[n][0]);
		break;
	}
	if(strncasecmp(toks[n],"START",5) == 0) {
		n++;
		strcpy(table[t].start,toks[n]);
		if (debug_level >= 8)
			printf("START	%s\n", table[t].start);
		break;
	}
	if(strncasecmp(toks[n],"STOP",4) == 0) {
		n++;
		strcpy(table[t].stop,toks[n]);
		if (debug_level >= 8)
			printf("STOP	%s\n", table[t].stop);
		break;
	}
	if(strncasecmp(toks[n],"SLD",3) == 0) {
		n++;
		strcpy(table[t].sld,toks[n]);
		if (debug_level >= 8)
			printf("SLD	%s\n", table[t].sld);
		break;
	}
	if(strncasecmp(toks[n],"SEL",3) == 0) {
		if (debug_level >= 8)
			printf("SEL	");
		n++;
		for(x=0; toks[n] != NULL; n++){
			strcpy(table[t].sel[x],toks[n]);
			if (debug_level >= 8)
				printf("%s ", table[t].sel[x]);
			x++;
		}
		if (debug_level >= 8)
			printf("\n");
		break;
	}
	if(strncasecmp(toks[n],"CAT",3) == 0) {
		n++;
		strcpy(table[t].cat,toks[n]);
		if (debug_level >= 8)
			printf("CAT	%s\n", table[t].cat);
		break;
	}
	if(strncasecmp(toks[n],"ACTION",6) == 0) {
		n++;
		bzero(table[t].action,BUFSIZE);
		for(x=0; toks[n] != NULL; n++){
			strcat(table[t].action,toks[n]);
			strcat(table[t].action," \0");
			x++;
		}
		if (debug_level >= 8)
			printf("ACTION	%s\n", table[t].action);
		break;
	}
	if(strncasecmp(toks[n],"ENDTABLE",8) == 0) {
		if (debug_level >= 8)
			printf("ENDTABLE	%c\n\n", t + 'A');
		break;
	}
}

readrec(fspc);

}

if (debug_level >= 8)
	printf("Finished parsing the config file\n");
fclose(fspc);
return(0);

}

