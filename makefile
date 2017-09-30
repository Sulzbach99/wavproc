all: wavvol.c common.h access.c access.h commandtreat.c commandtreat.h audiotreat.c audiotreat.h
	gcc -Wall wavvol.c access.c commandtreat.c audiotreat.c -o wavvol -g