# Define what compiler to use and the flags.
CC = cc
CXX = g++
CCFLAGS = -g -std=c++11 -Wall -Werror
LDLIBS = -lm

# List all header files
HEADERS = FileReader.h InstructionNode.h InstructionQueue.h InstructionHistory.h InstructionWindow.h Simulator.h Output.h

# Create the project executable
project: main.cpp $(HEADERS)
	$(CXX) $(CCFLAGS) main.cpp -o project $(LDLIBS)

# Clean up
clean:
	rm -f core hw6