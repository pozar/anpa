/* 
 * selector()
 *
 * Determins what to do with this article.
 *
 * Copyright 1994 Timothy Pozar
 *
 */

#include "anpa.h"

selector(x)
int x;
{
int n;

for (i = x; i < MAXTABLES; i++){
	if(strchr(table[i].sld,hdr.sld)){
		if((strchr(table[i].cat,hdr.cat))||(strchr(table[i].cat,'?'))){
			for (n = 0; n < MAXSEL; n++){
				if(strncmp(table[i].sel[n],hdr.selc,5) == 0){
					strcpy(act,table[i].action);
					return(i);
				}
			}
		}
	}
}
	
return(-1);

}

