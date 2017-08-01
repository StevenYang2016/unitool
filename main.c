#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"

void using(char *prog){
	
	printf("Using: %s <options> -i <input filename> -o <output filename>\n", prog);
    	printf("   -f function to be chosen\n");
	printf("	type 1 : convert HEX data content to binary data content both in plain text format\n");
        printf("        type 2 : convert HEX data content in plain text format to binary format\n");
	printf("        type 3 : convert binary format data to HEX content in plain text format\n");
    	printf("   -i file to input\n");
    	printf("   -o file to output\n");
}

int main(int argc, char *argv[])
{
//	int  function=0;
	int fun; 
	char *inputfile = NULL;
    	char *outputfile = NULL;
	int opt;
    	while (1) {
        	opt = getopt(argc, argv, "f:i:o:");
        	if (opt == -1) {
            		break;
        	}

        	switch(opt) {
        		case 'f':
            			fun   = atoi(optarg);
            		break;
        		case 'i':
            			inputfile  = optarg;
            		break;
        		case 'o':
            			outputfile = optarg;
            		break;
    		}
	}
    	if ( (inputfile== NULL) || (outputfile==NULL)) {
        	using(argv[0]);
        	return 1;
    	}
	switch(fun){
 		case 1:
			convert_txt(inputfile,outputfile);
		break;
		case 2:
			convert_txttobin(inputfile,outputfile);
		break;
		case 3:
			convert_bintotxt(inputfile,outputfile);
		break;
	}

    	return 0;
}
