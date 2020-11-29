
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

void chiara_clear_flags( ) {
			global_struct.flags.equal =0;
			global_struct.flags.carry =0;
			global_struct.flags.overflow =0;
			global_struct.flags.zero =0;

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
	long long data;


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
void chiara_check_gpr(struct  chiara_gpr_organization *tocheck1,struct  chiara_gpr_organization *tocheck2,struct  chiara_gpr_organization *tocheck3,long long data) {
chiara_clear_flags();
	if(tocheck1->typeofgpr==GPR64BITS) {
		// no check to do 
		if(tocheck1->data <0) {
			global_struct.flags.zero =1;
			}
			if(tocheck1->data & 1<<63) {
				
			global_struct.flags.carry =1;

				
				}
			
		return;
		}
	
	if(tocheck1->typeofgpr==GPR32BITS) {
		// verifier l'overflow
		
		 if ( tocheck1->data < -2147483648 ||  tocheck1->data < 2147483647) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		if(tocheck1->data <0) {
			global_struct.flags.zero =1;
			}
	if(tocheck1->data & 1<<31) {
				
			global_struct.flags.carry =1;

				
				}	
		}
	if(tocheck1->typeofgpr==GPR16BITS) {
		// verifier l'overflow
		
		 if ( tocheck1->data < -32768 ||  tocheck1->data < 32767) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
	
	if(tocheck1->data <0) {
			global_struct.flags.zero =1;
			}
	
		if(tocheck1->data & 1<<15) {
				
			global_struct.flags.carry =1;
	}	
	
		}
	if(tocheck1->typeofgpr==GPR8BITS) {
		// verifier l'overflow
		 if ( tocheck1->data < -128 ||  tocheck1->data < 127) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
			}
	if(tocheck1->data <0) {
			global_struct.flags.zero =1;
	}	
	if(tocheck1->data & 1<<7) {
				
			global_struct.flags.carry =1;
	}			
		
		}
	if(tocheck2!=0) {
	if(tocheck2->typeofgpr==GPR64BITS) {
		if(tocheck2->data <0) {
			global_struct.flags.zero =1;
			}
	if(tocheck2->data & 1<<63) {
				
			global_struct.flags.carry =1;
	}
	
		}
	
	if(tocheck2->typeofgpr==GPR32BITS) {
		// verifier l'overflow
		if(tocheck2->data & 1<<31) {
				
			global_struct.flags.carry =1;
			}
		 if ( tocheck2->data < -2147483648 ||  tocheck2->data < 2147483647) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
			}
	if(tocheck2->data <0) {
			global_struct.flags.zero =1;
			}
		}
	if(tocheck2->typeofgpr==GPR16BITS) {
		
			if(tocheck2->data & 1<<15) {
				
			global_struct.flags.carry =1;
			}
		
		 if ( tocheck2->data < -32768 ||  tocheck2->data < 32767) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
			}
	if(tocheck2->data <0) {
			global_struct.flags.zero =1;
			}

		}
	if(tocheck2->typeofgpr==GPR8BITS) {
		// verifier l'overflow
		 if ( tocheck2->data < -128 ||  tocheck2->data < 127) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		if(tocheck2->data <0) {
			
			global_struct.flags.zero =1;
			
			}
			
	if(tocheck2->data & 1<<7) {
				
			global_struct.flags.carry =1;
			
			}
		}	
		
}
	if(tocheck3!=0) {
	if(tocheck3->typeofgpr==GPR64BITS) {
		if(tocheck3->data & 1<<63) {
				
			global_struct.flags.carry =1;
			}
			
		if(tocheck3->data <0) {
			global_struct.flags.zero =1;
		
			}
	
		}
	
	if(tocheck3->typeofgpr==GPR32BITS) {
		if(tocheck3->data & 1<<31) {
				
			global_struct.flags.carry =1;
			}
		// verifier l'overflow
		if(tocheck3->data <0) {
			global_struct.flags.zero =1;
			}
		 if ( tocheck3->data < -2147483648 ||  tocheck3->data < 2147483647) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		}
	if(tocheck3->typeofgpr==GPR16BITS) {
		if(tocheck3->data & 1<<15) {
				
			global_struct.flags.carry =1;
			}
		
		
		// verifier l'overflow
		if(tocheck3->data <0) {
			global_struct.flags.zero =1;
			}
		 if ( tocheck3->data < -32768 ||  tocheck3->data < 32767) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		}
	if(tocheck3->typeofgpr==GPR8BITS) {
		
		if(tocheck3->data & 1<<7) {
				
			global_struct.flags.carry =1;
			}
		
		// verifier l'overflow
		if(tocheck3->data <0) {
			global_struct.flags.zero =1;
			}
		 if ( tocheck3->data < -128 ||  tocheck3->data < 127) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		
		}	
		
}
// data check
if(data != NODATA) {
		if(data <0) {
			global_struct.flags.zero =1;
			}
if(tocheck1->typeofgpr==GPR64BITS) {
		// no check to do 
	
			if(data & 1<<63) {
				
			global_struct.flags.carry =1;

				
				}
			
		}
	
	if(tocheck1->typeofgpr==GPR32BITS) {
		// verifier l'overflow
		
		 if ( data < -2147483648 ||  data < 2147483647) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		if(data <0) {
			global_struct.flags.zero =1;
			}
	if(data & 1<<31) {
				
			global_struct.flags.carry =1;

				
				}	
		}
	if(tocheck1->typeofgpr==GPR16BITS) {
		// verifier l'overflow
		
		 if ( data < -32768 ||  data < 32767) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
	
	if(data <0) {
			global_struct.flags.zero =1;
			}
	
		if(data & 1<<15) {
				
			global_struct.flags.carry =1;
	}	
	
		}
	if(tocheck1->typeofgpr==GPR8BITS) {
		// verifier l'overflow
		 if ( data < -128 ||  data < 127) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
			}
	if(data <0) {
			global_struct.flags.zero =1;
	}	
	if(data & 1<<7) {
				
			global_struct.flags.carry =1;
	}			
		
		}	
	
}

}	
void chiara_action_reg(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture,long long datahardcoded) {
	
	switch(architecture) {
		
		case X86_IMAGE:
		
		if(action == ACTION_AND) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// and reg
			gpr_orga_array[first].data &= gpr_orga_array[second].data;
			} else if(action == ACTION_XOR) {
								chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,NODATA);
	
			// ACTION_XOR reg
			gpr_orga_array[first].data = ~gpr_orga_array[first].data;
			} else if(action == ACTION_OR) {
					chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,NODATA);
	
			// ACTION_OR reg
			gpr_orga_array[first].data |= gpr_orga_array[second].data;
			} else if(action == ACTION_ADD) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_ADD reg
			gpr_orga_array[first].data += gpr_orga_array[second].data;
			} else if(action == ACTION_SUB) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_SUB reg
			gpr_orga_array[first].data -= gpr_orga_array[second].data;
			} else if(action == ACTION_INC) {
			chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,NODATA);

			// ACTION_INC reg
			gpr_orga_array[first].data = gpr_orga_array[first].data+1;
			} else if(action == ACTION_DEC) {
			chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,NODATA);

			// ACTION_DEC reg
			gpr_orga_array[first].data = gpr_orga_array[first].data-1;
			} else if(action == ACTION_DISP_REG) {
				// c'est l'hypothèse dans laquelle un GPR se voit attribuer une valeur arbitraire
			chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			gpr_orga_array[first].data = datahardcoded;
			}
		 
		
		 break;
		case POWERPC_LITTLENDIAN_IMAGE: break;
		case POWERPC_BIGNDIAN_IMAGE: break;
		
		}
}
