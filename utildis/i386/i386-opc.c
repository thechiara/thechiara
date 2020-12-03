/* Intel 80386 opcode table
   Copyright (C) 2007-2020 Free Software Foundation, Inc.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
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
#include <chiaracore.h>
#include "i386-opc.h"
#include "i386-tbl.h"
#include <stdio.h>
/* Segment stuff.  */
const seg_entry cs = { "cs", 0x2e };
const seg_entry ds = { "ds", 0x3e };
const seg_entry ss = { "ss", 0x36 };
const seg_entry es = { "es", 0x26 };
const seg_entry fs = { "fs", 0x64 };
const seg_entry gs = { "gs", 0x65 };

static struct insn_template * chiara_lookup_opcode(unsigned char instruction) {
	
	for(int x = 0;x<i386_opcode_table_size;x++) {
		
		if(i386_optab[x].base_opcode ==instruction) {
			
			return &i386_optab[x];
			}
		
		
		}
	return 0;
	}
// ok, x86 is a cisc ISA, I will scan the the instruction I when the program found a opcode -> increment the array with the size provided by the struct array
	
void chiara_emul_x86(unsigned char *instruction,int size) {
	long statusarray=0;
	for(;statusarray<size;statusarray++) {
		struct insn_template * tmp  = chiara_lookup_opcode(instruction[statusarray]) ;
		if( tmp !=0) {
			
			printf("X86 instruction -> %s \n",tmp->name);
			if(*tmp->to_chiara_gpr != 0) {
				// get attribute 
				
				unsigned long gpr[2];
				unsigned long errors[2];
				
				}
			statusarray += tmp->opcode_length;
			}
		
		}
	
}

