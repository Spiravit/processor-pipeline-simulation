# Define what compiler to use and the flags.
CC = cc
CXX = g++
CCFLAGS = -g -std=c++11 -Wall -Werror -Wno-unused-variable -Wno-unused-private-field
LDLIBS = -lm

# List all header files
HEADERS = FileReader.h InstructionNode.h InstructionQueue.h InstructionHistory.h InstructionWindow.h Simulator.h Output.h

# Create the project executable
proj: main.cpp $(HEADERS)
	$(CXX) $(CCFLAGS) main.cpp -o proj $(LDLIBS)

# Clean up
clean:
	rm -f core hw6
