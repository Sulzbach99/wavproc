all: wavautovol.c common.h access.c access.h commandtreat.c commandtreat.h audiotreat.c audiotreat.h
	gcc -Wall wavautovol.c access.c commandtreat.c audiotreat.c -o wavautovol -g