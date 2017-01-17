
/* 
 * setserial()
 *
 * Set the line attributes to the serial port we are reading the wire
 * from. Should be called after we opened the input file.
 *
 * Copywrite 1994 Timothy Pozar
 *
 */

#include "anpa.h"

setserial()
{
int fd;
struct termios tp;

       if(debug_level > 8)
                printf("Setting the Serial Port %s\n",fd);

/*
	if ((fd = open(dev, O_RDWR | O_NDELAY)) < 0) {
		perror(dev);
		exit(1);
	}
*/
	fd = fileno(fspi);

	if (tcgetattr (fd, &tp) < 0) {
		perror("setserial()"); /* Not a serial device */
		return(1);
	};
	cfmakeraw(&tp);

/*	tp.c_cflag |= CS8 | CLOCAL | CREAD | HUPCL | CRTSCTS;  */
	tp.c_cflag |= CS8 | CLOCAL | CREAD; 
	cfsetspeed(&tp, SPEED);

	if (tcsetattr (fd,TCSADRAIN, &tp) < 0) {
		perror("setserial()");
		fin(1);
	};
	return(fd);

} /* EOF setserial.c */
