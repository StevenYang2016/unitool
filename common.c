#include "common.h"
#include "stdio.h"
#include <fcntl.h>
#include <stdlib.h>

int readfile(finfo *mfinfo){
	
	int fd;
	struct stat stat_t;
	fd = open(mfinfo->name, O_RDONLY);
    	if (fd < 0) {
        	printf("Open %s failed \n", mfinfo->name);
        	return 1;
    	}

    	if (fstat(fd, &stat_t) < 0) {
       		printf("Get info about %s failed\n", mfinfo->name);
        	close(fd);
        	return 1;
    	}

    	mfinfo->data =(char *) malloc(stat_t.st_size);
   	if (mfinfo->data == NULL) {
        	printf("Allocating data for %s failed\n", mfinfo->name);
        	close(fd);
        	return 1;
    	}
   	 mfinfo->size = stat_t.st_size;

    	if (read(fd, mfinfo->data, mfinfo->size) < 0) {
        	printf(" Read  %s failed \n", mfinfo->name);
		free(mfinfo->data);
        	close(fd);
		return 1;
	}
	close(fd);

	return 0;
}
int writefile(finfo *mfinfo,char *buffer,int size){
	
	int fd,rc;
	fd = open(mfinfo->name, O_RDWR|O_CREAT|O_TRUNC);
    	if (fd < 0) {
        	printf("Error opening %s\n", mfinfo->name);
        	return 1;
    	}

	rc = write(fd, &buffer[0], size);
	if (rc == 0) {
		printf("Error writing to %s\n",mfinfo->name);
		//free(buffer);
		return 1;
	}
	close(fd);

}

int cleanfile(finfo *mfinfo){

	if(mfinfo->data!=NULL){
       	
		free(mfinfo->data);
	}

	if(mfinfo->data!=NULL)
		return 1;
	else
		return 0;
}
