#include "common.h"
#include "stdio.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

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

int merge(char *firstfile,char *secondfile,char *ofile){

	finfo first;
	finfo second;
	finfo output;
	int size=0,cur=0;	

	first.name=firstfile;
	second.name=secondfile;
	output.name=ofile;
	char *buffer;
	readfile(&first);
	readfile(&second);
	size=first.size+second.size;
	buffer=(char *)malloc(size);
	if(buffer==NULL){
		return 1;
	}
	memcpy(&buffer[cur],first.data,first.size);
	cur+=first.size;
	memcpy(&buffer[cur],second.data,second.size);
	if(writefile(&output,buffer,size)!=0){
		printf("writefile error \n");
		return 1;
	}	
	return 0;
}

int padding(char *srcfile,int addr){
        finfo src;
        int cur=0;

        src.name=srcfile;
        char *buffer;
        readfile(&src);
	if(src.size>addr){
		printf("Padding address error\n");
		return 1;
	}
        buffer=(char *)malloc(addr);
        if(buffer==NULL){
                return 1;
        }
        memcpy(&buffer[cur],src.data,src.size);
        cur+=src.size;
        memset(&buffer[cur],0xff,addr-src.size);
        if(writefile(&src,buffer,addr)!=0){
                printf("writefile error \n");
                return 1;
        }
        return 0;
}
