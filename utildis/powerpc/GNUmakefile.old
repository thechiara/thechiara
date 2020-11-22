CC=clang 
LD=ld
INCLUDEDIR:= include

CCOPTAFT =     -std=gnu99  -g  -Wall  -c  


SOURCES := chiara-ppc.c
OBJECTS := $(SOURCES:.c=.o)
OBJECTSD := $(SOURCES:.c=.d)




.PHONY: all   clean 



all : chiarav


%.o: %.c
			
			clang  $<   -c -MD -o $@  $(CCOPTAFT)

			


chiarav: $(OBJECTS)
			echo end of ppc module compilation
				

clean: cleanf



cleanf: $(OBJECTS)
			
			rm -rf  $(OBJECTS)
			rm -rf  $(OBJECTSD)
