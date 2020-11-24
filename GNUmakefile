CC=clang 
LD=ld
INCLUDEDIR:= include

CCOPTAFT =     -std=gnu99  -g  -Wall  -c  -I$(INCLUDEDIR) 


SOURCES := main.c utildis/powerpc/chiara-ppc.c utildis/elf/elf-parser.c utildis/alphadec/alphadec.c
OBJECTS := $(SOURCES:.c=.o)
OBJECTSD := $(SOURCES:.c=.d)




.PHONY: all   clean 



all : chiarav 


%.o: %.c

			gcc  $<   -c -MD -o $@  $(CCOPTAFT) 
			


chiarav: $(OBJECTS)
				 

				gcc -o thechiara $(OBJECTS) -pthread 
				

clean: cleanf



cleanf: $(OBJECTS)
							 
			

			rm -rf  chiarav
			rm -rf  $(OBJECTS)
			rm -rf  $(OBJECTSD)
