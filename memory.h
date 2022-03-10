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

#ifndef memory_h
#define memory_h

#include "hex.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

/**
 *
 * no parameters are here, these are just the inital declerations
 * the actual code to use them is in memory.cpp
 *
 * no return value here either as these are all just being initialized not
 * actually being used yet by the program
 *
 * @note provided by instructor, all of these are initilized here and then
 * being passed to another file
 **************************************************************************************/
class memory : public hex
{
public :
    memory ( uint32_t s ); //constructor
    ~ memory (); //deconstructor

    bool check_illegal ( uint32_t addr ) const ; //check illegal statement
    uint32_t get_size () const ; //get size function
    uint8_t get8 ( uint32_t addr ) const ; //unsigned int get8
    uint16_t get16 ( uint32_t addr ) const ; //unsigned int get16
    uint32_t get32 ( uint32_t addr ) const ; //unsigned int get32

    int32_t get8_sx ( uint32_t addr ) const ; //signed int get8
    int32_t get16_sx ( uint32_t addr ) const ; //signed int get16
    int32_t get32_sx ( uint32_t addr ) const ; //signed int get32

    void set8 ( uint32_t addr , uint8_t val ); //set8 to set address to new value
    void set16 ( uint32_t addr , uint16_t val ); //set16 to set address to new value
    void set32 ( uint32_t addr , uint32_t val ); //set32 to set address to new value

    void dump () const ; //memory dump output

    bool load_file ( const std :: string & fname ); //load file in and read it in binary

private :
    std :: vector < uint8_t > mem ; //vector of unsigned 8bit int
};

#endif /* memory_h */
