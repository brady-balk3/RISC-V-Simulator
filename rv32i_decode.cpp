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

#include "memory.h"
#include "hex.h"
#include "rv32i_decode.h"
#include <cassert>

/**
 * rv32i_decode decodes the given instructions by calling the correct
 * helper render function from a cascading switch statment
 *
 * @param addr the address of the instruction to be decoded
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the decoded instruction is then ouput via the correct
 * helper function as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::decode(uint32_t addr, uint32_t insn)
{
    uint32_t funct3 = get_funct3(insn); //will hold funct3
    uint32_t funct7 = get_funct7(insn); //will hold funct7
    
    if(insn == insn_ecall) //call ecall if the instruction matches exactly
    {
        return render_ecall(insn); //return ecall
    }
    if(insn == insn_ebreak) //call ebreak if the instruction matches exactly
    {
        return render_ebreak(insn); //return ebreak
    }
    
    //cascading switch statment based on opcodes and other variables to catch the given instructions
    switch(get_opcode(insn))
    {
    default: return render_illegal_insn(insn); //return default error with parameters if it is an illegal instruction
            
    case opcode_lui: return render_lui(insn); //return rendered lui with parameters if opcode matches
            
    case opcode_auipc: return render_auipc(insn); //return rendered auipc with parameters if opcode matches

    case opcode_jal: return render_jal(addr,insn); //return rendered jal with parameters if opcode matches
            
    case opcode_jalr: return render_jalr(insn); //return rendered jalr with parameters if opcode matches
      
    //check for btype opcode...
    case opcode_btype:
        //sort via funct3 value
        switch (funct3)
        {
        default: return render_illegal_insn(insn); //defualt bad instruction with parameters return
        case funct3_beq: return render_btype(addr, insn, "beq"); //return rendered beq with parameters if funct3 matches
        case funct3_bne: return render_btype(addr, insn, "bne"); //return rendered bne with parameters if funct3 matches
        case funct3_blt: return render_btype(addr, insn, "blt"); //return rendered blt with parameters if funct3 matches
        case funct3_bge: return render_btype(addr, insn, "bge"); //return rendered bge with parameters if funct3 matches
        case funct3_bltu: return render_btype(addr, insn, "bltu"); //return rendered bltu with parameters if funct3 matches
        case funct3_bgeu: return render_btype(addr, insn, "bgeu"); //return rendered bgeu with parameters if funct3 matches
        }
        assert(0 && "unrecognized funct3"); // impossible
     
    //check for load_imm opcode...
    case opcode_load_imm:
            //sort via funct3
            switch (funct3)
            {
            default: return render_illegal_insn(insn); //defualt bad instruction with parameters return
            case funct3_lb: return render_itype_load(insn, "lb"); //return rendered lb with parameters if funct3 matches
            case funct3_lh: return render_itype_load(insn, "lh"); //return rendered lh with parameters if funct3 matches
            case funct3_lw: return render_itype_load(insn, "lw"); //return rendered lw with parameters if funct3 matches
            case funct3_lbu: return render_itype_load(insn, "lbu"); //return rendered lbu with parameters if funct3 matches
            case funct3_lhu: return render_itype_load(insn, "lhu"); //return rendered lhu with parameters if funct3 matches
            }
            assert(0 && "unrecognized funct3"); // impossible
            
    //check for stype opcode...
    case opcode_stype:
            //sort via funct3
            switch (funct3)
            {
            default: return render_illegal_insn(insn); //defualt bad instruction with parameters return
            case funct3_sb: return render_stype(insn, "sb"); //return rendered sb with parameters if funct3 matches
            case funct3_sh: return render_stype(insn, "sh"); //return rendered sh with parameters if funct3 matches
            case funct3_sw: return render_stype(insn, "sw"); //return rendered sw with parameters if funct3 matches
            }
            assert(0 && "unrecognized funct3"); // impossible
            
    //check for alu imm opcode...
    case opcode_alu_imm:
        //sort via funct3
        switch (funct3)
        {
            default: return render_illegal_insn(insn); //defualt bad instruction with parameters return
            case funct3_add: return render_itype_alu(insn, "addi", get_imm_i(insn)); //return rendered add with parameters if funct3 matches
            case funct3_slt: return render_itype_alu(insn, "slti", get_imm_i(insn)); //return rendered slt with parameters if funct3 matches
            case funct3_sltu: return render_itype_alu(insn, "sltiu", get_imm_i(insn)); //return rendered sltu with parameters if funct3 matches
            case funct3_xor: return render_itype_alu(insn, "xori", get_imm_i(insn)); //return rendered xori with parameters if funct3 matches
            case funct3_or: return render_itype_alu(insn, "ori", get_imm_i(insn)); //return rendered ori with parameters if funct3 matches
            case funct3_and: return render_itype_alu(insn, "andi", get_imm_i(insn)); //return rendered and with parameters if funct3 matches
            case funct3_sll: return render_itype_alu(insn, "slli", get_imm_i(insn)%XLEN); //return rendered sll with parameters if funct3 matches
            //if it matches srx funct3, move to new twitch
            case funct3_srx:
                //new sort via funct7
                switch(funct7)
                {
                default: return render_illegal_insn(insn); //defualt bad instruction with parameters return
                case funct7_sra: return render_itype_alu(insn, "srai", get_imm_i(insn)%XLEN); //return rendered srai with parameters if funct7 matches
                case funct7_srl: return render_itype_alu(insn, "srli", get_imm_i(insn)%XLEN); //return rendered srli with parameters if funct7 matches
                }
                assert(0 && "unrecognized funct7"); // impossible
        }
        assert(0 && "unrecognized funct3"); // impossible

    //check for rtype opcode...
    case opcode_rtype:
        //sort via funct3
        switch(funct3)
        {
        default: return render_illegal_insn(insn); //defualt bad instruction with parameters return
        //move to new switch if funct3 = add
        case funct3_add:
            //sort via funct7
            switch(funct7)
            {
                case funct7_add: return render_rtype(insn, "add"); //return rendered add with parameters if funct7 matches
                case funct7_sub: return render_rtype(insn, "sub"); //return rendered sub with paramaters if funct7 matches
            }
            assert(0 && "unrecognized funct7"); // impossible
        case funct3_sll: return render_rtype(insn, "sll"); //return rendered sll with parameters if funct3 matches
        case funct3_slt: return render_rtype(insn, "slt"); //return rendered slt with parameters if funct3 matches
        case funct3_sltu: return render_rtype(insn, "sltu"); //return rendered sltu with parameters if funct3 matches
        case funct3_xor: return render_rtype(insn, "xor"); //return rendered xor with parameters if funct3 matches
            //move to new switch if funct3 = srx
            case funct3_srx:
                //sort via funct7
                switch(funct7)
                {
                    case funct7_srl: return render_rtype(insn, "srl"); //return rendered srl with parameters if funct7 matches
                    case funct7_sra: return render_rtype(insn, "sra"); //return rendered sra with parameters if funct7 matches
                }
                assert(0 && "unrecognized funct7"); // impossible
        case funct3_or: return render_rtype(insn, "or"); //return rendered or with parameters if funct3 matches
        case funct3_and: return render_rtype(insn, "and"); //return rendered and with parameters if funct3 matches
        }
        assert(0 && "unrecognized funct3"); // impossible
    
    //check for system opcode...
    case opcode_system:
        //sort via funct3
        switch(funct3)
            {
            default: return render_illegal_insn(insn); //defualt bad instruction with parameters return
            case funct3_csrrw: return render_csrrx(insn, "csrrw"); //return rendered csrrw with parameters if funct3 matches
            case funct3_csrrs: return render_csrrx(insn, "csrrs"); //return rendered csrrs with parameters if funct3 matches
            case funct3_csrrc: return render_csrrx(insn, "csrrc"); //return rendered csrrc with parameters if funct3 matches
            case funct3_csrrwi: return render_csrrxi(insn, "csrrwi"); //return rendered csrrwi with parameters if funct3 matches
            case funct3_csrrsi: return render_csrrxi(insn, "csrrsi"); //return rendered csrrsi with parameters if funct3 matches
            case funct3_csrrci: return render_csrrxi(insn, "csrrci"); //return rendered csrrci with parameters if funct3 matches
            }
            assert(0 && "unrecognized funct3"); // impossible
}
assert(0 && "unrecognized opcode"); // It should be impossible to ever get here!
}

/**
 * rv32i_decode::render_illegal_insn is the render function that is used
 * if the instruction is invalid
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return an error string explaining the problem
 *
 * @note provided by instructor
 **************************************************************************************/
