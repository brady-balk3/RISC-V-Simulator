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

#include "hex.h"

/**
 * hex::to_hex8 will take a hex value and then return it as a string
 *
 * @param i the hex value to be converted to a string
 *
 * @return returns the converted hex value as a string
 *
 * @note extended from the started code snippet that was given
 **************************************************************************************/
std::string hex::to_hex8(uint8_t i)
{
    std::ostringstream os; //declaring os to be used in formatting
    os<<std::hex<<std::setfill('0')<<std::setw(2)<<static_cast<uint16_t>(i); //formatting the 8bit int to hex string
    return os.str(); //return string
}

/**
 * hex::to_hex32 will take a hex value and then return it as a string
 *
 * @param i the hex value to be converted to a string
 *
 * @return returns the converted hex value as a string
 *
 * @note extended from the started code snippet that was given
 **************************************************************************************/
std::string hex::to_hex32(uint32_t i)
{
    std::ostringstream os; //declaring os to be used in formatting
    os<<std::hex<<std::setfill('0')<<std::setw(8)<<i; //formatting 32bit int to hex string
    return os.str(); //return string
}

/**
 * hex::to_hex0x32 will take a hex value and then return it as a string
 *
 * @param i the hex value to be converted to a string
 *
 * @return returns the converted hex value as a string with 0x in front
 *
 * @note extended from the started code snippet that was given
 **************************************************************************************/
std::string hex::to_hex0x32(uint32_t i)
{
    return std::string("0x")+to_hex32(i); //formatting 32bit int to hex string with 0x prefix and returning
}

/**
 * hex::to_hex0x32 will take a hex value and then return it as a string
 *
 * @param i the hex value to be converted to a string
 *
 * @return returns the converted hex value as a string with 0x in front
 * first 5 hex digits only
 *
 * @note extended from the started code snippet that was given
 **************************************************************************************/
std::string hex::to_hex0x20(uint32_t i)
{
    std::ostringstream os; //declaring os to be used in formatting
    os<<std::hex<<std::setfill('0')<<std::setw(5)<<i; //formatting the 20bit int to 5 digit hex string
    return std::string("0x")+os.str(); //return string
}

/**
 * hex::to_hex0x12 will take a hex value and then return it as a string
 *
 * @param i the hex value to be converted to a string
 *
 * @return returns the converted hex value as a string with 0x in front
 * first 3 hex digits only with proper and mask
 *
 * @note extended from the started code snippet that was given
 **************************************************************************************/
std::string hex::to_hex0x12(uint32_t i)
{
    std::ostringstream os; //declaring os to be used in formatting
    os<<std::hex<<std::setfill('0')<<std::setw(3)<<(i & 0x0000fff); //formatting the 12bit int to 3 digit hex string
    return std::string("0x")+os.str(); //return string
}
