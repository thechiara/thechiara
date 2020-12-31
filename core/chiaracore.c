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
#include <chiaracore.h>
#include <limits.h>
#include <unistd.h>
#include <byteswap.h>
#include <float.h> 
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

static long *mem;

void chiara_alloc_ram(int ramsize) {
	
	mem = malloc(ramsize);
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

void chiara_check_immediate_gpr( struct  chiara_gpr_organization *tocheck1, long long data) {
	
	if(data <0) {
			global_struct.flags.zero =1;
			}
if(tocheck1->typeofgpr==GPR64BITS) {
		// no check to do 
	
			if(data & 1<<63) {
				
			global_struct.flags.carry =1;

				
				}
			
		 if ( data < -9223372036854775808 ||  data <  9223372036854775807) {			
				global_struct.flags.overflow =1;
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

void chiara_check_gpr(struct  chiara_gpr_organization *tocheck1,struct  chiara_gpr_organization *tocheck2,struct  chiara_gpr_organization *tocheck3,long long data) {
chiara_clear_flags();
	if(tocheck1->typeofgpr==GPR64BITS) {
		// no check to do 
		if(tocheck1->data <0) {
			global_struct.flags.zero =1;
			}
			 if ( tocheck1->data < -9223372036854775808 ||  tocheck1->data <  9223372036854775807) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
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
			 if ( tocheck2->data < -9223372036854775808 ||  tocheck2->data <  9223372036854775807) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
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
 if ( tocheck3->data < -9223372036854775808 ||  tocheck3->data <  9223372036854775807) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
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
	chiara_check_immediate_gpr(tocheck1,data);
		

}
}	
void chiara_action_reg(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture,long long datahardcoded) {

	switch(architecture) {
		
		case X86_IMAGE:
	if (action == ACTION_DISP_MEM_TO_GPR) {
				chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,mem[datahardcoded]);
gpr_orga_array[first].data = mem[datahardcoded] ;
		return ;
	}else	if (action == ACTION_DISP_TO_MEM) {
		
		mem[datahardcoded] = gpr_orga_array[first].data;
		return;
		
	} else 	if(action == ACTION_AND) {

				if(datahardcoded != NODATA) {
		chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// and reg
			gpr_orga_array[first].data = gpr_orga_array[second].data & datahardcoded;			
					
return;
}

						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// and reg
			gpr_orga_array[first].data &= gpr_orga_array[second].data;
			} else if(action == ACTION_XOR) {
				
				if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);
	
			// ACTION_XOR reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ^ datahardcoded;					
return;
}
				
								chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
	
			// ACTION_XOR reg
			gpr_orga_array[first].data ^= gpr_orga_array[second].data;
			} else if(action == ACTION_OR) {
				if(datahardcoded != NODATA) {
	chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
	
			// ACTION_OR reg
			gpr_orga_array[first].data |= datahardcoded;

return;
}				
				
					chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,NODATA);
	
			// ACTION_OR reg
			gpr_orga_array[first].data |= gpr_orga_array[second].data;
			} else if(action == ACTION_ADD) {

if(datahardcoded != NODATA) {
	chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_ADD reg
			gpr_orga_array[first].data += datahardcoded;
return;
}	
				
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_ADD reg
			gpr_orga_array[first].data += gpr_orga_array[second].data;
			} else if(action == ACTION_SUB) {

if(datahardcoded != NODATA) {
	chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_SUB reg
			gpr_orga_array[first].data -= datahardcoded;	
return;
}				
				
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
			
			} else if(action == ACTION_DIVUNSIGNED) {
				
if(datahardcoded != NODATA) {

chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_DIVUNSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data /  datahardcoded;
return;
}				
				
			chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
//ACTION_DIVUNSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data /  gpr_orga_array[second].data;
			}else if(action == ACTION_DIVSIGNED) {
if(datahardcoded != NODATA) {

chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_UNSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data /  datahardcoded;
return;			
}				
			chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
//ACTION_UNSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data /  gpr_orga_array[second].data;
			} else if(action == ACTION_MULSIGNED) {
if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_MULSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data * datahardcoded;
return;
}				
			chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
//ACTION_MULSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data * gpr_orga_array[second].data;
			} else if(action == ACTION_MULUNSIGNED) {
if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_MULSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data * datahardcoded;
return;
}				
			chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
//ACTION_MULUNSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data * gpr_orga_array[second].data;
			}else if(action == ACTION_MODULO) {
if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_MULSIGNED
			gpr_orga_array[first].data = gpr_orga_array[first].data % datahardcoded;
return;
}				
			chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
