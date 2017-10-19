#Lucas Sulzbach
#GRR20171595

# Variáveis:
CC =			gcc
CFLAGS =		-Wall
OBJS =			access.o audiotreat.o commandtreat.o
HEADS =			common.h access.h audiotreat.h commandtreat.h

# Todos os targets a serem montados:
all:			wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix

# Targets e suas respectivas regras de ligação:
wavinfo:		wavinfo.o $(OBJS)
wavrev:			wavrev.o $(OBJS)
wavvol:			wavvol.o $(OBJS)
wavautovol:		wavautovol.o $(OBJS)
wavecho:		wavecho.o $(OBJS)
wavwide:		wavwide.o $(OBJS)
wavcat:			wavcat.o $(OBJS)
wavmix:			wavmix.o $(OBJS)

# Regras de compilação dos 'OBJS':
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
				-rm access.o audiotreat.o commandtreat.o wavinfo.o wavrev.o wavvol.o wavautovol.o wavecho.o wavwide.o wavcat.o wavmix.o

# Remove todos os binários:
purge:			clean
				-rm wavinfo wavrev wavvol wavautovol wavecho wavwide wavcat wavmix