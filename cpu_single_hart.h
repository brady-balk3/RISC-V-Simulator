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

#ifndef cpu_single_hart_h
#define cpu_single_hart_h

#include "memory.h"
#include "rv32i_hart.h"

using namespace std;


/**
 *
 * no parameters are here, these are just the inital declerations
 * the actual code to use them is in hex.cpp and memory.cpp
 *
 * no return value here either as these are all just being initialized not
 * actually being used yet by the program
 *
 * @note extneded from the starter code given
 **************************************************************************************/

class cpu_single_hart : public rv32i_hart //subclass of rv32i hart
{
    public:
        cpu_single_hart(memory &mem):rv32i_hart(mem) //public single hart function
        {
            
        }
    void run(uint64_t exec_limit); //run
};

#endif /* cpu_single_hart_h */
