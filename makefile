# Variáveis:
CFLAGS =		-Wall -g
COMMON_OBJS =	access.o audiotreat.o commandtreat.o
OBJS =			access.o audiotreat.o commandtreat.o wavinfo.o wavrev.o wavvol.o wavautovol.o wavecho.o wavwide.o wavcat.o wavmix.o
HEADS =			common.h access.h audiotreat.h commandtreat.h

# Todos os targets a serem montados:
all:			wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix clean

# Targets e suas respectivas regras de ligação:
wavinfo:		wavinfo.o $(COMMON_OBJS)
wavrev:			wavrev.o $(COMMON_OBJS)
wavvol:			wavvol.o $(COMMON_OBJS)
wavautovol:		wavautovol.o $(COMMON_OBJS)
wavecho:		wavecho.o $(COMMON_OBJS)
wavwide:		wavwide.o $(COMMON_OBJS)
wavcat:			wavcat.o $(COMMON_OBJS)
wavmix:			wavmix.o $(COMMON_OBJS)

# Regras de compilação dos 'COMMON_OBJS':
access.o:		access.c access.h common.h
audiotreat.o:	audiotreat.c audiotreat.h common.h access.h
commandtreat.o:	commandtreat.c commandtreat.h common.h

# Regras de compilação dos demais objetos:
wavinfo.o:		wavinfo.c $(HEADS)
wavrev.o:		wavrev.c $(HEADS)
wavvol.o:		wavvol.c $(HEADS)
wavautovol.o:	wavautovol.c $(HEADS)
wavecho.o:		wavecho.c $(HEADS)
wavwide.o:		wavwide.c $(HEADS)
wavcat.o:		wavcat.c $(HEADS)
wavmix.o:		wavmix.c $(HEADS)

# Remove todos os objetos:
clean:
				-rm $(OBJS)

# Remove todos os binários:
purge: clean
				-rm wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix