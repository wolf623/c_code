TARGET=main
CC=g++
RM=rm
CFLAGS=-g
SRC=$(wildcard *.c) $(wildcard *.cpp)
#OBJ=$(SRC:.c=.o)
OBJ=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRC)))
#DEP=$(patsubst %.o,%.d,$(OBJ))
DEP=$(OBJ:.o=.d)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

define gen_dep
set -e;\
rm -f $@;\
$(CC) -MM $< > $@.;\
sed 's/\($*\)\.o[ :]*/\1.o $@:/g' < $@. > $@;\
rm -f $@.
endef

%.d:%.c
	$(gen_dep)

%.d:%.cpp
	$(gen_dep)

-include $(DEP)
.PHONY: clean
clean:
	$(RM) -f $(TARGET) $(OBJ) $(DEP) $@.

#debug
echo:
	@echo src=$(SRC)
	@echo obj=$(OBJ)
	@echo dep=$(DEP)
	@echo cflags=$(CFLAGS)
