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

/**
 * This is the memory constructor for memsim. It sets the size of the memory
 * which is then rounded up to the nearest 16 bytes
 *
 * @param siz unsigned int which is used to allocate the size of memory
 *
 * no return is present in this function
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
memory::memory(uint32_t siz)
{
    siz=(siz+15)&0xfffffff0; //round the length up to mod16
    mem.resize(siz, 0xa5); //resize memory to fit new parameters
}

/**
 * This is the memory deconstructor for memsim. It cleans up any
 * necessary memory spillage that might occur
 *
 * no parameter present in this functin
 *
 * no return is present in this function
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
memory::~memory() //deconstructor, cleans up anything necessary
{
    mem.clear();
}

/**
 * memory::checkillegal checks to see if the passed address is within the
 * legal memory range as defined
 *
 * @param i unsigned int that contains the address that needs to be checked
 *
 * @return returns true if the address is illegal and false if not
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
bool memory::check_illegal(uint32_t i) const //check illegal function
{
    if(i>memory::get_size()) //if address size is less than memsize
    {
        std::cout<<"WARNING: Address out of range: "<<hex::to_hex0x32(i)<<std::endl; //output error
        return true;
    }
    else //else continue
    {
        return false;
    }
}
/**
 * memory::getsize() returns the size of the memory
 *
 * no parameter present in this function
 *
 * @return returns the size of memory in an unsigned int
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint32_t memory::get_size() const //getsize of the memory
{
    return mem.size(); //return the size of memory
}

/**
 * memory::get8 will return the byte(s) from the memory. Will
 * also check to see if the address is illegal. If it is it will return 0
 *
 * @param addr address of the byte(s) to be called and returned
 *
 * @return returns the byte at the specific address given
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint8_t memory::get8(uint32_t addr) const
{
    if(!memory::check_illegal(addr)) //check illegal
    {
        return mem[addr]; //if it is return the address
    }
    else //else continue
    {
        return 0;
    }
}

/**
 * memory::get16 will return the byte(s) from the memory. This function
 * does not check for an illegal address as it is more than one byte.
 * Calls get8 twice and then combines those values into a 16bit
 * little endian formatted value
 *
 * @param addr address of the byte(s) to be called and returned
 *
 * @return returns the byte(s) at the specific address given
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint16_t memory::get16(uint32_t addr) const
{
    uint8_t secaddr = get8(addr); //1st call
    uint8_t firstaddr = get8(addr + 1); //2nd call
    return ((uint16_t)firstaddr<<8) | secaddr; //combination of the two in little endian
}

/**
 * memory::get32 will return the byte(s) from the memory. This function
 * does not check for an illegal address as it is more than one byte.
 * Calls get16 twice and then combines those values into a 32bit
 * little endian formatted value
 *
 * @param addr address of the byte(s) to be called and returned
 *
 * @return returns the byte(s) at the specific address given
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
uint32_t memory::get32(uint32_t addr) const
{
    uint16_t secaddr = get16(addr); //1st call
    uint16_t firstaddr = get16(addr + 2); //2nd call
    return ((uint32_t)firstaddr<<16) | secaddr; //combining the two in little endian
}

/**
 * get8_sx gets called to return the value as a sign extended 32bit
 * int
 *
 * @param addr address of the byte(s) to be called and returned
 *
 * @return returns the byte(s) at the specific address given, sign
 * extended to be 32bits
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
int32_t memory::get8_sx(uint32_t addr) const
{
    return(int32_t)memory::get8(addr); //return the byte(s), sign extended to 32 bits
}

/**
 * get16_sx gets called to return the value as a sign extended 32bit
 * int
 *
 * @param addr address of the byte(s) to be called and returned
 *
 * @return returns the byte(s) at the specific address given, sign
 * extended to be 32bits
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
int32_t memory::get16_sx(uint32_t addr) const
{
    return(int32_t)memory::get16(addr); //return the byte(s), sign extended to 32 bits
}

/**
 * get32_sx gets called to return the value as a sign extended 32bit
 * int
 *
 * @param addr address of the byte(s) to be called and returned
 *
 * @return returns the byte(s) at the specific address given, sign
 * extended to be 32bits
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
int32_t memory::get32_sx(uint32_t addr) const
{
    return(int32_t)memory::get32(addr); //return the byte(s), sign extended to 32 bits
}

/**
 * memory::set8 will set the byte(s) at address to val. Also calls
 * check illegal to make sure the byte(s) called are legal, if they
 * aren't it is invalid and returns to the caller
 *
 * @param addr address of the byte(s) to be called and returned
 * @param val new value(s) for the called byte(s)
 *
 * no return present in this function
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
void memory::set8(uint32_t addr, uint8_t val)
{
    if(!memory::check_illegal(addr)) //check illegal if its not, proceed and set new value
    {
        mem[addr] = val;
    }
}

/**
 * memory::set16  calls set8 twice to set the byte(s) at address to val.
 * Also does not call check illegal to make sure the byte(s) called are legal
 * as they must already be for 16bytes. Will store the bytes in little endian
 * format
 *
 * @param addr address of the byte(s) to be called and returned
 * @param val new value(s) for the called byte(s)
 *
 * no return present in this function
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
void memory::set16(uint32_t addr, uint16_t val)
{
    uint8_t firstaddr = (uint8_t)((val & 0xFF00)>>8); //1st call formatting
    uint8_t secaddr = (uint8_t)(val & 0x00FF); //2nd call formatting
    memory::set8(addr+1,firstaddr); //combine the 1st address with the 1st call in little endian
    memory::set8(addr,secaddr); //combine the 2nd call with previous step in little endian
}

/**
 * memory::set32  calls set16 twice to set the byte(s) at address to val.
 * Also does not call check illegal to make sure the byte(s) called are legal
 * as they must already be for 32bytes. Will store the bytes in little endian
 * format
 *
 * @param addr address of the byte(s) to be called and returned
 * @param val new value(s) for the called byte(s)
 *
 * no return present in this function
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
void memory::set32(uint32_t addr, uint32_t val)
{
    uint16_t firstaddr = (uint16_t)((val & 0xFFFF0000)>>16); //1st call formatting
    uint16_t secaddr = (uint16_t)(val & 0x0000FFFF); //2nd call formatting
    memory::set16(addr+2,firstaddr); //combine the 1st address with the 1st call in little endian
    memory::set16(addr,secaddr); //combine the 2nd call with previous step in little endian
}

/**
 * memory::dump()  will dump the contents of the memory to cout. It will
 * dump the entirity of the contents in hex along with the equivilant ASCII
 * characters according to the assignment 3 handout
 *
 * no parameters are present in this function
 *
 * no return present in this function
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
void memory::dump() const
{
    std::string endline = ""; //find endline
    for(uint32_t addr = 0; addr<get_size();++addr) //for loop for formatting mem dump
    {
        if(addr%16==0)
            std::cout<<std::hex<<std::setfill('0')<<std::setw(8)<<addr<<": "; //if divisable by mod16 = 0 format this way
        std::cout<<hex::to_hex8(get8(addr))<<" ";
        uint8_t ch = get8(addr);
        ch=isprint(ch)?ch:'.'; //format with ASCII value
        endline+=ch;
        
        if(addr%16==7) //if divisable by mod16 = 7 format this way
            std::cout<<" ";
        if(addr%16==15) //if divisable by mod16 = 15 format this way
        {
            std::cout<<"*"<<endline<<"*"<<std::endl; //endline asterik output like in assembler
            endline.clear();
        }
    }
}

/**
 * memory::load_file will load a file into the program and then open it in
 * binary to read the the file's contents into the simulated memory
 *
 * no parameters are present in this function
 *
 * no return present in this function
 *
 * @note extended from starter code snippet that was given
 **************************************************************************************/
bool memory::load_file(const std::string &fname) //load file
{
    std::ifstream infile(fname, std::ios::in|std::ios::binary); //read in binary
    
    if(infile.is_open()) //while the file is open
    {
        uint8_t i; //usinged 8bit
        infile>>std::noskipws; //noskip when reading in
        for(uint32_t addr=0;infile>>i;++addr) //read loop
        {
            if(memory::check_illegal(addr)) //if the memory in the program is too large exit with 8
            {
                std::cerr<<"Program too big."<<std::endl;
                return false;
            }
            set8(addr,i); //8 bit address as i
        }
        return true; //successful read
    }
    else
    {
        std::cerr<<"File: '"<<fname<<"' can't be opened to read "<<std::endl; //else return an error with file can't be opened
        return false;
    }
}
