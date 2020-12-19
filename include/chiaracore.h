
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

#define GPR8BITS 1
#define GPR16BITS 2
#define GPR32BITS 3
#define GPR64BITS 4

#define NODATA 0
// first reg val,second is the second reg,third is the third reg ,action is the action perfomed on xor or ? , architecture is the source architecture x86p powerpc ?,datahardcoded is usefull for MOV AND DIP operation 
void chiara_action_reg(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture,long long datahardcoded);
