CC=clang 
LD=ld
INCLUDEDIR:= include

CCOPTAFT =     -std=gnu99  -g  -Wall  -c  -I$(INCLUDEDIR) 


SOURCES := main.c
OBJECTS := $(SOURCES:.c=.o)
OBJECTSD := $(SOURCES:.c=.d)




.PHONY: all   clean 



all : chiarav 


%.o: %.c

			clang  $<   -c -MD -o $@  $(CCOPTAFT) 
			


chiarav: $(OBJECTS)
				 $(MAKE) -C utildis/powerpc

				clang -o chiarav $(OBJECTS) -pthread  utilsdis/powerpc/chiara-ppc
				

clean: cleanf



cleanf: $(OBJECTS)
							 
			$(MAKE) -C utildis/powerpc clean

			rm -rf  chiarav
			rm -rf  $(OBJECTS)
			rm -rf  $(OBJECTSD)
