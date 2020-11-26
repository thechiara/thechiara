
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
 #define IMAGE_NUMBEROF_DIRECTORY_ENTRIES        16
 struct dos_header {      // DOS  header
    unsigned short   e_magic;                     
   unsigned short   e_cblp;                    
  unsigned  short   e_cp;                        
 unsigned   short   e_crlc;                     
   unsigned short   e_cparhdr;                 
  unsigned  short   e_minalloc;                  
 unsigned   short   e_maxalloc;                 
   unsigned short   e_ss;                        
   unsigned short   e_sp;                        
   unsigned short   e_csum;                      
   unsigned short   e_ip;                       
   unsigned short   e_cs;                       
   unsigned short   e_lfarlc;                    
   unsigned short   e_ovno;                     
   unsigned short   e_res[4];                    
   unsigned short   e_oemid;                    
   unsigned short   e_oeminfo;                  
   unsigned short   e_res2[10];                 
    unsigned  short   e_lfanew;                    // File pointer of new exe header
  };
 struct _IMAGE_FILE_HEADER {
  unsigned short  Machine;
  unsigned short  NumberOfSections;
  unsigned  long TimeDateStamp;      
  unsigned  long PointerToSymbolTable;
  unsigned  long NumberOfSymbols;
  unsigned  short  SizeOfOptionalHeader;
  unsigned  short  Characteristics;
} ;
typedef struct _IMAGE_DATA_DIRECTORY {
	unsigned long VirtualAddress;
	unsigned long Size;
} IMAGE_DATA_DIRECTORY,*PIMAGE_DATA_DIRECTORY;
typedef struct _IMAGE_OPTIONAL_HEADER {
  unsigned  short                 Magic;
  unsigned  char                 MajorLinkerVersion;
  unsigned  char                 MinorLinkerVersion;
  unsigned  long                SizeOfCode;
  unsigned  long                SizeOfInitializedData;
  unsigned  long                SizeOfUninitializedData;
  unsigned  long                AddressOfEntryPoint;
  unsigned  long                BaseOfCode;
  unsigned  long                BaseOfData;
  unsigned  long                ImageBase;
  unsigned  long                SectionAlignment;
  unsigned  long                FileAlignment;
  unsigned  short                 MajorOperatingSystemVersion;
  unsigned  short                 MinorOperatingSystemVersion;
  unsigned  short                 MajorImageVersion;
  unsigned  short                 MinorImageVersion;
  unsigned  short                 MajorSubsystemVersion;
  unsigned  short                 MinorSubsystemVersion;
  unsigned  long                Win32VersionValue;
  unsigned  long                SizeOfImage;
  unsigned  long                SizeOfHeaders;
  unsigned  long                CheckSum;
  unsigned  short                 Subsystem;
  unsigned  short                 DllCharacteristics;
  unsigned  long                SizeOfStackReserve;
  unsigned  long                SizeOfStackCommit;
  unsigned  long                SizeOfHeapReserve;
  unsigned  long                SizeOfHeapCommit;
  unsigned  long                LoaderFlags;
  unsigned  long                NumberOfRvaAndSizes;
 struct  _IMAGE_DATA_DIRECTORY DataDirectory[16];
} ;
 struct _IMAGE_NT_HEADERS {
  unsigned  long                 Signature;
  struct _IMAGE_FILE_HEADER     FileHeader;
 struct  _IMAGE_OPTIONAL_HEADER OptionalHeader;
} ;

