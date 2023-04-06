/**
 * @brief 
 * node used to store an instruction
 */
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;
class InstructionNode {
 public:
    unsigned int PC;
    int type;
    std::vector<unsigned int> dependencies;
    bool completed; // added this var so i dont think we need the instruction state class anymore

    InstructionNode(unsigned int PC, int type, const std::vector<unsigned int>& dependencies)
        : PC(PC), type(type), dependencies(dependencies) {}
};


enum class InstructionState
{
    FETCHED,
    DECODED,
    EXECUTING,
    MEMORY_ACCESS,
    COMPLETED
};


#endif // INSTRUCTION_H
