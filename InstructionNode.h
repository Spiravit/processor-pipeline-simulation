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

class InstructionNode
{
public:
    unsigned int PC;
    int type;                        // int instruction type : 0 = integer, 1 = float, 2 = branch, 3 = load, 4 = store
    InstructionType instructionType; // Enum instruction type (integer, float, branch, load, store)
    std::vector<unsigned int> dependencies;
    bool completed; // added this var so i dont think we need the instruction state class anymore

    InstructionNode(unsigned int PC, int type, const std::vector<unsigned int> &dependencies)
        : PC(PC), type(type), dependencies(dependencies)
    {
        instructionType = toInstructionType(type);
    }

    InstructionType toInstructionType(int type)
    {
        switch (type)
        {
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
            return InstructionType::INTEGER;
        }
    }

    bool isInteger()
    {
        return instructionType == InstructionType::INTEGER;
    }

    bool isFloat()
    {
        return instructionType == InstructionType::FLOATING_POINT;
    }

    bool isBranch()
    {
        return instructionType == InstructionType::BRANCH;
    }

    bool isLoad()
    {
        return instructionType == InstructionType::LOAD;
    }

    bool isStore()
    {
        return instructionType == InstructionType::STORE;
    }
};

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

#endif // INSTRUCTION_H
