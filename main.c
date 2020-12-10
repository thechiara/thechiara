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


int main (int argn,const char *argv[]) {

printf("Copyright 2020 Gaspard COURCHINOUX and contributors of thechiara project \n");
printf("thechiara can open elf files usage = -elf thenameofile \n");
printf("thechiara will detect the destination architecture of elf and start decompilling it and recompile in chiarasm \n");

if(strcmp(argv[1],"-elf") == 0) {
int file = open(argv[2],O_RDONLY);


int end = lseek(file,0,SEEK_END );
	
	lseek(file,0,SEEK_SET  ); // puyt on the begin
	
	// ici tester le fichier ELF ?iso ? raw
unsigned  char  *gaspard = malloc(end);
int size = 	read(file,gaspard,end);
close(file);
int status = 0;
printf("Now tell the elfmodule to analyze the elf file \n");
chiara_extract_elf(gaspard);

}else if(strcmp(argv[1],"-exe") == 0) {
int file = open(argv[2],O_RDONLY);


int end = lseek(file,0,SEEK_END );
	
	lseek(file,0,SEEK_SET  ); // puyt on the begin
	
	// ici tester le fichier ELF ?iso ? raw
unsigned  char  *gaspard = malloc(end);
int size = 	read(file,gaspard,end);
close(file);
int status = 0;
printf("Now call  the exe module to analyze the elf file \n");
chiara_dos_header_look(gaspard,end);


}else if(strcmp(argv[1],"-iso") == 0) {
	if(argn <=3) {
		printf("STOP : \n");
		printf("iso support several targets : \n");
		printf("-x86 for 32 bits intel \n");
		printf("-ppcle for power pc little endian \n");
		printf("-ppcbe for power pc big endian \n");
		return;
		
		}
int file = open(argv[2],O_RDONLY);

perror("ISO STATUS FILE");
int end = lseek(file,0,SEEK_END );
	
	lseek(file,0,SEEK_SET  ); // puyt on the begin
	
	// ici tester le fichier ELF ?iso ? raw
unsigned  char  *gaspard = malloc(end);
if(gaspard == NULL) {
perror("MALLOC STATUS ISO");
printf("Malloc cannot allow thechiara to get necessary memory, so thechiara will try to detect with your VFS fseek an ISO9660 filesystem \n");
chiara_init_huge_iso(file,end,argv[3]);

}else {
int size = 	read(file,gaspard,end);
close(file);
int status = 0;
printf("Now call the iso module \n");
chiara_init_iso(gaspard,end,argv[3]);
}
}else if(strcmp(argv[1],"-rawx86") == 0) {
	if(argn <=2) {
		printf("use this argument if you have a raw file contains x86 instructions \n");
		return;
		
		}
int file = open(argv[2],O_RDONLY);

perror("raw x86 STATUS FILE \n");
unsigned long long end = lseek(file,0,SEEK_END );
	
	lseek(file,0,SEEK_SET  ); // puyt on the begin
	
	// ici tester le fichier ELF ?iso ? raw
unsigned  char  *gaspard = malloc(end);

int size = 	read(file,gaspard,end);
close(file);
int status = 0;
printf("Now call the raw module \n");
chiara_emul_x86(gaspard,end);

}
while(1);
	





}

