CFLAGS = -Wall -g
OBJS = access.o audiotreat.o commandtreat.o wavinfo.o wavrev.o wavvol.o wavautovol.o wavecho.o wavwide.o wavcat.o wavmix.o

all:	wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix

wavinfo:	wavinfo.o access.o audiotreat.o commandtreat.o
wavrev:		wavrev.o access.o audiotreat.o commandtreat.o
wavvol:		wavvol.o access.o audiotreat.o commandtreat.o
wavautovol:	wavautovol.o access.o audiotreat.o commandtreat.o
wavecho:	wavecho.o access.o audiotreat.o commandtreat.o
wavwide:	wavwide.o access.o audiotreat.o commandtreat.o
wavcat:		wavcat.o access.o audiotreat.o commandtreat.o
wavmix:		wavmix.o access.o audiotreat.o commandtreat.o

access.o:		access.c access.h common.h
audiotreat.o:	audiotreat.c audiotreat.h common.h access.h
commandtreat.o:	commandtreat.c commandtreat.h common.h

wavinfo.o:		wavinfo.c access.h audiotreat.h commandtreat.h common.h
wavrev.o:		wavrev.c access.h audiotreat.h commandtreat.h common.h
wavvol.o:		wavvol.c access.h audiotreat.h commandtreat.h common.h
wavautovol.o:	wavautovol.c access.h audiotreat.h commandtreat.h common.h
wavecho.o:		wavecho.c access.h audiotreat.h commandtreat.h common.h
wavwide.o:		wavwide.c access.h audiotreat.h commandtreat.h common.h
wavcat.o:		wavcat.c access.h audiotreat.h commandtreat.h common.h
wavmix.o:		wavmix.c access.h audiotreat.h commandtreat.h common.h

clean:
	-rm $(OBJS)