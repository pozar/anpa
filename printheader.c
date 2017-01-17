/* 
 * printheader()
 *
 * Print the header to a file directed by FILE fspo* so it looks kinda
 * RFC-822ish. We need to have a "From <address>", and a "Subject: <>"
 * line in here for gopher and WAIS indexing.
 *
 * Copywrite 1994 Timothy Pozar
 *
 */

#include "anpa.h"

printheader()
{
time(&tc);
if(debug_level > 8)
	printf("%s\n",ctime(&tc));
fprintf(fspo,"From %s %s",MAILADDR,ctime(&tc));
if(debug_level > 0){
	fprintf(fspo,"Service-Level-Designator: %c = ",hdr.sld);
	if(debug_level > 8)
		printf("Service-Level-Designator: %c = \n",hdr.sld);
	switch(hdr.sld) {
		case 'a':
			fprintf(fspo,"Expanded APTV Newspaper-syle News");
			break;
		case 'b':
			fprintf(fspo,"APTV Newspaper-style National Feature or Advance");
			break;
		case 'c':
			fprintf(fspo,"Nationwide, selected standing features");
			break;
		case 'd':
		case 'e':
		case 'g':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
			fprintf(fspo,"State and Regional");
			break;
		case 'f':
			fprintf(fspo,"Newspaper-style financial wire");
			break;
		case 'o':
			fprintf(fspo,"Supreme Court Text or State and Regional - New York City, Ohio, Oklahoma Oregon");
			break;
		case 'p':
			fprintf(fspo,"Basic APTV Newspaper-style news");
			break;
		case 's':
		case 't':
			fprintf(fspo,"Nationwide Sports");
			break;
		case 'w':
			fprintf(fspo,"AP Alert or State and Regional - Wyoming");
			break;
		default:
			fprintf(fspo,"Not yet defined");
	}
	fputc('\n',fspo);
	fprintf(fspo,"Story-Number: %s\n",hdr.snum);
	fprintf(fspo,"Selector-Code: %s\n",hdr.selc);
		if(debug_level > 8)
			printf("Selector-Code: %s\n",hdr.selc);
	fprintf(fspo,"Priority: %c = ",hdr.priority);
		if(debug_level > 8)
			printf("Priority: %c = \n",hdr.priority);
		/* According to the RFCs that extend RFC-822, the data field should contain:
			"normal" | "non-urgent" | "urgent"
		   We should translate the ANPA into these fields and keep the ANPA in "<>". */
	switch(hdr.priority) {
		case 'f':
			fprintf(fspo,"Flash");
			break;
		case 'b':
			fprintf(fspo,"Bulletin");
			break;
		case 'u':
			fprintf(fspo,"Urgent");
			break;
		case 'r':
			fprintf(fspo,"Regular");
			break;
		case 'd':
		case 'h':
			fprintf(fspo,"Deferred");
			break;
		case 'a':
		case 's':
			fprintf(fspo,"Weekday Advance");
			break;
		case 'y':
			fprintf(fspo,"Rerun");
			break;
		default:
			fprintf(fspo,"Not yet defined");
	}
	fputc('\n',fspo);
	fprintf(fspo,"Category: %c = ",hdr.cat);
	if(debug_level > 8)
		printf("Category: %c = \n",hdr.cat);
	switch(hdr.cat) {
		case 'a':
			fprintf(fspo,"Domestic, non-Washington, general news stories");
			break;
		case 'b':
			fprintf(fspo,"Special events (Olymipic, special coverage)");
			break;
		case 'k':
			fprintf(fspo,"Commentary/editorial");
			break;
		case 'w':
			fprintf(fspo,"Washington-datelined general news");
			break;
		case 'd':
			fprintf(fspo,"National NewsWatche/Summary");
			break;
		case 'h':
			fprintf(fspo,"National NewsMinute/Headline");
			break;
		case 'i':
			fprintf(fspo,"International");
			break;
		case 'g':
			fprintf(fspo,"State NewsWatch/Summary");
			break;
		case 'j':
			fprintf(fspo,"State NewsMinute/Headline");
			break;
		case 'n':
			fprintf(fspo,"State Regional");
			break;
		case 'f':
			fprintf(fspo,"Business/Financial News");
			break;
		case 'p':
			fprintf(fspo,"Political Story/Results");
			break;
		case 'c':
			fprintf(fspo,"Standing General Feature");
			break;
		case 'e':
			fprintf(fspo,"Entertainment Television and Culture");
			break;
		case 'm':
			fprintf(fspo,"Farm/Agriculture");
			break;
		case 'q':
			fprintf(fspo,"Sports Scores");
			break;
		case 'o':
			fprintf(fspo,"Weather");
			break;
		case 's':
			fprintf(fspo,"Sports Stories");
			break;
		case 'r':
			fprintf(fspo,"Radio Network Billboards");
			break;
		case 't':
			fprintf(fspo,"Television Billboards, Advisory");
			break;
		case 'v':
			fprintf(fspo,"Advisories");
			break;
		default:
			fprintf(fspo,"Not yet defined");
	}
	fputc('\n',fspo);
	fprintf(fspo,"Format-Identifier: ");
	switch(hdr.format[0]) {
		case DC4:
			fprintf(fspo,"Agate");
			break;
		case DC3:
			fprintf(fspo,"Body-Type");
			break;
		default:
			fprintf(fspo,"Not Defined");
	}
	if ((hdr.format[0] == DC4) || (hdr.format[0] == DC3)) {
		switch(hdr.format[1]) {
			case DC2:
				fprintf(fspo," Tabular");
				break;
			case DC1:
				fprintf(fspo," Text");
				break;
		}
	}
	
	fputc('\n',fspo);
	
} /* endif debug > 0 */

fprintf(fspo,"Keywords: %s\n",hdr.keyword);

if(debug_level > 0){
	/* The version field is varible length. */
	if(hdr.vers[0] != '\0')
		fprintf(fspo,"Version: %s\n",hdr.vers);
	
	/* The reference field is varible length. */
	if(hdr.ref[0] != '\0')
		fprintf(fspo,"Reference: %s\n",hdr.ref);
	
	/* The date field is varible length. */
	if(hdr.date[0] != '\0')
		fprintf(fspo,"Story-Date: %s\n",hdr.date);
	
	fprintf(fspo,"Word-Count: %s\n",hdr.wordcnt);
} /* endif debug > 0 */
if (hdr.priority == 'b')
	fprintf(fspo,"Subject: BULLETIN -- %s\n",hdr.subject);
if (hdr.priority == 'u')
	fprintf(fspo,"Subject: URGENT -- %s\n",hdr.subject);
if ((hdr.priority != 'b') && (hdr.priority != 'b'))
	fprintf(fspo,"Subject: %s\n",hdr.subject);
	if(debug_level > 8)
		printf("Subject: %s\n",hdr.subject);

fputc('\n',fspo);	/* Newline between header and story */

} /* EOF printheader.c */
