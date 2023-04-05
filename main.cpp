#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "FileReader.h"
#include "InstructionNode.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Usage: ./program path_to_trace_file start_instruction_# instruction_count" << endl;
        return 1;
    }

    string path = argv[1];

    // Create a TraceFileParser object and parse the trace file
    FileReader parser = FileReader(path, atoi(argv[2]), atoi(argv[3]));

    // Get the parsed instructions and print them to the console
    vector<InstructionNode> instructions = parser.getInstructions();
    parser.printInstructions();

    // TODO: Implement the rest of the simulation
    return 0;
}
