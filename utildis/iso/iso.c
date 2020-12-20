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

   #include <unistd.h>

struct image_iso{
	unsigned char *image;
	unsigned long size;
	long instruction_type; // type instruction 
	
	
	};
struct image_iso image;

int chiara_test_cd (unsigned char*file,int sizeofiso) {
	if(sizeofiso <=2048) {
		
		return 0;
		}
	unsigned char volume_descriptor = file[2048*0x0f];
	printf("ISO : VOLUME DESCRIPTOR : %x \n",volume_descriptor);
	
	}
void chiara_init_huge_iso(int file,unsigned long sizeofiso, char *argvstring) {
	if(sizeofiso <=2048) {
		printf("Crazy : the size of the iso is inferior at 2048 \n");
		return 0;
		}	
	
int end = lseek(file,0x0f,SEEK_SET ); // we want the volume descriptor
perror("Seek status");
unsigned char *volume_descriptor = malloc(2048);
read(file,volume_descriptor,2048);	
perror("READ status");

	lseek(file,0,SEEK_SET  ); 
	perror("seek to zero status");

		printf("HUGE ISO : VOLUME DESCRIPTOR : %x \n",volume_descriptor[0]);

}
void chiara_init_iso(unsigned char*file,unsigned long sizeofiso, char *argvstring) {
	// detect if the iso is an ISO9660 file
	printf("ISO SIZE %x \n",sizeofiso);
unsigned char * init = malloc(446);	
	image.image =file;
	image.size =sizeofiso;
	
	for(int x = 0;x<446;x++) {
		init[x] = file[x];
		
		}
	if(strcmp(argvstring,"-x86") == 0) {
		printf("detect x86 iso\n");
		image.instruction_type = X86_IMAGE;
		chiara_emul_x86(init,446);
		
		} else if(strcmp(argvstring,"-ppcle") == 0) {
			
			printf("ppc little endian iso \n");
					image.instruction_type = POWERPC_LITTLENDIAN_IMAGE;

					chiara_emul_littleendian_ppc(init,446);

		} else if(strcmp(argvstring,"-ppcbe") == 0) {
			
			printf("ppc little endian iso \n");
		image.instruction_type = POWERPC_BIGNDIAN_IMAGE;
	
					chiara_emul_bigendian_ppc(init,446);

		}
}
