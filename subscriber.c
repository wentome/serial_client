#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	if(rc){
		exit(1);
	}else{
		mosquitto_subscribe(mosq, NULL, "samples/topic01", 0);
	}
}
void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos) {
	printf("subscribe successed\n");
}
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg){
	printf("%s\n", (char *)msg->payload);
	//exit(0);
}
int main(int argc, char *argv[]) {
	int rc;
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
	}
	mosquitto_lib_cleanup();
	return 1;
}
