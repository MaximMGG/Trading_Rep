CC = gcc
BINARY = trada
SRC_DIR = trader/src/ dc/src/ lib/ manager/src/ service/src/
SRC = $(foreach I, $(SRC_DIR), $(wildcard $(I)*.c))
OBJ = $(patsubst %.c, %.o, $(SRC))
LIBS = -l_util -lcurl -lpq


all: $(BINARY)

$(BINARY): $(OBJ)
	$(CC) -o $(BINARY) $^ $(LIBS)

%.o:%.c
	$(CC) -c -o $@ $<

clean:
	rm $(BINARY) $(OBJ)

a.out:
	gcc lib/m_string.c lib/m_list.c dc/src/datacenter.c dc/src/dbinsert.c     \
		manager/src/app.c service/src/getservice.c  service/src/logicservice.c\
		trader/src/trader.c													  \
		-l_util -lcurl -lpq -g
