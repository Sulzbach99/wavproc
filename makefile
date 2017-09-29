all: wavrev.c common.h access.c access.h commandtreat.c commandtreat.h
	gcc -Wall wavrev.c access.c commandtreat.c -o wavrev -g