#define CONVERT_F 1
#define CAT_F     2
typedef struct{

	char *name;
	char *data;
	int *size;
} finfo;

int readfile(finfo *mfinfo); 
int cleanfile(finfo *mfinfo);