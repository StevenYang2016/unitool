
#ifndef	COMMON_H
#define	COMMON_H

#define CONVERT_F 1
#define CAT_F     2
typedef struct{

	char *name;
	char *data;
	int size;
} finfo;

int readfile(finfo *mfinfo); 
int writefile(finfo *mfinfo,char *buffer,int size); 
int cleanfile(finfo *mfinfo);

#endif
