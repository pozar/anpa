/*
 *	ANPA wire feed parser.
 *
 *	Copyright 1994-1999 Tim Pozar
 *
 */

#include "anpa.h"

main(argc, argv)
int	argc;
char	**argv;
{
int s;

	ver = VER;
	rev = REV;
	if (argc == 1) {
		banner(argv[0]);
	}

	flg_pidfile = FALSE;
	flg_bay = FALSE;
	strcpy(pidfile, PIDFILE);
	debug_level=0;
	strcpy(cntlfile, CNTLFILE);

	for (i = 1; i < argc; i++) {
	if (argv[i][0] = '-'){
		switch(argv[i][1]){
		case 'i':
		case 'I':
			i++;
			strcpy(infile,argv[i]);
			if ((fspi = fopen(infile, "rb")) == NULL) {
				perror(infile);
				fin(1);
			}
			flg_stdin = FALSE;
			setserial();
			break;
		case 'c':
		case 'C':
			i++;
			strcpy(cntlfile,argv[i]);
			break;
		case 'p':
		case 'P':
			i++;
			if((i < argc) && (argv[i][0]!='-'))
				strcpy(pidfile,argv[i]);
			else
				i--;
			flg_pidfile = TRUE;
			break;
		case '\0':
			fspi = stdin;
			flg_stdin = TRUE;
			break;
		case 'b':
		case 'B':
			flg_bay = TRUE;
			break;
		case 'x':
		case 'X':
			i++;
			debug_level=atol(argv[i]);
			break;
		default:
			banner(argv[0]);
		}
	}
	}

	if(flg_pidfile){
		sprintf(buf,"%s.%i\0",pidfile,getpid());
		if ((fspp = fopen(buf, "w")) == NULL) {
			perror(buf);
			fin(1);
		}
		fclose(fspp);
	}

	strcpy(defact, DEFACT);
	strcpy(bulletin, BULLETIN);
	strcpy(urgent, URGENT);
	parsectl();	/* Parse the control file */
/*	signal(SIGHUP,parsectl()); */

/* The main event loop goes here... */
	while(TRUE){
		if (readf(fspi, &c, 1) == NUL)
			fin(0);
		while(c != SYN){
			if (readf(fspi, &c, 1) == NUL)
				fin(0);
		}
		getheader();
		strcpy(tmpfnp, "/tmp/anpa.temp.XXXXXX");
		mkstemp(tmpfnp);
		if(strlen(tmpfnp) == 0){
			perror(tmpfnp);
			fin(1);
		}
		if ((fspo = fopen(tmpfnp, "w")) == NULL) {
			perror(tmpfnp);
			fin(1);
		}
		printheader();
		printbody();
		fflush(NULL);
		sync();
 		if (fclose(fspo)!=0){	/* Close the output. */
			perror("Could not close output file");
      			printf("fclose error on output file\n");
		}
		if((s=selector(0))==-1){
			strcpy(act, defact);
			action();
		}else{
			while((s!=-1)&&(s<MAXTABLES)){
				action();
				s++;
				s=selector(s);
			}
	/* Any special cases for priority? */
			if(hdr.priority=='b'){ /* If this is a 'bulletin' message... */
				strcpy(act, bulletin);
				/* action(); */
			}
			if(hdr.priority=='u'){ /* If this is a 'urgent' message... */
				strcpy(act, urgent);
				/* action(); */
			}
		}
		if(unlink(tmpfnp) != 0){
			perror(tmpfnp);
      			printf("Problems unlinking file %s\n",tmpfnp);
		}
	}
	fin(0);

}	/* main() */

fin(x)
int x;
{
	if(debug_level > 8)
		printf("fin(%d)\n",x);
	fflush(NULL);
	if(debug_level > 0)
		printf("Exiting with an errorlevel of %i.\n",x);
	exit(x);
}

banner(c)
char * c;
{
	fprintf(stderr, "ANPA wire feed parser.\n Version.Revision = %d.%d Copyright 1994-1999 Tim Pozar\n Usage: %s [options]\n where [options] are:\n -i device | inputfile\n -  [stdin]\n -p pidfile (a filename that will be created\n with the PID number appended to it. Default: anpa.pid.<#>)\n -c controlfile (default: anpa.ctl)\n -x debug-level\n 0 = off (default)\n 8 = shows ctl file parsing\n 9 = verbose\n -b (enables hacks to read the Bay City News ANPA header correctly.\n", ver, rev, c);
	exit(1);
}