//ACTION_MODULO
			gpr_orga_array[first].data = gpr_orga_array[first].data % gpr_orga_array[second].data;
			}else if(action == ACTION_NOT) {
				
			chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,NODATA);
//ACTION_NOT
			gpr_orga_array[first].data = ~gpr_orga_array[first].data ;
			} else if(action == ACTION_DISP_REG_COPY) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_DISP_REG_COPY reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ;
			} 
		 
		
		 break;
		case POWERPC_LITTLENDIAN_IMAGE: 
		if(action == ACTION_AND) {
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// and reg
			gpr_orga_array[first].data = gpr_orga_array[second].data & gpr_orga_array[third].data;
			} else if(action == ACTION_XOR) {
				chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_XOR reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ^ gpr_orga_array[third].data;
			} else if(action == ACTION_OR) {
		chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data | gpr_orga_array[third].data;
			} else if(action == ACTION_ADD) {
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_ADD reg
			gpr_orga_array[first].data = gpr_orga_array[second].data +  gpr_orga_array[third].data;
			} else if(action == ACTION_SUB) {
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data - gpr_orga_array[third].data;
			} else if(action == ACTION_DISP_REG_COPY) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_DISP_REG_COPY reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ;
			} else if(action == ACTION_DISP_REG) {
						chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_DISP_REG reg
			gpr_orga_array[first].data = datahardcoded ;
			}else if(action == ACTION_DIV) {
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_DIV reg
			gpr_orga_array[first].data = gpr_orga_array[second].data / gpr_orga_array[third].data;
			} else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPRIGHT reg
			gpr_orga_array[first].data = bswap_64(gpr_orga_array[second].data);
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPLEFT reg
			gpr_orga_array[first].data = bswap_64(gpr_orga_array[second].data);
			}





		case ARM_64: {
			
			if(action == ACTION_AND) {
				if(datahardcoded != NODATA) {
	chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// and reg
			gpr_orga_array[first].data = gpr_orga_array[second].data & datahardcoded;
return;
}
				
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// and reg
			gpr_orga_array[first].data = gpr_orga_array[second].data & gpr_orga_array[third].data;
			} else if(action == ACTION_XOR) {
				
		if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_XOR reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ^ datahardcoded;
return;
}				
				chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_XOR reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ^ gpr_orga_array[third].data;
			} else if(action == ACTION_OR) {
		if(datahardcoded != NODATA) {
		
		chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data |datahardcoded;
return;
}				
				
		chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data | gpr_orga_array[third].data;
			} else if(action == ACTION_ADD) {

		if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_ADD reg
			gpr_orga_array[first].data = gpr_orga_array[second].data +  datahardcoded;
return;
}				
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_ADD reg
			gpr_orga_array[first].data = gpr_orga_array[second].data +  gpr_orga_array[third].data;
			} else if(action == ACTION_SUB) {
				
			if(datahardcoded != NODATA) {
	chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data - datahardcoded;
return;
}			
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data - gpr_orga_array[third].data;
			} else if(action == ACTION_DISP_REG_COPY) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_DISP_REG_COPY reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ;
			} else if(action == ACTION_DISP_REG) {
						chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_DISP_REG reg
			gpr_orga_array[first].data = datahardcoded ;
			}else if(action == ACTION_DIV) {
				
		if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_DIV reg
			gpr_orga_array[first].data = gpr_orga_array[second].data / datahardcoded;
return;
}				
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_DIV reg
			gpr_orga_array[first].data = gpr_orga_array[second].data / gpr_orga_array[third].data;
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPRIGHT reg
			gpr_orga_array[first].data = bswap_64(gpr_orga_array[second].data);
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPLEFT reg
			gpr_orga_array[first].data = bswap_64(gpr_orga_array[second].data);
			} else if(action == ACTION_MULNORMAL) {
				
		if(datahardcoded != NODATA) {

return;
}
							chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_MULNORMAL reg
			gpr_orga_array[first].data = gpr_orga_array[second].data *  gpr_orga_array[third].data;
			} 
			
			
	}
		break;
		case RISCV : {
			
		
			if(action == ACTION_AND) {
				
					if(datahardcoded != NODATA) {
	
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[third],(void*)0,datahardcoded);

			// and reg
			gpr_orga_array[first].data = gpr_orga_array[second].data & datahardcoded;	
	
return;
		}
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// and reg
			gpr_orga_array[first].data = gpr_orga_array[second].data & gpr_orga_array[third].data;
			} else if(action == ACTION_XOR) {
		if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_XOR reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ^ datahardcoded;
return ; 
}
				chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_XOR reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ^ gpr_orga_array[third].data;
			} else if(action == ACTION_OR) {
				if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data | datahardcoded;
return;
}		
				
		chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data | gpr_orga_array[third].data;
			} else if(action == ACTION_ADD) {
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_ADD reg
			gpr_orga_array[first].data = gpr_orga_array[second].data +  gpr_orga_array[third].data;
			} else if(action == ACTION_SUB) {
		if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data - datahardcoded;
return;
}
						chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			gpr_orga_array[first].data = gpr_orga_array[second].data - gpr_orga_array[third].data;
			} else if(action == ACTION_DISP_REG_COPY) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_DISP_REG_COPY reg
			gpr_orga_array[first].data = gpr_orga_array[second].data ;
			} else if(action == ACTION_DISP_REG) {
						chiara_check_gpr(&gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_DISP_REG reg
			gpr_orga_array[first].data = datahardcoded ;
			}else if(action == ACTION_DIV) {
				if(datahardcoded != NODATA) {
chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			
gpr_orga_array[first].data = gpr_orga_array[second].data / datahardcoded;					
					
				} else {
				
chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_DIV reg
			
gpr_orga_array[first].data = gpr_orga_array[second].data / gpr_orga_array[third].data;
		}
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPRIGHT reg
			gpr_orga_array[first].data = bswap_64(gpr_orga_array[second].data);
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPLEFT reg
			gpr_orga_array[first].data = bswap_64(gpr_orga_array[second].data);
			} else if(action == ACTION_MULNORMAL) {
					if(datahardcoded != NODATA) {
	chiara_check_gpr(&gpr_orga_array[first],&gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_MULNORMAL reg
			gpr_orga_array[first].data = gpr_orga_array[second].data *  datahardcoded;

return;
}			
				
							chiara_check_gpr(&gpr_orga_array[second],&gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_MULNORMAL reg
			gpr_orga_array[first].data = gpr_orga_array[second].data *  gpr_orga_array[third].data;
			}			
			
			
}
	
		case POWERPC_BIGNDIAN_IMAGE: break;
		
		}
}
/* 
 * FPU SUPPORT
 * 
 * 
 * */
