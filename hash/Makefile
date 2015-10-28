#makefile

CC = gcc
#source_file := $(wildcard *.c)
hash = hash
objects := $(patsubst %.c,%.o,$(wildcard *.c))
hash_objects := $(patsubst %.c,%.o,$(wildcard $(hash)/*.c))
#executables := $(patsubst %.c,%,$(wildcard *.c))

target := hashtest
#gcc -c $< -o $@

CFGFLAG += -lpthread

all: $(target) 
$(target): $(objects) $(hash_objects)
	gcc $^ -o $@ $(CFGFLAG)
	#gcc $^ -o $@ $(CFGFLAG)

clean:
	rm -f *.o 
	rm -rf $(target)

.PHONY: clean
