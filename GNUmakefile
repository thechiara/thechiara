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

			gcc  $<   -c -MD -o $@  $(CCOPTAFT) 
			


chiarav: $(OBJECTS)
				 $(MAKE) -C utildis/powerpc

				gcc -o chiarav $(OBJECTS) -pthread  utildis/powerpc/chiara-ppc.o
				

clean: cleanf



cleanf: $(OBJECTS)
							 
			$(MAKE) -C utildis/powerpc clean

			rm -rf  chiarav
			rm -rf  $(OBJECTS)
			rm -rf  $(OBJECTSD)
