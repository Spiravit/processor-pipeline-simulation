#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "InstructionNode.h"
#include "InstructionQueue.h"

/**
 * @brief
 * A class to read a file line by line and parse the instructions 
 * into InstructionNodes which are stored in an InstructionQueue
 */
class FileReader
{
public:
    FileReader(const string path, size_t start_line = 0, size_t instruction_count = 0);

    ~FileReader();

    InstructionQueue* parseTraceFile(const string path, size_t start_line, size_t instruction_count);
    InstructionQueue* getInstructions();
    void printInstructions();

    InstructionQueue* instructions_;

private:
    
};

/**
 * @brief
 * Constructor for the FileReader class
 * @param path
 * the path to the trace file
 * @param start_line
 * the line to start parsing from (1 is the first line)
 * @param instruction_count
 * the number of instructions to parse
*/
FileReader::FileReader(const string path, size_t start_line, size_t instruction_count)
{
    instructions_ = parseTraceFile(path, start_line, instruction_count);
}

/**
 * @brief
 * Parses a trace file and returns a list of instructions
 * @param path
 * the path to the trace file
 * @param start_line
 * the line to start parsing from (1 is the first line)
 * @param instruction_count
 * the number of instructions to parse
 * @return
 * a list of the instructions parsed from the trace file 
*/
InstructionQueue* FileReader::parseTraceFile(const string path, size_t start_line, size_t instruction_count)
{
    InstructionQueue* instructions = new InstructionQueue();
    std::ifstream trace_file(path);

    if (!trace_file.is_open())
    {
        std::cerr << "Error opening trace file: " << path << std::endl;
        return instructions;
    }

    std::string line;

    // Skip lines before the starting line
    for (size_t i = 1; i < start_line && std::getline(trace_file, line); ++i)
    {
    }
    size_t parsed_count = 0;

    while (parsed_count < instruction_count && std::getline(trace_file, line))
    {
        std::stringstream ss(line);
        std::string token;

        // Parse program counter (PC)
        std::getline(ss, token, ',');
        std::string PC = token;

        // Parse instruction type
        std::getline(ss, token, ',');
        int type = std::stoi(token);

        // Parse dependencies
        std::vector<std::string> dependencies;
        while (std::getline(ss, token, ','))
        {
            std::string dependency_PC = token;
            dependencies.push_back(dependency_PC);
        }
        
        // Create instruction and add it to the list
        InstructionNode* node = new InstructionNode(PC, type, dependencies);
        instructions->push(node);
        ++parsed_count;
    }

    trace_file.close();
    return instructions;
}

InstructionQueue* FileReader::getInstructions()
{
    return instructions_;
}

/**
 * @brief
 * Prints the instructions to the console
 * uses the instructions parsed from the constructor
*/
void FileReader::printInstructions()
{
    for (const auto &instruction : instructions_->getInstructionQueue())
    {
        std::cout << "PC: " << std::hex << instruction->PC << std::dec << ", Type: " << instruction->type;
        std::cout << ", Dependencies: ";
        for (const auto &dependency : instruction->dependencies)
        {
            std::cout << std::hex << dependency << std::dec << " ";
        }
        std::cout << std::endl;
    }
}

FileReader::~FileReader()
{
    // close file
}