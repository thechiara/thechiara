
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
