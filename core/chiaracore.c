
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

void chiara_action_reg(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture) {
	
	switch(architecture) {
		
		case X86_IMAGE: break;
		case POWERPC_LITTLENDIAN_IMAGE: break;
		case POWERPC_BIGNDIAN_IMAGE: break;
		
		}
}
