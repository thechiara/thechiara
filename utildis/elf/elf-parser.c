
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
// 


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
void chiara_extract_32bits( char *structheader) {
		Elf32_Ehdr *elfheader = structheader;

	unsigned char *programheader = structheader + elfheader->e_shoff + elfheader->e_shstrndx * sizeof(Elf32_Ehdr);
	Elf32_Phdr *programheaderstruct = programheader;
switch (programheaderstruct->p_type) {
	case PT_LOAD : printf("pt load \n"); break;
	case PT_NULL : printf("PT_NULL \n"); break;
	case PT_DYNAMIC : printf("PT_DYNAMIC \n"); break;
	case PT_INTERP : printf("PT_INTERP \n"); break;
	case PT_LOPROC : printf("PT_LOPROC \n"); break;
	default: printf("valeur %x \n",programheaderstruct->p_type); break;
	}

unsigned char *premieresection = structheader+elfheader->e_shoff;
Elf32_Shdr *sectionactuelstruct =  premieresection;

for (int sectionread;sectionread<elfheader->e_shnum;sectionread++) {

	unsigned char *instructionsection = structheader +sectionactuelstruct[sectionread].sh_offset ;
	printf("offset section header en hexa %x \n",sectionactuelstruct[sectionread].sh_offset);
	printf("size section header en hexa %x \n",sectionactuelstruct[sectionread].sh_size);
	printf("adresse section header en hexa %x \n",sectionactuelstruct[sectionread].sh_addr);
switch (sectionactuelstruct[sectionread].sh_type) {
	
	case SHT_NULL: printf("entete inactif \n"); break;
	case SHT_PROGBITS: printf("SHT_PROGBITS \n"); break;
	case SHT_SYMTAB: printf("SHT_SYMTAB \n"); break;
	case SHT_STRTAB: printf("SHT_STRTAB \n"); break;
	case SHT_RELA: printf("SHT_RELA \n"); break;
	case SHT_HASH: printf("SHT_HASH \n"); break;
	case SHT_DYNAMIC: printf("SHT_DYNAMIC \n"); break;
	case SHT_NOTE: printf("SHT_NOTE \n"); break;
	case SHT_NOBITS: printf("SHT_NOBITS \n"); break;
	case SHT_REL: printf("SHT_REL \n"); break;
	case SHT_SHLIB: printf("SHT_SHLIB \n"); break;
	case SHT_DYNSYM: printf("SHT_DYNSYM \n"); break;
	case SHT_LOPROC: printf("SHT_LOPROC \n"); break;
	case SHT_HIPROC: printf("SHT_HIPROC \n"); break;
	case SHT_LOUSER: printf("SHT_LOUSER \n"); break;
	case SHT_HIUSER: printf("SHT_HIUSER \n"); break;
	
	
	
	}
	if (sectionactuelstruct[sectionread].sh_flags & SHF_EXECINSTR | SHF_ALLOC) {
		printf("executable !!! \n");
		// go l'envoyer 
		
if (elfheader->e_ident[EI_DATA] == ELFDATA2LSB) {
		printf("low endian droite à gauche \n");
	
	
	switch (elfheader->e_machine) {
		case EM_PPC : printf("powerpc 32bits \n");  chiara_emul_littleendian_ppc (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
		case EM_PPC64 : printf("powerpc 64bits \n");  chiara_emul_littleendian_ppc (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
			case EM_VAX : printf("DEC ALPHA 64bits \n");  chiara_emul_littleendian_dec (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;

		case EM_X86_64 : chiara_emul_x86(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size); break;
		case EM_386 : chiara_emul_x86(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size); break;
		
	case EM_AARCH64 : printf("AARCH64 \n");  chiara_emul_arm(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 
		case EM_ARM : printf("EM_ARM \n");  chiara_emul_arm(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 	
		case EM_RISCV : chiara_emul_riscv(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size); break;
default : printf("Dont know fatal : %d \n",elfheader->e_machine);

		}

	
	
		}
	if (elfheader->e_ident[EI_DATA] == ELFDATA2MSB) {
		printf("big endian on lit de gauche à droite \n");
		
			switch (elfheader->e_machine) {
		case EM_PPC : printf("powerpc 32bits \n");  chiara_emul_bigendian_ppc (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
		case EM_PPC64 : printf("powerpc 64bits \n");  chiara_emul_bigendian_ppc (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
			case EM_VAX : printf("DEC ALPHA 64bits \n");  chiara_emul_littleendian_dec (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;

	case EM_X86_64 : chiara_emul_x86(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size); break;
	case EM_386 : chiara_emul_x86(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size); break;
	case EM_AARCH64 : printf("AARCH64 \n");  chiara_emul_arm(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 
		case EM_ARM : printf("EM_ARM \n");  chiara_emul_arm_big(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 
default : printf("Dont know fatal : %d \n",elfheader->e_machine);

		}

		
		}
	





		}
switch (sectionactuelstruct[sectionread].sh_flags) {
	
	case SHF_EXECINSTR: printf("executable !!! \n"); break;
	case SHF_ALLOC: printf("SHF_ALLOC !!! \n"); break;
	case SHF_MASKPROC: printf("SHF_MASKPROC !!! \n"); break;
	case SHF_WRITE: printf("SHF_WRITE !!! \n"); break;
	
	
	
	
	}

	}
	

	
	}
void chiara_extract_64bits( char *structheader) {
		Elf64_Ehdr *elfheader = structheader;

	unsigned char *programheader = structheader + elfheader->e_shoff + elfheader->e_shstrndx * sizeof(Elf64_Ehdr);
	Elf64_Phdr *programheaderstruct = programheader;
switch (programheaderstruct->p_type) {
	case PT_LOAD : printf("pt load \n"); break;
	case PT_NULL : printf("PT_NULL \n"); break;
	case PT_DYNAMIC : printf("PT_DYNAMIC \n"); break;
	case PT_INTERP : printf("PT_INTERP \n"); break;
	case PT_LOPROC : printf("PT_LOPROC \n"); break;
	default: printf("valeur %x \n",programheaderstruct->p_type); break;
	}

unsigned char *premieresection = structheader+elfheader->e_shoff;
Elf64_Shdr *sectionactuelstruct =  premieresection;

for (int sectionread;sectionread<elfheader->e_shnum;sectionread++) {

	unsigned char *instructionsection = structheader +sectionactuelstruct[sectionread].sh_offset ;
	printf("offset section header en hexa %x \n",sectionactuelstruct[sectionread].sh_offset);
	printf("size section header en hexa %x \n",sectionactuelstruct[sectionread].sh_size);
	printf("adresse section header en hexa %x \n",sectionactuelstruct[sectionread].sh_addr);
switch (sectionactuelstruct[sectionread].sh_type) {
	
	case SHT_NULL: printf("entete inactif \n"); break;
	case SHT_PROGBITS: printf("SHT_PROGBITS \n"); break;
	case SHT_SYMTAB: printf("SHT_SYMTAB \n"); break;
	case SHT_STRTAB: printf("SHT_STRTAB \n"); break;
	case SHT_RELA: printf("SHT_RELA \n"); break;
	case SHT_HASH: printf("SHT_HASH \n"); break;
	case SHT_DYNAMIC: printf("SHT_DYNAMIC \n"); break;
	case SHT_NOTE: printf("SHT_NOTE \n"); break;
	case SHT_NOBITS: printf("SHT_NOBITS \n"); break;
	case SHT_REL: printf("SHT_REL \n"); break;
	case SHT_SHLIB: printf("SHT_SHLIB \n"); break;
	case SHT_DYNSYM: printf("SHT_DYNSYM \n"); break;
	case SHT_LOPROC: printf("SHT_LOPROC \n"); break;
	case SHT_HIPROC: printf("SHT_HIPROC \n"); break;
	case SHT_LOUSER: printf("SHT_LOUSER \n"); break;
	case SHT_HIUSER: printf("SHT_HIUSER \n"); break;
	
	
	
	}
	if (sectionactuelstruct[sectionread].sh_flags & SHF_EXECINSTR | SHF_ALLOC) {
		printf("executable !!! \n");
	
	if (elfheader->e_ident[EI_DATA] == ELFDATA2LSB) {
		printf("low endian droite à gauche \n");
	
	
	switch (elfheader->e_machine) {
		case EM_PPC : printf("powerpc 32bits \n");  chiara_emul_littleendian_ppc (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
		case EM_PPC64 : printf("powerpc 64bits \n");  chiara_emul_littleendian_ppc (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
		case EM_VAX : printf("DEC ALPHA 64bits \n");  chiara_emul_littleendian_dec (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
		case EM_X86_64 :  chiara_emul_x86(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 
		case EM_386 :  chiara_emul_x86(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 
		case EM_AARCH64 : printf("AARCH64 \n");  chiara_emul_arm(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 
		case EM_ARM : printf("EM_ARM \n");  chiara_emul_arm(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 
		case EM_RISCV: chiara_emul_riscv(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
default : printf("Dont know fatal : %d \n",elfheader->e_machine);  

		}

	
	
		}
	if (elfheader->e_ident[EI_DATA] == ELFDATA2MSB) {
		printf("big endian on lit de gauche à droite \n");
		
			switch (elfheader->e_machine) {
		case EM_PPC : printf("powerpc 32bits \n");  chiara_emul_bigendian_ppc (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
		case EM_PPC64 : printf("powerpc 64bits \n");  chiara_emul_bigendian_ppc (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;
		case EM_VAX : printf("DEC ALPHA 64bits \n");  chiara_emul_littleendian_dec (structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break;

		case EM_X86_64 : chiara_emul_x86(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size); break;
		case EM_386 : chiara_emul_x86(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size); break;
		case EM_ARM : printf("EM_ARM  big endian \n");  chiara_emul_arm_big(structheader +sectionactuelstruct[sectionread].sh_offset,sectionactuelstruct[sectionread].sh_size);break; 

default : printf("Dont know fatal : %d \n",elfheader->e_machine);
		}

		
		}
	
	
		}


	}

	}

void chiara_extract_elf (char *structheader,int unused2) {
	
	Elf32_Ehdr *elfheader = structheader;

if (elfheader->e_ident[EI_MAG0] == 0x7f) {
	
	printf("ELF MESSAGE : Magic number found \n");
	}	 else {
		printf("ELF MESSAGE : not a an elf file \n");
exit(EXIT_FAILURE);	
		
		
		}
	if (elfheader->e_ident[EI_CLASS] == ELFCLASS32) {
		printf("32 bits elf \n");
		chiara_extract_32bits(structheader);

		}
	if (elfheader->e_ident[EI_CLASS] == ELFCLASS64) {
		printf("64 bits elf \n");
		//exit(EXIT_FAILURE);	
chiara_extract_64bits(structheader);
		}

		printf("ELF MESSAGE: data type %d \n",elfheader->e_ident[EI_DATA]);
	
	
	
}
