CC=clang 
LD=ld
INCLUDEDIR:= include

CCOPTAFT =     -std=gnu99  -g  -Wall  -c  -I$(INCLUDEDIR) 


SOURCES := main.c utildis/powerpc/chiara-ppc.c utildis/elf/elf-parser.c utildis/alphadec/alphadec.c  utildis/riscv/riscv.c utildis/i386/i386-opc.c utildis/pe32/chiara-exe.c

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
							 
			

			rm -rf  thechiara
			rm -rf  $(OBJECTS)
			rm -rf  $(OBJECTSD)

install: installf



installf: $(OBJECTS)
							 
			

			install thechiara /usr/bin/thechiara
