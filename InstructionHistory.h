#include <map>
#include <string>
#include "InstructionNode.h"

/**
 * @brief 
 * stores all instructions both executed and not executed
 * used to verify if instruction dependancies are met
*/
class InstructionHistory {
public:
    InstructionHistory();
    ~InstructionHistory();

    void add(InstructionNode* instructionNode);
    bool nodeFinished(InstructionNode* instructionNode);
    
private:
    // std::map<!place key here!, InstructionNode> instructionHistory;
};

InstructionHistory::InstructionHistory() {
    // initialize instruction map
    // std::map<!place key here!, InstructionNode> instructionHistory = new std::map<!place key here!, InstructionNode>();
}

InstructionHistory::~InstructionHistory() {
    // delete all instruction nodes
}

/**
 * add a instruction to the history
*/
void InstructionHistory::add(InstructionNode* instructionNode) {
    // add instruction to map using instructionID as key
}

/**
 * check if instruction has been executed
*/
bool InstructionHistory::nodeFinished(InstructionNode* instructionNode) {
    // check if instruction has been executed
    //
    // return true if executed
    // return false if not executed
    // if instruction is not in map, throw an error????
}

