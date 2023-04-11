#include <map>
#include <string>
#include <utility>
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

    void insert(InstructionNode* instructionNode);
    void erase(std::string PC);
    bool isComplete(const std::string PC);
    
private:
    std::map<std::string, InstructionNode*> instructionHistory;
};

InstructionHistory::InstructionHistory() {
    std::map<std::string, InstructionNode*> instructionHistory = std::map<std::string, InstructionNode*>();
}

InstructionHistory::~InstructionHistory() {
    for (std::map<std::string, InstructionNode*>::iterator it = instructionHistory.begin(); it != instructionHistory.end(); ++it) {
        delete it->second;
    }
}

/**
 * add a instruction to the history
*/
void InstructionHistory::insert(InstructionNode* instructionNode) {
    // erase the instruction if it already exists
    erase(instructionNode->PC);

    // pairs up the node and its key(PC)
    instructionHistory.insert(
        std::pair<std::string, InstructionNode*>(
            instructionNode->PC,
            instructionNode
        )
    );
}

/**
 * remove and free a instruction from the history
*/
void InstructionHistory::erase(std::string PC) {
    std::map<std::string, InstructionNode*>::iterator it = instructionHistory.find(PC);

    if (it != instructionHistory.end()) { // if the instruction exists 
        delete it->second;
        instructionHistory.erase(it);
    }
}

/**
 * returns true/false if the instruction has completed and been retired
*/
bool InstructionHistory::isComplete(const std::string PC) {
    std::map<std::string, InstructionNode*>::iterator it = instructionHistory.find(PC);

    if (it != instructionHistory.end()) { // if the instruction exists
        // second is used to access the node out of the pair
        return it->second->completed;
    }
    
    return true; // ignore dependencies if instruction does not exist
}