#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "InstructionNode.h"

using namespace std;
/**
 * @brief
 * A class to read a file line by line.
 * this class will be replaced with the 'TreeFileParser' class
 */
class FileReader
{
public:
    FileReader(const string path, size_t start_line = 0, size_t instruction_count = 0);

    ~FileReader();

    vector<InstructionNode> parseTraceFile(string path, size_t start_line, size_t instruction_count);
    vector<InstructionNode> getInstructions();
    void printInstructions();

private:
    vector<InstructionNode> instructions_;
};

FileReader::FileReader(const string path, size_t start_line, size_t instruction_count)
{
    instructions_ = parseTraceFile(path, start_line, instruction_count);
}

vector<InstructionNode> FileReader::parseTraceFile(const string path, size_t start_line, size_t instruction_count)
{
    std::vector<InstructionNode> instructions;
    std::ifstream trace_file(path);

    if (!trace_file.is_open())
    {
        std::cerr << "Error opening trace file: " << path << std::endl;
        return instructions;
    }

    std::string line;
    // Skip lines before the starting line
    for (size_t i = 0; i < start_line && std::getline(trace_file, line); ++i)
    {
    }
    size_t parsed_count = 0;

    while (parsed_count < instruction_count && std::getline(trace_file, line))
    {
        std::stringstream ss(line);
        std::string token;

        // Parse program counter (PC)
        std::getline(ss, token, ',');
        unsigned int PC = std::stoul(token, nullptr, 16);

        // Parse instruction type
        std::getline(ss, token, ',');
        int type = std::stoi(token);

        // Parse dependencies
        std::vector<unsigned int> dependencies;
        while (std::getline(ss, token, ','))
        {
            unsigned int dependency_PC = std::stoul(token, nullptr, 16);
            dependencies.push_back(dependency_PC);
        }

        // Create instruction and add it to the list
        instructions.emplace_back(PC, type, dependencies);
        ++parsed_count;
    }

    trace_file.close();
    return instructions;
}

vector<InstructionNode> FileReader::getInstructions()
{
    return instructions_;
}
// Function to print the parsed instructions to the console
void FileReader::printInstructions()
{
    for (const auto &instruction : instructions_)
    {
        std::cout << "PC: " << std::hex << instruction.PC << std::dec << ", Type: " << instruction.type;
        std::cout << ", Dependencies: ";
        for (const auto &dependency : instruction.dependencies)
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