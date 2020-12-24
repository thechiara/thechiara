/*
 * riscv.c is a concat of riscv-dis.c and riscv-opc.c from binutils libopcodes
 *    Copyright (C) 2011-2020 Free Software Foundation, Inc.
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
 




#include "opcode/riscv.h"
#include <stdio.h>
#include <string.h>
#include <chiaracore.h>

  unsigned long *pointer_riscv;

//https://github.com/riscv/riscv-asm-manual/blob/master/riscv-asm.md -> good link because the riscv docs sucks
/* Register names used by gas and objdump.  */
struct disassemble_info {
	
	
int UNUSED;	
};
const char * const riscv_gpr_names_numeric[NGPR] =
{
  "x0",   "x1",   "x2",   "x3",   "x4",   "x5",   "x6",   "x7",
  "x8",   "x9",   "x10",  "x11",  "x12",  "x13",  "x14",  "x15",
  "x16",  "x17",  "x18",  "x19",  "x20",  "x21",  "x22",  "x23",
  "x24",  "x25",  "x26",  "x27",  "x28",  "x29",  "x30",  "x31"
};

const char * const riscv_gpr_names_abi[NGPR] = {
  "zero", "ra", "sp",  "gp",  "tp", "t0",  "t1",  "t2",
  "s0",   "s1", "a0",  "a1",  "a2", "a3",  "a4",  "a5",
  "a6",   "a7", "s2",  "s3",  "s4", "s5",  "s6",  "s7",
  "s8",   "s9", "s10", "s11", "t3", "t4",  "t5",  "t6"
};

const char * const riscv_fpr_names_numeric[NFPR] =
{
  "f0",   "f1",   "f2",   "f3",   "f4",   "f5",   "f6",   "f7",
  "f8",   "f9",   "f10",  "f11",  "f12",  "f13",  "f14",  "f15",
  "f16",  "f17",  "f18",  "f19",  "f20",  "f21",  "f22",  "f23",
  "f24",  "f25",  "f26",  "f27",  "f28",  "f29",  "f30",  "f31"
};

const char * const riscv_fpr_names_abi[NFPR] = {
  "ft0", "ft1", "ft2",  "ft3",  "ft4", "ft5", "ft6",  "ft7",
  "fs0", "fs1", "fa0",  "fa1",  "fa2", "fa3", "fa4",  "fa5",
  "fa6", "fa7", "fs2",  "fs3",  "fs4", "fs5", "fs6",  "fs7",
  "fs8", "fs9", "fs10", "fs11", "ft8", "ft9", "ft10", "ft11"
};

static const char * _(const char *str) {
	
return str;	
}

/* The order of overloaded instructions matters.  Label arguments and
   register arguments look the same. Instructions that can have either
   for arguments must apear in the correct order in this table for the
   assembler to pick the right one. In other words, entries with
   immediate operands must apear after the same instruction with
   registers.

   Because of the lookup algorithm used, entries with the same opcode
   name must be contiguous.  */

#define MASK_RS1 (OP_MASK_RS1 << OP_SH_RS1)
#define MASK_RS2 (OP_MASK_RS2 << OP_SH_RS2)
#define MASK_RD (OP_MASK_RD << OP_SH_RD)
#define MASK_CRS2 (OP_MASK_CRS2 << OP_SH_CRS2)
#define MASK_IMM ENCODE_ITYPE_IMM (-1U)
#define MASK_RVC_IMM ENCODE_RVC_IMM (-1U)
#define MASK_UIMM ENCODE_UTYPE_IMM (-1U)
#define MASK_RM (OP_MASK_RM << OP_SH_RM)
#define MASK_PRED (OP_MASK_PRED << OP_SH_PRED)
#define MASK_SUCC (OP_MASK_SUCC << OP_SH_SUCC)
#define MASK_AQ (OP_MASK_AQ << OP_SH_AQ)
#define MASK_RL (OP_MASK_RL << OP_SH_RL)
#define MASK_AQRL (MASK_AQ | MASK_RL)

static int
match_opcode (const struct riscv_opcode *op, insn_t insn)
{
  return ((insn ^ op->match) & op->mask) == 0;
}

static int
match_never (const struct riscv_opcode *op __attribute__((unused)),
	     insn_t insn __attribute__((unused)))
{
  return 0;
}

static int
match_rs1_eq_rs2 (const struct riscv_opcode *op, insn_t insn)
{
  int rs1 = (insn & MASK_RS1) >> OP_SH_RS1;
  int rs2 = (insn & MASK_RS2) >> OP_SH_RS2;
  return match_opcode (op, insn) && rs1 == rs2;
}

static int
match_rd_nonzero (const struct riscv_opcode *op, insn_t insn)
{
  return match_opcode (op, insn) && ((insn & MASK_RD) != 0);
}

static int
match_c_add (const struct riscv_opcode *op, insn_t insn)
{
  return match_rd_nonzero (op, insn) && ((insn & MASK_CRS2) != 0);
}

/* We don't allow mv zero,X to become a c.mv hint, so we need a separate
   matching function for this.  */

static int
match_c_add_with_hint (const struct riscv_opcode *op, insn_t insn)
{
  return match_opcode (op, insn) && ((insn & MASK_CRS2) != 0);
}

static int
match_c_nop (const struct riscv_opcode *op, insn_t insn)
{
  return (match_opcode (op, insn)
	  && (((insn & MASK_RD) >> OP_SH_RD) == 0));
}

static int
match_c_addi16sp (const struct riscv_opcode *op, insn_t insn)
{
  return (match_opcode (op, insn)
	  && (((insn & MASK_RD) >> OP_SH_RD) == 2)
	  && EXTRACT_RVC_ADDI16SP_IMM (insn) != 0);
}

static int
match_c_lui (const struct riscv_opcode *op, insn_t insn)
{
  return (match_rd_nonzero (op, insn)
	  && (((insn & MASK_RD) >> OP_SH_RD) != 2)
	  && EXTRACT_RVC_LUI_IMM (insn) != 0);
}

/* We don't allow lui zero,X to become a c.lui hint, so we need a separate
   matching function for this.  */

static int
match_c_lui_with_hint (const struct riscv_opcode *op, insn_t insn)
{
  return (match_opcode (op, insn)
	  && (((insn & MASK_RD) >> OP_SH_RD) != 2)
	  && EXTRACT_RVC_LUI_IMM (insn) != 0);
}

static int
match_c_addi4spn (const struct riscv_opcode *op, insn_t insn)
{
  return match_opcode (op, insn) && EXTRACT_RVC_ADDI4SPN_IMM (insn) != 0;
}

/* This requires a non-zero shift.  A zero rd is a hint, so is allowed.  */

static int
match_c_slli (const struct riscv_opcode *op, insn_t insn)
{
  return match_opcode (op, insn) && EXTRACT_RVC_IMM (insn) != 0;
}

/* This requires a non-zero rd, and a non-zero shift.  */

static int
match_slli_as_c_slli (const struct riscv_opcode *op, insn_t insn)
{
  return match_rd_nonzero (op, insn) && EXTRACT_RVC_IMM (insn) != 0;
}

/* This requires a zero shift.  A zero rd is a hint, so is allowed.  */

static int
match_c_slli64 (const struct riscv_opcode *op, insn_t insn)
{
  return match_opcode (op, insn) && EXTRACT_RVC_IMM (insn) == 0;
}

/* This is used for both srli and srai.  This requires a non-zero shift.
   A zero rd is not possible.  */

static int
match_srxi_as_c_srxi (const struct riscv_opcode *op, insn_t insn)
{
  return match_opcode (op, insn) && EXTRACT_RVC_IMM (insn) != 0;
}

