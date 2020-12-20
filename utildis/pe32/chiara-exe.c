
// Copyright 2020 Gaspard COURCHINOUX 
/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */


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


#include "chiara-exe.h"
void chiara_pe_header_look(unsigned char *file,unsigned long size) {
struct _IMAGE_NT_HEADERS *pe ;
// e_lfanew suck 
for(int x = 0;x<450;x++) {
	
	if(file[x] == 0x50 && file[x+1] == 0x45 ) {
		
		printf("pe found \n");
		pe = (struct _IMAGE_NT_HEADERS*)file+x;
		}
	
	}
if(pe == 0) {
	printf("FATAL EXE ERROR NO PE HEADER FOUND \n");
	exit(1);
	return;
	}
	
printf("signature pe %x \n",pe->Signature);
printf("machine %x \n",(pe->FileHeader.Machine));
printf("NUM OF SECTIONS PE%x \n",pe->FileHeader.NumberOfSections);
}


void chiara_dos_header_look(unsigned char *file,unsigned long size) {
struct dos_header *header = file;	
	
	printf("dos _header %x \n",(header->e_magic));
	printf("adress of pe header  %x \n",header->e_lfanew);

chiara_pe_header_look(file,size);

}