struct chiara_fpu_gpr_organization{
	unsigned char typeofgpr;
	unsigned char position;
	double data;


	};
 struct chiara_fpu_gpr_organization fpu_gpr_orga_array[64] = { 
	 {.typeofgpr=GPRFLOAT,.position=0},
{.typeofgpr=GPRFLOAT,.position=1},
{.typeofgpr=GPRFLOAT,.position=2},
{.typeofgpr=GPRFLOAT,.position=3},
{.typeofgpr=GPRFLOAT,.position=4},
{.typeofgpr=GPRFLOAT,.position=5},
{.typeofgpr=GPRFLOAT,.position=6},
{.typeofgpr=GPRFLOAT,.position=7},
{.typeofgpr=GPRFLOAT,.position=8},
{.typeofgpr=GPRFLOAT,.position=9},
{.typeofgpr=GPRFLOAT,.position=10},
{.typeofgpr=GPRFLOAT,.position=11},
{.typeofgpr=GPRFLOAT,.position=12},
{.typeofgpr=GPRFLOAT,.position=13},
{.typeofgpr=GPRFLOAT,.position=14},
{.typeofgpr=GPRFLOAT,.position=15},
{.typeofgpr=GPRFLOAT,.position=16},
{.typeofgpr=GPRFLOAT,.position=17},
{.typeofgpr=GPRFLOAT,.position=18},
{.typeofgpr=GPRFLOAT,.position=19},
{.typeofgpr=GPRFLOAT,.position=20},
{.typeofgpr=GPRFLOAT,.position=21},
{.typeofgpr=GPRFLOAT,.position=22},
{.typeofgpr=GPRFLOAT,.position=23},
{.typeofgpr=GPRFLOAT,.position=24},
{.typeofgpr=GPRFLOAT,.position=25},
{.typeofgpr=GPRFLOAT,.position=26},
{.typeofgpr=GPRFLOAT,.position=27},
{.typeofgpr=GPRFLOAT,.position=28},
{.typeofgpr=GPRFLOAT,.position=29},
{.typeofgpr=GPRFLOAT,.position=30},
{.typeofgpr=GPRFLOAT,.position=31},
{.typeofgpr=GPRDOUBLE,.position=0},
{.typeofgpr=GPRDOUBLE,.position=1},
{.typeofgpr=GPRDOUBLE,.position=2},
{.typeofgpr=GPRDOUBLE,.position=3},
{.typeofgpr=GPRDOUBLE,.position=4},
{.typeofgpr=GPRDOUBLE,.position=5},
{.typeofgpr=GPRDOUBLE,.position=6},
{.typeofgpr=GPRDOUBLE,.position=7},
{.typeofgpr=GPRDOUBLE,.position=8},
{.typeofgpr=GPRDOUBLE,.position=9},
{.typeofgpr=GPRDOUBLE,.position=10},
{.typeofgpr=GPRDOUBLE,.position=11},
{.typeofgpr=GPRDOUBLE,.position=12},
{.typeofgpr=GPRDOUBLE,.position=13},
{.typeofgpr=GPRDOUBLE,.position=14},
{.typeofgpr=GPRDOUBLE,.position=15},
{.typeofgpr=GPRDOUBLE,.position=16},
{.typeofgpr=GPRDOUBLE,.position=17},
{.typeofgpr=GPRDOUBLE,.position=18},
{.typeofgpr=GPRDOUBLE,.position=19},
{.typeofgpr=GPRDOUBLE,.position=20},
{.typeofgpr=GPRDOUBLE,.position=21},
{.typeofgpr=GPRDOUBLE,.position=22},
{.typeofgpr=GPRDOUBLE,.position=23},
{.typeofgpr=GPRDOUBLE,.position=24},
{.typeofgpr=GPRDOUBLE,.position=25},
{.typeofgpr=GPRDOUBLE,.position=26},
{.typeofgpr=GPRDOUBLE,.position=27},
{.typeofgpr=GPRDOUBLE,.position=28},
{.typeofgpr=GPRDOUBLE,.position=29},
{.typeofgpr=GPRDOUBLE,.position=30},
{.typeofgpr=GPRDOUBLE,.position=31},
	 
 };
