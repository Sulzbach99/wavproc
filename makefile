all: wavinfo.c common.h access.c access.h commandtreat.c commandtreat.h
	gcc -Wall wavinfo.c access.c commandtreat.c -o wavinfo -g