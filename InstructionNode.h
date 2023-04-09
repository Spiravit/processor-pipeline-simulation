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

enum class InstructionType
{
    INTEGER,
    FLOATING_POINT,
    BRANCH,
    LOAD,
    STORE
};

enum class InstructionState
{
    FETCHED,
    DECODED,
    EXECUTING,
    MEMORY_ACCESS,
    COMPLETED
};

class InstructionNode {
 public:
    unsigned int PC;
    int type;
    std::vector<unsigned int> dependencies;
    bool completed; // added this var so i dont think we need the instruction state class anymore
    InstructionType getType();

    InstructionNode(unsigned int PC, int type, const std::vector<unsigned int>& dependencies)
        : PC(PC), type(type), dependencies(dependencies) {}
};


InstructionType InstructionNode::getType() {
    switch (type) {
        case 0:
            return InstructionType::INTEGER;
        case 1:
            return InstructionType::FLOATING_POINT;
        case 2:
            return InstructionType::BRANCH;
        case 3:
            return InstructionType::LOAD;
        case 4:
            return InstructionType::STORE;
        default:
            throw std::invalid_argument("Invalid instruction type");
    }
}
#endif // INSTRUCTION_H