void chiara_check_immediate_gpr_fpu( struct  chiara_fpu_gpr_organization *tocheck1, double data) {
	
	if(data <0) {
			global_struct.flags.zero =1;
			}
			
if(tocheck1->typeofgpr==GPRDOUBLE) {
		 if ( tocheck1->data < DBL_MIN   ||  tocheck1->data < DBL_MAX ) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	} 
	
	 if (data < DBL_MIN ||  data < DBL_MAX) {
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
				
				}
		if(tocheck1->data <0) {
			global_struct.flags.zero =1;
			}
	
	
		}
	
	if(tocheck1->typeofgpr==GPRFLOAT) {
		
		 if ( tocheck1->data < FLT_MIN ||  tocheck1->data < FLT_MAX) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
			} 
			
			 if (data < FLT_MIN ||  data < FLT_MAX) {
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
				
				}
	if(tocheck1->data <0) {
			global_struct.flags.zero =1;
			}
		}			
}
 void chiara_check_gpr_fpu(struct  chiara_fpu_gpr_organization *tocheck1,struct  chiara_fpu_gpr_organization *tocheck2,struct  chiara_fpu_gpr_organization *tocheck3,double data) {
if(tocheck1->typeofgpr==GPRDOUBLE) {
			 if ( tocheck1->data < DBL_MIN   ||  tocheck1->data < DBL_MAX ) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		if(tocheck1->data <0) {
			global_struct.flags.zero =1;
			}
			
			
	
		}
	
	if(tocheck1->typeofgpr==GPRFLOAT) {
		// verifier l'overflow
		
		 if ( tocheck1->data < FLT_MIN  ||  tocheck1->data < FLT_MAX ) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		if(tocheck1->data <0) {
			global_struct.flags.zero =1;
			}
	
		}
if(tocheck2!=0) {
	if(tocheck2->typeofgpr==GPRDOUBLE) {
		 if ( tocheck2->data < DBL_MIN   ||  tocheck2->data < DBL_MAX ) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		if(tocheck2->data <0) {
			global_struct.flags.zero =1;
			}
	
	
		}
	
	if(tocheck2->typeofgpr==GPRFLOAT) {
		
		 if ( tocheck2->data < FLT_MIN ||  tocheck2->data < FLT_MAX) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
			}
	if(tocheck2->data <0) {
			global_struct.flags.zero =1;
			}
		}
}	
if(tocheck3!=0) {
	if(tocheck3->typeofgpr==GPRDOUBLE) {
		 if ( tocheck3->data < DBL_MIN   ||  tocheck3->data < DBL_MAX ) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
	}
		if(tocheck3->data <0) {
			global_struct.flags.zero =1;
			}
	
	
		}
	
	if(tocheck3->typeofgpr==GPRFLOAT) {
		
		 if ( tocheck3->data < FLT_MIN ||  tocheck3->data < FLT_MAX) {			
				global_struct.flags.overflow =1;
				global_struct.flags.carry =1;
			}
	if(tocheck3->data <0) {
			global_struct.flags.zero =1;
			}
		}
}	
	if(data != NODATA) {
		
chiara_check_immediate_gpr_fpu(tocheck1,data);		
		
}
}
void chiara_action_reg_fpu(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture,double datahardcoded) {
	switch(architecture) {
		
		case X86_IMAGE:
		
	 if(action == ACTION_FPU_TO_INT) {

if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_FPU_TO_INT reg
			gpr_orga_array[first].data = datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_FPU_TO_INT reg
						gpr_orga_array[first].data = fpu_gpr_orga_array[second].data;

}			else  if(action == ACTION_FPU_TO_INTUNSIGNED) {
if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_FPU_TO_INT reg
			gpr_orga_array[first].data = datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_FPU_TO_INT reg
						gpr_orga_array[first].data = (unsigned)fpu_gpr_orga_array[second].data;	
	
	
	} else  if(action == ACTION_ADD) {

if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_ADD reg
			fpu_gpr_orga_array[first].data += datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_ADD reg
			fpu_gpr_orga_array[first].data += fpu_gpr_orga_array[second].data;
			} else if(action == ACTION_SUB) {

if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_SUB reg
			fpu_gpr_orga_array[first].data -= datahardcoded;	
return;
}				
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_SUB reg
			fpu_gpr_orga_array[first].data -= fpu_gpr_orga_array[second].data;
			} else if(action == ACTION_INC) {
			chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,NODATA);

			// ACTION_INC reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data+1;
			} else if(action == ACTION_DEC) {
			chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,NODATA);

			// ACTION_DEC reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data-1;
			} else if(action == ACTION_DISP_REG) {
				// c'est l'hypothèse dans laquelle un GPR se voit attribuer une valeur arbitraire
			chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			fpu_gpr_orga_array[first].data = datahardcoded;
			
			} else if(action == ACTION_DIVUNSIGNED) {
				
if(datahardcoded != NODATA) {

chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_DIVUNSIGNED
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data /  datahardcoded;
return;
}				
				
			chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
//ACTION_DIVUNSIGNED
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data /  fpu_gpr_orga_array[second].data;
			}else if(action == ACTION_DIVSIGNED) {
if(datahardcoded != NODATA) {

chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_UNSIGNED
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data /  datahardcoded;
return;			
}				
			chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
//ACTION_UNSIGNED
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data /  fpu_gpr_orga_array[second].data;
			} else if(action == ACTION_MULSIGNED) {
if(datahardcoded != NODATA) {
chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_MULSIGNED
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data * datahardcoded;
return;
}				
			chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
//ACTION_MULSIGNED
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data * fpu_gpr_orga_array[second].data;
			} else if(action == ACTION_MULUNSIGNED) {
if(datahardcoded != NODATA) {
chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);
//ACTION_MULSIGNED
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data * datahardcoded;
return;
}				
			chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
