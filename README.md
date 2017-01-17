ANPA is a utility takes a wire service feed that conforms to the ANPA-RI (American Newspaper Publishers Association*) Bulletin 1312 specification from a tty or file and outputs a RFC-822 (mail.local or rmail) compliment file that can be injected into some data stream like USENET or Internet mail.

Files include:

Makefile		The Makefile (BSD style)

README			This file you are looking at right now

action.c		What todo when an article that matches comes in.

anpa.1			Main man page

anpa.ctl		Sample control file (AP)

anpa.ctl.5		Man page for control file

anpa.h			Header for source

baycity.ctl		Sample control file (Bay City News)

getheader.c		Gets ANPA headers

main.c			Starting point for program

parsectl.c		Parse the control file

printbody.c		Print the body of the article

printheader.c		Pritn the header of the article

rc.local.sample		Sample start up line for BSD's rc.local

readf.c			Read a char in

readrec.c		Read a line in.

selector.c		Match articles to what the control file defines

setserial.c		Sets the serial port parameters

testfile.ap		Sample ANPA wire copy from AP

testfile.baycity	Sample ANPA wire copy from Bay City News

cgi-bin/ap		Sample perl cgi-bin for parsing the program's output (mail.local) file
