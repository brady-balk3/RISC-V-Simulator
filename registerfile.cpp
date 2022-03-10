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

#include "registerfile.h"
#include "hex.h"
#include <cstdint>
#include <iostream>
#include <iomanip>

using namespace std;


registerfile::registerfile()
{
    reset(); //reset registerfile
}

void registerfile::reset()
{
    reg[0] = 0x0; //set register 0 on reset
    for(int i=1;i<32;i++)
    {
        reg[i] = 0xf0f0f0f0; //set other registers on reset
    }
}

void registerfile::set(uint32_t r, int32_t val)
{
    if(r==0)
    {
        return; //if register is 0 return on set
    }
    else
    {
        reg[r] = val; //else set val
    }
}

int32_t registerfile::get(uint32_t r)const
{
    if(r==0)
    {
        return 0; //if register is 0 on get return 0
    }
    else
    {
        return reg[r]; //else return r
    }
}

void registerfile::dump(const std::string &hdr)const
{
    for(size_t i=0;i<32;i++) //dump condition loop
    {
        if(i!=0 && i%8==0)
        {
            std::cout<<std::endl; //endline
        }
        if(i%8==0)
        {
            std::string h; //hex string
            if(i==0)
            {
                h="x0"; //i is 0 then x0
            }
            else if(i==8)
            {
                h="x8"; //i is 8 then x8
            }
            else if(i==16)
            {
                h="x16"; //i is 16 then x16
            }
            else if(i==24)
            {
                h="x24"; //i is 24 then x24
            }
            std::cout<<hdr<<std::dec<<std::right<<::std::setw(3)<<std::setfill(' ')<<h<<" "; //output formatted h
        }
        if(i%8==7)
        {
            std::cout<<hex::to_hex32(reg[i]); //output registers that meet conditional statement
        }
        else if(i%4==0 && i!=0 && i%8 !=0)
        {
            std::cout<<" "<<hex::to_hex32(reg[i])<<" "; //output registers that meet conditional statement
        }
        else
        {
            std::cout<<hex::to_hex32(reg[i])<<" "; //output all other registers
        }
    }
}
