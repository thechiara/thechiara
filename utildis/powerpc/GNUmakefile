CC=clang 
LD=ld
INCLUDEDIR:= include

CCOPTAFT =     -std=gnu99  -g  -Wall  -c  


SOURCES := ppc-opc.c
OBJECTS := $(SOURCES:.c=.o)
OBJECTSD := $(SOURCES:.c=.d)




.PHONY: all   clean 



all : chiarav


%.o: %.c
			
			clang  $<   -c -MD -o $@  $(CCOPTAFT)

			


chiarav: $(OBJECTS)
				clang -o chiara-ppc $(OBJECTS) 
				

clean: cleanf



cleanf: $(OBJECTS)
			rm -rf  chiara-ppc
			rm -rf  $(OBJECTS)
			rm -rf  $(OBJECTSD)