//ACTION_MULUNSIGNED
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[first].data * fpu_gpr_orga_array[second].data;
			} else if(action == ACTION_DISP_REG_COPY) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_DISP_REG_COPY reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data ;
			} 
		 
		
		 break;
		case POWERPC_LITTLENDIAN_IMAGE: 
		
		
		
		
 if(action == ACTION_FPU_TO_INT) {

if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_FPU_TO_INT reg
			gpr_orga_array[first].data = datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_FPU_TO_INT reg
						gpr_orga_array[first].data = fpu_gpr_orga_array[second].data;

}			else  if(action == ACTION_FPU_TO_INTUNSIGNED) {
if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_FPU_TO_INT reg
			gpr_orga_array[first].data = datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_FPU_TO_INT reg
						gpr_orga_array[first].data = (unsigned)fpu_gpr_orga_array[second].data;	
	
	
	} else		 if(action == ACTION_ADD) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_ADD reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data +  fpu_gpr_orga_array[third].data;
			} else if(action == ACTION_SUB) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data - fpu_gpr_orga_array[third].data;
			} else if(action == ACTION_DISP_REG_COPY) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_DISP_REG_COPY reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data ;
			} else if(action == ACTION_DISP_REG) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_DISP_REG reg
			fpu_gpr_orga_array[first].data = datahardcoded ;
			}else if(action == ACTION_DIV) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_DIV reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data / fpu_gpr_orga_array[third].data;
			} else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPRIGHT reg
			fpu_gpr_orga_array[first].data = bswap_64(fpu_gpr_orga_array[second].data);
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPLEFT reg
			fpu_gpr_orga_array[first].data = bswap_64(fpu_gpr_orga_array[second].data);
			}





		case ARM_64: {
			
	 if(action == ACTION_FPU_TO_INT) {

if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_FPU_TO_INT reg
			gpr_orga_array[first].data = datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_FPU_TO_INT reg
						gpr_orga_array[first].data = fpu_gpr_orga_array[second].data;

}			else  if(action == ACTION_FPU_TO_INTUNSIGNED) {
if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_FPU_TO_INT reg
			gpr_orga_array[first].data = datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_FPU_TO_INT reg
						gpr_orga_array[first].data = (unsigned)fpu_gpr_orga_array[second].data;	
	
	
	} else		 if(action == ACTION_ADD) {

		if(datahardcoded != NODATA) {
chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_ADD reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data +  datahardcoded;
return;
}				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_ADD reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data +  fpu_gpr_orga_array[third].data;
			} else if(action == ACTION_SUB) {
				
			if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_SUB reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data - datahardcoded;
return;
}			
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data - fpu_gpr_orga_array[third].data;
			} else if(action == ACTION_DISP_REG_COPY) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_DISP_REG_COPY reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data ;
			} else if(action == ACTION_DISP_REG) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_DISP_REG reg
			fpu_gpr_orga_array[first].data = datahardcoded ;
			}else if(action == ACTION_DIV) {
				
		if(datahardcoded != NODATA) {
chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_DIV reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data / datahardcoded;
return;
}				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_DIV reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data / fpu_gpr_orga_array[third].data;
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPRIGHT reg
			fpu_gpr_orga_array[first].data = bswap_64(fpu_gpr_orga_array[second].data);
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPLEFT reg
			fpu_gpr_orga_array[first].data = bswap_64(fpu_gpr_orga_array[second].data);
			} else if(action == ACTION_MULNORMAL) {
				
		if(datahardcoded != NODATA) {

return;
}
							chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_MULNORMAL reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data *  fpu_gpr_orga_array[third].data;
			} 
			
			
	}
		break;
		case RISCV : {
			
		
 if(action == ACTION_FPU_TO_INT) {

if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_FPU_TO_INT reg
			gpr_orga_array[first].data = datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_FPU_TO_INT reg
						gpr_orga_array[first].data = fpu_gpr_orga_array[second].data;

}			else  if(action == ACTION_FPU_TO_INTUNSIGNED) {
if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_FPU_TO_INT reg
			gpr_orga_array[first].data = datahardcoded;
return;
}	
				
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_FPU_TO_INT reg
						gpr_orga_array[first].data = (unsigned)fpu_gpr_orga_array[second].data;	
	
	
	} else		if(action == ACTION_ADD) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_ADD reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data +  fpu_gpr_orga_array[third].data;
			} else if(action == ACTION_SUB) {
		if(datahardcoded != NODATA) {
chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_SUB reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data - datahardcoded;
return;
}
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_SUB reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data - fpu_gpr_orga_array[third].data;
			} else if(action == ACTION_DISP_REG_COPY) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);

			// ACTION_DISP_REG_COPY reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data ;
			} else if(action == ACTION_DISP_REG) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],(void*)0,(void*)0,datahardcoded);

			// ACTION_DISP_REG reg
			fpu_gpr_orga_array[first].data = datahardcoded ;
			}else if(action == ACTION_DIV) {
				if(datahardcoded != NODATA) {
chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,datahardcoded);

			
fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data / datahardcoded;					
					
				} else {
				
chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_DIV reg
			
fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data / fpu_gpr_orga_array[third].data;
		}
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPRIGHT reg
			fpu_gpr_orga_array[first].data = bswap_64(fpu_gpr_orga_array[second].data);
			}	 else if(action == ACTION_BSWAPRIGHT) {
						chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,NODATA);
			// ACTION_BSWAPLEFT reg
			fpu_gpr_orga_array[first].data = bswap_64(fpu_gpr_orga_array[second].data);
			} else if(action == ACTION_MULNORMAL) {
					if(datahardcoded != NODATA) {
	chiara_check_gpr_fpu(&fpu_gpr_orga_array[first],&fpu_gpr_orga_array[second],(void*)0,datahardcoded);

			// ACTION_MULNORMAL reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data *  datahardcoded;

return;
}			
				
							chiara_check_gpr_fpu(&fpu_gpr_orga_array[second],&fpu_gpr_orga_array[third],(void*)0,NODATA);

			// ACTION_MULNORMAL reg
			fpu_gpr_orga_array[first].data = fpu_gpr_orga_array[second].data *  fpu_gpr_orga_array[third].data;
			}			
			
			
}
	
		case POWERPC_BIGNDIAN_IMAGE: break;
		
		}

}
/* Memory support here*/



