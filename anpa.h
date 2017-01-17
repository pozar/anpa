#ifndef _ANPA_H_
#define _ANPA_H_

/* 
 * anpa header file...
 *
 * Copyright 1994-1999 Timothy Pozar
 *
 */

#define VER	1
#define REV	0

#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define FALSE	0
#define TRUE	1
#define NO	FALSE
#define YES	TRUE

#define	NUL	0
#define SOH	1
#define STX	2
#define ETX	3
#define EOT	4
#define TLI	8
#define LF	10
#define VT	11
#define FF	12
#define CR	13
#define DC1	17
#define DC2	18
#define DC3	19
#define DC4	20
#define SYN	22
#define TFI	31
#define SP	' '

#define MAILADDR	"apadmin"
#define CNTLFILE	"anpa.ctl"
#define PIDFILE		"anpa.pid"

#define DEFACT		"/bin/cat %s > /dev/null" 
				/* default action to do with the articles 
				   if not defined by the control file */
#define BULLETIN	"/bin/cat %s > /dev/null" 
				/* default action to do with bulletins
				   if not defined by the control file */
#define URGENT		"/bin/cat %s > /dev/null" 
				/* default action to do with "urgent" articles
				   if not defined by the control file */

#define SPEED	9600/* speed of the tty port that the wire is coming in on */

#define BUFSIZE	255
#define RECSIZE	255

int	i,		/* All around int */ 
	ver, rev, 	/* version and revision level */
	debug_level, 	/* debug level */
	flg_stdin, 	/* standard in is defined */
	flg_pidfile, 	/* pidfile is defined */
	flg_bay;	/* hack for Bay City News is defined */
char	c, act[BUFSIZE], urgent[BUFSIZE], bulletin[BUFSIZE], defact[BUFSIZE], 
           buf[BUFSIZE], recbuf[RECSIZE], pidfile[BUFSIZE], infile[BUFSIZE], 
           outfile[BUFSIZE], cntlfile[BUFSIZE], oldoutfile[BUFSIZE], tmpfnp[BUFSIZE];
FILE	*fspi, *fspo, *fspp;
time_t	tb, tc;

/* 
 * Site data
 * This is used when looking for updates for us that may come down via
 * the wire.
 *
 */

char sid1[6], sid2[6];

/*
 * This is the selector table for passing and rejecting articles.
 * Articles are parsed for header info and then matched against this 
 * table. If there is a match, the article is acted on by the "action" 
 * field. If no match, the article is skipped. 
 *
 * The '%s' in the action field will be replaced by the output file.
 *
 * We are making room for 26 table entries [A-Z].
 *
 */
#define MAXTABLES	26
#define MAXSEL	20
struct table_struct {
	char start[5];		/* Start time i.e., "0000" */
	char stop[5];		/* Stop time i.e., "2359" */
	char sld[27];		/* SLD i.e., 'abce...'  */
	char sel[MAXSEL][6];	/* Selector Code i.e., "'Opcl-',1nt--','1al--',..." */
	char cat[27];		/* Category code i.e., 'ac..' */
	char action[BUFSIZE];	/* What action to take. 
				   i.e., "/usr/sbin/sendmail ap < %s" */
} table[MAXTABLES];

/*
 * ANPA header structure.
 * String fields may be longer than the standard as they may have
 * space for the NUL for the termination of the string (ala 'C').
 *
 */

struct hdr_struct {
	char somh[2];		/* Start Of Message Header "SYN, SYN, SOH"
				   but drops first SYN since it was scarfed
				   by the event loop. */
	char sld;		/* Service-Level Designator i.e., 'v' */
	char snum[5];		/* Story NUMber i.e., "0404" NUL terminated */
	char upi_dev[15];	/* Strange UPI junk */
	char eofd1;		/* End Of Field is: TFI */
	char selc[5];		/* SELector Code ie. "0pcl-" */
	char eofd2;		/* End Of Field is: LF */
	char priority;		/* Priority of story ie. 
				   'r' = regular
				   'b' = bulletin */
	char eofd3;		/* End Of Field is: SP */
	char cat;		/* CATegory of story i.e., 'n' */
	char format[2];		/* FORMAT identifier ie: DC3, DC1 */
	char eofd4;		/* End Of Field is: SP */
	char keyword[25];	/* Keyword i.e., "AP-HI--Asian/PacificNews" */
				/* varible 0-24 char string with NUL term */
	char eofd5;		/* End Of Field is: SP */
	char vers[40];		/* VERSion i.e., "take3" */
				/* varible 0-infinit char string */
	char eofd6;		/* End Of Field is: SP */
	char ref[40];		/* REFerence i.e., "2ndLd-Writethru" */
				/* varible 0-infinit char string */
	char eofd7;		/* End Of Field is: SP */
	char date[5];		/* AP's DATE field i.e.; "08-18" NUL term */
	char eofd8;		/* End Of Field is: SP */
	char wordcnt[5];	/* WORD CouNT i.e.; "0340" NUL term */
	char eofd9[2];		/* End Of Field is: CR, LF */
	char subject[80];	/* This is a more verbose keyword string that
				   AP sticks in the body. A varible 0-infinit 
				   char string */
} hdr;

#endif /* !_ANPA_H_ */

