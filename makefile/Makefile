TARGET=main
CC=g++
RM=rm
CFLAGS=-g
SRC=$(wildcard *.c) $(wildcard *.cpp)
#OBJ=$(SRC:.c=.o)
OBJ=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRC)))
DEP=$(patsubst %.c,%.d,$(SRC))

all:$(TARGET)
$(TARGET): $(OBJ)
	$(CC) $^ -o $@

$(DEP):%.d:%.c
	set -e;\
	rm -f $@;\
	$(CC) -MM $< > $@.;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@. > $@;\
	rm -f $@.

-include $(DEP)
.PHONY: clean
clean:
	$(RM) -f $(TARGET) $(DEP) $(OBJ) $@.


#debug
echo:
	@echo src=$(SRC)
	@echo obj=$(OBJ)
	@echo dep=$(DEP)
	@echo cflags=$(CFLAGS)
