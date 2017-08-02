#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"

void using(char *prog){
	
    	printf("   -f function to be chosen\n");
	printf("	type 1 : convert HEX data content to binary data content both in plain text format\n");
	printf("	Using: %s -f 1 -i <input filename> -o <output filename>\n", prog);
        printf("        type 2 : convert HEX data content in plain text format to binary format\n");
	printf("	Using: %s -f 2 -i <input filename> -o <output filename>\n", prog);
	printf("        type 3 : convert binary format data to HEX content in plain text format\n");
	printf("	Using: %s -f 3 -i <input filename> -o <output filename>\n", prog);
	printf("        type 4 : merge two files together\n");
	printf("	Using: %s -f 4 -i <input filename1> -j <input filename2> -o <output filename>\n", prog);
        printf("        type 5 : padding the file to the designated address\n");
	printf("	Using: %s -f 5 -i <input filename> -d <address>\n", prog);

}

int main(int argc, char *argv[])
{
//	int  function=0;
	int fun; 
	char *inputfile = NULL;
    	char *outputfile = NULL;
	char *sec_inputfile=NULL;
	int padaddr,opt;
    	while (1) {
        	opt = getopt(argc, argv, "f:i:o:j:d:");
        	if (opt == -1) {
            		break;
        	}

        	switch(opt) {
        		case 'd':
            			padaddr= atoi(optarg);
            		break;
			case 'f':
            			fun   = atoi(optarg);
            		break;
        		case 'i':
            			inputfile  = optarg;
            		break;
        		case 'j':
            			sec_inputfile = optarg;
            		break;
        		case 'o':
            			outputfile = optarg;
            		break;
    		}
	}
    	if ( inputfile== NULL) {
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
		case 4:
			merge(inputfile,sec_inputfile,outputfile);
		break;
		case 5:
			padding(inputfile,padaddr);
		break;
	}

    	return 0;
}
