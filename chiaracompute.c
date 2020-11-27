
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

#include <chiaracompute.h>
#include <limits.h>

//~ void gaspard_clear_flags( ) {
			//~ global_struct.flags.equal =0;
			//~ global_struct.flags.carry =0;
			//~ global_struct.flags.overflow =0;

//~ }
//~ void gaspard_check_flags_result(long res) {
	//~ if(res<0) {
					//~ global_struct.flags.zero =1;

				//~ }
		//~ if (res & 1<< 31 ) {
			//~ global_struct.flags.carry =1;
			//~ global_struct.flags.overflow =1;

					//~ }
					
					 //~ if ( res < INT_MIN ||  res < INT_MIN) {			
				//~ global_struct.flags.overflow =1;
	//~ }
	
	//~ }
//~ void gaspard_check_flags( long a, long b) {
	//~ if(a==b) {
		//~ global_struct.flags.equal =1;
		
		//~ } else {
			
	//~ global_struct.flags.equal =0;

			//~ }
			
	//~ if(a<0) {
					//~ global_struct.flags.zero =1;

				//~ }
	//~ if(b<0) {
					//~ global_struct.flags.zero =1;

				//~ }
				
		//~ if (a & 1<< 31 == b & 1<< 31) {
			//~ global_struct.flags.carry =1;
			//~ global_struct.flags.overflow =1;

					//~ }
					
	 //~ if ( a < INT_MIN ||  b < INT_MIN) {			
				//~ global_struct.flags.overflow =1;
	//~ }
	//~ }

//~ void chiara_divide_by_zero_err(unsigned char s,unsigned char d) {
						//~ global_struct.flags.zero =1;

	//~ }
//~ void chiara_illegal_instruction(unsigned char s) {

	//~ }
  //~ void chiara_emul_add (unsigned char source, unsigned char destination) {
	 //~ gaspard_clear_flags();
	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);
//~ global_struct.register32[source] = global_struct.register32[source] + global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);
//~ }
  //~ void chiara_emul_mul (unsigned char source, unsigned char destination) {
	 //~ gaspard_clear_flags();
	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);
//~ global_struct.register32[source] = global_struct.register32[source] * global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);
//~ }
  //~ void chiara_emul_simul (unsigned char source, unsigned char destination) {
	 //~ gaspard_clear_flags();
	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);
//~ global_struct.register32[source] = (signed long) global_struct.register32[source] * (signed long) global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);
//~ }
  //~ void chiara_emul_div  (unsigned char source, unsigned char destination) {
	 //~ gaspard_clear_flags();
	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);
//~ global_struct.register32[source] = global_struct.register32[source] / global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);
//~ }
  //~ void chiara_emul_div_unsigned  (unsigned char source, unsigned char destination) {
	 //~ gaspard_clear_flags();
	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);
//~ global_struct.register32[source] = (unsigned long) global_struct.register32[source] /(unsigned long) global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);
//~ }
  //~ void chiara_emul_mod_unsigned  (unsigned char source, unsigned char destination) {
	 //~ gaspard_clear_flags();
	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);
//~ global_struct.register32[source] = (unsigned long) global_struct.register32[source]  %(unsigned long) global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);
//~ }
  //~ void chiara_emul_sub (unsigned char source, unsigned char destination) {
	  	 //~ gaspard_clear_flags();

	  	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] = global_struct.register32[source] - global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_mod (unsigned char source, unsigned char destination) {
		 //~ gaspard_clear_flags();

	  	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] = global_struct.register32[source] % global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_shift_left (unsigned char source, unsigned char destination) {
		 //~ gaspard_clear_flags();

	  	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] = global_struct.register32[source] << global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_shift_right (unsigned char source, unsigned char destination) {
			 //~ gaspard_clear_flags();

	  	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] = global_struct.register32[source] >> global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_shift_xor (unsigned char source, unsigned char destination) {
	  		 //~ gaspard_clear_flags();

	  	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] = global_struct.register32[source] ^ global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_or (unsigned char source, unsigned char destination) {
	  			 //~ gaspard_clear_flags();

	  	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] = global_struct.register32[source] | global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_and (unsigned char source, unsigned char destination) {
	  			 //~ gaspard_clear_flags();

	  	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] = global_struct.register32[source] & global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_not (unsigned char source, unsigned char destination) {
	 		 //~ gaspard_clear_flags();

	  	//~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] = global_struct.register32[source] & global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_load (unsigned char source, unsigned char destination) {
	  		 //~ gaspard_clear_flags();

//~ global_struct.register32[source] = global_struct.mem[global_struct.register32[destination]];


//~ }
  //~ void chiara_emul_load_absolute (unsigned char source, unsigned long destination) {
	  		 //~ gaspard_clear_flags();

//~ global_struct.register32[source] = global_struct.mem[destination];


//~ }
  //~ void chiara_emul_store_absolute (unsigned char source, unsigned long destination) {
	  		 //~ gaspard_clear_flags();

//~ global_struct.mem[destination] = global_struct.register32[source];


//~ }

  //~ void chiara_emul_store_array (unsigned char source, unsigned char destination) {
	  		 //~ gaspard_clear_flags();

//~ global_struct.mem[destination] = global_struct.register32[source] + (short)global_struct.mem[source];


//~ }
  //~ void chiara_emul_mov (unsigned char source, unsigned char destination) {
	  		 //~ gaspard_clear_flags();

//~ global_struct.register32[source] = global_struct.register32[destination];


//~ }
  //~ void chiara_emul_inc (unsigned char source) {
		 //~ gaspard_clear_flags();

//~ global_struct.register32[source]++;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_dec (unsigned char source) {
		 //~ gaspard_clear_flags();

//~ global_struct.register32[source]++;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
  //~ void chiara_emul_div (unsigned char source, unsigned char destination) {
		 //~ gaspard_clear_flags();

	  //~ if(global_struct.register32[global_struct.register32[destination]] == 0) {
		  
		  //~ chiara_divide_by_zero_err(source,destination);
		  //~ }
		  	  	  //~ gaspard_check_flags(global_struct.register32[source],global_struct.register32[destination]);

//~ global_struct.register32[source] =  global_struct.register32[source] & global_struct.register32[destination] ;
//~ gaspard_check_flags_result(global_struct.register32[source]);

//~ }
