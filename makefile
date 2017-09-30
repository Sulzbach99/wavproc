all: wavinfo wavrev wavvol wavautovol wavwide

wavinfo: wavinfo.c common.h access.c access.h commandtreat.c commandtreat.h
	gcc -Wall wavinfo.c access.c commandtreat.c -o wavinfo -g

wavrev: wavrev.c common.h access.c access.h commandtreat.c commandtreat.h audiotreat.c audiotreat.h
	gcc -Wall wavrev.c access.c commandtreat.c audiotreat.c -o wavrev -g

wavvol: wavvol.c common.h access.c access.h commandtreat.c commandtreat.h audiotreat.c audiotreat.h
	gcc -Wall wavvol.c access.c commandtreat.c audiotreat.c -o wavvol -g

wavautovol: wavautovol.c common.h access.c access.h commandtreat.c commandtreat.h audiotreat.c audiotreat.h
	gcc -Wall wavautovol.c access.c commandtreat.c audiotreat.c -o wavautovol -g

wavwide: wavwide.c common.h access.c access.h commandtreat.c commandtreat.h audiotreat.c audiotreat.h
	gcc -Wall wavwide.c access.c commandtreat.c audiotreat.c -o wavwide -g