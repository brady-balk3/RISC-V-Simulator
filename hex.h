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

#ifndef hex_h
#define hex_h

#include <sstream>
#include <iomanip>
#include <string>


/**
 *
 * no parameters are here, these are just the inital declerations
 * the actual code to use them is in hex.cpp and memory.cpp
 *
 * no return value here either as these are all just being initialized not
 * actually being used yet by the program
 *
 * @note provided by instructor, all of these are initilized here and then
 * being passed to another file
 **************************************************************************************/
class hex
{
public :
    static std::string to_hex8 ( uint8_t i ); //string conversion 8bit
    static std::string to_hex32 ( uint32_t i ); //string conversion 32bit
    static std::string to_hex0x32 ( uint32_t i ); //string conversion 32bit with 0x in front
    static std::string to_hex0x20(uint32_t i); //string conversion with 0x in front showing the first 5 hex digits
    static std::string to_hex0x12(uint32_t i); //string conversion with 0x in front showing the first 3 hex digits
};

#endif /* hex_h */
