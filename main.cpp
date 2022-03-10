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

#include <getopt.h>
#include "hex.h"
#include "memory.h"
#include "rv32i_decode.h"
#include "rv32i_hart.h"
#include "cpu_single_hart.h"



using namespace std;

/**
 * Usage prints an error message and the pattern to stderr and
 * then terminates the program
 *
 * no parameters present in this function
 *
 * no return present in this function, only output to std:cerr
 *
 * @note provided by instructor
 **************************************************************************************/
static void usage()
{
    std::cerr << "Usage: rv32i [-d] [i] [-r] [-z] [-l execution-limit] [-m hex-mem-size] infile" << std::endl; //infile error
    std::cerr << "    -d show disassembly before program execution" <<std::endl; //disassembly error
    std::cerr << "    -i show instruction printing during execution" <<std::endl; //instruction error
    std::cerr << "    -l maximum number of instructions to exec" <<std::endl; //limit error
    std::cerr << "    -m specify memory size (default = 0x100)" << std::endl; //memsize error
    std::cerr << "    -r show register printing during execution" <<std::endl; //register error
    std::cerr << "    -z show a dump of the regs & memory after simulation" <<std::endl; //dump error
    exit(1); //exit code
}

/**
 * disassembles the given instructions by getting memory size
 * then dividing by 4 as the insn is 4bytes in a loop to perform
 * for all instructions. It is then decoded and output and the mem
 * counter is incremented by 4
 *
 * @param mem the memory which holds the instructions
 *
 * no return present in this function
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
static void disassemble(const memory &mem)
{
    uint32_t pc = 0; //program counter value
    uint32_t insn = 0; //instruction value
    
    while(pc<mem.get_size()) //while program counter is less than the memsize
    {
        cout<<hex::to_hex32(pc)<<": "; //output pc in hex32
        insn=mem.get32(pc); //set instruction equal to pc value in memory
        cout<<hex::to_hex32(insn)<<" "; //output instruction in hex32
        cout<<rv32i_decode::decode(pc,insn)<<endl; //decode the pc value and instruction and output
    }
}

/**
 * main function that runs and executes the a4 disassemble program
 * @param argv takes user input from command line such as opening
 *  a file and then reading and passing those args to the program to be
 *  ran
 *
 * @return 0 on successful completion and printout of results otherwise
 * an appropriate error message will be printed
 *
 * @note provided by instructor
 **************************************************************************************/
int main(int argc, char **argv)
{
    uint32_t memory_limit = 0x100; // default memory size = 256 bytes
    int opt;
    int exec_limit = 0; //execution limit value
    int dfl = 0; //d flag for command line args
    int ifl = 0; //i flag for command line args
    int rfl = 0; //r flag for command line args
    int zfl = 0; //z flag for command line args
    while ((opt = getopt(argc, argv, "m:l:dirz")) != -1) //updated command line args
    {
        switch (opt) //switch to select which arguments were selected
        {
            default: usage(); //default statement
            case 'm':
            {
                memory_limit = stoul(optarg,nullptr,16); //memory limit case
                break;
            }
            case 'd':
            {
                dfl=1; //set d flag to 1 and then run the condition where d flag is one
                break;
            }
            case 'i':
            {
                ifl=1; //set i flag to 1 and then run the condition where i flag is one
                break;
            }
            case 'r':
            {
                rfl=1; //set r flag to 1 and then run the condition where r flag is one
                break;
            }
            case 'z':
            {
                zfl=1; //set z flag to 1 and then run the condition where z flag is one
                break;
            }
            case 'l':
            {
                exec_limit = std::stoul(optarg,nullptr,0); //execution limit case
                break;
            }
            
        }
    }
    
    if (optind >= argc)
        usage(); // missing filename
    
    memory mem(memory_limit); //memory limit
    
    if (!mem.load_file(argv[optind]))
        usage(); //default usage error
    
    rv32i_hart sim(mem); //load simulator with memory
    cpu_single_hart cpu(mem); //run cpu with loaded memory instructions
    
    if(dfl==1)
    {
        disassemble(mem); //disassemble memory when d flag is 1
      // sim.reset(); //reset simulator when d flag is 1
       // cpu.reset(); //reset cpu when d flag is 1
    }
    if(ifl==1)
    {
        cpu.set_show_instructions(true); //set cpu to show instructions when i flag is 1
    }
    if(rfl==1)
    {
        cpu.set_show_registers(true); //set cpu to show all registers when r flag is 1
    }
    cpu.run(exec_limit); //run the cpu until execution limit is hit
    
    if(zfl==1)
    {
        cpu.dump(); //dump cpu contents when z flag is 1
        mem.dump(); //dump memory contents when z flag is 1
    }
    
    return 0; //successful return value
}
