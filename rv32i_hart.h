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

#ifndef rv32i_hart_h
#define rv32i_hart_h

#include <stdio.h>
#include "hex.h"
#include "rv32i_decode.h"
#include "memory.h"
#include "registerfile.h"
#include <cassert>

using namespace std;


/**
 *
 * no parameters are here, these are just the inital declerations
 * the actual code to use them is in hex.cpp and memory.cpp
 *
 * no return value here either as these are all just being initialized not
 * actually being used yet by the program
 *
 * @note extneded from the starter code given with parts given from the
 * instructor
 **************************************************************************************/
class rv32i_hart : public rv32i_decode //rv32i hart class public subclass of decode
{
    
public :
    rv32i_hart (memory &m) : mem (m) { } //hart of riscv
    void set_show_instructions (bool b) { show_instructions = b ; } //show instructions
    void set_show_registers (bool b) { show_registers = b; } //show registers
    bool is_halted () const {return halt;} //halted condition
    const std :: string & get_halt_reason () const { return halt_reason ; } //halt reason
    uint64_t get_insn_counter () const { return insn_counter ; } //insn counter
    void set_mhartid ( int i ) { mhartid = i; } //hart id

    void tick ( const std :: string & hdr ="") ; //tick
    void dump ( const std :: string & hdr ="") const ; //dump contents
    void reset () ; //reset

    
private :
    static constexpr int instruction_width = 35; //insn width
    void exec ( uint32_t insn , std :: ostream *) ; //execute
    void exec_illegal_insn ( uint32_t insn , std :: ostream *) ; //illegal instruction
    void exec_lui(uint32_t insn, std::ostream* pos); //lui instruction
    void exec_auipc(uint32_t insn, std::ostream* pos); //auipc instruction
    void exec_jal(uint32_t insn, std::ostream* pos); //jal instruction
    void exec_jalr(uint32_t insn, std::ostream* pos); //jalr instruction
    void exec_beq(uint32_t insn, std::ostream* pos); //beq instruction
    void exec_bne(uint32_t insn, std::ostream* pos); //bne instruction
    void exec_blt(uint32_t insn, std::ostream* pos); //blt instruction
    void exec_bge(uint32_t insn, std::ostream* pos); //bge instruction
    void exec_bltu(uint32_t insn, std::ostream* pos); //bltu instruction
    void exec_bgeu(uint32_t insn, std::ostream* pos); //bgeu instruction
    void exec_lb(uint32_t insn, std::ostream* pos); //lb instruction
    void exec_lh(uint32_t insn, std::ostream* pos); //lh instruction
    void exec_lw(uint32_t insn, std::ostream* pos); //lw instruction
    void exec_lbu(uint32_t insn, std::ostream* pos); //lbu instruction
    void exec_lhu(uint32_t insn, std::ostream* pos); //lhu instruction
    void exec_sb(uint32_t insn, std::ostream* pos); //sb instruction
    void exec_sh(uint32_t insn, std::ostream* pos); //sh instruction
    void exec_sw(uint32_t insn, std::ostream* pos); //sw instruction
    void exec_addi(uint32_t insn, std::ostream* pos); //addi instruction
    void exec_slti(uint32_t insn, std::ostream* pos); //slti instruction
    void exec_sltiu(uint32_t insn, std::ostream* pos); //sltiu instruction
    void exec_xori(uint32_t insn, std::ostream* pos); //xori instruction
    void exec_ori(uint32_t insn, std::ostream* pos); //ori instruction
    void exec_andi(uint32_t insn, std::ostream* pos); //andi instruction
    void exec_slli(uint32_t insn, std::ostream* pos); //slli instruction
    void exec_srli(uint32_t insn, std::ostream* pos); //srli instruction
    void exec_srai(uint32_t insn, std::ostream* pos); //srai instruction
    void exec_add(uint32_t insn, std::ostream* pos); //add instruction
    void exec_sub(uint32_t insn, std::ostream* pos); //sub instruction
    void exec_sll(uint32_t insn, std::ostream* pos); //sll instruction
    void exec_slt(uint32_t insn, std::ostream* pos); //slt instruction
    void exec_sltu(uint32_t insn, std::ostream* pos); //sltu instruction
    void exec_xor(uint32_t insn, std::ostream* pos); //xor instruction
    void exec_srl(uint32_t insn, std::ostream* pos); //srl instruction
    void exec_sra(uint32_t insn, std::ostream* pos); //sra instruction
    void exec_or(uint32_t insn, std::ostream* pos); //or instruction
    void exec_and(uint32_t insn, std::ostream* pos); //and instruction
    void exec_ecall(uint32_t insn, std::ostream* pos); //ecall instruction
    void exec_ebreak(uint32_t insn, std::ostream* pos); //ebreak instruction
    void exec_csrrs(uint32_t insn, std::ostream* pos); //csrrs instruction

    bool halt = { false }; //halt condition
    std :: string halt_reason = { " none " }; //halt reason
    bool show_instructions = { false }; //show instructions condition
    bool show_registers = { false }; //show registers condition
    uint64_t insn_counter = { 0 }; //insn counter
    uint32_t pc = { 0 }; //pc
    uint32_t mhartid = { 0 }; //hart id
    
protected :
    registerfile regs; //register
    memory &mem; //memory
    
};

#endif /* rv32i_hart_h */
