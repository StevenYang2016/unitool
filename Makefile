
unitool:main.o common.o convert.o 
	cc -o unitool main.o common.o convert.o
main.o:main.c main.h
	cc -c main.c
common.o:common.c common.h
	cc -c common.c
convert.o:convert.c convert.h
	cc -c convert.c


clean:
	rm unitool *.o
