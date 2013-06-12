
#include <stdio.h>
#include <string.h>
#include "utils_sockets.h"
#include "fcfutils.h"
#include "fcfmain.h"

#define LISTEN_PORT 36000
#define DEVICE_NAME "virt_ADIS"
#define ADIS_IP "192.168.0.196"
#define ADIS_PORT "35002"

static unsigned char buffer[1000];


static void common_cb(const char * src, int fd){
	int rc = readsocket(fd, buffer, sizeof(buffer));
	if (rc > 0){
		sendADISData(buffer, rc);
	}
}

//active fd
static void virtADIS_cb(struct pollfd *pfd){
	common_cb(DEVICE_NAME, pfd->fd);
}

int adis_init(){
	int fd = getsocket(ADIS_IP, ADIS_PORT, LISTEN_PORT);
	int rc = fcf_add_fd(fd, POLLIN, virtADIS_cb);
	return rc;
}

void adis_final(){
}

