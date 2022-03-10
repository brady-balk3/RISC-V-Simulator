//***************************************************************************
//
//  Brady Balk
//  Z1905404
//  CSCI 463-1
//  Due: 11/05/2021
//
//  I certify that this is my own work and where appropriate an extension
//  of the starter code provided for the assignment.
//
//***************************************************************************

#include "rv32i_hart.h"

using namespace std;

/**
 * rv32i_hart::tick is what tells the simulator to run an instruction
 *
 * @param hdr prints to the left of all instructions
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::tick(const std::string &hdr)
{
    if(halt==true)
    {
        return; //if halt is true then return back
    }
    insn_counter +=1; //increment instruction counter
    
    if(show_registers==true)
    {
        dump(hdr); //if show registers is selected then dump the hdr
    }
    uint32_t insn = mem.get32(pc); //set instruction equal to pc from memory
    
    if(show_instructions==true)
    {
        std::cout<<hdr<<hex::to_hex32(pc)<<": "<<hex::to_hex32(insn)<<"  "; //if show instructions is true then output the formated instruction
        exec(insn, &std::cout); //execute the instruction via output
    }
    else
    {
        exec(insn, nullptr); //else execute instructions with nullptr
    }
}

/**
 * rv32i_hart::tick dumps the contents of the hart
 *
 * @param hdr set to be at the start of every line
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::dump(const std::string &hdr) const
{
    regs.dump(hdr); //dump hdr from registers
    std::cout<<std::endl<<std::right<<std::setw(4)<<"pc "<<hex::to_hex32(pc)<<std::endl; //output said dump formatted correctly
}

/**
 * rv32i_hart::reset resets the registers
 *
 * no parameters are present in this function
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::reset()
{
    pc = 0; //pc value equal to 0
    regs.reset(); //reset registers
    insn_counter = 0; //instruction counter equal to 0
    halt = false; //set halt to false
    halt_reason = "none"; //show halt reason as none
}

/**
 * rv32i_hart::exec uses a casecading switch statement to execute the
 * given instructions
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output to be written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec(uint32_t insn, std::ostream* pos)
{
    uint32_t funct3= get_funct3(insn); //hold funct3 for comparison
    uint32_t funct7= get_funct7(insn); //hold funct7 for comparison
    
    if(insn==insn_ebreak) //if instruction is ebreak
    {
        exec_ebreak(insn, pos); //execute ebreak and then return
        return;
    }
    
    switch(get_opcode(insn)) //cascading switch statment based on opcodes and other variables to catch the given instructions
    {
        default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
        case opcode_lui: exec_lui(insn, pos); return; //exec lui with parameters if opcode matches
        case opcode_auipc: exec_auipc(insn, pos); return; //exec auipc with parameters if opcode matches
        case opcode_jal: exec_jal(insn, pos); return; //exec jal with parameters if opcode matches
        case opcode_jalr: exec_jalr(insn, pos); return; //exec jalr with parameters if opcode matches
            
            //check for btype opcode...
        case opcode_btype:
            //sort via funct3 value
          switch (funct3)
          {
          default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
          case funct3_beq: exec_beq(insn, pos); return; //exec beq with parameters if funct3 matches
          case funct3_bne: exec_bne(insn, pos); return; //exec bne with parameters if funct3 matches
          case funct3_blt: exec_blt(insn, pos); return; //exec blt with parameters if funct3 matches
          case funct3_bge: exec_bge(insn, pos); return; //exec bge with parameters if funct3 matches
          case funct3_bltu: exec_bltu(insn, pos); return; //exec bltu with parameters if funct3 matches
          case funct3_bgeu: exec_bgeu(insn, pos); return; //exec bgeu with parameters if funct3 matches
          }
          assert (0 && "unrecognized funct3"); // impossible
            //check for load imm opcode...
        case opcode_load_imm:
            //sort via funct3 value
          switch (funct3)
          {
          default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
          case funct3_lb: exec_lb(insn, pos); return; //exec lb with parameters if funct3 matches
          case funct3_lh: exec_lh(insn, pos); return; //exec lh with parameters if funct3 matches
          case funct3_lw: exec_lw(insn, pos); return; //exec lw with parameters if funct3 matches
          case funct3_lbu: exec_lbu(insn, pos); return; //exec lbu with parameters if funct3 matches
          case funct3_lhu: exec_lhu(insn, pos); return; //exec lhu with parameters if funct3 matches
          }
          assert (0 && "unrecognized funct3"); // impossible
            //check for stype opcode...
        case opcode_stype:
            //sort via funct3 value
          switch (funct3)
          {
          default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
          case funct3_sb: exec_sb(insn, pos); return; //exec sb with parameters if funct3 matches
          case funct3_sh: exec_sh(insn, pos); return; //exec sh with parameters if funct3 matches
          case funct3_sw: exec_sw(insn, pos); return; //exec sw with parameters if funct3 matches
          }
          assert (0 && "unrecognized funct3"); // impossible
            //check for alu imm opcode...
        case opcode_alu_imm:
            //sort via funct3 value
          switch (funct3)
          {
          default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
          case funct3_add: exec_addi(insn, pos); return; //exec addi with parameters if funct3 matches
          case funct3_slt: exec_slti(insn, pos); return; //exec slti with parameters if funct3 matches
          case funct3_sltu: exec_sltiu(insn, pos); return; //exec sltiu with parameters if funct3 matches
          case funct3_xor: exec_xori(insn, pos); return; //exec xori with parameters if funct3 matches
          case funct3_or: exec_ori(insn, pos); return; //exec ori with parameters if funct3 matches
          case funct3_and: exec_andi(insn, pos); return; //exec andi with parameters if funct3 matches
          case funct3_sll: exec_slli(insn, pos); return; //exec slli with parameters if funct3 matches
                  
          case funct3_srx:
              //sort via funct7 value
            switch (funct7)
            {
            default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
            case funct7_srl: exec_srli(insn, pos); return; //exec srli with parameters if funct7 matches
            case funct7_sra: exec_srai(insn, pos); return; //exec srai with parameters if funct7 matches
            }
            assert (0 && "unrecognized funct7"); // impossible
          }
          assert (0 && "unrecognized funct3"); // impossible
            //check for rtype opcode...
        case opcode_rtype:
            //sort via funct3 value
          switch (funct3)
          {
          default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
          case funct3_add:
              //sort via funct7 value
            switch (funct7)
            {
            default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
            case funct7_add: exec_add(insn, pos); return; //exec add with parameters if funct7 matches
            case funct7_sub: exec_sub(insn, pos); return; //exec sub with parameters if funct7 matches
            }
            assert (0 && "unrecognozed funct7"); // impossible
          case funct3_sll: exec_sll(insn, pos); return; //exec sll with parameters if funct3 matches
          case funct3_slt: exec_slt(insn, pos); return; //exec slt with parameters if funct3 matches
          case funct3_sltu: exec_sltu(insn, pos); return; //exec sltu with parameters if funct3 matches
          case funct3_xor: exec_xor(insn, pos); return; //exec xor with parameters if funct3 matches
          case funct3_srx:
                //sort via funct3 value
            switch (funct7)
            {
            default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
            case funct7_srl: exec_srl(insn, pos); return; //exec srl with parameters if funct7 matches
            case funct7_sra: exec_sra(insn, pos); return; //exec sra with parameters if funct7 matches
            }
            assert (0 && "unrecognized funct7"); // impossible
          case funct3_or: exec_or(insn, pos); return; //exec or with parameters if funct3 matches
          case funct3_and: exec_and(insn, pos); return; //exec and with parameters if funct3 matches
          }
          assert (0 && "unrecognized funct3"); // impossible
            //check for system opcode...
        case opcode_system:
            //sort via funct3 value
          switch (funct3)
          {
          default: exec_illegal_insn(insn, pos); return; //exec default error with parameters if it is an illegal instruction
          case funct3_csrrs: exec_csrrs(insn, pos); return; //exec csrrs with parameters if funct3 matches
          }
          assert (0 && "unrecognized funct3"); // impossible
        }
        assert (0 && "unrecognized opcode"); //should never get here
}

/**
 * rv32i_hart::exex_illegal_insn is the exec function for illegal instructions
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_illegal_insn(uint32_t insn, std::ostream* pos)
{
  (void)insn; //instruction
  if (pos) { *pos << render_illegal_insn(insn); } //render the illegal instruction
  halt = true; //set halt to true
  halt_reason = "Illegal instruction"; //halt reason set to illegal instruction
}

/**
 * rv32i_hart::exex_lui is the exec function for the lui instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_lui(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd value from instruction
  uint32_t imm_u = get_imm_u(insn); //get and store immu value from instruction

  if (pos)
  {
    std::string s = render_lui(insn); //set s to render lui instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted lui instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(imm_u); //output rd and immu formatted
      std::cout<<std::endl;
  }

  regs.set(rd, imm_u); //set register to immediate
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_auipc is the exec function for the auipc instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_auipc(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd value from instruction
  uint32_t imm_u = get_imm_u(insn); //get and store immu value from instruction

  int32_t val = pc + imm_u; //get the value of val

  if (pos)
  {
    std::string s = render_auipc(insn); //set s to render auipc instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output rendered auipc instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(pc) << " + " << //along with rd, pc, immu, and val all formatted
            hex::to_hex0x32(imm_u) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_jal is the exec function for the jal instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_jal(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd value from instruction
  uint32_t imm_j = get_imm_j(insn); //get and store immj from instruction

  int32_t val_rd = pc + 4; //hold value of rd from pc+4
  int32_t val_pc = pc + imm_j; //hold new value of pc from the immj instruction

  if (pos)
  {
    std::string s = render_jal(pc, insn); //set s to render jal instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted jal instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(val_rd) << ",  pc = " << //along with the other values associated with it
            hex::to_hex0x32(pc) << " + " << hex::to_hex0x32(imm_j) << " = " << hex::to_hex0x32(val_pc);
      std::cout<<std::endl;
  }

  regs.set(rd, val_rd); //set registers to valrd
  pc = val_pc; //pc now eqails valpc

}

/**
 * rv32i_hart::exex_jalr is the exec function for the jalr instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_jalr(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  //variable to hold the value stored at rd and pc
  int32_t val_rd = pc + 4; //hold value of rd from pc+4
  int32_t val_pc = (regs.get(rs1) + imm_i) & 0xfffffffe; //hold value of pc from immi and rs1 after undergoing and on bits

  if (pos)
  {
    std::string s = render_jalr(insn); //set s to render jalr instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(val_rd) << ",  pc = (" << hex::to_hex0x32(imm_i) << //along with other associated values
            " + " << hex::to_hex0x32(regs.get(rs1)) << ") & 0xfffffffe = " << hex::to_hex0x32(val_pc);
      std::cout<<std::endl;
  }

  regs.set(rd, val_rd); //set register to valrd
  pc = val_pc; //set pc to valpc

}

/**
 * rv32i_hart::exex_beq is the exec function for the beq instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_beq(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
  uint32_t imm_b = get_imm_b(insn); //get and store immb from instruction

  int32_t val = pc + ((regs.get(rs1) == regs.get(rs2)) ? imm_b : 4); //hold val from pc

  if (pos)
  {
    std::string s = render_btype(pc, insn, "beq"); //set s to render beq instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted instruction
    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " == " << hex::to_hex0x32(regs.get(rs2)) << //along with associated values
            " ? " << hex::to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  pc = val; //set pc to val
}

/**
 * rv32i_hart::exex_bne is the exec function for the bne instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_bne(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
  uint32_t imm_b = get_imm_b(insn); //get and store immb from instruction

  int32_t val = pc + ((regs.get(rs1) != regs.get(rs2)) ? imm_b : 4); //hold the value of pc

  if (pos)
  {
    std::string s = render_btype(pc, insn, "bne"); //set s to render bne instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output rendered bne instruction
    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " != " << hex::to_hex0x32(regs.get(rs2)) << //along with associated values
            " ? " << hex::to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  pc = val; //set pc to val
}

/**
 * rv32i_hart::exex_blt is the exec function for the bne instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_blt(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instructiom
  uint32_t imm_b = get_imm_b(insn); //get and store immb from instruction

  int32_t val = pc + ((regs.get(rs1) < regs.get(rs2)) ? imm_b : 4); //hold the value of pc

  if (pos)
  {
    std::string s = render_btype(pc, insn, "blt"); //set s to render blt instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted instruction
    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " < " << hex::to_hex0x32(regs.get(rs2)) << //along with associated values
            " ? " << hex::to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  pc = val; //set pc to val
}

/**
 * rv32i_hart::exex_bge is the exec function for the bge instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_bge(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
  uint32_t imm_b = get_imm_b(insn); //get and store immb from instruction

  int32_t val = pc + ((regs.get(rs1) >= regs.get(rs2)) ? imm_b : 4); //hold the value of pc

  if (pos)
  {
    std::string s = render_btype(pc, insn, "bge"); //set s to render bge instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted bge instruction
    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " >= " << hex::to_hex0x32(regs.get(rs2)) << //along with associated values
            " ? " << hex::to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  pc = val; //set pc to val
}

/**
 * rv32i_hart::exex_bltu is the exec function for the bltu instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_bltu(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
  uint32_t imm_b = get_imm_b(insn); //get and store immb from instruction

  uint32_t val = pc + ((static_cast<uint32_t>(regs.get(rs1)) < static_cast<uint32_t>(regs.get(rs2))) ? imm_b : 4); //hold value of pc

  if (pos)
  {
    std::string s = render_btype(pc, insn, "bltu"); //set s to render bltu instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted bltu instruction
    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " <U " << hex::to_hex0x32(regs.get(rs2)) << //along with associated values
            " ? " << hex::to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  pc = val; //set pc to val
}

/**
 * rv32i_hart::exex_bgeu is the exec function for the bgeu instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_bgeu(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
  uint32_t imm_b = get_imm_b(insn); //get and store immb from instruction
    
  uint32_t val = pc + ((static_cast<uint32_t>(regs.get(rs1)) >= static_cast<uint32_t>(regs.get(rs2))) ? imm_b : 4); //hold the value of pc

  if (pos)
  {
    std::string s = render_btype(pc, insn, "bgeu"); //set s to render bgeu instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted bgeu instruction
    *pos << "// pc += (" << hex::to_hex0x32(regs.get(rs1)) << " >=U " << hex::to_hex0x32(regs.get(rs2)) << //along with associated values
            " ? " << hex::to_hex0x32(imm_b) << " : 4) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  pc = val; //set pc to val
}

/**
 * rv32i_hart::exex_lb is the exec function for the lb instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_lb(uint32_t insn, std::ostream* pos)
{
  //variable definitions to get rd, rs1, and imm_i
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t addr = regs.get(rs1) + imm_i; //hold address of register
  int32_t val = mem.get8(addr); //hold value of register

  if (val & 0x00000080) { val |= 0xffffff00; } //if msb is active sign extend to the left

  if (pos)
  {
    std::string s = render_itype_load(insn, "lb"); //set s to render lb instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted lb instruction
    *pos << "// " << render_reg(rd) << " = sx(m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " << //along with assoicated values
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_lhi is the exec function for the lh instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_lh(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t addr = regs.get(rs1) + imm_i; //hold address of register
  int32_t val = mem.get16(addr); //hold value of register

  if (val & 0x00008000) { val |= 0xffff0000; } //if msb is active sign extend to the left

  if (pos)
  {
    std::string s = render_itype_load(insn, "lh"); //set s to render lh instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //ouput formatted lh instruction
    *pos << "// " << render_reg(rd) << " = sx(m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " << //along with associated values
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_lw is the exec function for the lw instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_lw(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t addr = regs.get(rs1) + imm_i; //hold address of register
  int32_t val = mem.get32(addr); //hold value of register

  if (val & 0x80000000) { val |= 0x00000000; } //if msb is active sign extend to the left

  if (pos)
  {
    std::string s = render_itype_load(insn, "lw"); //set s to render lw instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted lw instruction
    *pos << "// " << render_reg(rd) << " = sx(m32(" << hex::to_hex0x32(regs.get(rs1)) << " + " << //along with associated values
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_lbu is the exec function for the lbu instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_lbu(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t addr = regs.get(rs1) + imm_i; //hold address of register
  uint32_t val = mem.get8(addr); //hold value of register

  if (pos)
  {
    std::string s = render_itype_load(insn, "lbu"); //set s to render lbu instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted lbu instruction
    *pos << "// " << render_reg(rd) << " = zx(m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " << //along with associated values
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_lhu is the exec function for the lhu instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_lhu(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t addr = regs.get(rs1) + imm_i; //hold address of register
  uint32_t val = mem.get16(addr); //hold value of register

  if (pos)
  {
    std::string s = render_itype_load(insn, "lhu"); //set s to render lhu instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted lhu instruction
    *pos << "// " << render_reg(rd) << " = zx(m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " << //along with associated values
            hex::to_hex0x32(imm_i) << ")) = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_sb is the exec function for the sb instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_sb(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
  uint32_t imm_s = get_imm_s(insn); //get and store imms from instruction

  int32_t addr = regs.get(rs1) + imm_s; //hold register address
  int32_t val = regs.get(rs2) & 0x000000ff; //hold register value

  if (pos)
  {
    std::string s = render_stype(insn, "sb"); //set s to render sb instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted sb instruction
    *pos << "// m8(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << //along with associated values
            ") = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  mem.set8(addr, val); //set memory address as val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_sh is the exec function for the sh instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_sh(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
  uint32_t imm_s = get_imm_s(insn); //get and store imms from instruction

  int32_t addr = regs.get(rs1) + imm_s; //hold register address
  int32_t val = regs.get(rs2) & 0x0000ffff; //hold register value

  if (pos)
  {
    std::string s = render_stype(insn, "sh"); //set s to render sh instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted sh instruction
    *pos << "// m16(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << //along with associated values
            ") = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  mem.set16(addr, val); //set memory address as val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_sw is the exec function for the sw instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_sw(uint32_t insn, std::ostream* pos)
{
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
  uint32_t imm_s = get_imm_s(insn); //get and store imms from instruction

  int32_t addr = regs.get(rs1) + imm_s; //hold register address
  int32_t val = regs.get(rs2); //hold register value

  if (pos)
  {
    std::string s = render_stype(insn, "sw"); //set s to render sw instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted sw instruction
    *pos << "// m32(" << hex::to_hex0x32(regs.get(rs1)) << " + " << hex::to_hex0x32(imm_s) << //along with associated values
            ") = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  mem.set32(addr, val); //set memory as val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_addi is the exec function for the addi instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_addi(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t val = regs.get(rs1) + imm_i; //hold value of rs1 + imm

  if (pos)
  {
    std::string s = render_itype_alu(insn, "addi", imm_i); //set s to render addi instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted addi instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " + " << //along with associated values
            hex::to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4

}

/**
 * rv32i_hart::exex_slti is the exec function for the slti instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_slti(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t imm_i = get_imm_i(insn); //get and store immi

  int32_t val = (regs.get(rs1) < imm_i) ? 1 : 0; //holds value from rs1 and immi

  if (pos)
  {
    std::string s = render_itype_alu(insn, "slti", imm_i); //set s to render slti instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted slti instruction
    *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " < " << //along with associated values
            std::dec << imm_i << ") ? 1 : 0 = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }
    
  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_sltiu is the exec function for the sltiu instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_sltiu(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  uint32_t val = (static_cast<uint32_t>(regs.get(rs1)) < static_cast<uint32_t>(imm_i)) ? 1 : 0; //hold value of rs1 and immi

  if (pos)
  {
    std::string s = render_itype_alu(insn, "sltiu", imm_i); //set s to render sltiu instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted sltiu instruction
    *pos << "// " << render_reg(rd) << " = (" << hex::to_hex0x32(regs.get(rs1)) << " <U " << //along with associated values
            std::dec << imm_i << ") ? 1 : 0 = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_xori is the exec function for the xori instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_xori(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t val = regs.get(rs1) ^ imm_i; //hold value of rs1 and immi

  if (pos)
  {
    std::string s = render_itype_alu(insn, "xori", imm_i); //set s to render xori instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted xori instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " ^ " << //along with associated values
            hex::to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_ori is the exec function for the ori instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_ori(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t val = regs.get(rs1) | imm_i; //hold value of rs1 and immi

  if (pos)
  {
    std::string s = render_itype_alu(insn, "ori", imm_i); //set s to render ori instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted ori instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " | " << //along with associated values
            hex::to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_andi is the exec function for the andi instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_andi(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t imm_i = get_imm_i(insn); //get and store immi from instruction

  int32_t val = regs.get(rs1) & imm_i; //hold value of rs1 and immi

  if (pos)
  {
    std::string s = render_itype_alu(insn, "andi", imm_i); //set s to render andi instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted andi instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " & " << //along with associated values
            hex::to_hex0x32(imm_i) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_slli is the exec function for the slli instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_slli(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t shamt_i = get_rs2(insn); //get and store shamti from instruction

  int32_t val = regs.get(rs1) << shamt_i; //hold value of rs1 and shamti

  if (pos)
  {
    std::string s = render_itype_alu(insn, "slli", shamt_i); //set s to render slli instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted slli instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " << " << //along with associated values
            std::dec << shamt_i << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_srli is the exec function for the srli instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_srli(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t shamt_i = get_rs2(insn); //get and store shamti from instruction

  int32_t mask = 0x80000000; //mask for shift right logical

  shamt_i = shamt_i & 0xfffffe1f; //set up shift right logical
  mask = ~((mask >> shamt_i) << 1);

  int32_t val = (regs.get(rs1) >> shamt_i) & mask; //value after shift right logical

  if (pos)
  {
    std::string s = render_itype_alu(insn, "srli", shamt_i); //set s to render srli instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " << //along with associated values
            std::dec << shamt_i << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_srai is the exec function for the srai instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_srai(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t shamt_i = get_rs2(insn); //get and store shamti from instruction

  int32_t val = regs.get(rs1) >> shamt_i; //hold value from rs1 and shamti

  if (pos)
  {
    std::string s = render_itype_alu(insn, "srai", shamt_i); //set s to render srai instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted srai instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " << //along with associated values
            std::dec << shamt_i << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_add is the exec function for the add instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_add(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  int32_t val = regs.get(rs1) + regs.get(rs2); //hold value from rs1 and rs2

  if (pos)
  {
    std::string s = render_rtype(insn, "add"); //set s to render add instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted add instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " + " << //along with associated values
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_sub is the exec function for the sub instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_sub(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  int32_t val = regs.get(rs1) - regs.get(rs2); //hold value from rs1 and rs2

  if (pos)
  {
    std::string s = render_rtype(insn, "sub"); //set s to render sub instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted sub instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " - " << //along with associated values
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_sll is the exec function for the sll instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_sll(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  int32_t val = regs.get(rs1) << (regs.get(rs2) % XLEN); //hold value from rs1 and rs2%XLEN

  if (pos)
  {
    std::string s = render_rtype(insn, "sll"); //set s to render sll instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted sll instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " << " << //along with associated values
            std::dec << (regs.get(rs2) % XLEN) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_slt is the exec function for the slt instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_slt(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  int32_t val = (regs.get(rs1) < regs.get(rs2)) ? 1 : 0; //hold value from rs1 and rs2

  if (pos)
  {
    std::string s = render_rtype(insn, "slt"); //set s to render slt instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //ouput formatted slt instruction
    *pos << "// " << render_reg(rd) << " = (" << to_hex0x32(regs.get(rs1)) << " < " << //along with associated values
            to_hex0x32(regs.get(rs2)) << ") ? 1 : 0 = " << to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set the register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_sltu is the exec function for the sltu instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_sltu(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  uint32_t val = (regs.get(rs1) < regs.get(rs2)) ? 1 : 0; //hold value from rs1 and rs2

  if (pos)
  {
    std::string s = render_rtype(insn, "sltu"); //set s to render sltu instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted sltu instruction
    *pos << "// " << render_reg(rd) << " = (" << to_hex0x32(regs.get(rs1)) << " <U " << //along with associated values
            to_hex0x32(regs.get(rs2)) << ") ? 1 : 0 = " << to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_xor is the exec function for the xor instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_xor(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  int32_t val = regs.get(rs1) ^ regs.get(rs2); //hold value from rs1 and rs2

  if (pos)
  {
    std::string s = render_rtype(insn, "xor"); //set s to render xor instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted xor instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " ^ " << //along with associated values
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_srl is the exec function for the srl instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_srl(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t rs2 = get_rs2(insn); //get and store rs2 from instruction
 
  int32_t mask = 0x80000000; //mask to do shift right logical
  
  int32_t rs2XLEN = regs.get(rs2) % XLEN; //perform shift right logical
  mask = ~((mask >> rs2XLEN) << 1);

  int32_t val = (regs.get(rs1) >> rs2XLEN) & mask; //value to hold after shift

  if (pos)
  {
    std::string s = render_rtype(insn, "srl"); //set s to render srl instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted srl instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " << //along with associated values
            std::dec << (regs.get(rs2) % XLEN) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_sra is the exec function for the sra instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_sra(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  int32_t val = regs.get(rs1) >> (regs.get(rs2) % XLEN); //hold value from rs1 and rs2

  if (pos)
  {
    std::string s = render_rtype(insn, "sra"); //set s to render sra instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted sra instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " >> " << //along with associated values
            std::dec << (regs.get(rs2) % XLEN) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_or is the exec function for the or instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_or(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  int32_t val = regs.get(rs1) | regs.get(rs2); //hold value from rs1 and rs2

  if (pos)
  {
    std::string s = render_rtype(insn, "or"); //set s to render or instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted or instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " | " << //along with associated values
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to value
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_and is the exec function for the and instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_and(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  uint32_t rs2 = get_rs2(insn); //get and store rs2 from instruction

  int32_t val = regs.get(rs1) & regs.get(rs2); //hold value from rs1 and rs2

  if (pos)
  {
    std::string s = render_rtype(insn, "and"); //set s to render and instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted and instruction
    *pos << "// " << render_reg(rd) << " = " << hex::to_hex0x32(regs.get(rs1)) << " & " << //along with associated values
            hex::to_hex0x32(regs.get(rs2)) << " = " << hex::to_hex0x32(val);
      std::cout<<std::endl;
  }

  regs.set(rd, val); //set register to val
  pc += 4; //increment pc by 4
}

/**
 * rv32i_hart::exex_ecall is the exec function for the ecall instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_ecall(uint32_t insn, std::ostream* pos)
{
  if (pos)
  {
    std::string s = render_ecall(insn); //set s to render ecall instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted ecall instruction
    *pos << "// HALT"; //with halt message
      std::cout<<std::endl;
  }

  halt = true; //set halt to true
  halt_reason = "ECALL instruction"; //set halt reason
}


/**
 * rv32i_hart::exex_ebreak is the exec function for the ebreak instruction
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_ebreak(uint32_t insn, std::ostream* pos)
{
  if (pos)
  {
    std::string s = render_ebreak(insn); //set s to render ebreak instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted ebreak instruction
    *pos << "// HALT"; //with halt message
      std::cout<<std::endl;
  }

  halt = true; //set halt to true
  halt_reason = "EBREAK instruction"; //set halt reason
}

/**
 * rv32i_hart::exex_csrrs is the exec function for the csrrs instructions
 *
 * @param insn the literal riscv instruction to be executed
 * @param pos the output that is written to
 *
 * no return present in this function
 *
 * @note extended from starter code
 **************************************************************************************/
void rv32i_hart::exec_csrrs(uint32_t insn, std::ostream* pos)
{
  uint32_t rd = get_rd(insn); //get and store rd from instruction
  uint32_t rs1 = get_rs1(insn); //get and store rs1 from instruction
  int32_t csr = get_imm_i(insn) & 0x00000fff; //get and store csr from instruction

  if (csr != 0xf14 || rs1 != 0) //halt condition
  {
    halt = true; //set halt to true
    halt_reason = "Illegal CSR in CSRSS instruction"; //halt reason
  }

  if (pos)
  {
    std::string s = render_csrrx(insn, "csrrs"); //set s to render csr instruction
    *pos << std::setw(instruction_width) << std::setfill(' ') << std::left << s; //output formatted csr instruction
    *pos << "// " << render_reg(rd) << " = " << std::dec << mhartid; //along with associated values
      std::cout<<std::endl;
  }

  if (!halt) //if no halt
  {
    regs.set(rd, mhartid); //set register to mhartid
    pc += 4; //increment pc by 4
  }
}
