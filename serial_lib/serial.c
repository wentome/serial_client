#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include "serial.h"

int serial_init(char *dev,int baudrate )
{
    int fd,c, res;
    struct termios oldtio,newtio;
    char buf[255];
    if( (fd = open(dev, O_RDWR | O_NOCTTY ))<0){
        perror("open serial failed");
        exit(1);
    }

    //tcgetattr(fd,&oldtio); /* save current serial port settings */
        //tcgetattr(fd,&newtio);//CP
    //bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

         //newtio.c_iflag = IGNPAR | ICRNL;
         //newtio.c_iflag &= ~(IXOFF);// turn off IXOFF

         //--Configure termios, actually, the key parmat is baudrate--
    newtio.c_iflag &= ~(INLCR| ICRNL |IGNCR );//
    newtio.c_oflag &=~OPOST;
         //newtio.c_oflag |=(OPOST );
    newtio.c_cflag = baudrate | CS8 | CLOCAL | CREAD;
    newtio.c_lflag &=~(ICANON |ECHO| ECHOE | ISIG) ; //CP



    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
    return fd;
    }


void serial_close(int serial_fd)
{
    close(serial_fd);

}

