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

#ifndef rvi32decode_h
#define rvi32decode_h

#include "hex.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

/**
 *
 * no parameters are here, these are just the inital declerations
 * the actual code to use them is in rv321_decode.cpp
 *
 * no return value here either as these are all just being initialized not
 * actually being used yet by the program
 *
 * @note provided by instructor, all of these are initilized here and then
 * being passed to another file
 **************************************************************************************/
class rv32i_decode : public hex
{
public:

    ///@parm addr The memory address where the insn is stored.
    static std::string decode(uint32_t addr, uint32_t insn);

protected:
    static constexpr int mnemonic_width             = 8; //width for output

    static constexpr uint32_t opcode_lui            = 0b0110111; //binary representation
    static constexpr uint32_t opcode_auipc          = 0b0010111; //binary representation
    static constexpr uint32_t opcode_jal            = 0b1101111; //binary representation
    static constexpr uint32_t opcode_jalr           = 0b1100111; //binary representation
    static constexpr uint32_t opcode_btype          = 0b1100011; //binary representation
    static constexpr uint32_t opcode_load_imm       = 0b0000011; //binary representation
    static constexpr uint32_t opcode_stype          = 0b0100011; //binary representation
    static constexpr uint32_t opcode_alu_imm        = 0b0010011; //binary representation
    static constexpr uint32_t opcode_rtype          = 0b0110011; //binary representation
    static constexpr uint32_t opcode_system         = 0b1110011; //binary representation

    static constexpr uint32_t funct3_beq            = 0b000; //binary representation
    static constexpr uint32_t funct3_bne            = 0b001; //binary representation
    static constexpr uint32_t funct3_blt            = 0b100; //binary representation
    static constexpr uint32_t funct3_bge            = 0b101; //binary representation
    static constexpr uint32_t funct3_bltu           = 0b110; //binary representation
    static constexpr uint32_t funct3_bgeu           = 0b111; //binary representation

    static constexpr uint32_t funct3_lb             = 0b000; //binary representation
    static constexpr uint32_t funct3_lh             = 0b001; //binary representation
    static constexpr uint32_t funct3_lw             = 0b010; //binary representation
    static constexpr uint32_t funct3_lbu            = 0b100; //binary representation
    static constexpr uint32_t funct3_lhu            = 0b101; //binary representation

    static constexpr uint32_t funct3_sb             = 0b000; //binary representation
    static constexpr uint32_t funct3_sh             = 0b001; //binary representation
    static constexpr uint32_t funct3_sw             = 0b010; //binary representation

    static constexpr uint32_t funct3_add            = 0b000; //binary representation
    static constexpr uint32_t funct3_sll            = 0b001; //binary representation
    static constexpr uint32_t funct3_slt            = 0b010; //binary representation
    static constexpr uint32_t funct3_sltu           = 0b011; //binary representation
    static constexpr uint32_t funct3_xor            = 0b100; //binary representation
    static constexpr uint32_t funct3_srx            = 0b101; //binary representation
    static constexpr uint32_t funct3_or             = 0b110; //binary representation
    static constexpr uint32_t funct3_and            = 0b111; //binary representation

    static constexpr uint32_t funct7_srl            = 0b0000000; //binary representation
    static constexpr uint32_t funct7_sra            = 0b0100000; //binary representation

    static constexpr uint32_t funct7_add            = 0b0000000; //binary representation
    static constexpr uint32_t funct7_sub            = 0b0100000; //binary representation

    static constexpr uint32_t insn_ecall            = 0x00000073; //binary representation
    static constexpr uint32_t insn_ebreak           = 0x00100073; //binary representation

    static constexpr uint32_t funct3_csrrw          = 0b001; //binary representation
    static constexpr uint32_t funct3_csrrs          = 0b010; //binary representation
    static constexpr uint32_t funct3_csrrc          = 0b011; //binary representation
    static constexpr uint32_t funct3_csrrwi         = 0b101; //binary representation
    static constexpr uint32_t funct3_csrrsi         = 0b110; //binary representation
    static constexpr uint32_t funct3_csrrci         = 0b111; //binary representation

    static uint32_t get_opcode(uint32_t insn); //int to hold opcode from instruction
    static uint32_t get_rd(uint32_t insn); //int to hold rd from instruction
    static uint32_t get_funct3(uint32_t insn); //int to hold funct3 from instruction
    static uint32_t get_rs1(uint32_t insn); //int to hold rs1 from instruction
    static uint32_t get_rs2(uint32_t insn); //int to hold rs2 from instruction
    static uint32_t get_funct7(uint32_t insn); //int to hold funct7 from instruction
    static int32_t get_imm_i(uint32_t insn); //int to hold imm_i from instruction
    static int32_t get_imm_u(uint32_t insn); //int to hold imm_u from instruction
    static int32_t get_imm_b(uint32_t insn); //int to hold imm_b from instruction
    static int32_t get_imm_s(uint32_t insn); //int to hold imm_s from instruction
    static int32_t get_imm_j(uint32_t insn); //int to hold imm_j from instruction

    static constexpr uint32_t XLEN = 32; //divisor length so we dont have to shift

    static std::string render_illegal_insn(uint32_t insn); //string to hold rendered instruction
    static std::string render_lui(uint32_t insn); //string to hold rendered instruction
    static std::string render_auipc(uint32_t insn); //string to hold rendered instruction

    ///@parm addr The memory address where the insn is stored.
    static std::string render_jal(uint32_t addr, uint32_t insn); //string to hold rendered instruction

    static std::string render_jalr(uint32_t insn); //string to hold rendered instruction

    ///@parm addr The memory address where the insn is stored.
    static std::string render_btype(uint32_t addr, uint32_t insn, const char *mnemonic); //string to hold rendered instruction

    static std::string render_itype_load(uint32_t insn, const char *mnemonic); //string to hold rendered instruction
    static std::string render_stype(uint32_t insn, const char *mnemonic); //string to hold rendered instruction
    static std::string render_itype_alu(uint32_t insn, const char *mnemonic, int32_t imm_i); //string to hold rendered instruction
    static std::string render_rtype(uint32_t insn, const char *mnemonic); //string to hold rendered instruction
    static std::string render_ecall(uint32_t insn); //string to hold rendered instruction
    static std::string render_ebreak(uint32_t insn); //string to hold rendered instruction
    static std::string render_csrrx(uint32_t insn, const char *mnemonic); //string to hold rendered instruction
    static std::string render_csrrxi(uint32_t insn, const char *mnemonic); //string to hold rendered instruction

    static std::string render_reg(int r); //string to hold rendered register int
    static std::string render_base_disp(uint32_t base, int32_t disp); //string to hold rendered disp
    static std::string render_mnemonic(const std::string &m); //string to hold specified rendered mnemonic
};

#endif /* rvi32decode_h */
