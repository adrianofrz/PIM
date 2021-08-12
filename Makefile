# Referencia
# https://terminalroot.com.br/2019/12/como-criar-um-makefile.html
TARGET=pim.out
CC=gcc
#DEBUG=-g
OPT=-O0 -fPIE
#WARN=-Wall
#PTHREAD=-pthread
CCFLAGS= $(OPT)
LD=gcc
#LDFLAGS=$(PTHREAD) -export-dynamic
OBJDIR=/files/obj
OBJS= principal.o controle_sala.o controle_data.o controle_caixa.o utils.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS)
 
principal.o: src/principal.c
	$(CC) -c $(CCFLAGS) src/principal.c -o principal.o
 
controle_sala.o: src/controle_sala.c
	$(CC) -c $(CCFLAGS) src/controle_sala.c  -o controle_sala.o

controle_data.o: src/controle_data.c
	$(CC) -c $(CCFLAGS) src/controle_data.c  -o controle_data.o

controle_caixa.o: src/controle_caixa.c
	$(CC) -c $(CCFLAGS) src/controle_caixa.c  -o controle_caixa.o 

utils.o: src/utils.c
	$(CC) -c $(CCFLAGS) src/utils.c  -o utils.o 

clean:
	rm -f *.o