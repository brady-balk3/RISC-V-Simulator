#
# PROGRAM: rv32i
# AUTHOR:  Brady Balk
# ZId:     Z1905404
# Course:  CSCI463-1
# I certify that this is my own work and where appropriate an extension
# of the starter code provided for the assignment.

CXXFLAGS = -g -ansi -pedantic -Wall -Werror -std=c++14

rv32i: main.o memory.o hex.o rv32i_decode.o registerfile.o rv32i_hart.o cpu_single_hart.o
	g++ $(CXXFLAGS) -o rv32i main.o memory.o hex.o rv32i_decode.o registerfile.o rv32i_hart.o cpu_single_hart.o

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp

memory.o: memory.cpp memory.h
	g++ $(CXXFLAGS) -c memory.cpp

hex.o: hex.cpp hex.h
	g++ $(CXXFLAGS) -c hex.cpp

rv32i_decode.o: rv32i_decode.cpp rv32i_decode.h
	g++ $(CXXFLAGS) -c rv32i_decode.cpp

registerfile.o: registerfile.cpp registerfile.h
	g++ $(CXXFLAGS) -c registerfile.cpp

rv32i_hart.o: rv32i_hart.cpp rv32i_hart.h
	g++ $(CXXFLAGS) -c rv32i_hart.cpp

cpu_single_hart.o: cpu_single_hart.cpp cpu_single_hart.h
	g++ $(CXXFLAGS) -c cpu_single_hart.cpp


clean:
	rm -f *.o rv32i
