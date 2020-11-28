
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
#include <chiaracore.h>
#include <limits.h>
   #include <unistd.h>

void gaspard_clear_flags( ) {
			global_struct.flags.equal =0;
			global_struct.flags.carry =0;
			global_struct.flags.overflow =0;

}
void gaspard_check_flags_result(long res) {
	if(res<0) {
					global_struct.flags.zero =1;

				}
		if (res & 1<< 31 ) {
			global_struct.flags.carry =1;
			global_struct.flags.overflow =1;

					}
					
					 if ( res < INT_MIN ||  res < INT_MIN) {			
				global_struct.flags.overflow =1;
	}
	
	}
void gaspard_check_flags( long a, long b) {
	if(a==b) {
		global_struct.flags.equal =1;
		
		} else {
			
	global_struct.flags.equal =0;

			}
			
	if(a<0) {
					global_struct.flags.zero =1;

				}
	if(b<0) {
					global_struct.flags.zero =1;

				}
				
		if (a & 1<< 31 == b & 1<< 31) {
			global_struct.flags.carry =1;
			global_struct.flags.overflow =1;

					}
					
	 if ( a < INT_MIN ||  b < INT_MIN) {			
				global_struct.flags.overflow =1;
	}
	}
	
struct chiara_gpr_organization{
	unsigned char typeofgpr;
	unsigned char position;
	union {
		char data8;
		short data16;
		long data32;
		long long data64;
		
		};
	};
	
 struct chiara_gpr_organization gpr_orga_array[128] = { 
{.typeofgpr=GPR8BITS,.position=0},
{.typeofgpr=GPR8BITS,.position=1},
{.typeofgpr=GPR8BITS,.position=2},
{.typeofgpr=GPR8BITS,.position=3},
{.typeofgpr=GPR8BITS,.position=4},
{.typeofgpr=GPR8BITS,.position=5},
{.typeofgpr=GPR8BITS,.position=6},
{.typeofgpr=GPR8BITS,.position=7},
{.typeofgpr=GPR8BITS,.position=8},
{.typeofgpr=GPR8BITS,.position=9},
{.typeofgpr=GPR8BITS,.position=10},
{.typeofgpr=GPR8BITS,.position=11},
{.typeofgpr=GPR8BITS,.position=12},
{.typeofgpr=GPR8BITS,.position=13},
{.typeofgpr=GPR8BITS,.position=14},
{.typeofgpr=GPR8BITS,.position=15},
{.typeofgpr=GPR8BITS,.position=16},
{.typeofgpr=GPR8BITS,.position=17},
{.typeofgpr=GPR8BITS,.position=18},
{.typeofgpr=GPR8BITS,.position=19},
{.typeofgpr=GPR8BITS,.position=20},
{.typeofgpr=GPR8BITS,.position=21},
{.typeofgpr=GPR8BITS,.position=22},
{.typeofgpr=GPR8BITS,.position=23},
{.typeofgpr=GPR8BITS,.position=24},
{.typeofgpr=GPR8BITS,.position=25},
{.typeofgpr=GPR8BITS,.position=26},
{.typeofgpr=GPR8BITS,.position=27},
{.typeofgpr=GPR8BITS,.position=28},
{.typeofgpr=GPR8BITS,.position=29},
{.typeofgpr=GPR8BITS,.position=30},
{.typeofgpr=GPR8BITS,.position=31},
{.typeofgpr=GPR16BITS,.position=0},
{.typeofgpr=GPR16BITS,.position=1},
{.typeofgpr=GPR16BITS,.position=2},
{.typeofgpr=GPR16BITS,.position=3},
{.typeofgpr=GPR16BITS,.position=4},
{.typeofgpr=GPR16BITS,.position=5},
{.typeofgpr=GPR16BITS,.position=6},
{.typeofgpr=GPR16BITS,.position=7},
{.typeofgpr=GPR16BITS,.position=8},
{.typeofgpr=GPR16BITS,.position=9},
{.typeofgpr=GPR16BITS,.position=10},
{.typeofgpr=GPR16BITS,.position=11},
{.typeofgpr=GPR16BITS,.position=12},
{.typeofgpr=GPR16BITS,.position=13},
{.typeofgpr=GPR16BITS,.position=14},
{.typeofgpr=GPR16BITS,.position=15},
{.typeofgpr=GPR16BITS,.position=16},
{.typeofgpr=GPR16BITS,.position=17},
{.typeofgpr=GPR16BITS,.position=18},
{.typeofgpr=GPR16BITS,.position=19},
{.typeofgpr=GPR16BITS,.position=20},
{.typeofgpr=GPR16BITS,.position=21},
{.typeofgpr=GPR16BITS,.position=22},
{.typeofgpr=GPR16BITS,.position=23},
{.typeofgpr=GPR16BITS,.position=24},
{.typeofgpr=GPR16BITS,.position=25},
{.typeofgpr=GPR16BITS,.position=26},
{.typeofgpr=GPR16BITS,.position=27},
{.typeofgpr=GPR16BITS,.position=28},
{.typeofgpr=GPR16BITS,.position=29},
{.typeofgpr=GPR16BITS,.position=30},
{.typeofgpr=GPR16BITS,.position=31},
{.typeofgpr=GPR32BITS,.position=0},
{.typeofgpr=GPR32BITS,.position=1},
{.typeofgpr=GPR32BITS,.position=2},
{.typeofgpr=GPR32BITS,.position=3},
{.typeofgpr=GPR32BITS,.position=4},
{.typeofgpr=GPR32BITS,.position=5},
{.typeofgpr=GPR32BITS,.position=6},
{.typeofgpr=GPR32BITS,.position=7},
{.typeofgpr=GPR32BITS,.position=8},
{.typeofgpr=GPR32BITS,.position=9},
{.typeofgpr=GPR32BITS,.position=10},
{.typeofgpr=GPR32BITS,.position=11},
{.typeofgpr=GPR32BITS,.position=12},
{.typeofgpr=GPR32BITS,.position=13},
{.typeofgpr=GPR32BITS,.position=14},
{.typeofgpr=GPR32BITS,.position=15},
{.typeofgpr=GPR32BITS,.position=16},
{.typeofgpr=GPR32BITS,.position=17},
{.typeofgpr=GPR32BITS,.position=18},
{.typeofgpr=GPR32BITS,.position=19},
{.typeofgpr=GPR32BITS,.position=20},
{.typeofgpr=GPR32BITS,.position=21},
{.typeofgpr=GPR32BITS,.position=22},
{.typeofgpr=GPR32BITS,.position=23},
{.typeofgpr=GPR32BITS,.position=24},
{.typeofgpr=GPR32BITS,.position=25},
{.typeofgpr=GPR32BITS,.position=26},
{.typeofgpr=GPR32BITS,.position=27},
{.typeofgpr=GPR32BITS,.position=28},
{.typeofgpr=GPR32BITS,.position=29},
{.typeofgpr=GPR32BITS,.position=30},
{.typeofgpr=GPR32BITS,.position=31},
{.typeofgpr=GPR64BITS,.position=0},
{.typeofgpr=GPR64BITS,.position=1},
{.typeofgpr=GPR64BITS,.position=2},
{.typeofgpr=GPR64BITS,.position=3},
{.typeofgpr=GPR64BITS,.position=4},
{.typeofgpr=GPR64BITS,.position=5},
{.typeofgpr=GPR64BITS,.position=6},
{.typeofgpr=GPR64BITS,.position=7},
{.typeofgpr=GPR64BITS,.position=8},
{.typeofgpr=GPR64BITS,.position=9},
{.typeofgpr=GPR64BITS,.position=10},
{.typeofgpr=GPR64BITS,.position=11},
{.typeofgpr=GPR64BITS,.position=12},
{.typeofgpr=GPR64BITS,.position=13},
{.typeofgpr=GPR64BITS,.position=14},
{.typeofgpr=GPR64BITS,.position=15},
{.typeofgpr=GPR64BITS,.position=16},
{.typeofgpr=GPR64BITS,.position=17},
{.typeofgpr=GPR64BITS,.position=18},
{.typeofgpr=GPR64BITS,.position=19},
{.typeofgpr=GPR64BITS,.position=20},
{.typeofgpr=GPR64BITS,.position=21},
{.typeofgpr=GPR64BITS,.position=22},
{.typeofgpr=GPR64BITS,.position=23},
{.typeofgpr=GPR64BITS,.position=24},
{.typeofgpr=GPR64BITS,.position=25},
{.typeofgpr=GPR64BITS,.position=26},
{.typeofgpr=GPR64BITS,.position=27},
{.typeofgpr=GPR64BITS,.position=28},
{.typeofgpr=GPR64BITS,.position=29},
{.typeofgpr=GPR64BITS,.position=30},
{.typeofgpr=GPR64BITS,.position=31},	
};
		
void chiara_action_reg(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture,long long datahardcoded) {
	
	switch(architecture) {
		
		case X86_IMAGE:
		
		if(action == ACTION_AND) {
			
			// and reg
			
			}
		
		
		 break;
		case POWERPC_LITTLENDIAN_IMAGE: break;
		case POWERPC_BIGNDIAN_IMAGE: break;
		
		}
}
