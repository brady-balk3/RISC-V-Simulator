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

#ifndef registerfile_h
#define registerfile_h

#include <string>
#include <stdint.h>
#include <vector>

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
class registerfile //registerfile class
{
public: //public to be used through program
    registerfile(); //registerfile
    void reset(); //reset regs
    void set(uint32_t r, int32_t val); //set the value of r and val
    int32_t get(uint32_t r) const; //get r as a constant
    void dump(const std::string &hdr)const; //dump hdr
    
private: //private vector
    int32_t reg[32];
};

#endif /* registerfile_h */