struct thechiara_pagination {

long long from;
long long to;

struct 	thechiara_pagination * next;
	
};
 struct chiara_x86_cr3
 {
  unsigned long unused          :3;
   unsigned long write :1; /*  */
   unsigned long cache:1; 
   unsigned long unused2          :7; 
  unsigned long pd_paddr       :20;
 } __attribute__ ((packed));
struct chiara_x86_page_directory {
	
	 unsigned long  present        :1; /* 1=PT mapped */
  unsigned long  write          :1; /* 0=read-only, 1=read/write */
   unsigned long  user           :1; /* 0=supervisor, 1=user */
  unsigned long  write_through  :1; /* 0=write-back, 1=write-through */
   unsigned long  cache_disabled :1; /* 1=cache disabled */
   unsigned long  accessed       :1; /* 1=read/write access since last clear */
   unsigned long  zero           :1; /* Intel reserved */
   unsigned long  page_size      :1; /* 0=4kB, 1=4MB or 2MB (depending on PAE) */
  unsigned long  unused    :1; 
   unsigned long  custom         :3;
	
unsigned long adressptr:20;
	
};


/* 
 * the main function for modifying paging / interrupt etc on all targets !
 * */
void chiara_action_internal(unsigned long first,unsigned long second,unsigned long third,unsigned long action,unsigned long architecture,long long datahardcoded) {

switch (action) {
	
	case ACTION_X86_CR3: {
		printf("INFO: An instruction wants to modify the thechiara pagination/memory/interrupt configuration \n");
		// x86  first =cr second = reg where modif 
		
		struct chiara_x86_page_directory * chiara_x86_page_directorytmp;
		struct chiara_x86_cr3 * chiara_x86_cr3tmp;
		chiara_x86_cr3tmp = (struct chiara_x86_cr3 *) &gpr_orga_array[second];
		
		printf("INFO:chiara_x86_cr3 addr in mem of page directory %x \n ",chiara_x86_cr3tmp->pd_paddr);
		
		break;
		}
	
	default :
		break;
	
	}

}
