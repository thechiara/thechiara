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
// 
	//~ struct chiara_compute_flags {
	
	//~ unsigned char equal;
	//~ unsigned char carry;
	//~ unsigned char overflow;
	//~ unsigned char zero;
	
	
	//~ };
//~ struct chiara_compute_global {
	//~ unsigned long register32[31];
	//~ unsigned long long register64[31];
	//~ unsigned short register16[31];
	//~ unsigned char register8[31];
	//~ long long *mem;// not used now 
	//~ unsigned long specialregister;
	//~ struct chiara_compute_flags flags;
	//~ };
	//~ struct chiara_compute_global global_struct;
void chiara_emul_bigendian_ppc(unsigned char *instruction,int size) ;
void chiara_emul_littleendian_ppc(unsigned char *instruction,int size);

void chiara_dos_header_look(unsigned char *file,unsigned long size);
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
