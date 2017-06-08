.PHONY:  clean


SERIAL_CFLAGS:=-I. 
libserial.so.1:serial.o
	gcc -shared  $^ -o $@ 

serial.o:serial.c 
	gcc $(SERIAL_CFLAGS) -c $< -o $@


clean:
	rm *.o  *so.1 
