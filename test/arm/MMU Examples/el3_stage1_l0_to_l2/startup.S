//==================================================================
// Armv8-A example - Minimal EL3 MMU set up example
//
// Copyright (C) Arm Limited, 2019 All rights reserved.
//
// The example code is provided to you as an aid to learning when working
// with Arm-based technology, including but not limited to programming tutorials.
// Arm hereby grants to you, subject to the terms and conditions of this Licence,
// a non-exclusive, non-transferable, non-sub-licensable, free-of-charge licence,
// to use and copy the Software solely for the purpose of demonstration and
// evaluation.
//
// You accept that the Software has not been tested by Arm therefore the Software
// is provided �as is�, without warranty of any kind, express or implied. In no
// event shall the authors or copyright holders be liable for any claim, damages
// or other liability, whether in action or contract, tort or otherwise, arising
// from, out of or in connection with the Software or the use of Software.
//==================================================================

// Build commands:
// armclang -gdwarf-3 -c --target=aarch64-arm-none-eabi startup.s

  .section  BOOT,"ax"
  .align 3

// ------------------------------------------------------------

.equ Mode_USR, 0x10

.equ AArch32_Mode_USR,     0x10
.equ AArch32_Mode_FIQ,     0x11
.equ AArch32_Mode_IRQ,     0x12
.equ AArch32_Mode_SVC,     0x13
.equ AArch32_Mode_ABT,     0x17
.equ AArch32_Mode_UNDEF,   0x1B
.equ AArch32_Mode_SYS,     0x1F
.equ AArch32_Mode_HYP,     0x1A
.equ AArch32_Mode_MON,     0x16

.equ AArch64_EL2_SP2,      0x09    // EL2h
.equ AArch64_EL2_SP0,      0x08    // EL2t
.equ AArch64_EL1_SP1,      0x05    // EL1h
.equ AArch64_EL1_SP0,      0x04    // EL1t
.equ AArch64_EL0_SP0,      0x00

.equ AArch32_State_Thumb,  0x20
.equ AArch32_State_ARM,    0x00

// ------------------------------------------------------------

.equ TT_S1_TABLE,          0x00000000000000003    // NSTable=0, PXNTable=0, UXNTable=0, APTable=0

// TT block entries templates   (L1 and L2, NOT L3)
// Assuming table contents:
// 0 = b01000100 = Normal, Inner/Outer Non-Cacheable
// 1 = b11111111 = Normal, Inner/Outer WB/WA/RA
// 2 = b00000000 = Device-nGnRnE
.equ TT_S1_FAULT,           0x0
.equ TT_S1_NORMAL_NO_CACHE, 0x00000000000000401    // Index = 0, AF=1
.equ TT_S1_NORMAL_WBWA,     0x00000000000000405    // Index = 1, AF=1
.equ TT_S1_DEVICE_nGnRnE,   0x00600000000000409    // Index = 2, AF=1, PXN=1, UXN=1

.equ TT_S1_UXN,             (1 << 54)
.equ TT_S1_PXN,             (1 << 53)
.equ TT_S1_nG,              (1 << 11)
.equ TT_S1_NS,              (1 << 5)

.equ TT_S1_NON_SHARED,      (0 << 8)               // Non-shareable
.equ TT_S1_INNER_SHARED,    (3 << 8)               // Inner-shareable
.equ TT_S1_OUTER_SHARED,    (2 << 8)               // Outer-shareable

.equ TT_S1_PRIV_RW,         (0x0)
.equ TT_S1_PRIV_RO,         (0x2 << 6)
.equ TT_S1_USER_RW,         (0x1 << 6)
.equ TT_S1_USER_RO,         (0x3 << 6)

// ------------------------------------------------------------

  .global start64
  .type start64, @function
start64:

  // Clear registers
  // ---------------
  // This is primarily for RTL simulators, to avoid
  // possibility of X propergation
  MOV      x0, #0
  MOV      x1, #0
  MOV      x2, #0
  MOV      x3, #0
  MOV      x4, #0
  MOV      x5, #0
  MOV      x6, #0
  MOV      x7, #0
  MOV      x8, #0
  MOV      x9, #0
  MOV      x10, #0
  MOV      x11, #0
  MOV      x12, #0
  MOV      x13, #0
  MOV      x14, #0
  MOV      x15, #0
  MOV      x16, #0
  MOV      x17, #0
  MOV      x18, #0
  MOV      x19, #0
  MOV      x20, #0
  MOV      x21, #0
  MOV      x22, #0
  MOV      x23, #0
  MOV      x24, #0
  MOV      x25, #0
  MOV      x26, #0
  MOV      x27, #0
  MOV      x28, #0
  MOV      x29, #0
  MOV      x30, #0
  
  // Which core am I
  // ----------------
  MRS      x0, MPIDR_EL1
  AND      x0, x0, #0xFF                     // Mask off to leave Aff0
  CBZ      x0, primary                       // If core 0, run the primary init
  B        secondary                         // Else, run secondary init

