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
 
struct chiara_compute_flags {
	
	unsigned char equal;
	unsigned char carry;
	unsigned char overflow;
	unsigned char zero;
	
	
	};
struct chiara_compute_stats {
unsigned long useof8bitsreg; // for example if bits zero is set the register8[0] contain data	
unsigned long useof16bitsreg; // for example if bits zero is set the register16[0] contain data	
unsigned long useof32bitsreg; // for example if bits zero is set the register32[0] contain data	
unsigned long useof64bitsreg; // for example if bits zero is set the register64[0] contain data	
	
};	

//typedef __attribute__((unused))  ATTRIBUTE_UNUSED
struct chiara_compute_global {
	 long long register64[31];
	 long register32[31];
	 short register16[31];
	 char register8[31];
	
	//~ long gpr[31];
	unsigned long specialregister;
	struct chiara_compute_flags flags;
	struct chiara_compute_stats stats;
	};
struct chiara_compute_global global_struct;
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#define X86_IMAGE 0x44
#define POWERPC_LITTLENDIAN_IMAGE 0x20
#define POWERPC_BIGNDIAN_IMAGE 0x21
#define ARM_64 0x22
#define RISCV 0x11

#define NO_ACTION 0x0
#define ACTION_AND 0x1
#define ACTION_XOR 0x2
#define ACTION_OR 0x3
#define ACTION_ADD 0x4
#define ACTION_SUB 0x5
#define ACTION_INC 0x6
#define ACTION_DEC 0x7
#define ACTION_DISP_REG 0x8
#define ACTION_DIVUNSIGNED 0x9
#define ACTION_DIVSIGNED 0xa
#define ACTION_MULSIGNED 0xb
#define ACTION_MULUNSIGNED 0xc
#define ACTION_SHIFTLEFT 0xd
#define ACTION_SHIFTRIGHT 0xe
#define ACTION_MODULO 0xf
#define ACTION_NOT 0x10
#define ACTION_DISP_REG_COPY 0x11 //copy reg in another reg
#define ACTION_DIV 0x12
#define ACTION_CMP 0x13
#define ACTION_BSWAPRIGHT 0x14 // reverse byte order 
#define ACTION_BSWAPLEFT 0x15 // reverse byte order 
#define ACTION_MULNORMAL 0x16 
#define ACTION_FPU_TO_INT 0x17 
#define ACTION_FPU_TO_INTUNSIGNED 0x18 






#define GPR8BITS 1
#define GPR16BITS 2
#define GPR32BITS 3
#define GPR64BITS 4

#define GPRFLOAT  5
#define GPRDOUBLE 6

#define NODATA 0
// first reg val,second is the second reg,third is the third reg ,action is the action perfomed on xor or ? , architecture is the source architecture x86p powerpc ?,datahardcoded is usefull for MOV AND DIP operation 
void chiara_action_reg(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture,long long datahardcoded);
void chiara_action_reg_fpu(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture,double datahardcoded);
void chiara_init_iso(unsigned char*file,unsigned long sizeofiso, char *argvstring);
void chiara_extract_elf (char *structheader,int unused2);
void chiara_emul_x86(unsigned char *instruction,int size);
void chiara_emul_riscv(unsigned char *instruction,int size);