std::string rv32i_decode::render_illegal_insn(uint32_t insn)
{
    (void)insn; //voids instruction
    return "ERROR: UNIMPLEMENTED INSTRUCTION"; //returns error message
}

/**
 * rv32i_decode::render_lui is the render helper function that is used
 * to render, format,  and output the lui instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the decoded lui instruction is then ouput as a string
 *
 * @note provided by instructor
 **************************************************************************************/
std::string rv32i_decode::render_lui(uint32_t insn)
{
    uint32_t rd = get_rd(insn); //rd value
    int32_t imm_u = get_imm_u(insn); //imm_u value
    std::ostringstream os; //string to hold return value
    os << render_mnemonic("lui") << render_reg(rd) << "," << hex::to_hex0x20((imm_u >> 12) & 0x0fffff); //formatted and shifted
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_auipc is the render helper function that
 * is used to render, format, and output the auipc instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the decoded auipc instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_auipc(uint32_t insn)
{
    uint32_t rd = get_rd(insn); //rd value
    int32_t imm_u = get_imm_u(insn); //imm_u value
    std::ostringstream os; //string to hold return value
    os << render_mnemonic("auipc") << render_reg(rd) << "," << hex::to_hex0x20((imm_u >> 12) & 0x0fffff); //formatted and shifted
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_jal is the render helper function that
 * is used to render, format, and output the jal instruction
 *
 * @param addr the address of the instruction to be decoded
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the decoded jal instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_jal(uint32_t addr, uint32_t insn)
{
    uint32_t rd = get_rd(insn); //rd value
    int32_t imm_j = get_imm_j(insn); //imm_j value
    int32_t pcrel_21 = addr + imm_j; //pcrel for relative addressing
    std::ostringstream os; //string to hold return value
    os << render_mnemonic("jal") << render_reg(rd) << "," << hex::to_hex0x32(pcrel_21); //formatted output
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_jalr is the render helper function that
 * is used to render, format, and output the jalr instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the decoded jalr instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_jalr(uint32_t insn)
{
    uint32_t rd = get_rd(insn); //rd value
    uint32_t rs1 = get_rs1(insn); //rs1 value
    int32_t imm_i = get_imm_i(insn); //imm_i value
    std::ostringstream os; //string to hold return value
    os << render_mnemonic("jalr") << render_reg(rd) << "," << render_base_disp(rs1,imm_i); //formatted output
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_btype is the render helper function that
 * is used to render, format, and output the bytpe instructions
 *
 * @param addr the address of the instruction to be decoded
 * @param insn the literal riscv instruction to be decoded
 * @param mnemonic character mnemonic that identifies specific instruction
 *
 * @return the decoded btype instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_btype(uint32_t addr, uint32_t insn, const char *mnemonic)
{
    uint32_t rs1 = get_rs1(insn); //rs1 value
    uint32_t rs2 = get_rs2(insn); //rs2 value
    int32_t imm_b = get_imm_b(insn); //imm_b value
    int32_t pcrel_13 = addr + imm_b; //pcrel value for relative adressing
    std::ostringstream os; //string to hold return value
    os << render_mnemonic(mnemonic) << render_reg(rs1) << "," << render_reg(rs2) << "," << hex::to_hex0x32(pcrel_13); //formatted output
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_itype_load is the render helper function that
 * is used to render, format, and output the load itype instructions
 *
 * @param insn the literal riscv instruction to be decoded
 * @param mnemonic character mnemonic that identifies specific instruction
 *
 * @return the decoded load itype instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_itype_load(uint32_t insn, const char *mnemonic)
{
    uint32_t rd = get_rd(insn); //rd value
    uint32_t rs1 = get_rs1(insn); //rs1 value
    int32_t imm_i = get_imm_i(insn); //imm_i value
    std::ostringstream os; //string to hold return value
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << render_base_disp(rs1,imm_i); //formatted output
    return os.str();  //return formatted string
}

/**
 * rv32i_decode::render_stype is the render helper function that
 * is used to render, format, and output the sytpe instructions
 *
 * @param insn the literal riscv instruction to be decoded
 * @param mnemonic character mnemonic that identifies specific instruction
 *
 * @return the decoded stype instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_stype(uint32_t insn, const char *mnemonic)
{
    uint32_t rs1 = get_rs1(insn); //rs1 value
    uint32_t rs2 = get_rs2(insn); //rs2 value
    int32_t imm_s = get_imm_s(insn); //imm_s value
    std::ostringstream os; //string to hold return value
    os << render_mnemonic(mnemonic) << render_reg(rs2) << "," << render_base_disp(rs1,imm_s); //formatted output
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_itype_alu is the render helper function that
 * is used to render, format, and output the alu itype instructions
 *
 * @param insn the literal riscv instruction to be decoded
 * @param mnemonic character mnemonic that identifies specific instruction
 * @param imm_i int that represents and immediate value to be used
 *
 * @return the decoded alu itype instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_itype_alu(uint32_t insn, const char *mnemonic, int32_t imm_i)
{
    uint32_t rd = get_rd(insn); //rd value
    uint32_t rs1 = get_rs1(insn); //rs1 value
    std::ostringstream os; //string to hold return value
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << render_reg(rs1) << "," << imm_i; //formatted output
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_rtype is the render helper function that
 * is used to render, format, and output the rtype instructions
 *
 * @param insn the literal riscv instruction to be decoded
 * @param mnemonic character mnemonic that identifies specific instruction
 *
 * @return the decoded rtype instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_rtype(uint32_t insn, const char *mnemonic)
{
    uint32_t rd = get_rd(insn); //rd value
    uint32_t rs1 = get_rs1(insn); //rs1 value
    uint32_t rs2 = get_rs2(insn); //rs2 value
    std::ostringstream os; //string to hold return value
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << render_reg(rs1) << "," << render_reg(rs2); //formatted output
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_ecall is the render helper function that
 * is used to render, format, and output the ecall instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the decoded ecall instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_ecall(uint32_t insn)

{
    std::ostringstream os; //string to hold return value
    os << "ecall"; //send 'ecall' to be held as a string
    return os.str(); //return string
}

/**
 * rv32i_decode::render_ebreak is the render helper function that
 * is used to render, format, and output the ebreak instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the decoded ebreak instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_ebreak(uint32_t insn)

{
    std::ostringstream os; //string to hold return value
    os << "ebreak"; //send 'ebreak' to be held as a string
    return os.str(); //return string
}

/**
 * rv32i_decode::render_csrrx is the render helper function that
 * is used to render, format, and output the csrrx instructions
 *
 * @param insn the literal riscv instruction to be decoded
 * @param mnemonic character mnemonic that identifies specific instruction
 *
 * @return the decoded csrrx instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_csrrx(uint32_t insn, const char *mnemonic)

{
    uint32_t rd = get_rd(insn); //rd value
    uint32_t rs1 = get_rs1(insn); //rs1 value
    int32_t csrr = get_imm_i(insn); //csrr value via immediate imm_i
    std::ostringstream os; //string to hold return value
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << hex::to_hex0x12(csrr) << "," << render_reg(rs1); //formatted output
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_csrrxi is the render helper function that
 * is used to render, format, and output the csrrxi instructions
 *
 * @param insn the literal riscv instruction to be decoded
 * @param mnemonic character mnemonic that identifies specific instruction
 *
 * @return the decoded csrrxi instruction is then ouput as a string
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_csrrxi(uint32_t insn, const char *mnemonic)

{
    uint32_t rd = get_rd(insn); //rd value
    int32_t rs1 = get_rs1(insn); //rs1 value
    uint32_t csrri = get_imm_i(insn); //csrri value via immediate imm_i
    std::ostringstream os; //string to hold return value
    os << render_mnemonic(mnemonic) << render_reg(rd) << "," << hex::to_hex0x12(csrri) << "," << rs1; //formatted output
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::render_regis the render helper function that
 * is used to render, format, and output the register number
 *
 * @param r int that is register number
 *
 * @return decoded and then output as a string in x(r) format
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_reg(int r)
{
    std::ostringstream os; //string to hold return vale
    os << "x" << r; //send 'x' to string paird with reg number
    return os.str(); //return string
}

/**
 * rv32i_decode::render_base_disp is the render helper function that
 * is used to render, format, and output the base disposition of the reg
 *
 * @param r int that is register number
 * @param imm immediate value to be used to calculate disp
 *
 * @return decoded and then output as a string showing disp off reg
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_base_disp(uint32_t r, int32_t imm)
{
    std::ostringstream os; //string to hold return value
    os << imm << "(" << render_reg(r) << ")"; //string is immediate value with r number disp
    return os.str(); //return string
}

/**
 * rv32i_decode::render_mnemonic is the render helper function that
 * is used to render, format, and output instruction mnemonic
 *
 * @param mnemonic the literal riscv instruction to be shown
 *
 * @return mnemonic is formatted and output as the right instruction
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
std::string rv32i_decode::render_mnemonic(const std::string &mnemonic)
{
    std::ostringstream os; //string to hold return value
    os << std::setw(mnemonic_width) << std::setfill(' ') << std::left << mnemonic; //setwidth of mnemoic value and send the actual name of instruction
    return os.str(); //return formatted string
}

/**
 * rv32i_decode::get_opcode gets the opcode of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the opcode is decoded and then matched against
 * const binary value
 *
 * @note provided by instructor
 **************************************************************************************/
uint32_t rv32i_decode::get_opcode(uint32_t insn)
{
    return (insn & 0x0000007f); //opcode return
}

/**
 * rv32i_decode::get_rd gets the rd of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the rd is decoded and then used to compare instructions
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint32_t rv32i_decode::get_rd(uint32_t insn)
{
    return (insn & 0x00000f80) >> 7; //rd return with correct bits used
}

/**
 * rv32i_decode::get_funct3 gets the funct3 of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the funct3 is decoded and then used to compare instructions
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint32_t rv32i_decode::get_funct3(uint32_t insn)
{
    return (insn & 0x00007000) >> 12; //funct3 return with correct bits used
}

/**
 * rv32i_decode::get_rs1gets the rs1 of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the rs1 is decoded and then used to compare instructions
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint32_t rv32i_decode::get_rs1(uint32_t insn)
{
    return (insn & 0x000f8000) >> 15; //rs1 return with correct bits used
}

/**
 * rv32i_decode::get_rs2 gets the rs2 of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the rs2 is decoded and then used to compare instructions
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint32_t rv32i_decode::get_rs2(uint32_t insn)
{
    return (insn & 0x01f00000) >> 20; //rs2 return with correct bits used
}

/**
 * rv32i_decode::get_funct7 gets the funct7 of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the funct7 is decoded and then used to compare instructions
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint32_t rv32i_decode::get_funct7(uint32_t insn)
{
    return (insn & 0xfe000000) >> 25; //funct7 return with correct bits used
}

/**
 * rv32i_decode::get_imm_i gets the imm_i  of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the bits that represent imm_i
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
int32_t rv32i_decode::get_imm_i(uint32_t insn)
{
    int32_t imm_i = (insn & 0xfff00000) >> (20-0); //shift right the bits from 20 to 0 and compare with & mask
    
    if (insn & 0x80000000) //msb identifier
        imm_i |= 0xfffff000; // sign-extend the left if msb is active
    return imm_i; //return value
}

/**
 * rv32i_decode::get_imm_u gets the imm_u of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the bits that represent imm_u
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
int32_t rv32i_decode::get_imm_u(uint32_t insn)
{
    int32_t imm_u = (insn & 0x00000fff) & 0; //set bits to 0 (0-11) with & mask
    imm_u |= (insn & 0xfffff000); //these bits stay the same
    
    return imm_u; //return value
}

/**
 * rv32i_decode::get_imm_b gets the imm_b  of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the bits that represent imm_b
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
int32_t rv32i_decode::get_imm_b(uint32_t insn)
{
    int32_t imm_b = (insn & 0x00000001) & 0; //set lsb as 0
    imm_b |= (insn & 0x00000f00) >> (8-1); //shift right & mask
    imm_b |= (insn & 0x7e000000) >> (25-5); //shift right & mask
    imm_b |= (insn & 0x00000080) << (11-7); //shift left with & mask
    imm_b |= (insn & 0x80000000) >> (31-12); //shift right with & mask
    
    if (insn & 0x80000000) //msb identifier
        imm_b |= 0xffffe000; // sign-extend the left if msb is active
    return imm_b;
}

/**
 * rv32i_decode::get_imm_s gets the imm_s of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the bits that represent imm_s
 *
 * @note provided by instructor
 **************************************************************************************/
int32_t rv32i_decode::get_imm_s(uint32_t insn)
{
    int32_t imm_s = (insn & 0xfe000000) >> (25-5); //right shift with & mask
    imm_s |= (insn & 0x00000f80) >> (7-0); //right shift with & mask
    
    if (insn & 0x80000000) //msb identifier
        imm_s |= 0xfffff000; // sign-extend the left if msb is active
    return imm_s;
}

/**
 * rv32i_decode::get_imm_j gets the imm_j  of the instruction
 *
 * @param insn the literal riscv instruction to be decoded
 *
 * @return the bits that represent imm_j
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
int32_t rv32i_decode::get_imm_j(uint32_t insn)
{
    int32_t imm_j = (insn & 0x00000001) & 0; //set lsb as 0
    imm_j |= (insn & 0x7fe00000) >> (21-1); //right shift with & mask
    imm_j |= (insn & 0x00100000) >> (20-11); //right shift with & mask
    imm_j |= (insn & 0x000ff000); //keep these bits the same with & mask
    imm_j |= (insn & 0x80000000) >> (31-20); // right shift with & mask
    
    if (insn & 0x80000000) //msb identifier
        imm_j |= 0xffe00000; // sign-extend the left if msb active
    return imm_j;
}