const struct riscv_opcode riscv_opcodes[] =
{
/* name,     xlen, isa,   operands, match, mask, match_func, pinfo.  */
{"unimp",       0, INSN_CLASS_C,   "",  0, 0xffffU,  match_opcode, INSN_ALIAS },
{"unimp",       0, INSN_CLASS_I,   "",  MATCH_CSRRW | (CSR_CYCLE << OP_SH_CSR), 0xffffffffU,  match_opcode, 0 }, /* csrw cycle, x0 */
{"ebreak",      0, INSN_CLASS_C,   "",  MATCH_C_EBREAK, MASK_C_EBREAK, match_opcode, INSN_ALIAS },
{"ebreak",      0, INSN_CLASS_I,   "",    MATCH_EBREAK, MASK_EBREAK, match_opcode, 0 },
{"sbreak",      0, INSN_CLASS_C,   "",  MATCH_C_EBREAK, MASK_C_EBREAK, match_opcode, INSN_ALIAS },
{"sbreak",      0, INSN_CLASS_I,   "",    MATCH_EBREAK, MASK_EBREAK, match_opcode, INSN_ALIAS },
{"ret",         0, INSN_CLASS_C,   "",  MATCH_C_JR | (X_RA << OP_SH_RD), MASK_C_JR | MASK_RD, match_opcode, INSN_ALIAS|INSN_BRANCH },
{"ret",         0, INSN_CLASS_I,   "",  MATCH_JALR | (X_RA << OP_SH_RS1), MASK_JALR | MASK_RD | MASK_RS1 | MASK_IMM, match_opcode, INSN_ALIAS|INSN_BRANCH },
{"jr",          0, INSN_CLASS_C,   "d",  MATCH_C_JR, MASK_C_JR, match_rd_nonzero, INSN_ALIAS|INSN_BRANCH  , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG_COPY  },
{"jr",          0, INSN_CLASS_I,   "s",  MATCH_JALR, MASK_JALR | MASK_RD | MASK_IMM, match_opcode, INSN_ALIAS|INSN_BRANCH , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG   },
{"jr",          0, INSN_CLASS_I,   "o(s)",  MATCH_JALR, MASK_JALR | MASK_RD, match_opcode, INSN_ALIAS|INSN_BRANCH , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG   },
{"jr",          0, INSN_CLASS_I,   "s,j",  MATCH_JALR, MASK_JALR | MASK_RD, match_opcode, INSN_ALIAS|INSN_BRANCH  , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG  },
{"jalr",        0, INSN_CLASS_C,   "d",  MATCH_C_JALR, MASK_C_JALR, match_rd_nonzero, INSN_ALIAS|INSN_JSR },
{"jalr",        0, INSN_CLASS_I,   "s",  MATCH_JALR | (X_RA << OP_SH_RD), MASK_JALR | MASK_RD | MASK_IMM, match_opcode, INSN_ALIAS|INSN_JSR },
{"jalr",        0, INSN_CLASS_I,   "o(s)",  MATCH_JALR | (X_RA << OP_SH_RD), MASK_JALR | MASK_RD, match_opcode, INSN_ALIAS|INSN_JSR },
{"jalr",        0, INSN_CLASS_I,   "s,j",  MATCH_JALR | (X_RA << OP_SH_RD), MASK_JALR | MASK_RD, match_opcode, INSN_ALIAS|INSN_JSR },
{"jalr",        0, INSN_CLASS_I,   "d,s",  MATCH_JALR, MASK_JALR | MASK_IMM, match_opcode, INSN_ALIAS|INSN_JSR },
{"jalr",        0, INSN_CLASS_I,   "d,o(s)",  MATCH_JALR, MASK_JALR, match_opcode, INSN_JSR },
{"jalr",        0, INSN_CLASS_I,   "d,s,j",  MATCH_JALR, MASK_JALR, match_opcode, INSN_JSR },
{"j",           0, INSN_CLASS_C,   "Ca",  MATCH_C_J, MASK_C_J, match_opcode, INSN_ALIAS|INSN_BRANCH },
{"j",           0, INSN_CLASS_I,   "a",  MATCH_JAL, MASK_JAL | MASK_RD, match_opcode, INSN_ALIAS|INSN_BRANCH },
{"jal",         0, INSN_CLASS_I,   "d,a",  MATCH_JAL, MASK_JAL, match_opcode, INSN_JSR },
{"jal",        32, INSN_CLASS_C,   "Ca",  MATCH_C_JAL, MASK_C_JAL, match_opcode, INSN_ALIAS|INSN_JSR },
{"jal",         0, INSN_CLASS_I,   "a",  MATCH_JAL | (X_RA << OP_SH_RD), MASK_JAL | MASK_RD, match_opcode, INSN_ALIAS|INSN_JSR },
{"call",        0, INSN_CLASS_I,   "d,c", (X_T1 << OP_SH_RS1), (int) M_CALL,  match_never, INSN_MACRO },
{"call",        0, INSN_CLASS_I,   "c", (X_RA << OP_SH_RS1) | (X_RA << OP_SH_RD), (int) M_CALL,  match_never, INSN_MACRO },
{"tail",        0, INSN_CLASS_I,   "c", (X_T1 << OP_SH_RS1), (int) M_CALL,  match_never, INSN_MACRO },
{"jump",        0, INSN_CLASS_I,   "c,s", 0, (int) M_CALL,  match_never, INSN_MACRO },
{"nop",         0, INSN_CLASS_C,   "",  MATCH_C_ADDI, 0xffff, match_opcode, INSN_ALIAS },
{"nop",         0, INSN_CLASS_I,   "",         MATCH_ADDI, MASK_ADDI | MASK_RD | MASK_RS1 | MASK_IMM, match_opcode, INSN_ALIAS },
{"lui",         0, INSN_CLASS_C,   "d,Cu",  MATCH_C_LUI, MASK_C_LUI, match_c_lui, INSN_ALIAS },
{"lui",         0, INSN_CLASS_I,   "d,u",  MATCH_LUI, MASK_LUI, match_opcode, 0 },
{"li",          0, INSN_CLASS_C,   "d,Cv",  MATCH_C_LUI, MASK_C_LUI, match_c_lui, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG },
{"li",          0, INSN_CLASS_C,   "d,Co",  MATCH_C_LI, MASK_C_LI, match_rd_nonzero, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG },
{"li",          0, INSN_CLASS_I,   "d,j",      MATCH_ADDI, MASK_ADDI | MASK_RS1, match_opcode, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG}, /* addi */
{"li",          0, INSN_CLASS_I,   "d,I",  0,    (int) M_LI,  match_never, INSN_MACRO, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG },
{"mv",          0, INSN_CLASS_C,   "d,CV",  MATCH_C_MV, MASK_C_MV, match_c_add, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG_COPY },
{"mv",          0, INSN_CLASS_I,   "d,s",  MATCH_ADDI, MASK_ADDI | MASK_IMM, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG_COPY },
{"move",        0, INSN_CLASS_C,   "d,CV",  MATCH_C_MV, MASK_C_MV, match_c_add, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG_COPY},
{"move",        0, INSN_CLASS_I,   "d,s",  MATCH_ADDI, MASK_ADDI | MASK_IMM, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG_COPY },
{"andi",        0, INSN_CLASS_C,   "Cs,Cw,Co",  MATCH_C_ANDI, MASK_C_ANDI, match_opcode, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_AND  }, /* GPR[0],GPR[1] & data */
{"andi",        0, INSN_CLASS_I,   "d,s,j",  MATCH_ANDI, MASK_ANDI, match_opcode, 0 , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_AND   },
{"and",         0, INSN_CLASS_C,   "Cs,Cw,Ct",  MATCH_C_AND, MASK_C_AND, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_AND  },
{"and",         0, INSN_CLASS_C,   "Cs,Ct,Cw",  MATCH_C_AND, MASK_C_AND, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_AND  },
{"and",         0, INSN_CLASS_C,   "Cs,Cw,Co",  MATCH_C_ANDI, MASK_C_ANDI, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_AND  },
{"and",         0, INSN_CLASS_I,   "d,s,t",  MATCH_AND, MASK_AND, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_AND  },
{"and",         0, INSN_CLASS_I,   "d,s,j",  MATCH_ANDI, MASK_ANDI, match_opcode, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_AND },
{"beqz",        0, INSN_CLASS_C,   "Cs,Cp",  MATCH_C_BEQZ, MASK_C_BEQZ, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"beqz",        0, INSN_CLASS_I,   "s,p",  MATCH_BEQ, MASK_BEQ | MASK_RS2, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"beq",         0, INSN_CLASS_C,   "Cs,Cz,Cp",  MATCH_C_BEQZ, MASK_C_BEQZ, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"beq",         0, INSN_CLASS_I,   "s,t,p",  MATCH_BEQ, MASK_BEQ, match_opcode, INSN_CONDBRANCH },
{"blez",        0, INSN_CLASS_I,   "t,p",  MATCH_BGE, MASK_BGE | MASK_RS1, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bgez",        0, INSN_CLASS_I,   "s,p",  MATCH_BGE, MASK_BGE | MASK_RS2, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bge",         0, INSN_CLASS_I,   "s,t,p",  MATCH_BGE, MASK_BGE, match_opcode, INSN_CONDBRANCH },
{"bgeu",        0, INSN_CLASS_I,   "s,t,p",  MATCH_BGEU, MASK_BGEU, match_opcode, INSN_CONDBRANCH },
{"ble",         0, INSN_CLASS_I,   "t,s,p",  MATCH_BGE, MASK_BGE, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bleu",        0, INSN_CLASS_I,   "t,s,p",  MATCH_BGEU, MASK_BGEU, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bltz",        0, INSN_CLASS_I,   "s,p",  MATCH_BLT, MASK_BLT | MASK_RS2, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bgtz",        0, INSN_CLASS_I,   "t,p",  MATCH_BLT, MASK_BLT | MASK_RS1, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"blt",         0, INSN_CLASS_I,   "s,t,p",  MATCH_BLT, MASK_BLT, match_opcode, INSN_CONDBRANCH },
{"bltu",        0, INSN_CLASS_I,   "s,t,p",  MATCH_BLTU, MASK_BLTU, match_opcode, INSN_CONDBRANCH },
{"bgt",         0, INSN_CLASS_I,   "t,s,p",  MATCH_BLT, MASK_BLT, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bgtu",        0, INSN_CLASS_I,   "t,s,p",  MATCH_BLTU, MASK_BLTU, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bnez",        0, INSN_CLASS_C,   "Cs,Cp",  MATCH_C_BNEZ, MASK_C_BNEZ, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bnez",        0, INSN_CLASS_I,   "s,p",  MATCH_BNE, MASK_BNE | MASK_RS2, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bne",         0, INSN_CLASS_C,   "Cs,Cz,Cp",  MATCH_C_BNEZ, MASK_C_BNEZ, match_opcode, INSN_ALIAS|INSN_CONDBRANCH },
{"bne",         0, INSN_CLASS_I,   "s,t,p",  MATCH_BNE, MASK_BNE, match_opcode, INSN_CONDBRANCH },
{"addi",        0, INSN_CLASS_C,   "Ct,Cc,CK", MATCH_C_ADDI4SPN, MASK_C_ADDI4SPN, match_c_addi4spn, INSN_ALIAS  , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD },
{"addi",        0, INSN_CLASS_C,   "d,CU,Cj",  MATCH_C_ADDI, MASK_C_ADDI, match_rd_nonzero, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD },
{"addi",        0, INSN_CLASS_C,   "d,CU,z",    MATCH_C_NOP, MASK_C_ADDI | MASK_RVC_IMM, match_c_nop, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"addi",        0, INSN_CLASS_C,   "Cc,Cc,CL", MATCH_C_ADDI16SP, MASK_C_ADDI16SP, match_c_addi16sp, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"addi",        0, INSN_CLASS_C,   "d,Cz,Co",  MATCH_C_LI, MASK_C_LI, match_rd_nonzero, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD },
{"addi",        0, INSN_CLASS_I,   "d,s,j",  MATCH_ADDI, MASK_ADDI, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"add",         0, INSN_CLASS_C,   "d,CU,CV",  MATCH_C_ADD, MASK_C_ADD, match_c_add, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"add",         0, INSN_CLASS_C,   "d,CV,CU",  MATCH_C_ADD, MASK_C_ADD, match_c_add, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"add",         0, INSN_CLASS_C,   "d,CU,Co",  MATCH_C_ADDI, MASK_C_ADDI, match_rd_nonzero, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"add",         0, INSN_CLASS_C,   "Ct,Cc,CK", MATCH_C_ADDI4SPN, MASK_C_ADDI4SPN, match_c_addi4spn, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"add",         0, INSN_CLASS_C,   "Cc,Cc,CL", MATCH_C_ADDI16SP, MASK_C_ADDI16SP, match_c_addi16sp, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD },
{"add",         0, INSN_CLASS_C,   "d,Cz,CV",  MATCH_C_MV, MASK_C_MV, match_c_add, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"add",         0, INSN_CLASS_I,   "d,s,t",  MATCH_ADD, MASK_ADD, match_opcode, 0 },
/* This is used for TLS, where the fourth arg is %tprel_add, to get a reloc
   applied to an add instruction, for relaxation to use.  */
{"add",         0, INSN_CLASS_I,   "d,s,t,1",MATCH_ADD, MASK_ADD, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"add",         0, INSN_CLASS_I,   "d,s,j",  MATCH_ADDI, MASK_ADDI, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD  },
{"la",          0, INSN_CLASS_I,   "d,B",  0,    (int) M_LA,  match_never, INSN_MACRO },
{"lla",         0, INSN_CLASS_I,   "d,B",  0,    (int) M_LLA,  match_never, INSN_MACRO },
{"la.tls.gd",   0, INSN_CLASS_I,   "d,A",  0,    (int) M_LA_TLS_GD,  match_never, INSN_MACRO },
{"la.tls.ie",   0, INSN_CLASS_I,   "d,A",  0,    (int) M_LA_TLS_IE,  match_never, INSN_MACRO },
{"neg",         0, INSN_CLASS_I,   "d,t",  MATCH_SUB, MASK_SUB | MASK_RS1, match_opcode, INSN_ALIAS }, /* sub 0 */
{"slli",        0, INSN_CLASS_C,   "d,CU,C>",  MATCH_C_SLLI, MASK_C_SLLI, match_slli_as_c_slli, INSN_ALIAS },
{"slli",        0, INSN_CLASS_I,   "d,s,>",   MATCH_SLLI, MASK_SLLI, match_opcode, 0 },
{"sll",         0, INSN_CLASS_C,   "d,CU,C>",  MATCH_C_SLLI, MASK_C_SLLI, match_slli_as_c_slli, INSN_ALIAS },
{"sll",         0, INSN_CLASS_I,   "d,s,t",   MATCH_SLL, MASK_SLL, match_opcode, 0 },
{"sll",         0, INSN_CLASS_I,   "d,s,>",   MATCH_SLLI, MASK_SLLI, match_opcode, INSN_ALIAS },
{"srli",        0, INSN_CLASS_C,   "Cs,Cw,C>",  MATCH_C_SRLI, MASK_C_SRLI, match_srxi_as_c_srxi, INSN_ALIAS },
{"srli",        0, INSN_CLASS_I,   "d,s,>",   MATCH_SRLI, MASK_SRLI, match_opcode, 0 },
{"srl",         0, INSN_CLASS_C,   "Cs,Cw,C>",  MATCH_C_SRLI, MASK_C_SRLI, match_srxi_as_c_srxi, INSN_ALIAS },
{"srl",         0, INSN_CLASS_I,   "d,s,t",   MATCH_SRL, MASK_SRL, match_opcode, 0 },
{"srl",         0, INSN_CLASS_I,   "d,s,>",   MATCH_SRLI, MASK_SRLI, match_opcode, INSN_ALIAS },
{"srai",        0, INSN_CLASS_C,   "Cs,Cw,C>",  MATCH_C_SRAI, MASK_C_SRAI, match_srxi_as_c_srxi, INSN_ALIAS },
{"srai",        0, INSN_CLASS_I,   "d,s,>",   MATCH_SRAI, MASK_SRAI, match_opcode, 0 },
{"sra",         0, INSN_CLASS_C,   "Cs,Cw,C>",  MATCH_C_SRAI, MASK_C_SRAI, match_srxi_as_c_srxi, INSN_ALIAS },
{"sra",         0, INSN_CLASS_I,   "d,s,t",   MATCH_SRA, MASK_SRA, match_opcode, 0 },
{"sra",         0, INSN_CLASS_I,   "d,s,>",   MATCH_SRAI, MASK_SRAI, match_opcode, INSN_ALIAS },
{"sub",         0, INSN_CLASS_C,   "Cs,Cw,Ct",  MATCH_C_SUB, MASK_C_SUB, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_SUB },
{"sub",         0, INSN_CLASS_I,   "d,s,t",  MATCH_SUB, MASK_SUB, match_opcode, 0 , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_SUB },
{"lb",          0, INSN_CLASS_I,   "d,o(s)",  MATCH_LB, MASK_LB, match_opcode, INSN_DREF|INSN_1_BYTE },
{"lb",          0, INSN_CLASS_I,   "d,A",  0, (int) M_LB, match_never, INSN_MACRO },
{"lbu",         0, INSN_CLASS_I,   "d,o(s)",  MATCH_LBU, MASK_LBU, match_opcode, INSN_DREF|INSN_1_BYTE },
{"lbu",         0, INSN_CLASS_I,   "d,A",  0, (int) M_LBU, match_never, INSN_MACRO },
{"lh",          0, INSN_CLASS_I,   "d,o(s)",  MATCH_LH, MASK_LH, match_opcode, INSN_DREF|INSN_2_BYTE },
{"lh",          0, INSN_CLASS_I,   "d,A",  0, (int) M_LH, match_never, INSN_MACRO },
{"lhu",         0, INSN_CLASS_I,   "d,o(s)",  MATCH_LHU, MASK_LHU, match_opcode, INSN_DREF|INSN_2_BYTE },
{"lhu",         0, INSN_CLASS_I,   "d,A",  0, (int) M_LHU, match_never, INSN_MACRO },
{"lw",          0, INSN_CLASS_C,   "d,Cm(Cc)",  MATCH_C_LWSP, MASK_C_LWSP, match_rd_nonzero, INSN_ALIAS|INSN_DREF|INSN_4_BYTE , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG   },
{"lw",          0, INSN_CLASS_C,   "Ct,Ck(Cs)",  MATCH_C_LW, MASK_C_LW, match_opcode, INSN_ALIAS|INSN_DREF|INSN_4_BYTE , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG   },
{"lw",          0, INSN_CLASS_I,   "d,o(s)",  MATCH_LW, MASK_LW, match_opcode, INSN_DREF|INSN_4_BYTE  , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG  },
{"lw",          0, INSN_CLASS_I,   "d,A",  0, (int) M_LW, match_never, INSN_MACRO , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG   },
{"not",         0, INSN_CLASS_I,   "d,s",  MATCH_XORI | MASK_IMM, MASK_XORI | MASK_IMM, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_NOT  },
{"ori",         0, INSN_CLASS_I,   "d,s,j",  MATCH_ORI, MASK_ORI, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_OR  },
{"or",          0, INSN_CLASS_C,   "Cs,Cw,Ct",  MATCH_C_OR, MASK_C_OR, match_opcode, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_OR },
{"or",          0, INSN_CLASS_C,   "Cs,Ct,Cw",  MATCH_C_OR, MASK_C_OR, match_opcode, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_OR },
{"or",          0, INSN_CLASS_I,   "d,s,t",  MATCH_OR, MASK_OR, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_OR  },
{"or",          0, INSN_CLASS_I,   "d,s,j",  MATCH_ORI, MASK_ORI, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_OR  },
{"auipc",       0, INSN_CLASS_I,   "d,u",  MATCH_AUIPC, MASK_AUIPC, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_OR  },
{"seqz",        0, INSN_CLASS_I,   "d,s",  MATCH_SLTIU | ENCODE_ITYPE_IMM (1), MASK_SLTIU | MASK_IMM, match_opcode, INSN_ALIAS },
{"snez",        0, INSN_CLASS_I,   "d,t",  MATCH_SLTU, MASK_SLTU | MASK_RS1, match_opcode, INSN_ALIAS },
{"sltz",        0, INSN_CLASS_I,   "d,s",  MATCH_SLT, MASK_SLT | MASK_RS2, match_opcode, INSN_ALIAS },
{"sgtz",        0, INSN_CLASS_I,   "d,t",  MATCH_SLT, MASK_SLT | MASK_RS1, match_opcode, INSN_ALIAS },
{"slti",        0, INSN_CLASS_I,   "d,s,j",  MATCH_SLTI, MASK_SLTI, match_opcode, 0 },
{"slt",         0, INSN_CLASS_I,   "d,s,t",  MATCH_SLT, MASK_SLT, match_opcode, 0 },
{"slt",         0, INSN_CLASS_I,   "d,s,j",  MATCH_SLTI, MASK_SLTI, match_opcode, INSN_ALIAS },
{"sltiu",       0, INSN_CLASS_I,   "d,s,j",  MATCH_SLTIU, MASK_SLTIU, match_opcode, 0 },
{"sltu",        0, INSN_CLASS_I,   "d,s,t",  MATCH_SLTU, MASK_SLTU, match_opcode, 0 },
{"sltu",        0, INSN_CLASS_I,   "d,s,j",  MATCH_SLTIU, MASK_SLTIU, match_opcode, INSN_ALIAS },
{"sgt",         0, INSN_CLASS_I,   "d,t,s",  MATCH_SLT, MASK_SLT, match_opcode, INSN_ALIAS },
{"sgtu",        0, INSN_CLASS_I,   "d,t,s",  MATCH_SLTU, MASK_SLTU, match_opcode, INSN_ALIAS },
{"sb",          0, INSN_CLASS_I,   "t,q(s)",  MATCH_SB, MASK_SB, match_opcode, INSN_DREF|INSN_1_BYTE },
{"sb",          0, INSN_CLASS_I,   "t,A,s",  0, (int) M_SB, match_never, INSN_MACRO },
{"sh",          0, INSN_CLASS_I,   "t,q(s)",  MATCH_SH, MASK_SH, match_opcode, INSN_DREF|INSN_2_BYTE },
{"sh",          0, INSN_CLASS_I,   "t,A,s",  0, (int) M_SH, match_never, INSN_MACRO },
{"sw",          0, INSN_CLASS_C,   "CV,CM(Cc)",  MATCH_C_SWSP, MASK_C_SWSP, match_opcode, INSN_ALIAS|INSN_DREF|INSN_4_BYTE },
{"sw",          0, INSN_CLASS_C,   "Ct,Ck(Cs)",  MATCH_C_SW, MASK_C_SW, match_opcode, INSN_ALIAS|INSN_DREF|INSN_4_BYTE },
{"sw",          0, INSN_CLASS_I,   "t,q(s)",  MATCH_SW, MASK_SW, match_opcode, INSN_DREF|INSN_4_BYTE },
{"sw",          0, INSN_CLASS_I,   "t,A,s",  0, (int) M_SW, match_never, INSN_MACRO },
{"fence",       0, INSN_CLASS_I,   "",  MATCH_FENCE | MASK_PRED | MASK_SUCC, MASK_FENCE | MASK_RD | MASK_RS1 | MASK_IMM, match_opcode, INSN_ALIAS },
{"fence",       0, INSN_CLASS_I,   "P,Q",  MATCH_FENCE, MASK_FENCE | MASK_RD | MASK_RS1 | (MASK_IMM & ~MASK_PRED & ~MASK_SUCC), match_opcode, 0 },
{"fence.i",     0, INSN_CLASS_I,   "",  MATCH_FENCE_I, MASK_FENCE | MASK_RD | MASK_RS1 | MASK_IMM, match_opcode, 0 },
{"fence.tso",   0, INSN_CLASS_I,   "",  MATCH_FENCE_TSO, MASK_FENCE_TSO | MASK_RD | MASK_RS1, match_opcode, INSN_ALIAS },
{"rdcycle",     0, INSN_CLASS_I,   "d",  MATCH_RDCYCLE, MASK_RDCYCLE, match_opcode, INSN_ALIAS },
{"rdinstret",   0, INSN_CLASS_I,   "d",  MATCH_RDINSTRET, MASK_RDINSTRET, match_opcode, INSN_ALIAS },
{"rdtime",      0, INSN_CLASS_I,   "d",  MATCH_RDTIME, MASK_RDTIME, match_opcode, INSN_ALIAS },
{"rdcycleh",   32, INSN_CLASS_I,   "d",  MATCH_RDCYCLEH, MASK_RDCYCLEH, match_opcode, INSN_ALIAS },
{"rdinstreth", 32, INSN_CLASS_I,   "d",  MATCH_RDINSTRETH, MASK_RDINSTRETH, match_opcode, INSN_ALIAS },
{"rdtimeh",    32, INSN_CLASS_I,   "d",  MATCH_RDTIMEH, MASK_RDTIMEH, match_opcode, INSN_ALIAS },
{"ecall",       0, INSN_CLASS_I,   "",    MATCH_SCALL, MASK_SCALL, match_opcode, 0 },
{"scall",       0, INSN_CLASS_I,   "",    MATCH_SCALL, MASK_SCALL, match_opcode, 0 },
{"xori",        0, INSN_CLASS_I,   "d,s,j",  MATCH_XORI, MASK_XORI, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_XOR  },
{"xor",         0, INSN_CLASS_C,   "Cs,Cw,Ct",  MATCH_C_XOR, MASK_C_XOR, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_XOR   },
{"xor",         0, INSN_CLASS_C,   "Cs,Ct,Cw",  MATCH_C_XOR, MASK_C_XOR, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_XOR   },
{"xor",         0, INSN_CLASS_I,   "d,s,t",  MATCH_XOR, MASK_XOR, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_XOR   },
{"xor",         0, INSN_CLASS_I,   "d,s,j",  MATCH_XORI, MASK_XORI, match_opcode, INSN_ALIAS , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_XOR  },
{"lwu",        64, INSN_CLASS_I, "d,o(s)",  MATCH_LWU, MASK_LWU, match_opcode, INSN_DREF|INSN_4_BYTE },
{"lwu",        64, INSN_CLASS_I, "d,A",  0, (int) M_LWU, match_never, INSN_MACRO },
{"ld",         64, INSN_CLASS_C, "d,Cn(Cc)",  MATCH_C_LDSP, MASK_C_LDSP, match_rd_nonzero, INSN_ALIAS|INSN_DREF|INSN_8_BYTE , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG  },
{"ld",         64, INSN_CLASS_C, "Ct,Cl(Cs)",  MATCH_C_LD, MASK_C_LD, match_opcode, INSN_ALIAS|INSN_DREF|INSN_8_BYTE , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG   },
{"ld",         64, INSN_CLASS_I, "d,o(s)", MATCH_LD, MASK_LD, match_opcode, INSN_DREF|INSN_8_BYTE , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG   },
{"ld",         64, INSN_CLASS_I, "d,A",  0, (int) M_LD, match_never, INSN_MACRO , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DISP_REG   },
{"sd",         64, INSN_CLASS_C, "CV,CN(Cc)",  MATCH_C_SDSP, MASK_C_SDSP, match_opcode, INSN_ALIAS|INSN_DREF|INSN_8_BYTE },
{"sd",         64, INSN_CLASS_C, "Ct,Cl(Cs)",  MATCH_C_SD, MASK_C_SD, match_opcode, INSN_ALIAS|INSN_DREF|INSN_8_BYTE },
{"sd",         64, INSN_CLASS_I, "t,q(s)",  MATCH_SD, MASK_SD, match_opcode, INSN_DREF|INSN_8_BYTE },
{"sd",         64, INSN_CLASS_I, "t,A,s",  0, (int) M_SD, match_never, INSN_MACRO },
{"sext.w",     64, INSN_CLASS_C, "d,CU",  MATCH_C_ADDIW, MASK_C_ADDIW | MASK_RVC_IMM, match_rd_nonzero, INSN_ALIAS },
{"sext.w",     64, INSN_CLASS_I, "d,s",  MATCH_ADDIW, MASK_ADDIW | MASK_IMM, match_opcode, INSN_ALIAS },
{"addiw",      64, INSN_CLASS_C, "d,CU,Co",  MATCH_C_ADDIW, MASK_C_ADDIW, match_rd_nonzero, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD   },
{"addiw",      64, INSN_CLASS_I, "d,s,j",  MATCH_ADDIW, MASK_ADDIW, match_opcode, 0 , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD   },
{"addw",       64, INSN_CLASS_C, "Cs,Cw,Ct",  MATCH_C_ADDW, MASK_C_ADDW, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD    },
{"addw",       64, INSN_CLASS_C, "Cs,Ct,Cw",  MATCH_C_ADDW, MASK_C_ADDW, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD    },
{"addw",       64, INSN_CLASS_C, "d,CU,Co",  MATCH_C_ADDIW, MASK_C_ADDIW, match_rd_nonzero, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD    },
{"addw",       64, INSN_CLASS_I, "d,s,t",  MATCH_ADDW, MASK_ADDW, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD    },
{"addw",       64, INSN_CLASS_I, "d,s,j",  MATCH_ADDIW, MASK_ADDIW, match_opcode, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_ADD    },
{"negw",       64, INSN_CLASS_I, "d,t",  MATCH_SUBW, MASK_SUBW | MASK_RS1, match_opcode, INSN_ALIAS }, /* sub 0 */
{"slliw",      64, INSN_CLASS_I, "d,s,<",   MATCH_SLLIW, MASK_SLLIW, match_opcode, 0 },
{"sllw",       64, INSN_CLASS_I, "d,s,t",   MATCH_SLLW, MASK_SLLW, match_opcode, 0 },
{"sllw",       64, INSN_CLASS_I, "d,s,<",   MATCH_SLLIW, MASK_SLLIW, match_opcode, INSN_ALIAS },
{"srliw",      64, INSN_CLASS_I, "d,s,<",   MATCH_SRLIW, MASK_SRLIW, match_opcode, 0 },
{"srlw",       64, INSN_CLASS_I, "d,s,t",   MATCH_SRLW, MASK_SRLW, match_opcode, 0 },
{"srlw",       64, INSN_CLASS_I, "d,s,<",   MATCH_SRLIW, MASK_SRLIW, match_opcode, INSN_ALIAS },
{"sraiw",      64, INSN_CLASS_I, "d,s,<",   MATCH_SRAIW, MASK_SRAIW, match_opcode, 0 },
{"sraw",       64, INSN_CLASS_I, "d,s,t",   MATCH_SRAW, MASK_SRAW, match_opcode, 0 },
{"sraw",       64, INSN_CLASS_I, "d,s,<",   MATCH_SRAIW, MASK_SRAIW, match_opcode, INSN_ALIAS },
{"subw",       64, INSN_CLASS_C, "Cs,Cw,Ct",  MATCH_C_SUBW, MASK_C_SUBW, match_opcode, INSN_ALIAS },
{"subw",       64, INSN_CLASS_I, "d,s,t",  MATCH_SUBW, MASK_SUBW, match_opcode, 0 },

/* Atomic memory operation instruction subset */
{"lr.w",         0, INSN_CLASS_A,   "d,0(s)",    MATCH_LR_W, MASK_LR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"sc.w",         0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_SC_W, MASK_SC_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoadd.w",     0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOADD_W, MASK_AMOADD_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoswap.w",    0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOSWAP_W, MASK_AMOSWAP_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoand.w",     0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOAND_W, MASK_AMOAND_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoor.w",      0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOOR_W, MASK_AMOOR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoxor.w",     0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOXOR_W, MASK_AMOXOR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomax.w",     0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMAX_W, MASK_AMOMAX_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomaxu.w",    0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMAXU_W, MASK_AMOMAXU_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomin.w",     0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMIN_W, MASK_AMOMIN_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amominu.w",    0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMINU_W, MASK_AMOMINU_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"lr.w.aq",      0, INSN_CLASS_A,   "d,0(s)",    MATCH_LR_W | MASK_AQ, MASK_LR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"sc.w.aq",      0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_SC_W | MASK_AQ, MASK_SC_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoadd.w.aq",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOADD_W | MASK_AQ, MASK_AMOADD_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoswap.w.aq", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOSWAP_W | MASK_AQ, MASK_AMOSWAP_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoand.w.aq",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOAND_W | MASK_AQ, MASK_AMOAND_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoor.w.aq",   0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOOR_W | MASK_AQ, MASK_AMOOR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoxor.w.aq",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOXOR_W | MASK_AQ, MASK_AMOXOR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomax.w.aq",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMAX_W | MASK_AQ, MASK_AMOMAX_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomaxu.w.aq", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMAXU_W | MASK_AQ, MASK_AMOMAXU_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomin.w.aq",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMIN_W | MASK_AQ, MASK_AMOMIN_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amominu.w.aq", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMINU_W | MASK_AQ, MASK_AMOMINU_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"lr.w.rl",      0, INSN_CLASS_A,   "d,0(s)",    MATCH_LR_W | MASK_RL, MASK_LR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"sc.w.rl",      0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_SC_W | MASK_RL, MASK_SC_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoadd.w.rl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOADD_W | MASK_RL, MASK_AMOADD_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoswap.w.rl", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOSWAP_W | MASK_RL, MASK_AMOSWAP_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoand.w.rl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOAND_W | MASK_RL, MASK_AMOAND_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoor.w.rl",   0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOOR_W | MASK_RL, MASK_AMOOR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoxor.w.rl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOXOR_W | MASK_RL, MASK_AMOXOR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomax.w.rl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMAX_W | MASK_RL, MASK_AMOMAX_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomaxu.w.rl", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMAXU_W | MASK_RL, MASK_AMOMAXU_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomin.w.rl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMIN_W | MASK_RL, MASK_AMOMIN_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amominu.w.rl", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMINU_W | MASK_RL, MASK_AMOMINU_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"lr.w.aqrl",    0, INSN_CLASS_A,   "d,0(s)",    MATCH_LR_W | MASK_AQRL, MASK_LR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"sc.w.aqrl",    0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_SC_W | MASK_AQRL, MASK_SC_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoadd.w.aqrl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOADD_W | MASK_AQRL, MASK_AMOADD_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoswap.w.aqrl", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOSWAP_W | MASK_AQRL, MASK_AMOSWAP_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoand.w.aqrl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOAND_W | MASK_AQRL, MASK_AMOAND_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoor.w.aqrl",   0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOOR_W | MASK_AQRL, MASK_AMOOR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amoxor.w.aqrl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOXOR_W | MASK_AQRL, MASK_AMOXOR_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomax.w.aqrl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMAX_W | MASK_AQRL, MASK_AMOMAX_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomaxu.w.aqrl", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMAXU_W | MASK_AQRL, MASK_AMOMAXU_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amomin.w.aqrl",  0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMIN_W | MASK_AQRL, MASK_AMOMIN_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"amominu.w.aqrl", 0, INSN_CLASS_A,   "d,t,0(s)",  MATCH_AMOMINU_W | MASK_AQRL, MASK_AMOMINU_W | MASK_AQRL, match_opcode, INSN_DREF|INSN_4_BYTE },
{"lr.d",         64, INSN_CLASS_A , "d,0(s)",    MATCH_LR_D, MASK_LR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"sc.d",         64, INSN_CLASS_A , "d,t,0(s)",  MATCH_SC_D, MASK_SC_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoadd.d",     64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOADD_D, MASK_AMOADD_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoswap.d",    64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOSWAP_D, MASK_AMOSWAP_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoand.d",     64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOAND_D, MASK_AMOAND_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoor.d",      64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOOR_D, MASK_AMOOR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoxor.d",     64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOXOR_D, MASK_AMOXOR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomax.d",     64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMAX_D, MASK_AMOMAX_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomaxu.d",    64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMAXU_D, MASK_AMOMAXU_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomin.d",     64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMIN_D, MASK_AMOMIN_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amominu.d",    64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMINU_D, MASK_AMOMINU_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"lr.d.aq",      64, INSN_CLASS_A , "d,0(s)",    MATCH_LR_D | MASK_AQ, MASK_LR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"sc.d.aq",      64, INSN_CLASS_A , "d,t,0(s)",  MATCH_SC_D | MASK_AQ, MASK_SC_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoadd.d.aq",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOADD_D | MASK_AQ, MASK_AMOADD_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoswap.d.aq", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOSWAP_D | MASK_AQ, MASK_AMOSWAP_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoand.d.aq",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOAND_D | MASK_AQ, MASK_AMOAND_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoor.d.aq",   64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOOR_D | MASK_AQ, MASK_AMOOR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoxor.d.aq",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOXOR_D | MASK_AQ, MASK_AMOXOR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomax.d.aq",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMAX_D | MASK_AQ, MASK_AMOMAX_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomaxu.d.aq", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMAXU_D | MASK_AQ, MASK_AMOMAXU_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomin.d.aq",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMIN_D | MASK_AQ, MASK_AMOMIN_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amominu.d.aq", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMINU_D | MASK_AQ, MASK_AMOMINU_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"lr.d.rl",      64, INSN_CLASS_A , "d,0(s)",    MATCH_LR_D | MASK_RL, MASK_LR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"sc.d.rl",      64, INSN_CLASS_A , "d,t,0(s)",  MATCH_SC_D | MASK_RL, MASK_SC_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoadd.d.rl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOADD_D | MASK_RL, MASK_AMOADD_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoswap.d.rl", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOSWAP_D | MASK_RL, MASK_AMOSWAP_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoand.d.rl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOAND_D | MASK_RL, MASK_AMOAND_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoor.d.rl",   64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOOR_D | MASK_RL, MASK_AMOOR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoxor.d.rl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOXOR_D | MASK_RL, MASK_AMOXOR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomax.d.rl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMAX_D | MASK_RL, MASK_AMOMAX_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomaxu.d.rl", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMAXU_D | MASK_RL, MASK_AMOMAXU_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomin.d.rl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMIN_D | MASK_RL, MASK_AMOMIN_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amominu.d.rl", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMINU_D | MASK_RL, MASK_AMOMINU_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"lr.d.aqrl",    64, INSN_CLASS_A , "d,0(s)",    MATCH_LR_D | MASK_AQRL, MASK_LR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"sc.d.aqrl",    64, INSN_CLASS_A , "d,t,0(s)",  MATCH_SC_D | MASK_AQRL, MASK_SC_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoadd.d.aqrl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOADD_D | MASK_AQRL, MASK_AMOADD_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoswap.d.aqrl", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOSWAP_D | MASK_AQRL, MASK_AMOSWAP_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoand.d.aqrl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOAND_D | MASK_AQRL, MASK_AMOAND_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoor.d.aqrl",   64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOOR_D | MASK_AQRL, MASK_AMOOR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amoxor.d.aqrl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOXOR_D | MASK_AQRL, MASK_AMOXOR_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomax.d.aqrl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMAX_D | MASK_AQRL, MASK_AMOMAX_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomaxu.d.aqrl", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMAXU_D | MASK_AQRL, MASK_AMOMAXU_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amomin.d.aqrl",  64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMIN_D | MASK_AQRL, MASK_AMOMIN_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },
{"amominu.d.aqrl", 64, INSN_CLASS_A , "d,t,0(s)",  MATCH_AMOMINU_D | MASK_AQRL, MASK_AMOMINU_D | MASK_AQRL, match_opcode, INSN_DREF|INSN_8_BYTE },

/* Multiply/Divide instruction subset */
{"mul",       0, INSN_CLASS_M,   "d,s,t",  MATCH_MUL, MASK_MUL, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MULNORMAL    },
{"mulh",      0, INSN_CLASS_M,   "d,s,t",  MATCH_MULH, MASK_MULH, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MULNORMAL   },
{"mulhu",     0, INSN_CLASS_M,   "d,s,t",  MATCH_MULHU, MASK_MULHU, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MULNORMAL },
{"mulhsu",    0, INSN_CLASS_M,   "d,s,t",  MATCH_MULHSU, MASK_MULHSU, match_opcode, 0 , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MULNORMAL},
{"div",       0, INSN_CLASS_M,   "d,s,t",  MATCH_DIV, MASK_DIV, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DIV },
{"divu",      0, INSN_CLASS_M,   "d,s,t",  MATCH_DIVU, MASK_DIVU, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DIVUNSIGNED },
{"rem",       0, INSN_CLASS_M,   "d,s,t",  MATCH_REM, MASK_REM, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MODULO },
{"remu",      0, INSN_CLASS_M,   "d,s,t",  MATCH_REMU, MASK_REMU, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MODULO  },
{"mulw",     64, INSN_CLASS_M, "d,s,t",  MATCH_MULW, MASK_MULW, match_opcode, 0  , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MULNORMAL },
{"divw",     64, INSN_CLASS_M, "d,s,t",  MATCH_DIVW, MASK_DIVW, match_opcode, 0  , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DIV},
{"divuw",    64, INSN_CLASS_M, "d,s,t",  MATCH_DIVUW, MASK_DIVUW, match_opcode, 0, .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_DIVUNSIGNED },
{"remw",     64, INSN_CLASS_M, "d,s,t",  MATCH_REMW, MASK_REMW, match_opcode, 0 , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MODULO  },
{"remuw",    64, INSN_CLASS_M, "d,s,t",  MATCH_REMUW, MASK_REMUW, match_opcode, 0  , .to_chiara_gpr = chiara_action_reg, .gpraction = ACTION_MODULO },

/* Single-precision floating-point instruction subset */
{"frcsr",     0, INSN_CLASS_F,   "d",  MATCH_FRCSR, MASK_FRCSR, match_opcode, INSN_ALIAS },
{"frsr",      0, INSN_CLASS_F,   "d",  MATCH_FRCSR, MASK_FRCSR, match_opcode, INSN_ALIAS },
{"fscsr",     0, INSN_CLASS_F,   "s",  MATCH_FSCSR, MASK_FSCSR | MASK_RD, match_opcode, INSN_ALIAS },
{"fscsr",     0, INSN_CLASS_F,   "d,s",  MATCH_FSCSR, MASK_FSCSR, match_opcode, INSN_ALIAS },
{"fssr",      0, INSN_CLASS_F,   "s",  MATCH_FSCSR, MASK_FSCSR | MASK_RD, match_opcode, INSN_ALIAS },
{"fssr",      0, INSN_CLASS_F,   "d,s",  MATCH_FSCSR, MASK_FSCSR, match_opcode, INSN_ALIAS },
{"frrm",      0, INSN_CLASS_F,   "d",  MATCH_FRRM, MASK_FRRM, match_opcode, INSN_ALIAS },
{"fsrm",      0, INSN_CLASS_F,   "s",  MATCH_FSRM, MASK_FSRM | MASK_RD, match_opcode, INSN_ALIAS },
{"fsrm",      0, INSN_CLASS_F,   "d,s",  MATCH_FSRM, MASK_FSRM, match_opcode, INSN_ALIAS },
{"fsrmi",     0, INSN_CLASS_F,   "d,Z",  MATCH_FSRMI, MASK_FSRMI, match_opcode, INSN_ALIAS },
{"fsrmi",     0, INSN_CLASS_F,   "Z",  MATCH_FSRMI, MASK_FSRMI | MASK_RD, match_opcode, INSN_ALIAS },
{"frflags",   0, INSN_CLASS_F,   "d",  MATCH_FRFLAGS, MASK_FRFLAGS, match_opcode, INSN_ALIAS },
{"fsflags",   0, INSN_CLASS_F,   "s",  MATCH_FSFLAGS, MASK_FSFLAGS | MASK_RD, match_opcode, INSN_ALIAS },
{"fsflags",   0, INSN_CLASS_F,   "d,s",  MATCH_FSFLAGS, MASK_FSFLAGS, match_opcode, INSN_ALIAS },
{"fsflagsi",  0, INSN_CLASS_F,   "d,Z",  MATCH_FSFLAGSI, MASK_FSFLAGSI, match_opcode, INSN_ALIAS },
{"fsflagsi",  0, INSN_CLASS_F,   "Z",  MATCH_FSFLAGSI, MASK_FSFLAGSI | MASK_RD, match_opcode, INSN_ALIAS },
{"flw",      32, INSN_CLASS_F_AND_C, "D,Cm(Cc)",  MATCH_C_FLWSP, MASK_C_FLWSP, match_opcode, INSN_ALIAS|INSN_DREF|INSN_4_BYTE },
{"flw",      32, INSN_CLASS_F_AND_C, "CD,Ck(Cs)",  MATCH_C_FLW, MASK_C_FLW, match_opcode, INSN_ALIAS|INSN_DREF|INSN_4_BYTE },
{"flw",       0, INSN_CLASS_F,   "D,o(s)",  MATCH_FLW, MASK_FLW, match_opcode, INSN_DREF|INSN_4_BYTE },
{"flw",       0, INSN_CLASS_F,   "D,A,s",  0, (int) M_FLW, match_never, INSN_MACRO },
{"fsw",      32, INSN_CLASS_F_AND_C, "CT,CM(Cc)",  MATCH_C_FSWSP, MASK_C_FSWSP, match_opcode, INSN_ALIAS|INSN_DREF|INSN_4_BYTE },
{"fsw",      32, INSN_CLASS_F_AND_C, "CD,Ck(Cs)",  MATCH_C_FSW, MASK_C_FSW, match_opcode, INSN_ALIAS|INSN_DREF|INSN_4_BYTE },
{"fsw",       0, INSN_CLASS_F,   "T,q(s)",  MATCH_FSW, MASK_FSW, match_opcode, INSN_DREF|INSN_4_BYTE },
{"fsw",       0, INSN_CLASS_F,   "T,A,s",  0, (int) M_FSW, match_never, INSN_MACRO },

{"fmv.x.w",    0, INSN_CLASS_F,   "d,S",  MATCH_FMV_X_S, MASK_FMV_X_S, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DISP_REG_COPY },
{"fmv.w.x",    0, INSN_CLASS_F,   "D,s",  MATCH_FMV_S_X, MASK_FMV_S_X, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DISP_REG_COPY },

{"fmv.x.s",    0, INSN_CLASS_F,   "d,S",  MATCH_FMV_X_S, MASK_FMV_X_S, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DISP_REG_COPY  },
{"fmv.s.x",    0, INSN_CLASS_F,   "D,s",  MATCH_FMV_S_X, MASK_FMV_S_X, match_opcode, 0 , .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DISP_REG_COPY },

{"fmv.s",      0, INSN_CLASS_F,   "D,U",  MATCH_FSGNJ_S, MASK_FSGNJ_S, match_rs1_eq_rs2, INSN_ALIAS, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DISP_REG_COPY },
{"fneg.s",     0, INSN_CLASS_F,   "D,U",  MATCH_FSGNJN_S, MASK_FSGNJN_S, match_rs1_eq_rs2, INSN_ALIAS },
{"fabs.s",     0, INSN_CLASS_F,   "D,U",  MATCH_FSGNJX_S, MASK_FSGNJX_S, match_rs1_eq_rs2, INSN_ALIAS },
{"fsgnj.s",    0, INSN_CLASS_F,   "D,S,T",  MATCH_FSGNJ_S, MASK_FSGNJ_S, match_opcode, 0 },
{"fsgnjn.s",   0, INSN_CLASS_F,   "D,S,T",  MATCH_FSGNJN_S, MASK_FSGNJN_S, match_opcode, 0 },
{"fsgnjx.s",   0, INSN_CLASS_F,   "D,S,T",  MATCH_FSGNJX_S, MASK_FSGNJX_S, match_opcode, 0 },
{"fadd.s",     0, INSN_CLASS_F,   "D,S,T",  MATCH_FADD_S | MASK_RM, MASK_FADD_S | MASK_RM, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_ADD },
{"fadd.s",     0, INSN_CLASS_F,   "D,S,T,m",  MATCH_FADD_S, MASK_FADD_S, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_ADD },
{"fsub.s",     0, INSN_CLASS_F,   "D,S,T",  MATCH_FSUB_S | MASK_RM, MASK_FSUB_S | MASK_RM, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_SUB },
{"fsub.s",     0, INSN_CLASS_F,   "D,S,T,m",  MATCH_FSUB_S, MASK_FSUB_S, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_SUB  },
{"fmul.s",     0, INSN_CLASS_F,   "D,S,T",  MATCH_FMUL_S | MASK_RM, MASK_FMUL_S | MASK_RM, match_opcode, 0 , .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_MULNORMAL },
{"fmul.s",     0, INSN_CLASS_F,   "D,S,T,m",  MATCH_FMUL_S, MASK_FMUL_S, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_MULNORMAL },
{"fdiv.s",     0, INSN_CLASS_F,   "D,S,T",  MATCH_FDIV_S | MASK_RM, MASK_FDIV_S | MASK_RM, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DIV },
{"fdiv.s",     0, INSN_CLASS_F,   "D,S,T,m",  MATCH_FDIV_S, MASK_FDIV_S, match_opcode, 0 , match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DIV},
{"fsqrt.s",    0, INSN_CLASS_F,   "D,S",  MATCH_FSQRT_S | MASK_RM, MASK_FSQRT_S | MASK_RM, match_opcode, 0 },
{"fsqrt.s",    0, INSN_CLASS_F,   "D,S,m",  MATCH_FSQRT_S, MASK_FSQRT_S, match_opcode, 0 },
{"fmin.s",     0, INSN_CLASS_F,   "D,S,T",  MATCH_FMIN_S, MASK_FMIN_S, match_opcode, 0 },
{"fmax.s",     0, INSN_CLASS_F,   "D,S,T",  MATCH_FMAX_S, MASK_FMAX_S, match_opcode, 0 },
{"fmadd.s",    0, INSN_CLASS_F,   "D,S,T,R",  MATCH_FMADD_S | MASK_RM, MASK_FMADD_S | MASK_RM, match_opcode, 0 },
{"fmadd.s",    0, INSN_CLASS_F,   "D,S,T,R,m",  MATCH_FMADD_S, MASK_FMADD_S, match_opcode, 0 },
{"fnmadd.s",   0, INSN_CLASS_F,   "D,S,T,R",  MATCH_FNMADD_S | MASK_RM, MASK_FNMADD_S | MASK_RM, match_opcode, 0 },
{"fnmadd.s",   0, INSN_CLASS_F,   "D,S,T,R,m",  MATCH_FNMADD_S, MASK_FNMADD_S, match_opcode, 0 },
{"fmsub.s",    0, INSN_CLASS_F,   "D,S,T,R",  MATCH_FMSUB_S | MASK_RM, MASK_FMSUB_S | MASK_RM, match_opcode, 0 },
{"fmsub.s",    0, INSN_CLASS_F,   "D,S,T,R,m",  MATCH_FMSUB_S, MASK_FMSUB_S, match_opcode, 0 },
{"fnmsub.s",   0, INSN_CLASS_F,   "D,S,T,R",  MATCH_FNMSUB_S | MASK_RM, MASK_FNMSUB_S | MASK_RM, match_opcode, 0 },
{"fnmsub.s",   0, INSN_CLASS_F,   "D,S,T,R,m",  MATCH_FNMSUB_S, MASK_FNMSUB_S, match_opcode, 0 },
{"fcvt.w.s",   0, INSN_CLASS_F,   "d,S",  MATCH_FCVT_W_S | MASK_RM, MASK_FCVT_W_S | MASK_RM, match_opcode, 0 },
{"fcvt.w.s",   0, INSN_CLASS_F,   "d,S,m",  MATCH_FCVT_W_S, MASK_FCVT_W_S, match_opcode, 0 },
{"fcvt.wu.s",  0, INSN_CLASS_F,   "d,S",  MATCH_FCVT_WU_S | MASK_RM, MASK_FCVT_WU_S | MASK_RM, match_opcode, 0 },
{"fcvt.wu.s",  0, INSN_CLASS_F,   "d,S,m",  MATCH_FCVT_WU_S, MASK_FCVT_WU_S, match_opcode, 0 },
{"fcvt.s.w",   0, INSN_CLASS_F,   "D,s",  MATCH_FCVT_S_W | MASK_RM, MASK_FCVT_S_W | MASK_RM, match_opcode, 0 },
{"fcvt.s.w",   0, INSN_CLASS_F,   "D,s,m",  MATCH_FCVT_S_W, MASK_FCVT_S_W, match_opcode, 0 },
{"fcvt.s.wu",  0, INSN_CLASS_F,   "D,s",  MATCH_FCVT_S_WU | MASK_RM, MASK_FCVT_S_W | MASK_RM, match_opcode, 0 },
{"fcvt.s.wu",  0, INSN_CLASS_F,   "D,s,m",  MATCH_FCVT_S_WU, MASK_FCVT_S_WU, match_opcode, 0 },
{"fclass.s",   0, INSN_CLASS_F,   "d,S",  MATCH_FCLASS_S, MASK_FCLASS_S, match_opcode, 0 },
{"feq.s",      0, INSN_CLASS_F,   "d,S,T",    MATCH_FEQ_S, MASK_FEQ_S, match_opcode, 0 },
{"flt.s",      0, INSN_CLASS_F,   "d,S,T",    MATCH_FLT_S, MASK_FLT_S, match_opcode, 0 },
{"fle.s",      0, INSN_CLASS_F,   "d,S,T",    MATCH_FLE_S, MASK_FLE_S, match_opcode, 0 },
{"fgt.s",      0, INSN_CLASS_F,   "d,T,S",    MATCH_FLT_S, MASK_FLT_S, match_opcode, 0 },
{"fge.s",      0, INSN_CLASS_F,   "d,T,S",    MATCH_FLE_S, MASK_FLE_S, match_opcode, 0 },
{"fcvt.l.s",  64, INSN_CLASS_F, "d,S",  MATCH_FCVT_L_S | MASK_RM, MASK_FCVT_L_S | MASK_RM, match_opcode, 0 },
{"fcvt.l.s",  64, INSN_CLASS_F, "d,S,m",  MATCH_FCVT_L_S, MASK_FCVT_L_S, match_opcode, 0 },
{"fcvt.lu.s", 64, INSN_CLASS_F, "d,S",  MATCH_FCVT_LU_S | MASK_RM, MASK_FCVT_LU_S | MASK_RM, match_opcode, 0 },
{"fcvt.lu.s", 64, INSN_CLASS_F, "d,S,m",  MATCH_FCVT_LU_S, MASK_FCVT_LU_S, match_opcode, 0 },
{"fcvt.s.l",  64, INSN_CLASS_F, "D,s",  MATCH_FCVT_S_L | MASK_RM, MASK_FCVT_S_L | MASK_RM, match_opcode, 0 },
{"fcvt.s.l",  64, INSN_CLASS_F, "D,s,m",  MATCH_FCVT_S_L, MASK_FCVT_S_L, match_opcode, 0 },
{"fcvt.s.lu", 64, INSN_CLASS_F, "D,s",  MATCH_FCVT_S_LU | MASK_RM, MASK_FCVT_S_L | MASK_RM, match_opcode, 0 },
{"fcvt.s.lu", 64, INSN_CLASS_F, "D,s,m",  MATCH_FCVT_S_LU, MASK_FCVT_S_LU, match_opcode, 0 },

/* Double-precision floating-point instruction subset */
{"fld",        0, INSN_CLASS_D_AND_C,   "D,Cn(Cc)",  MATCH_C_FLDSP, MASK_C_FLDSP, match_opcode, INSN_ALIAS|INSN_DREF|INSN_8_BYTE },
{"fld",        0, INSN_CLASS_D_AND_C,   "CD,Cl(Cs)",  MATCH_C_FLD, MASK_C_FLD, match_opcode, INSN_ALIAS|INSN_DREF|INSN_8_BYTE },
{"fld",        0, INSN_CLASS_D,   "D,o(s)",  MATCH_FLD, MASK_FLD, match_opcode, INSN_DREF|INSN_8_BYTE },
{"fld",        0, INSN_CLASS_D,   "D,A,s",  0, (int) M_FLD, match_never, INSN_MACRO },
{"fsd",        0, INSN_CLASS_D_AND_C,   "CT,CN(Cc)",  MATCH_C_FSDSP, MASK_C_FSDSP, match_opcode, INSN_ALIAS|INSN_DREF|INSN_8_BYTE },
{"fsd",        0, INSN_CLASS_D_AND_C,   "CD,Cl(Cs)",  MATCH_C_FSD, MASK_C_FSD, match_opcode, INSN_ALIAS|INSN_DREF|INSN_8_BYTE },
{"fsd",        0, INSN_CLASS_D,   "T,q(s)",  MATCH_FSD, MASK_FSD, match_opcode, INSN_DREF|INSN_8_BYTE },
{"fsd",        0, INSN_CLASS_D,   "T,A,s",  0, (int) M_FSD, match_never, INSN_MACRO },
{"fmv.d",      0, INSN_CLASS_D,   "D,U",  MATCH_FSGNJ_D, MASK_FSGNJ_D, match_rs1_eq_rs2, INSN_ALIAS },
{"fneg.d",     0, INSN_CLASS_D,   "D,U",  MATCH_FSGNJN_D, MASK_FSGNJN_D, match_rs1_eq_rs2, INSN_ALIAS },
{"fabs.d",     0, INSN_CLASS_D,   "D,U",  MATCH_FSGNJX_D, MASK_FSGNJX_D, match_rs1_eq_rs2, INSN_ALIAS },
{"fsgnj.d",    0, INSN_CLASS_D,   "D,S,T",  MATCH_FSGNJ_D, MASK_FSGNJ_D, match_opcode, 0 },
{"fsgnjn.d",   0, INSN_CLASS_D,   "D,S,T",  MATCH_FSGNJN_D, MASK_FSGNJN_D, match_opcode, 0 },
{"fsgnjx.d",   0, INSN_CLASS_D,   "D,S,T",  MATCH_FSGNJX_D, MASK_FSGNJX_D, match_opcode, 0 },
{"fadd.d",     0, INSN_CLASS_D,   "D,S,T",  MATCH_FADD_D | MASK_RM, MASK_FADD_D | MASK_RM, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_ADD },
{"fadd.d",     0, INSN_CLASS_D,   "D,S,T,m",  MATCH_FADD_D, MASK_FADD_D, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_ADD },
{"fsub.d",     0, INSN_CLASS_D,   "D,S,T",  MATCH_FSUB_D | MASK_RM, MASK_FSUB_D | MASK_RM, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_SUB },
{"fsub.d",     0, INSN_CLASS_D,   "D,S,T,m",  MATCH_FSUB_D, MASK_FSUB_D, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_SUB  },
{"fmul.d",     0, INSN_CLASS_D,   "D,S,T",  MATCH_FMUL_D | MASK_RM, MASK_FMUL_D | MASK_RM, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_MULNORMAL  },
{"fmul.d",     0, INSN_CLASS_D,   "D,S,T,m",  MATCH_FMUL_D, MASK_FMUL_D, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_MULNORMAL },
{"fdiv.d",     0, INSN_CLASS_D,   "D,S,T",  MATCH_FDIV_D | MASK_RM, MASK_FDIV_D | MASK_RM, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DIV },
{"fdiv.d",     0, INSN_CLASS_D,   "D,S,T,m",  MATCH_FDIV_D, MASK_FDIV_D, match_opcode, 0, .to_chiara_gpr = chiara_action_reg_fpu, .gpraction = ACTION_DIV },
{"fsqrt.d",    0, INSN_CLASS_D,   "D,S",  MATCH_FSQRT_D | MASK_RM, MASK_FSQRT_D | MASK_RM, match_opcode, 0 },
{"fsqrt.d",    0, INSN_CLASS_D,   "D,S,m",  MATCH_FSQRT_D, MASK_FSQRT_D, match_opcode, 0 },
{"fmin.d",     0, INSN_CLASS_D,   "D,S,T",  MATCH_FMIN_D, MASK_FMIN_D, match_opcode, 0 },
{"fmax.d",     0, INSN_CLASS_D,   "D,S,T",  MATCH_FMAX_D, MASK_FMAX_D, match_opcode, 0 },
{"fmadd.d",    0, INSN_CLASS_D,   "D,S,T,R",  MATCH_FMADD_D | MASK_RM, MASK_FMADD_D | MASK_RM, match_opcode, 0 },
{"fmadd.d",    0, INSN_CLASS_D,   "D,S,T,R,m",  MATCH_FMADD_D, MASK_FMADD_D, match_opcode, 0 },
{"fnmadd.d",   0, INSN_CLASS_D,   "D,S,T,R",  MATCH_FNMADD_D | MASK_RM, MASK_FNMADD_D | MASK_RM, match_opcode, 0 },
{"fnmadd.d",   0, INSN_CLASS_D,   "D,S,T,R,m",  MATCH_FNMADD_D, MASK_FNMADD_D, match_opcode, 0 },
{"fmsub.d",    0, INSN_CLASS_D,   "D,S,T,R",  MATCH_FMSUB_D | MASK_RM, MASK_FMSUB_D | MASK_RM, match_opcode, 0 },
{"fmsub.d",    0, INSN_CLASS_D,   "D,S,T,R,m",  MATCH_FMSUB_D, MASK_FMSUB_D, match_opcode, 0 },
{"fnmsub.d",   0, INSN_CLASS_D,   "D,S,T,R",  MATCH_FNMSUB_D | MASK_RM, MASK_FNMSUB_D | MASK_RM, match_opcode, 0 },
{"fnmsub.d",   0, INSN_CLASS_D,   "D,S,T,R,m",  MATCH_FNMSUB_D, MASK_FNMSUB_D, match_opcode, 0 },
{"fcvt.w.d",   0, INSN_CLASS_D,   "d,S",  MATCH_FCVT_W_D | MASK_RM, MASK_FCVT_W_D | MASK_RM, match_opcode, 0 },
{"fcvt.w.d",   0, INSN_CLASS_D,   "d,S,m",  MATCH_FCVT_W_D, MASK_FCVT_W_D, match_opcode, 0 },
{"fcvt.wu.d",  0, INSN_CLASS_D,   "d,S",  MATCH_FCVT_WU_D | MASK_RM, MASK_FCVT_WU_D | MASK_RM, match_opcode, 0 },
{"fcvt.wu.d",  0, INSN_CLASS_D,   "d,S,m",  MATCH_FCVT_WU_D, MASK_FCVT_WU_D, match_opcode, 0 },
{"fcvt.d.w",   0, INSN_CLASS_D,   "D,s",  MATCH_FCVT_D_W, MASK_FCVT_D_W | MASK_RM, match_opcode, 0 },
{"fcvt.d.wu",  0, INSN_CLASS_D,   "D,s",  MATCH_FCVT_D_WU, MASK_FCVT_D_WU | MASK_RM, match_opcode, 0 },
{"fcvt.d.s",   0, INSN_CLASS_D,   "D,S",  MATCH_FCVT_D_S, MASK_FCVT_D_S | MASK_RM, match_opcode, 0 },
{"fcvt.s.d",   0, INSN_CLASS_D,   "D,S",  MATCH_FCVT_S_D | MASK_RM, MASK_FCVT_S_D | MASK_RM, match_opcode, 0 },
{"fcvt.s.d",   0, INSN_CLASS_D,   "D,S,m",  MATCH_FCVT_S_D, MASK_FCVT_S_D, match_opcode, 0 },
{"fclass.d",   0, INSN_CLASS_D,   "d,S",  MATCH_FCLASS_D, MASK_FCLASS_D, match_opcode, 0 },
{"feq.d",      0, INSN_CLASS_D,   "d,S,T",    MATCH_FEQ_D, MASK_FEQ_D, match_opcode, 0 },
{"flt.d",      0, INSN_CLASS_D,   "d,S,T",    MATCH_FLT_D, MASK_FLT_D, match_opcode, 0 },
{"fle.d",      0, INSN_CLASS_D,   "d,S,T",    MATCH_FLE_D, MASK_FLE_D, match_opcode, 0 },
{"fgt.d",      0, INSN_CLASS_D,   "d,T,S",    MATCH_FLT_D, MASK_FLT_D, match_opcode, 0 },
{"fge.d",      0, INSN_CLASS_D,   "d,T,S",    MATCH_FLE_D, MASK_FLE_D, match_opcode, 0 },
{"fmv.x.d",   64, INSN_CLASS_D, "d,S",  MATCH_FMV_X_D, MASK_FMV_X_D, match_opcode, 0 },
{"fmv.d.x",   64, INSN_CLASS_D, "D,s",  MATCH_FMV_D_X, MASK_FMV_D_X, match_opcode, 0 },
{"fcvt.l.d",  64, INSN_CLASS_D, "d,S",  MATCH_FCVT_L_D | MASK_RM, MASK_FCVT_L_D | MASK_RM, match_opcode, 0 },
{"fcvt.l.d",  64, INSN_CLASS_D, "d,S,m",  MATCH_FCVT_L_D, MASK_FCVT_L_D, match_opcode, 0 },
{"fcvt.lu.d", 64, INSN_CLASS_D, "d,S",  MATCH_FCVT_LU_D | MASK_RM, MASK_FCVT_LU_D | MASK_RM, match_opcode, 0 },
{"fcvt.lu.d", 64, INSN_CLASS_D, "d,S,m",  MATCH_FCVT_LU_D, MASK_FCVT_LU_D, match_opcode, 0 },
{"fcvt.d.l",  64, INSN_CLASS_D, "D,s",  MATCH_FCVT_D_L | MASK_RM, MASK_FCVT_D_L | MASK_RM, match_opcode, 0 },
{"fcvt.d.l",  64, INSN_CLASS_D, "D,s,m",  MATCH_FCVT_D_L, MASK_FCVT_D_L, match_opcode, 0 },
{"fcvt.d.lu", 64, INSN_CLASS_D, "D,s",  MATCH_FCVT_D_LU | MASK_RM, MASK_FCVT_D_L | MASK_RM, match_opcode, 0 },
{"fcvt.d.lu", 64, INSN_CLASS_D, "D,s,m",  MATCH_FCVT_D_LU, MASK_FCVT_D_LU, match_opcode, 0 },

/* Quad-precision floating-point instruction subset */
{"flq",        0, INSN_CLASS_Q,   "D,o(s)",  MATCH_FLQ, MASK_FLQ, match_opcode, INSN_DREF|INSN_16_BYTE },
{"flq",        0, INSN_CLASS_Q,   "D,A,s",  0, (int) M_FLQ, match_never, INSN_MACRO },
{"fsq",        0, INSN_CLASS_Q,   "T,q(s)",  MATCH_FSQ, MASK_FSQ, match_opcode, INSN_DREF|INSN_16_BYTE },
{"fsq",        0, INSN_CLASS_Q,   "T,A,s",  0, (int) M_FSQ, match_never, INSN_MACRO },
{"fmv.q",      0, INSN_CLASS_Q,   "D,U",  MATCH_FSGNJ_Q, MASK_FSGNJ_Q, match_rs1_eq_rs2, INSN_ALIAS },
{"fneg.q",     0, INSN_CLASS_Q,   "D,U",  MATCH_FSGNJN_Q, MASK_FSGNJN_Q, match_rs1_eq_rs2, INSN_ALIAS },
{"fabs.q",     0, INSN_CLASS_Q,   "D,U",  MATCH_FSGNJX_Q, MASK_FSGNJX_Q, match_rs1_eq_rs2, INSN_ALIAS },
{"fsgnj.q",    0, INSN_CLASS_Q,   "D,S,T",  MATCH_FSGNJ_Q, MASK_FSGNJ_Q, match_opcode, 0 },
{"fsgnjn.q",   0, INSN_CLASS_Q,   "D,S,T",  MATCH_FSGNJN_Q, MASK_FSGNJN_Q, match_opcode, 0 },
{"fsgnjx.q",   0, INSN_CLASS_Q,   "D,S,T",  MATCH_FSGNJX_Q, MASK_FSGNJX_Q, match_opcode, 0 },
{"fadd.q",     0, INSN_CLASS_Q,   "D,S,T",  MATCH_FADD_Q | MASK_RM, MASK_FADD_Q | MASK_RM, match_opcode, 0 },
{"fadd.q",     0, INSN_CLASS_Q,   "D,S,T,m",  MATCH_FADD_Q, MASK_FADD_Q, match_opcode, 0 },
{"fsub.q",     0, INSN_CLASS_Q,   "D,S,T",  MATCH_FSUB_Q | MASK_RM, MASK_FSUB_Q | MASK_RM, match_opcode, 0 },
{"fsub.q",     0, INSN_CLASS_Q,   "D,S,T,m",  MATCH_FSUB_Q, MASK_FSUB_Q, match_opcode, 0 },
{"fmul.q",     0, INSN_CLASS_Q,   "D,S,T",  MATCH_FMUL_Q | MASK_RM, MASK_FMUL_Q | MASK_RM, match_opcode, 0 },
{"fmul.q",     0, INSN_CLASS_Q,   "D,S,T,m",  MATCH_FMUL_Q, MASK_FMUL_Q, match_opcode, 0 },
{"fdiv.q",     0, INSN_CLASS_Q,   "D,S,T",  MATCH_FDIV_Q | MASK_RM, MASK_FDIV_Q | MASK_RM, match_opcode, 0 },
{"fdiv.q",     0, INSN_CLASS_Q,   "D,S,T,m",  MATCH_FDIV_Q, MASK_FDIV_Q, match_opcode, 0 },
{"fsqrt.q",    0, INSN_CLASS_Q,   "D,S",  MATCH_FSQRT_Q | MASK_RM, MASK_FSQRT_Q | MASK_RM, match_opcode, 0 },
{"fsqrt.q",    0, INSN_CLASS_Q,   "D,S,m",  MATCH_FSQRT_Q, MASK_FSQRT_Q, match_opcode, 0 },
{"fmin.q",     0, INSN_CLASS_Q,   "D,S,T",  MATCH_FMIN_Q, MASK_FMIN_Q, match_opcode, 0 },
{"fmax.q",     0, INSN_CLASS_Q,   "D,S,T",  MATCH_FMAX_Q, MASK_FMAX_Q, match_opcode, 0 },
{"fmadd.q",    0, INSN_CLASS_Q,   "D,S,T,R",  MATCH_FMADD_Q | MASK_RM, MASK_FMADD_Q | MASK_RM, match_opcode, 0 },
{"fmadd.q",    0, INSN_CLASS_Q,   "D,S,T,R,m",  MATCH_FMADD_Q, MASK_FMADD_Q, match_opcode, 0 },
{"fnmadd.q",   0, INSN_CLASS_Q,   "D,S,T,R",  MATCH_FNMADD_Q | MASK_RM, MASK_FNMADD_Q | MASK_RM, match_opcode, 0 },
{"fnmadd.q",   0, INSN_CLASS_Q,   "D,S,T,R,m",  MATCH_FNMADD_Q, MASK_FNMADD_Q, match_opcode, 0 },
{"fmsub.q",    0, INSN_CLASS_Q,   "D,S,T,R",  MATCH_FMSUB_Q | MASK_RM, MASK_FMSUB_Q | MASK_RM, match_opcode, 0 },
{"fmsub.q",    0, INSN_CLASS_Q,   "D,S,T,R,m",  MATCH_FMSUB_Q, MASK_FMSUB_Q, match_opcode, 0 },
{"fnmsub.q",   0, INSN_CLASS_Q,   "D,S,T,R",  MATCH_FNMSUB_Q | MASK_RM, MASK_FNMSUB_Q | MASK_RM, match_opcode, 0 },
{"fnmsub.q",   0, INSN_CLASS_Q,   "D,S,T,R,m",  MATCH_FNMSUB_Q, MASK_FNMSUB_Q, match_opcode, 0 },
{"fcvt.w.q",   0, INSN_CLASS_Q,   "d,S",  MATCH_FCVT_W_Q | MASK_RM, MASK_FCVT_W_Q | MASK_RM, match_opcode, 0 },
{"fcvt.w.q",   0, INSN_CLASS_Q,   "d,S,m",  MATCH_FCVT_W_Q, MASK_FCVT_W_Q, match_opcode, 0 },
{"fcvt.wu.q",  0, INSN_CLASS_Q,   "d,S",  MATCH_FCVT_WU_Q | MASK_RM, MASK_FCVT_WU_Q | MASK_RM, match_opcode, 0 },
{"fcvt.wu.q",  0, INSN_CLASS_Q,   "d,S,m",  MATCH_FCVT_WU_Q, MASK_FCVT_WU_Q, match_opcode, 0 },
{"fcvt.q.w",   0, INSN_CLASS_Q,   "D,s",  MATCH_FCVT_Q_W, MASK_FCVT_Q_W | MASK_RM, match_opcode, 0 },
{"fcvt.q.wu",  0, INSN_CLASS_Q,   "D,s",  MATCH_FCVT_Q_WU, MASK_FCVT_Q_WU | MASK_RM, match_opcode, 0 },
{"fcvt.q.s",   0, INSN_CLASS_Q,   "D,S",  MATCH_FCVT_Q_S, MASK_FCVT_Q_S | MASK_RM, match_opcode, 0 },
{"fcvt.q.d",   0, INSN_CLASS_Q,   "D,S",  MATCH_FCVT_Q_D, MASK_FCVT_Q_D | MASK_RM, match_opcode, 0 },
{"fcvt.s.q",   0, INSN_CLASS_Q,   "D,S",  MATCH_FCVT_S_Q | MASK_RM, MASK_FCVT_S_Q | MASK_RM, match_opcode, 0 },
{"fcvt.s.q",   0, INSN_CLASS_Q,   "D,S,m",  MATCH_FCVT_S_Q, MASK_FCVT_S_Q, match_opcode, 0 },
{"fcvt.d.q",   0, INSN_CLASS_Q,   "D,S",  MATCH_FCVT_D_Q | MASK_RM, MASK_FCVT_D_Q | MASK_RM, match_opcode, 0 },
{"fcvt.d.q",   0, INSN_CLASS_Q,   "D,S,m",  MATCH_FCVT_D_Q, MASK_FCVT_D_Q, match_opcode, 0 },
{"fclass.q",   0, INSN_CLASS_Q,   "d,S",  MATCH_FCLASS_Q, MASK_FCLASS_Q, match_opcode, 0 },
{"feq.q",      0, INSN_CLASS_Q,   "d,S,T",    MATCH_FEQ_Q, MASK_FEQ_Q, match_opcode, 0 },
{"flt.q",      0, INSN_CLASS_Q,   "d,S,T",    MATCH_FLT_Q, MASK_FLT_Q, match_opcode, 0 },
{"fle.q",      0, INSN_CLASS_Q,   "d,S,T",    MATCH_FLE_Q, MASK_FLE_Q, match_opcode, 0 },
{"fgt.q",      0, INSN_CLASS_Q,   "d,T,S",    MATCH_FLT_Q, MASK_FLT_Q, match_opcode, 0 },
{"fge.q",      0, INSN_CLASS_Q,   "d,T,S",    MATCH_FLE_Q, MASK_FLE_Q, match_opcode, 0 },
{"fmv.x.q",   64, INSN_CLASS_Q, "d,S",  MATCH_FMV_X_Q, MASK_FMV_X_Q, match_opcode, 0 },
{"fmv.q.x",   64, INSN_CLASS_Q, "D,s",  MATCH_FMV_Q_X, MASK_FMV_Q_X, match_opcode, 0 },
{"fcvt.l.q",  64, INSN_CLASS_Q, "d,S",  MATCH_FCVT_L_Q | MASK_RM, MASK_FCVT_L_Q | MASK_RM, match_opcode, 0 },
{"fcvt.l.q",  64, INSN_CLASS_Q, "d,S,m",  MATCH_FCVT_L_Q, MASK_FCVT_L_Q, match_opcode, 0 },
{"fcvt.lu.q", 64, INSN_CLASS_Q, "d,S",  MATCH_FCVT_LU_Q | MASK_RM, MASK_FCVT_LU_Q | MASK_RM, match_opcode, 0 },
{"fcvt.lu.q", 64, INSN_CLASS_Q, "d,S,m",  MATCH_FCVT_LU_Q, MASK_FCVT_LU_Q, match_opcode, 0 },
{"fcvt.q.l",  64, INSN_CLASS_Q, "D,s",  MATCH_FCVT_Q_L | MASK_RM, MASK_FCVT_Q_L | MASK_RM, match_opcode, 0 },
{"fcvt.q.l",  64, INSN_CLASS_Q, "D,s,m",  MATCH_FCVT_Q_L, MASK_FCVT_Q_L, match_opcode, 0 },
{"fcvt.q.lu", 64, INSN_CLASS_Q, "D,s",  MATCH_FCVT_Q_LU | MASK_RM, MASK_FCVT_Q_L | MASK_RM, match_opcode, 0 },
{"fcvt.q.lu", 64, INSN_CLASS_Q, "D,s,m",  MATCH_FCVT_Q_LU, MASK_FCVT_Q_LU, match_opcode, 0 },

/* Compressed instructions.  */
{"c.unimp",    0, INSN_CLASS_C,   "",  0, 0xffffU,  match_opcode, 0 },
{"c.ebreak",   0, INSN_CLASS_C,   "",  MATCH_C_EBREAK, MASK_C_EBREAK, match_opcode, 0 },
{"c.jr",       0, INSN_CLASS_C,   "d",  MATCH_C_JR, MASK_C_JR, match_rd_nonzero, INSN_BRANCH },
{"c.jalr",     0, INSN_CLASS_C,   "d",  MATCH_C_JALR, MASK_C_JALR, match_rd_nonzero, INSN_JSR },
{"c.j",        0, INSN_CLASS_C,   "Ca",  MATCH_C_J, MASK_C_J, match_opcode, INSN_BRANCH },
{"c.jal",     32, INSN_CLASS_C, "Ca",  MATCH_C_JAL, MASK_C_JAL, match_opcode, INSN_JSR },
{"c.beqz",     0, INSN_CLASS_C,   "Cs,Cp",  MATCH_C_BEQZ, MASK_C_BEQZ, match_opcode, INSN_CONDBRANCH },
{"c.bnez",     0, INSN_CLASS_C,   "Cs,Cp",  MATCH_C_BNEZ, MASK_C_BNEZ, match_opcode, INSN_CONDBRANCH },
{"c.lwsp",     0, INSN_CLASS_C,   "d,Cm(Cc)",  MATCH_C_LWSP, MASK_C_LWSP, match_rd_nonzero, 0 },
{"c.lw",       0, INSN_CLASS_C,   "Ct,Ck(Cs)",  MATCH_C_LW, MASK_C_LW, match_opcode, INSN_DREF|INSN_4_BYTE },
{"c.swsp",     0, INSN_CLASS_C,   "CV,CM(Cc)",  MATCH_C_SWSP, MASK_C_SWSP, match_opcode, INSN_DREF|INSN_4_BYTE },
{"c.sw",       0, INSN_CLASS_C,   "Ct,Ck(Cs)",  MATCH_C_SW, MASK_C_SW, match_opcode, INSN_DREF|INSN_4_BYTE },
{"c.nop",      0, INSN_CLASS_C,   "",  MATCH_C_ADDI, 0xffff, match_opcode, INSN_ALIAS },
{"c.nop",      0, INSN_CLASS_C,   "Cj",  MATCH_C_ADDI, MASK_C_ADDI | MASK_RD, match_opcode, INSN_ALIAS },
{"c.mv",       0, INSN_CLASS_C,   "d,CV",  MATCH_C_MV, MASK_C_MV, match_c_add_with_hint, 0 },
{"c.lui",      0, INSN_CLASS_C,   "d,Cu",  MATCH_C_LUI, MASK_C_LUI, match_c_lui_with_hint, 0 },
{"c.li",       0, INSN_CLASS_C,   "d,Co",  MATCH_C_LI, MASK_C_LI, match_opcode, 0 },
{"c.addi4spn", 0, INSN_CLASS_C,   "Ct,Cc,CK", MATCH_C_ADDI4SPN, MASK_C_ADDI4SPN, match_c_addi4spn, 0 },
{"c.addi16sp", 0, INSN_CLASS_C,   "Cc,CL", MATCH_C_ADDI16SP, MASK_C_ADDI16SP, match_c_addi16sp, 0 },
{"c.addi",     0, INSN_CLASS_C,   "d,Co",  MATCH_C_ADDI, MASK_C_ADDI, match_opcode, 0 },
{"c.add",      0, INSN_CLASS_C,   "d,CV",  MATCH_C_ADD, MASK_C_ADD, match_c_add_with_hint, 0 },
{"c.sub",      0, INSN_CLASS_C,   "Cs,Ct",  MATCH_C_SUB, MASK_C_SUB, match_opcode, 0 },
{"c.and",      0, INSN_CLASS_C,   "Cs,Ct",  MATCH_C_AND, MASK_C_AND, match_opcode, 0 },
{"c.or",       0, INSN_CLASS_C,   "Cs,Ct",  MATCH_C_OR, MASK_C_OR, match_opcode, 0 },
{"c.xor",      0, INSN_CLASS_C,   "Cs,Ct",  MATCH_C_XOR, MASK_C_XOR, match_opcode, 0 },
{"c.slli",     0, INSN_CLASS_C,   "d,C>",  MATCH_C_SLLI, MASK_C_SLLI, match_c_slli, 0 },
{"c.srli",     0, INSN_CLASS_C,   "Cs,C>",  MATCH_C_SRLI, MASK_C_SRLI, match_c_slli, 0 },
{"c.srai",     0, INSN_CLASS_C,   "Cs,C>",  MATCH_C_SRAI, MASK_C_SRAI, match_c_slli, 0 },
{"c.slli64",   0, INSN_CLASS_C,   "d",  MATCH_C_SLLI64, MASK_C_SLLI64, match_c_slli64, 0 },
{"c.srli64",   0, INSN_CLASS_C,   "Cs",  MATCH_C_SRLI64, MASK_C_SRLI64, match_c_slli64, 0 },
{"c.srai64",   0, INSN_CLASS_C,   "Cs",  MATCH_C_SRAI64, MASK_C_SRAI64, match_c_slli64, 0 },
{"c.andi",     0, INSN_CLASS_C,   "Cs,Co",  MATCH_C_ANDI, MASK_C_ANDI, match_opcode, 0 },
{"c.addiw",   64, INSN_CLASS_C, "d,Co",  MATCH_C_ADDIW, MASK_C_ADDIW, match_rd_nonzero, 0 },
{"c.addw",    64, INSN_CLASS_C, "Cs,Ct",  MATCH_C_ADDW, MASK_C_ADDW, match_opcode, 0 },
{"c.subw",    64, INSN_CLASS_C, "Cs,Ct",  MATCH_C_SUBW, MASK_C_SUBW, match_opcode, 0 },
{"c.ldsp",    64, INSN_CLASS_C, "d,Cn(Cc)",  MATCH_C_LDSP, MASK_C_LDSP, match_rd_nonzero, INSN_DREF|INSN_8_BYTE },
{"c.ld",      64, INSN_CLASS_C, "Ct,Cl(Cs)",  MATCH_C_LD, MASK_C_LD, match_opcode, INSN_DREF|INSN_8_BYTE },
{"c.sdsp",    64, INSN_CLASS_C, "CV,CN(Cc)",  MATCH_C_SDSP, MASK_C_SDSP, match_opcode, INSN_DREF|INSN_8_BYTE },
{"c.sd",      64, INSN_CLASS_C, "Ct,Cl(Cs)",  MATCH_C_SD, MASK_C_SD, match_opcode, INSN_DREF|INSN_8_BYTE },
{"c.fldsp",    0, INSN_CLASS_D_AND_C,   "D,Cn(Cc)",  MATCH_C_FLDSP, MASK_C_FLDSP, match_opcode, INSN_DREF|INSN_8_BYTE },
{"c.fld",      0, INSN_CLASS_D_AND_C,   "CD,Cl(Cs)",  MATCH_C_FLD, MASK_C_FLD, match_opcode, INSN_DREF|INSN_8_BYTE },
{"c.fsdsp",    0, INSN_CLASS_D_AND_C,   "CT,CN(Cc)",  MATCH_C_FSDSP, MASK_C_FSDSP, match_opcode, INSN_DREF|INSN_8_BYTE },
{"c.fsd",      0, INSN_CLASS_D_AND_C,   "CD,Cl(Cs)",  MATCH_C_FSD, MASK_C_FSD, match_opcode, INSN_DREF|INSN_8_BYTE },
{"c.flwsp",   32, INSN_CLASS_F_AND_C, "D,Cm(Cc)",  MATCH_C_FLWSP, MASK_C_FLWSP, match_opcode, INSN_DREF|INSN_4_BYTE },
{"c.flw",     32, INSN_CLASS_F_AND_C, "CD,Ck(Cs)",  MATCH_C_FLW, MASK_C_FLW, match_opcode, INSN_DREF|INSN_4_BYTE },
{"c.fswsp",   32, INSN_CLASS_F_AND_C, "CT,CM(Cc)",  MATCH_C_FSWSP, MASK_C_FSWSP, match_opcode, INSN_DREF|INSN_4_BYTE },
{"c.fsw",     32, INSN_CLASS_F_AND_C, "CD,Ck(Cs)",  MATCH_C_FSW, MASK_C_FSW, match_opcode, INSN_DREF|INSN_4_BYTE },

/* Supervisor instructions */
{"csrr",       0, INSN_CLASS_I,   "d,E",  MATCH_CSRRS, MASK_CSRRS | MASK_RS1, match_opcode, INSN_ALIAS },
{"csrwi",      0, INSN_CLASS_I,   "E,Z",  MATCH_CSRRWI, MASK_CSRRWI | MASK_RD, match_opcode, INSN_ALIAS },
{"csrsi",      0, INSN_CLASS_I,   "E,Z",  MATCH_CSRRSI, MASK_CSRRSI | MASK_RD, match_opcode, INSN_ALIAS },
{"csrci",      0, INSN_CLASS_I,   "E,Z",  MATCH_CSRRCI, MASK_CSRRCI | MASK_RD, match_opcode, INSN_ALIAS },
{"csrw",       0, INSN_CLASS_I,   "E,s",  MATCH_CSRRW, MASK_CSRRW | MASK_RD, match_opcode, INSN_ALIAS },
{"csrw",       0, INSN_CLASS_I,   "E,Z",  MATCH_CSRRWI, MASK_CSRRWI | MASK_RD, match_opcode, INSN_ALIAS },
{"csrs",       0, INSN_CLASS_I,   "E,s",  MATCH_CSRRS, MASK_CSRRS | MASK_RD, match_opcode, INSN_ALIAS },
{"csrs",       0, INSN_CLASS_I,   "E,Z",  MATCH_CSRRSI, MASK_CSRRSI | MASK_RD, match_opcode, INSN_ALIAS },
{"csrc",       0, INSN_CLASS_I,   "E,s",  MATCH_CSRRC, MASK_CSRRC | MASK_RD, match_opcode, INSN_ALIAS },
{"csrc",       0, INSN_CLASS_I,   "E,Z",  MATCH_CSRRCI, MASK_CSRRCI | MASK_RD, match_opcode, INSN_ALIAS },
{"csrrwi",     0, INSN_CLASS_I,   "d,E,Z",  MATCH_CSRRWI, MASK_CSRRWI, match_opcode, 0 },
{"csrrsi",     0, INSN_CLASS_I,   "d,E,Z",  MATCH_CSRRSI, MASK_CSRRSI, match_opcode, 0 },
{"csrrci",     0, INSN_CLASS_I,   "d,E,Z",  MATCH_CSRRCI, MASK_CSRRCI, match_opcode, 0 },
{"csrrw",      0, INSN_CLASS_I,   "d,E,s",  MATCH_CSRRW, MASK_CSRRW, match_opcode, 0 },
{"csrrw",      0, INSN_CLASS_I,   "d,E,Z",  MATCH_CSRRWI, MASK_CSRRWI, match_opcode, INSN_ALIAS },
{"csrrs",      0, INSN_CLASS_I,   "d,E,s",  MATCH_CSRRS, MASK_CSRRS, match_opcode, 0 },
{"csrrs",      0, INSN_CLASS_I,   "d,E,Z",  MATCH_CSRRSI, MASK_CSRRSI, match_opcode, INSN_ALIAS },
{"csrrc",      0, INSN_CLASS_I,   "d,E,s",  MATCH_CSRRC, MASK_CSRRC, match_opcode, 0 },
{"csrrc",      0, INSN_CLASS_I,   "d,E,Z",  MATCH_CSRRCI, MASK_CSRRCI, match_opcode, INSN_ALIAS },
{"uret",       0, INSN_CLASS_I,   "",     MATCH_URET, MASK_URET, match_opcode, 0 },
{"sret",       0, INSN_CLASS_I,   "",     MATCH_SRET, MASK_SRET, match_opcode, 0 },
{"hret",       0, INSN_CLASS_I,   "",     MATCH_HRET, MASK_HRET, match_opcode, 0 },
{"mret",       0, INSN_CLASS_I,   "",     MATCH_MRET, MASK_MRET, match_opcode, 0 },
{"dret",       0, INSN_CLASS_I,   "",     MATCH_DRET, MASK_DRET, match_opcode, 0 },
{"sfence.vm",  0, INSN_CLASS_I,   "",     MATCH_SFENCE_VM, MASK_SFENCE_VM | MASK_RS1, match_opcode, 0 },
{"sfence.vm",  0, INSN_CLASS_I,   "s",    MATCH_SFENCE_VM, MASK_SFENCE_VM, match_opcode, 0 },
{"sfence.vma", 0, INSN_CLASS_I,   "",     MATCH_SFENCE_VMA, MASK_SFENCE_VMA | MASK_RS1 | MASK_RS2, match_opcode, INSN_ALIAS },
{"sfence.vma", 0, INSN_CLASS_I,   "s",    MATCH_SFENCE_VMA, MASK_SFENCE_VMA | MASK_RS2, match_opcode, INSN_ALIAS },
{"sfence.vma", 0, INSN_CLASS_I,   "s,t",  MATCH_SFENCE_VMA, MASK_SFENCE_VMA, match_opcode, 0 },
{"wfi",        0, INSN_CLASS_I,   "",     MATCH_WFI, MASK_WFI, match_opcode, 0 },

/* Terminate the list.  */
{0, 0, INSN_CLASS_NONE, 0, 0, 0, 0, 0}
};
static const unsigned long opcodesnum =
  sizeof (riscv_opcodes) / sizeof (riscv_opcodes[0]);
/* Instruction format for .insn directive.  */
const struct riscv_opcode riscv_insn_types[] =
{
/* name, xlen, isa,          operands, match, mask,    match_func, pinfo.  */
{"r",       0, INSN_CLASS_I,  "O4,F3,F7,d,s,t",     0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F7,D,s,t",     0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F7,d,S,t",     0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F7,D,S,t",     0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F7,d,s,T",     0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F7,D,s,T",     0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F7,d,S,T",     0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F7,D,S,T",     0,    0,  match_opcode, 0 },

{"r",       0, INSN_CLASS_I,  "O4,F3,F2,d,s,t,r",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,D,s,t,r",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,d,S,t,r",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,D,S,t,r",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,d,s,T,r",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,D,s,T,r",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,d,S,T,r",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,D,S,T,r",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,d,s,t,R",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,D,s,t,R",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,d,S,t,R",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,D,S,t,R",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,d,s,T,R",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,D,s,T,R",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,d,S,T,R",   0,    0,  match_opcode, 0 },
{"r",       0, INSN_CLASS_F,  "O4,F3,F2,D,S,T,R",   0,    0,  match_opcode, 0 },

{"r4",      0, INSN_CLASS_I,  "O4,F3,F2,d,s,t,r",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,D,s,t,r",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,d,S,t,r",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,D,S,t,r",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,d,s,T,r",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,D,s,T,r",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,d,S,T,r",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,D,S,T,r",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,d,s,t,R",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,D,s,t,R",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,d,S,t,R",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,D,S,t,R",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,d,s,T,R",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,D,s,T,R",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,d,S,T,R",   0,    0,  match_opcode, 0 },
{"r4",      0, INSN_CLASS_F,  "O4,F3,F2,D,S,T,R",   0,    0,  match_opcode, 0 },

{"i",       0, INSN_CLASS_I,  "O4,F3,d,s,j",        0,    0,  match_opcode, 0 },
{"i",       0, INSN_CLASS_F,  "O4,F3,D,s,j",        0,    0,  match_opcode, 0 },
{"i",       0, INSN_CLASS_F,  "O4,F3,d,S,j",        0,    0,  match_opcode, 0 },
{"i",       0, INSN_CLASS_F,  "O4,F3,D,S,j",        0,    0,  match_opcode, 0 },

{"i",       0, INSN_CLASS_I,  "O4,F3,d,o(s)",       0,    0,  match_opcode, 0 },
{"i",       0, INSN_CLASS_F,  "O4,F3,D,o(s)",       0,    0,  match_opcode, 0 },

{"s",       0, INSN_CLASS_I,  "O4,F3,t,q(s)",       0,    0,  match_opcode, 0 },
{"s",       0, INSN_CLASS_F,  "O4,F3,T,q(s)",       0,    0,  match_opcode, 0 },

{"sb",      0, INSN_CLASS_I,  "O4,F3,s,t,p",        0,    0,  match_opcode, 0 },
{"sb",      0, INSN_CLASS_F,  "O4,F3,S,t,p",        0,    0,  match_opcode, 0 },
{"sb",      0, INSN_CLASS_F,  "O4,F3,s,T,p",        0,    0,  match_opcode, 0 },
{"sb",      0, INSN_CLASS_F,  "O4,F3,S,T,p",        0,    0,  match_opcode, 0 },

{"b",      0, INSN_CLASS_I,  "O4,F3,s,t,p",        0,    0,  match_opcode, 0 },
{"b",      0, INSN_CLASS_F,  "O4,F3,S,t,p",        0,    0,  match_opcode, 0 },
{"b",      0, INSN_CLASS_F,  "O4,F3,s,T,p",        0,    0,  match_opcode, 0 },
{"b",      0, INSN_CLASS_F,  "O4,F3,S,T,p",        0,    0,  match_opcode, 0 },

{"u",       0, INSN_CLASS_I,  "O4,d,u",             0,    0,  match_opcode, 0 },
{"u",       0, INSN_CLASS_F,  "O4,D,u",             0,    0,  match_opcode, 0 },

{"uj",      0, INSN_CLASS_I,  "O4,d,a",             0,    0,  match_opcode, 0 },
{"uj",      0, INSN_CLASS_F,  "O4,D,a",             0,    0,  match_opcode, 0 },

{"j",      0, INSN_CLASS_I,  "O4,d,a",             0,    0,  match_opcode, 0 },
{"j",      0, INSN_CLASS_F,  "O4,D,a",             0,    0,  match_opcode, 0 },

{"cr",      0, INSN_CLASS_C,  "O2,CF4,d,CV",        0,    0,  match_opcode, 0 },
{"cr",      0, INSN_CLASS_F_AND_C,  "O2,CF4,D,CV",        0,    0,  match_opcode, 0 },
{"cr",      0, INSN_CLASS_F_AND_C,  "O2,CF4,d,CT",        0,    0,  match_opcode, 0 },
{"cr",      0, INSN_CLASS_F_AND_C,  "O2,CF4,D,CT",        0,    0,  match_opcode, 0 },

{"ci",      0, INSN_CLASS_C,  "O2,CF3,d,Co",        0,    0,  match_opcode, 0 },
{"ci",      0, INSN_CLASS_F_AND_C,  "O2,CF3,D,Co",        0,    0,  match_opcode, 0 },

{"ciw",     0, INSN_CLASS_C,  "O2,CF3,Ct,C8",       0,    0,  match_opcode, 0 },
{"ciw",     0, INSN_CLASS_F_AND_C,  "O2,CF3,CD,C8",       0,    0,  match_opcode, 0 },

{"ca",      0, INSN_CLASS_C,  "O2,CF6,CF2,Cs,Ct",   0,    0,  match_opcode, 0 },
{"ca",      0, INSN_CLASS_F_AND_C,  "O2,CF6,CF2,CS,Ct",   0,    0,  match_opcode, 0 },
{"ca",      0, INSN_CLASS_F_AND_C,  "O2,CF6,CF2,Cs,CD",   0,    0,  match_opcode, 0 },
{"ca",      0, INSN_CLASS_F_AND_C,  "O2,CF6,CF2,CS,CD",   0,    0,  match_opcode, 0 },

{"cb",      0, INSN_CLASS_C,  "O2,CF3,Cs,Cp",       0,    0,  match_opcode, 0 },
{"cb",      0, INSN_CLASS_F_AND_C,  "O2,CF3,CS,Cp",       0,    0,  match_opcode, 0 },

{"cj",      0, INSN_CLASS_C,  "O2,CF3,Ca",          0,    0,  match_opcode, 0 },
/* Terminate the list.  */
{0, 0, INSN_CLASS_NONE, 0, 0, 0, 0, 0}
};

/* All standard extensions defined in all supported ISA spec.  */
const struct riscv_ext_version riscv_ext_version_table[] =
{
/* name, ISA spec, major version, minor_version.  */
{"e", ISA_SPEC_CLASS_20191213, 1, 9},
{"e", ISA_SPEC_CLASS_20190608, 1, 9},
{"e", ISA_SPEC_CLASS_2P2,      1, 9},

{"i", ISA_SPEC_CLASS_20191213, 2, 1},
{"i", ISA_SPEC_CLASS_20190608, 2, 1},
{"i", ISA_SPEC_CLASS_2P2,      2, 0},

{"m", ISA_SPEC_CLASS_20191213, 2, 0},
{"m", ISA_SPEC_CLASS_20190608, 2, 0},
{"m", ISA_SPEC_CLASS_2P2,      2, 0},

{"a", ISA_SPEC_CLASS_20191213, 2, 1},
{"a", ISA_SPEC_CLASS_20190608, 2, 0},
{"a", ISA_SPEC_CLASS_2P2,      2, 0},

{"f", ISA_SPEC_CLASS_20191213, 2, 2},
{"f", ISA_SPEC_CLASS_20190608, 2, 2},
{"f", ISA_SPEC_CLASS_2P2,      2, 0},

{"d", ISA_SPEC_CLASS_20191213, 2, 2},
{"d", ISA_SPEC_CLASS_20190608, 2, 2},
{"d", ISA_SPEC_CLASS_2P2,      2, 0},

{"q", ISA_SPEC_CLASS_20191213, 2, 2},
{"q", ISA_SPEC_CLASS_20190608, 2, 2},
{"q", ISA_SPEC_CLASS_2P2,      2, 0},

{"c", ISA_SPEC_CLASS_20191213, 2, 0},
{"c", ISA_SPEC_CLASS_20190608, 2, 0},
{"c", ISA_SPEC_CLASS_2P2,      2, 0},

{"p", ISA_SPEC_CLASS_20191213, 0, 2},
{"p", ISA_SPEC_CLASS_20190608, 0, 2},
{"p", ISA_SPEC_CLASS_2P2,      0, 1},

{"v", ISA_SPEC_CLASS_20191213, 0, 7},
{"v", ISA_SPEC_CLASS_20190608, 0, 7},
{"v", ISA_SPEC_CLASS_2P2,      0, 7},

{"n", ISA_SPEC_CLASS_20190608, 1, 1},
{"n", ISA_SPEC_CLASS_2P2,      1, 1},

{"zicsr", ISA_SPEC_CLASS_20191213, 2, 0},
{"zicsr", ISA_SPEC_CLASS_20190608, 2, 0},

/* Terminate the list.  */
{NULL, 0, 0, 0}
};

struct isa_spec_t
{
  const char *name;
  enum riscv_isa_spec_class class;
};

/* List for all supported ISA spec versions.  */
static const struct isa_spec_t isa_specs[] =
{
  {"2.2",      ISA_SPEC_CLASS_2P2},
  {"20190608", ISA_SPEC_CLASS_20190608},
  {"20191213", ISA_SPEC_CLASS_20191213},

/* Terminate the list.  */
  {NULL, 0}
};

/* Get the corresponding ISA spec class by giving a ISA spec string.  */

int
riscv_get_isa_spec_class (const char *s,
                         enum riscv_isa_spec_class *class)
{
  const struct isa_spec_t *version;

  if (s == NULL)
    return 0;

  for (version = &isa_specs[0]; version->name != NULL; ++version)
    if (strcmp (version->name, s) == 0)
      {
       *class = version->class;
       return 1;
      }

  /* Can not find the supported ISA spec.  */
  return 0;
}

/* Begin concat of riscv-dis.c  */
static enum riscv_priv_spec_class default_priv_spec = PRIV_SPEC_CLASS_NONE;

struct riscv_private_data
{
  unsigned long gp;
  unsigned long print_addr;
  unsigned long hi_addr[OP_MASK_RD + 1];
};

static const char * const *riscv_gpr_names;
static const char * const *riscv_fpr_names;

/* Other options.  */
static int no_aliases;	/* If set disassemble as most general inst.  */

static void
set_default_riscv_dis_options (void)
{
  riscv_gpr_names = riscv_gpr_names_abi;
  riscv_fpr_names = riscv_fpr_names_abi;
  no_aliases = 0;
}



/* Print one argument from an array.  */

static void
arg_print (struct disassemble_info *info, unsigned long val,
	   const char* const* array, size_t size)
{
  const char *s = val >= size || array[val] == NULL ? "unknown" : array[val];
  printf( "%s", s);
}
static void
maybe_print_address (struct riscv_private_data *pd, int base_reg, int offset)
{
  if (pd->hi_addr[base_reg] != (unsigned long)-1)
    {
		// increment pointer adress 
      pd->print_addr = (base_reg != 0 ? pd->hi_addr[base_reg] : 0) + offset;
      pd->hi_addr[base_reg] = -1;
    }
  else if (base_reg == X_GP && pd->gp != (unsigned long)-1)
    pd->print_addr = pd->gp + offset;
  else if (base_reg == X_TP || base_reg == 0)
    pd->print_addr = offset;
}

/* Print insn arguments for 32/64-bit code.  */

static void
print_insn_args (const char *d, unsigned long long l, unsigned long pc, struct disassemble_info *info,struct riscv_opcode *insn)
{
	unsigned long GPR[3] = {0,0,0,0};
	int status_gpr = 0;
	long long immediatedata = 0;
  int rs1 = (l >> OP_SH_RS1) & OP_MASK_RS1;
  int rd = (l >> OP_SH_RD) & OP_MASK_RD;

  if (*d != '\0')
    printf ("\t");

  for (; *d != '\0'; d++)
    {
      switch (*d)
	{
	case 'C': /* RVC */
	  switch (*++d)
	    {
	    case 's': /* RS1 x8-x15 */
	    case 'w': /* RS1 x8-x15 */
	      printf ("%s",
		     riscv_gpr_names[EXTRACT_OPERAND (CRS1S, l) + 8]);
		     GPR[status_gpr] = 31+EXTRACT_OPERAND (CRS1S, l) + 8;
		     status_gpr++;
	      break;
	    case 't': /* RS2 x8-x15 */
	    case 'x': /* RS2 x8-x15 */
	      printf ( "%s",
		     riscv_gpr_names[EXTRACT_OPERAND (CRS2S, l) + 8]);
		      GPR[status_gpr] = 31+EXTRACT_OPERAND (CRS1S, l) + 8;
		     status_gpr++;
	      break;
	    case 'U': /* RS1, constrained to equal RD */
	      printf ("%s", riscv_gpr_names[rd]);
	       GPR[status_gpr] = 31+rd;
		     status_gpr++;
	      break;
	    case 'c': /* RS1, constrained to equal sp */
	      printf ("%s", riscv_gpr_names[X_SP]);
	       GPR[status_gpr] = 31+X_SP;
		     status_gpr++;
	      break;
	    case 'V': /* RS2 */
	      printf ( "%s",
		     riscv_gpr_names[EXTRACT_OPERAND (CRS2, l)]);
		     GPR[status_gpr] = 31+EXTRACT_OPERAND (CRS2, l);
		     status_gpr++;
	      break;
	    case 'i':
	      printf ("%d", (int)EXTRACT_RVC_SIMM3 (l));
	      immediatedata = EXTRACT_RVC_SIMM3 (l);
	      break;
	    case 'o':
	    case 'j':
	      printf ("%d", (int)EXTRACT_RVC_IMM (l));
	      	      immediatedata = EXTRACT_RVC_IMM (l);

	      break;
	    case 'k':
	      printf ("%d", (int)EXTRACT_RVC_LW_IMM (l));
	      	      	      immediatedata = EXTRACT_RVC_LW_IMM (l);

	      break;
	    case 'l':
	      printf ("%d", (int)EXTRACT_RVC_LD_IMM (l));
	      	immediatedata = EXTRACT_RVC_LD_IMM (l);

	      break;
	    case 'm':
	      printf ("%d", (int)EXTRACT_RVC_LWSP_IMM (l));
	      	immediatedata = EXTRACT_RVC_LWSP_IMM (l);
	      
	      break;
	    case 'n':
	      printf ("%d", (int)EXTRACT_RVC_LDSP_IMM (l));
	    	      	immediatedata = EXTRACT_RVC_LWSP_IMM (l);
  
	      break;
	    case 'K':
	      printf ( "%d", (int)EXTRACT_RVC_ADDI4SPN_IMM (l));
	      	    	      	immediatedata = EXTRACT_RVC_ADDI4SPN_IMM (l);

	      break;
	    case 'L':
	      printf ("%d", (int)EXTRACT_RVC_ADDI16SP_IMM (l));
	   	      	    	      	immediatedata = EXTRACT_RVC_ADDI16SP_IMM (l);
   
	      break;
	    case 'M':
	      printf ("%d", (int)EXTRACT_RVC_SWSP_IMM (l));
	      	   	      	    	      	immediatedata = EXTRACT_RVC_SWSP_IMM (l);

	      break;
	    case 'N':
	      printf ("%d", (int)EXTRACT_RVC_SDSP_IMM (l));
	      	      	   	      	    	      	immediatedata = EXTRACT_RVC_SDSP_IMM (l);

	      break;
	    case 'p':
	      
	      break;
	    case 'a':
	      //~ info->target = EXTRACT_RVC_J_IMM (l) + pc;
	      //~ (*info->print_address_func) (info->target, info);
	      break;
	    case 'u':
	      printf ( "0x%x",
		     (int)(EXTRACT_RVC_IMM (l) & (RISCV_BIGIMM_REACH-1)));
		     	      	      	   	      	    	      	immediatedata = EXTRACT_RVC_IMM (l) & (RISCV_BIGIMM_REACH-1);

	      break;
	    case '>':
	      printf ("0x%x", (int)EXTRACT_RVC_IMM (l) & 0x3f);
	      
	      immediatedata = EXTRACT_RVC_IMM (l) & 0x3f;

	      break;
	    case '<':
	      printf ("0x%x", (int)EXTRACT_RVC_IMM (l) & 0x1f);
	      	
	      	immediatedata = EXTRACT_RVC_IMM (l) & 0x1f;

	      break;
	    case 'T': /* floating-point RS2 */
	      printf ("%s",
		     riscv_fpr_names[EXTRACT_OPERAND (CRS2, l)]);
		   
	      break;
	    case 'D': /* floating-point RS2 x8-x15 */
	      printf ("%s",
		     riscv_fpr_names[EXTRACT_OPERAND (CRS2S, l) + 8]);
	      break;
	    }
	  break;

	case ',':
	case '(':
	case ')':
	case '[':
	case ']':
	  printf ("%c", *d);
	  break;

	case '0':
	  /* Only print constant 0 if it is the last argument */
	  if (!d[1])
	    printf ("0");
	  break;

	case 'b':
	case 's':
	  if ((l & MASK_JALR) == MATCH_JALR)
	    maybe_print_address ((void*)0, rs1, 0);
	  printf ("%s", riscv_gpr_names[rs1]);
	   //~ GPR[status_gpr] = 31+rs1;
		     //~ status_gpr++;
	  break;

	case 't':
	  printf ("%s",
		 riscv_gpr_names[EXTRACT_OPERAND (RS2, l)]);
		 GPR[status_gpr] = 31+EXTRACT_OPERAND (RS2, l);
		     status_gpr++;
	  break;

	case 'u':
	  printf ("0x%x",
		 (unsigned)EXTRACT_UTYPE_IMM (l) >> RISCV_IMM_BITS);
		 	      	immediatedata = (unsigned)EXTRACT_UTYPE_IMM (l) >> RISCV_IMM_BITS;

	  break;

	case 'm':
	  arg_print (info, EXTRACT_OPERAND (RM, l),
		     riscv_rm, ARRAY_SIZE (riscv_rm));
	  break;

	case 'P':
	  arg_print (info, EXTRACT_OPERAND (PRED, l),
		     riscv_pred_succ, ARRAY_SIZE (riscv_pred_succ));
	  break;

	case 'Q':
	  arg_print (info, EXTRACT_OPERAND (SUCC, l),
		     riscv_pred_succ, ARRAY_SIZE (riscv_pred_succ));
	  break;

	case 'o':
	  maybe_print_address ((void*)0, rs1, EXTRACT_ITYPE_IMM (l));
	  /* Fall through.  */
	case 'j':
	  if (((l & MASK_ADDI) == MATCH_ADDI && rs1 != 0)
	      || (l & MASK_JALR) == MATCH_JALR)
	    maybe_print_address ((void*)0, rs1, EXTRACT_ITYPE_IMM (l));
	  printf ("%d", (int)EXTRACT_ITYPE_IMM (l));
	  	  	  	  immediatedata = EXTRACT_ITYPE_IMM (l);

	  break;

	case 'q':
	  maybe_print_address ((void*)0, rs1, EXTRACT_STYPE_IMM (l));
	  printf ("%d", (int)EXTRACT_STYPE_IMM (l));
	  	  	  immediatedata = EXTRACT_STYPE_IMM (l);

	  break;

	case 'a':
	  //~ info->target = EXTRACT_UJTYPE_IMM (l) + pc;
	  // immediate here 
	  //~ (*info->print_address_func) (info->target, info);
	  printf("immediate data \n");
	  immediatedata = EXTRACT_UJTYPE_IMM (l) + pc;
	  
	  break;

	case 'p':
	  //~ info->target = EXTRACT_SBTYPE_IMM (l) + pc;
	  // poitner adresse
	  //~ (*info->print_address_func) (info->target, info);
	  	  printf("immediate data \n");

	  	  immediatedata = EXTRACT_SBTYPE_IMM (l) + pc;

	  break;

	case 'd':
	  if ((l & MASK_AUIPC) == MATCH_AUIPC) {
	    //~ pd->hi_addr[rd] = pc + EXTRACT_UTYPE_IMM (l);
	    // immediate ere 
			printf("immediate data \n");
			immediatedata = pc + EXTRACT_UTYPE_IMM (l);


	  } else if ((l & MASK_LUI) == MATCH_LUI) {
	    //~ pd->hi_addr[rd] = EXTRACT_UTYPE_IMM (l);
	    // immediate increment attention 
			immediatedata = EXTRACT_UTYPE_IMM (l);


	   } else if ((l & MASK_C_LUI) == MATCH_C_LUI){
	    //~ pd->hi_addr[rd] = EXTRACT_RVC_LUI_IMM (l);
	    							  	  immediatedata = EXTRACT_RVC_LUI_IMM (l);
}
	  printf ("%s", riscv_gpr_names[rd]);
	   GPR[status_gpr] = 31+rd;
		     status_gpr++;
	  break;

	case 'z':
	  printf ( "%s", riscv_gpr_names[0]);
	   GPR[status_gpr] = 0;
		     status_gpr++;
	  break;

	case '>':
	  printf ("0x%x", (int)EXTRACT_OPERAND (SHAMT, l));
	  	    							  	  immediatedata = EXTRACT_OPERAND (SHAMT, l);

	  break;

	case '<':
	  printf ("0x%x", (int)EXTRACT_OPERAND (SHAMTW, l));
	  	  	    							  	  immediatedata = EXTRACT_OPERAND (SHAMTW, l);

	  break;

	case 'S':
	case 'U':
	  printf ("%s", riscv_fpr_names[rs1]);
	  break;

	case 'T':
	  printf ("%s", riscv_fpr_names[EXTRACT_OPERAND (RS2, l)]);
	  break;

	case 'D':
	  printf ("%s", riscv_fpr_names[rd]);
	  break;

	case 'R':
	  printf ("%s", riscv_fpr_names[EXTRACT_OPERAND (RS3, l)]);
	  break;

	case 'E':
	  {
	    static const char *riscv_csr_hash[4096];    /* Total 2^12 CSR.  */
	    static int init_csr = 0;
	    unsigned int csr = EXTRACT_OPERAND (CSR, l);

	    if (!init_csr)
	      {
		unsigned int i;
		for (i = 0; i < 4096; i++)
		  riscv_csr_hash[i] = NULL;

		/* Set to the newest privilege version.  */
		if (default_priv_spec == PRIV_SPEC_CLASS_NONE)
		  default_priv_spec = PRIV_SPEC_CLASS_DRAFT - 1;

#define DECLARE_CSR(name, num, class, define_version, abort_version)	\
		if (riscv_csr_hash[num] == NULL 			\
		    && ((define_version == PRIV_SPEC_CLASS_NONE 	\
			 && abort_version == PRIV_SPEC_CLASS_NONE)	\
			|| (default_priv_spec >= define_version 	\
			    && default_priv_spec < abort_version)))	\
		  riscv_csr_hash[num] = #name;
#define DECLARE_CSR_ALIAS(name, num, class, define_version, abort_version) \
		DECLARE_CSR (name, num, class, define_version, abort_version)
#include "opcode/riscv-opc.h"
#undef DECLARE_CSR
	      }

	    if (riscv_csr_hash[csr] != NULL)
	      printf ("%s", riscv_csr_hash[csr]);
	    else
	      printf ("0x%x", csr);
	    break;
	  }

	case 'Z':
	  printf ("%d", rs1);
	  break;

	default:
	  /* xgettext:c-format */
	  printf ("# internal error, undefined modifier (%c)",*d);
	  return;
	}
    }
    if(insn->gpraction != 0) {
	printf("GPR0 %d \n",GPR[0]);
	printf("GPR1 %d \n",GPR[1]);
	printf("GPR2 %d \n",GPR[2]);
	printf("GPR3 %d \n",GPR[3]);
	printf("immediate %d \n",immediatedata);
	  chiara_action_reg(GPR[0],GPR[1],GPR[2],insn->gpraction,RISCV,immediatedata);  
	
		
}
    
}

void chiara_parse_riscv_instruction(unsigned long long instruction) {
	for(int x = 0;x<opcodesnum;x++) {


		if(riscv_opcodes[x].match_func(&riscv_opcodes[x],instruction)) {
			printf("NAME RISCV %s \n",riscv_opcodes[x].name);
			// call chiara and decrypt operand
		
			print_insn_args (riscv_opcodes[x].args, instruction, pointer_riscv, (void*)0,&riscv_opcodes[x]);

			break;
			}


	}	
}
void chiara_emul_riscv(unsigned char *instruction,int size) {
	set_default_riscv_dis_options();
	pointer_riscv = instruction;
int size_4 = size/4;

for(int x = 0;x<size_4;x++,pointer_riscv++) {
	chiara_parse_riscv_instruction(*pointer_riscv);
	
}
		
		}



