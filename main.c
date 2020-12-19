// Copyright 2020 Gaspard COURCHINOUX 
/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

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

decrypt.call(gaspard,end);	
close(decrypt.file);

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
} else {
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

chiara_decrypt_arguments(argn,argv);

while(1);
	





}

