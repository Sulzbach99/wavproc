all: wavrev.c common.h access.c access.h commandtreat.c commandtreat.h audiotreat.c audiotreat.h
	gcc -Wall wavrev.c access.c commandtreat.c audiotreat.c -o wavrev -g