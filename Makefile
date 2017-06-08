
.PHONY:client 
 
CLIENT_CFLAGS=-I./lib -I./serial_lib 
CLIENT_LDFLAGS=./lib/libmosquitto.so.1 ./serial_lib/libserial.so.1

client:client.c
	gcc $(CLIENT_CFLAGS) $< $(CLIENT_LDFLAGS) -o $@ 
