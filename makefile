all: wavvol.c common.h access.c access.h commandtreat.c commandtreat.h
	gcc -Wall wavvol.c access.c commandtreat.c -o wavvol -g