// ------------------------------------------------------------
// Primary core
// ------------------------------------------------------------

primary:


  // Disable trapping of CPTR_EL3 accesses or use of Adv.SIMD/FPU
  // -------------------------------------------------------------
  MSR      CPTR_EL3, xzr


  // Configure SCR_EL3
  // ------------------
  MOV      x0, #1                           // NS=1
  ORR      x0, x0, #(1 << 1)                // IRQ=1         IRQs routed to EL3
  ORR      x0, x0, #(1 << 2)                // FIQ=1         FIQs routed to EL3
  ORR      x0, x0, #(1 << 3)                // EA=1          SError routed to EL3
  ORR      x0, x0, #(1 << 8)                // HCE=1         HVC instructions are enabled
  ORR      x0, x0, #(1 << 10)               // RW=1          Next EL down uses AArch64
  ORR      x0, x0, #(1 << 11)               // ST=1          Secure EL1 can access CNTPS_TVAL_EL1, CNTPS_CTL_EL1 & CNTPS_CVAL_EL1
                                            // SIF=0         Secure state instruction fetches from Non-secure memory are permitted
                                            // SMD=0         SMC instructions are enabled
                                            // TWI=0         EL2, EL1 and EL0 execution of WFI instructions is not trapped to EL3
                                            // TWE=0         EL2, EL1 and EL0 execution of WFE instructions is not trapped to EL3
  MSR      SCR_EL3, x0


  // Install dummy vector table
  // ---------------------------
  LDR      x0, =vector_table
  MSR      VBAR_EL3, x0
  MSR      VBAR_EL2, x0
  MSR      VBAR_EL1, x0


  //
  //
  // MMU setup
  //
  //


  // Set the Base address
  // ---------------------
  LDR      x0, =tt_l0_base                  // Get address of level 1 for TTBR0_EL3
  MSR      TTBR0_EL3, x0                    // Set TTBR0_EL3 (NOTE: There is no TTBR1 at EL3)


  // Set up memory attributes
  // -------------------------
  // This equates to:
  // 0 = b01000100 = Normal, Inner/Outer Non-Cacheable
  // 1 = b11111111 = Normal, Inner/Outer WB/WA/RA
  // 2 = b00000000 = Device-nGnRnE
  MOV      x0, #0x000000000000FF44
  MSR      MAIR_EL3, x0


  // Set up TCR_EL3
  // ---------------
  MOV      x0, #16                          // T0SZ=0b011001 Limits VA space to 48 bits, translation starts @ l0
  ORR      x0, x0, #(0x1 << 8)              // IGRN0=0b01    Walks to TTBR0 are Inner WB/WA
  ORR      x0, x0, #(0x1 << 10)             // OGRN0=0b01    Walks to TTBR0 are Outer WB/WA
  ORR      x0, x0, #(0x3 << 12)             // SH0=0b11      Inner Shareable
  MOV      x1, #(0x5 << 16)
  ORR      x0, x0, x1                       // IPS=0b101     32-bit PA space
                                            // TBI0=0b0      Top byte not ignored
                                            // TG0=0b00      4KB granule
  MSR      TCR_EL3, x0


  // Ensure changes to system register are visible before MMU enabled
  ISB
  

  // Invalidate TLBs
  // ----------------
  TLBI     ALLE3
  DSB      SY
  ISB


  //
  // This example has a 4 entry L1 table, which points at four contigous L2 tables.
  // Allowing the L2 table to be treated as a single table.
  //

  // Generate Translation Table
  // ---------------------------

  //
  // Populate L0 table with pointer to L1 table
  //
  LDR      x0, =tt_l0_base                    // Address of L0 table
  LDR      x1, =tt_l1_base                    // Address of first L1 table

  LDR      x2, =TT_S1_TABLE                   // Entry template
  ORR      x2, x2, x1                         // Combine template with L1 table Base address
  STR      x2, [x0, #0]                       // Write template into entry table[0]

  // NOTE: The way the space for the tables is reserved pre-fills it with zeros
  // When loading the image into a simulation this saves time.  On real hardware
  // you would want a zeroing loop.

  // We now have an L0 table, with the following entries:
  // [0] = Pointer to L1 table
  // [*] = Fault

  //
  // Populate L1 table with pointers to L2 tables
  //
  // This L1 table covers VAs 0x0-0x0000_007F_FFFF_FFFF

  LDR      x0, =tt_l1_base                    // Address of L1 table
  LDR      x1, =tt_l2_base                    // Address of first L2 table

  LDR      x2, =TT_S1_TABLE                   // Entry template
  ORR      x2, x2, x1                         // Combine template with L2 table Base address
  STR      x2, [x0, #0]                       // Write template into entry table[0]
  ADD      x2, x2, #0x1000                    // Move pointer on to the next table in memory
  STR      x2, [x0, #8]                       // Write template into entry table[1]
  ADD      x2, x2, #0x1000
  STR      x2, [x0, #16]                      // Write template into entry table[2]
  ADD      x2, x2, #0x1000
  STR      x2, [x0, #24]                      // Write template into entry table[3]

  // NOTE: The way the space for the table is reserved pre-fills it with zeros
  // When loading the image into a simulation this saves time.  On real hardware
  // you would want a zeroing loop.

  //
  // Now populate L2 table (strictly there are four, but they are placed back-to-back)
  //

  // NOTE: The way the space for the tables are reserved pre-fills it with zeros
  // When loading the image into a simulation this saves time.  On real hardware
  // you would want a zeroing loop.

  // The four L2 tables in this example map the first 4GB of address space @ 2MB granualrity.
  //  To map in a block:
  // x2 = VA >> 21    This gives you which table entry you need
  // x2 = x2 << 3     This gets multiplied by 8, as there are 8 bytes per entry, to give a byte offset
  // addr of entry = x2 + tt_l2_base

  LDR      x0, =tt_l2_base                    // Address of first L2 table

  // Now we're going to populate the entries we need
  // This example runs from address 0x8000_0000
  MOV      x1, #0x80000000
  LSR      x2, x1, #21                        // Work out which 2MB block this falls in (discard bottom 21 bits)
  LSL      x2, x2, #3                         // Now convert into a byte offset (8-bytes per entry)
  LDR      x3, =TT_S1_NORMAL_WBWA             // Load template entry
                                              // AP=0, RW
  ORR      x1, x1, x3                         // Combine template with address
  STR      x1, [x0, x2]                       // Store to base addr + byte offset

  DSB      SY


  // Enable MMU
  // -----------
  MOV      x0, #(1 << 0)                      // M=1 bit       Enable the stage 1 MMU
  ORR      x0, x0, #(1 << 2)                  // C=1 bit       Enable data and unified caches
  ORR      x0, x0, #(1 << 12)                 // I=1           Enable instruction fetches to allocate into unified caches
                                              // A=0           Strict alignment checking disabled
                                              // SA=0          Stack alignment checking disabled
                                              // WXN=0         Write permission does not imply XN
                                              // EE=0          EL3 data accesses are little endian
  MSR      SCTLR_EL3, x0
  ISB

  //
  // MMU is now enabled
  //

  NOP
  NOP
  NOP
  NOP

  // Semihosting exit
  MOV      w0, #0x18
  HLT      #0xf000

1:
  WFI
  B        1b


// ------------------------------------------------------------
// Secondary cores
// ------------------------------------------------------------

secondary:
  WFI
  B        secondary

// ------------------------------------------------------------
// Vector Table
// ------------------------------------------------------------

  .align 12

  .global vector_table
vector_table:

// ------------------------------------------------------------
// Current EL with SP0
// ------------------------------------------------------------
  .balign 128
sync_current_el_sp0:
  B        .                    //        Synchronous

  .balign 128
irq_current_el_sp0:
  B        .                    //        IRQ

  .balign 128
fiq_current_el_sp0:
  B        .                    //        FIQ

  .balign 128
serror_current_el_sp0:
  B        .                    //        SError

// ------------------------------------------------------------
// Current EL with SPx
// ------------------------------------------------------------

  .balign 128
sync_current_el_spx:
  B        .                    //        Synchronous

  .balign 128
irq_current_el_spx:
  B        .                    //        IRQ

  .balign 128
fiq_current_el_spx:
  B        .                    //        FIQ

  .balign 128
serror_current_el_spx:
  B        .                    //        SError

// ------------------------------------------------------------
// Lower EL using AArch64
// ------------------------------------------------------------

  .balign 128
sync_lower_el_aarch64:
   B        .                    

  .balign 128
irq_lower_el_aarch64:
  B        .                    //        IRQ

  .balign 128
fiq_lower_el_aarch64:
  B        .                    //        FIQ

  .balign 128
serror_lower_el_aarch64:
  B        .                    //        SError

// ------------------------------------------------------------
// Lower EL using AArch32
// ------------------------------------------------------------

  .balign 128
sync_lower_el_aarch32:
   B        .

  .balign 128
irq_lower_el_aarch32:
  B        .                    //        IRQ

  .balign 128
fiq_lower_el_aarch32:
  B        .                    //        FIQ

  .balign 128
serror_lower_el_aarch32:
  B        .                    //        SError


// ------------------------------------------------------------
// Translation tables
// ------------------------------------------------------------

  .section  TT,"ax"
  .align 12

  .global tt_l0_base
tt_l0_base:
  .fill 4096 , 1 , 0

// ------------------------------------------------------------

  .global tt_l1_base
tt_l1_base:
  .fill 4096 , 1 , 0

// ------------------------------------------------------------

  // Allocate space for 4 contigous L2 tables

  .global tt_l2_base
tt_l2_base:
  .fill 16384 , 1 , 0

// ------------------------------------------------------------
// End of file
// ------------------------------------------------------------

