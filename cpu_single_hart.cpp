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

#include "cpu_single_hart.h"
#include "hex.h"
#include "rv32i_decode.h"
#include "registerfile.h"
#include "rv32i_hart.h"

using namespace std;


/**
 * rv32i_hart::tick is what tells the simulator to run an instruction
 *
 * @param exec_limit takes in the exec limit paramter
 *
 * no return present in this function, just output to standard output
 *
 * @note extended from starter code
 **************************************************************************************/
void cpu_single_hart::run(uint64_t exec_limit) //run function
{
    regs.set(2, mem.get_size()); //set reg to size of memory
    while((is_halted() != true && exec_limit==0)||(is_halted()!=true && get_insn_counter()<exec_limit))
    {
        tick(); //tick while its not halted and exec limit is 0 or insn counter is less than exec limit
    }
    if(is_halted())
    {
        std::cout<<"Execution terminated. Reason: "<<get_halt_reason()<<std::endl; //if it is halted output halt message
    }
    std::cout<<get_insn_counter()<<" instructions executed"<<std::endl; //else show how many instructions were ran
}


