#include "common.h"
#include "stdio.h"
#include "fcntl.h"
#include "stdlib.h"

int convert_txt(char *srcfile,char *destfile){

	finfo src;
	finfo dest;
	int size = 0, i = 0, rc;
	char *buffer;
	int fd=0;
	src.name = srcfile;
	dest.name = destfile;
	readfile(&src);
	size = src.size;
	size=size-1;
	buffer = (char*)malloc(4 * size);
	for (i = 0; i < size; i++) {
		if (('0' <= src.data[i])&& (src.data[i] <= '9')) {
			buffer[4 * i+3] = ((src.data[i] - '0') & 0x1)+'0';
			buffer[4 * i+2] = (((src.data[i] - '0')>>1 )& 0x1) + '0';
			buffer[4 * i+1] = (((src.data[i] - '0')>>2) & 0x1) + '0';
			buffer[4 * i ] = (((src.data[i] - '0')>>3) & 0x1) + '0';
		}
		else if (('a' <= src.data[i])&&(src.data[i] <= 'f')) {
			buffer[4 * i+3] = ((src.data[i] - 'a'+10) & 0x1) + '0';
			buffer[4 * i+2] = (((src.data[i] - 'a' + 10) >> 1) & 0x1) + '0';
			buffer[4 * i+1] = (((src.data[i] - 'a' + 10) >> 2) & 0x1) + '0';
			buffer[4 * i ] = (((src.data[i] - 'a' + 10) >> 3) & 0x1) + '0';
		}
		else if (('A' <= src.data[i])&&(src.data[i]<= 'F')) {
			buffer[4 * i+3] = ((src.data[i] - 'A' + 10) & 0x1) + '0';
			buffer[4 * i+2] = (((src.data[i] - 'A' + 10) >> 1) & 0x1) + '0';
			buffer[4 * i+1] = (((src.data[i] - 'A' + 10) >> 2) & 0x1) + '0';
			buffer[4 * i] = (((src.data[i] - 'A' + 10) >> 3) & 0x1) + '0';
		}
		else {
			free(buffer);
			return 1;
		}

	}
	fd = open(dest.name, O_RDWR|O_CREAT|O_TRUNC);
    	if (fd < 0) {
        	printf("Error opening %s\n", dest.name);
        	return 1;
    	}

	rc = write(fd, &buffer[0], 4*size);
	if (rc == 0) {
		printf("Error writing to %s\n", dest.name);
		free(buffer);
		return 1;
	}
	close(fd);
	free(buffer);

	return 0;
}
int convert_txttobin(char *srcfile,char *destfile){

	finfo src;
	finfo dest;
	int size = 0, i = 0, rc;
	char *buffer;
	int fd=0,num=0,offset=0;
	src.name = srcfile;
	dest.name = destfile;
	readfile(&src);
	size = src.size;
	num=size/2;
	buffer = (char*)malloc(num);
	memset(buffer,0x00,num);
	for (i = 0; i < size-1; i++) {
		offset=((i+1)%2)*4;
		if (('0' <= src.data[i])&& (src.data[i] <= '9')) {
			buffer[i/2] = ((src.data[i] - '0')<<offset)+buffer[i/2];
		}
		else if (('a' <= src.data[i])&&(src.data[i] <= 'f')) {
			buffer[i/2] = (((src.data[i] - 'a')+10)<<offset)+buffer[i/2];
		}
		else if (('A' <= src.data[i])&&(src.data[i]<= 'F')) {
			buffer[i/2] = (((src.data[i] - 'A')+10)<<offset)+buffer[i/2];
		}
		else {
			free(buffer);
			return 1;
		}

	}
	fd = open(dest.name, O_RDWR|O_CREAT|O_TRUNC);
    	if (fd < 0) {
        	printf("Error opening %s\n", dest.name);
        	return 1;
    	}

	rc = write(fd, &buffer[0],num);
	if (rc == 0) {
		printf("Error writing to %s\n", dest.name);
		free(buffer);
		return 1;
	}
	close(fd);
	free(buffer);

	return 0;
}
int convert_bintotxt(char *srcfile,char *destfile){

	finfo src;
	finfo dest;
	int size = 0, i = 0, rc;
	char *buffer;
	int fd=0,hb=0,lb=0,offset=0;
	src.name = srcfile;
	dest.name = destfile;
	readfile(&src);
	size = src.size;
	size=size;
	buffer = (char*)malloc(size*2);
	for (i = 0; i < size; i++) {
		lb=src.data[i]&0x0f;
		hb=(src.data[i]&0xf0)>>4;
		if ((0<= hb)&& (hb<=9)) {
			buffer[2*i] = hb+'0';
		}
		else if ((10<= hb)&& (hb<=15)) {
			buffer[2*i] =  hb-10+'A';
		}
		else {
			free(buffer);
			return 1;
		}
		if ((0<= lb)&& (lb<=9)) {
			buffer[2*i+1] = lb+'0';
		}
		else if ((10<= lb)&& (lb<=15)) {
			buffer[2*i+1] =  lb-10+'A';
		}
		else {
			free(buffer);
			return 1;
		}

	}
	fd = open(dest.name, O_RDWR|O_CREAT|O_TRUNC);
    	if (fd < 0) {
        	printf("Error opening %s\n", dest.name);
        	return 1;
    	}

	rc = write(fd, &buffer[0],size*2);
	if (rc == 0) {
		printf("Error writing to %s\n", dest.name);
		free(buffer);
		return 1;
	}
	close(fd);
	free(buffer);

	return 0;
}
