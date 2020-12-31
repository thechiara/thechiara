/*
Copyright (C) 2020 Elliot-Gaspard COURCHINOUX
*    This program  is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING3. If not,
   see <http://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <chiara-elf.h>
#include <chiaracompute.h>
#include <chiaracore.h>


#define CHIARA_EXTRACT_ELF 1<<1
#define CHIARA_EXTRACT_PE 1<<2
#define CHIARA_EXTRACT_ISO 1<<3
#define CHIARA_EXTRACT_RAWX86 1<<4
#define CHIARA_EXTRACT_RAWRISCV 1<<5


struct thechiaradecrypt{
int file;
unsigned long long arguments;
	void (*call)(char*,int);
	}decrypt;
	
static void chiara_parse_argv_iso(int argn,const char *argv[]) {
int status  = 1;

decrypt.arguments = CHIARA_EXTRACT_ISO;

if(2+status != argn) {
	

int end = lseek(decrypt.file,0,SEEK_END );
	
	lseek(decrypt.file,0,SEEK_SET  ); 
	
unsigned  char  *gaspard = malloc(end);	
	
int size = 	read(decrypt.file,gaspard,end);
close(decrypt.file);
printf("Now call the iso module \n");
chiara_init_iso(gaspard,end,argv[3]);	
	} else {
	printf("You don't provide the iso filename or the target architecture \n ");	
	printf("thechiara : fatal error \n ");	
		exit(1);
	}

}
static void chiara_call_function() {
	

int end = lseek(decrypt.file,0,SEEK_END );
	
	lseek(decrypt.file,0,SEEK_SET  ); 
	
unsigned  char  *gaspard = malloc(end);	
	
int size = 	read(decrypt.file,gaspard,end);
close(decrypt.file);

decrypt.call(gaspard,end);	

}
	
static void chiara_decrypt_arguments(int argn,const char *argv[]) {
	
int status = 0;

while(status!= argn) {
printf("argv : %s argv num %d  \n",argv[status],argn);
if(strcmp(argv[status],"-elf") == 0) {
	status++;
	decrypt.arguments |=  CHIARA_EXTRACT_ELF;
	if(status != argn) {
		printf("We will decrypt elf : %s \n",argv[status]);
		decrypt.file  = open(argv[status],O_RDONLY);
		decrypt.call = chiara_extract_elf;

		} else {
		printf("You don't provide an elf file STOP\n");	
			exit(1);
		}
}	else if (strcmp(argv[status],"-exe") == 0) {
	status++;
	decrypt.arguments |=  CHIARA_EXTRACT_RAWX86;
	if(status != argn) {
		printf("We will decrypt exe  : %s \n",argv[status]);
		decrypt.file  = open(argv[status],O_RDONLY);
		decrypt.call = chiara_dos_header_look;
		} else {
		printf("You don't provide an exe file thechiara STOP\n");	
			exit(1);
		}	
	
} else if (strcmp(argv[status],"-rawx86") == 0) {
	
status++;
	decrypt.arguments |=  CHIARA_EXTRACT_RAWX86;
	if(status != argn) {
		printf("We will decrypt raw x86 file  : %s \n",argv[status]);
		decrypt.file  = open(argv[status],O_RDONLY);
		decrypt.call = chiara_emul_x86;
		} else {
		printf("You don't provide a  file thechiara STOP\n");	
			exit(1);
		}		
} else if (strcmp(argv[1],"-iso") == 0) {
	return chiara_parse_argv_iso(argn,argv);
} else if (strcmp(argv[status],"-rawriscv") == 0) {
	
status++;
	decrypt.arguments |=  CHIARA_EXTRACT_RAWRISCV;
	if(status != argn) {
		printf("We will decrypt raw riscv file  : %s \n",argv[status]);
		decrypt.file  = open(argv[status],O_RDONLY);
		decrypt.call = chiara_emul_riscv;
		} else {
		printf("You don't provide a  file thechiara STOP\n");	
			exit(1);
		}		
}

else {
	status++;
	
}

}
if(*decrypt.call != 0) {
	chiara_call_function();
	
	} else {
printf("You don't provide arguments : \n");
	printf("usage of thechiara  : \n ");
	printf("-iso [NAME] [ARCHITECTURE,ppcle,x86,ppcbe,arm64,riscv64] \n ");
	printf("-elf [NAME]  \n");
	printf("-rawx86 [NAME]   \n");	
	exit(1);
}	
	
}

int main (int argn,const char *argv[]) {
printf("Copyright 2020 Gaspard COURCHINOUX and contributors of thechiara project \n");
if(argn <= 2) {
	printf("You don't provide arguments : \n");
	printf("usage of thechiara  : \n ");
	printf("-iso [NAME] [ARCHITECTURE,ppcle,x86,ppcbe,arm64,riscv64] \n ");
	printf("-elf [NAME]  \n");
	printf("-rawx86 [NAME]   \n");	
	return;
}
chiara_alloc_ram(320000000); // 32kb of memory for testing 

chiara_decrypt_arguments(argn,argv);

while(1);
	





}

