#include<stdio.h>
#include<serial.h>
int main()
{
    int fd;
    printf("serial main\n");
    fd=serial_init("/dev/ttyUSB0",9600);
    write(fd,"hello\n",7);
    read(fd,)
    serial_close(fd);
    printf("end\n");
    return 0;
}
