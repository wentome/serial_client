#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <serial.h>
int fd=0;
int send_mid=1;
char read_buf[256];
int cnt;
void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	if(rc){
		exit(1);
	}else{
		printf("connect successed\n");
		mosquitto_subscribe(mosq, NULL, "serial/input01", 0);
	}
}
void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos) {
	printf("subscribe successed\n");
	fd=serial_init("/dev/ttyUSB0",9600);
}
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg){
	write(fd,msg->payload,msg->payloadlen);
}

int main(int argc, char *argv[]) {
	int rc;
	char read_buf[256];
	struct mosquitto *mosq;
	mosquitto_lib_init();
	mosq = mosquitto_new("publish-qos1-test", true, NULL);
	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_subscribe_callback_set(mosq, on_subscribe);
	mosquitto_message_callback_set(mosq, on_message);
	mosquitto_message_retry_set(mosq, 3);
	rc = mosquitto_connect(mosq, "181.215.100.177", 1883, 60);
	while(1){
		mosquitto_loop(mosq, 300, 1);
		if(fd!=0){
		    cnt=read(fd,read_buf,10);
      		    if(cnt>0){
		        printf("serial get data\n");
		        mosquitto_publish(mosq, &send_mid, "serial/output01", cnt, read_buf, 0, false);
		    }
		}
	}
	mosquitto_lib_cleanup();
        serial_close(fd);
	return 1;
}
