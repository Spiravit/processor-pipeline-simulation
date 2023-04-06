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
    void erase(InstructionNode* instructionNode);
    bool isComplete(const unsigned int PC);
    
private:
    std::map<unsigned int, InstructionNode*> instructionHistory;
};

InstructionHistory::InstructionHistory() {
    std::map<unsigned int, InstructionNode*> instructionHistory = std::map<unsigned int, InstructionNode*>();
}

InstructionHistory::~InstructionHistory() {
    for (std::map<unsigned int, InstructionNode*>::iterator it = instructionHistory.begin(); it != instructionHistory.end(); ++it) {
        delete it->second;
    }
}

/**
 * add a instruction to the history
*/
void InstructionHistory::insert(InstructionNode* instructionNode) {
    // pairs up the node and its key(PC)
    instructionHistory.insert(
        std::pair<unsigned int, InstructionNode*>(
            instructionNode->PC, 
            instructionNode
        )
    );
}

/**
 * remove and free a instruction from the history
*/
void InstructionHistory::erase(InstructionNode* instructionNode) {
    InstructionNode* node = instructionHistory.at(instructionNode->PC);
    instructionHistory.erase(instructionNode->PC);
    delete node;
}

/**
 * returns true/false if the instruction has completed and been retired
*/
bool InstructionHistory::isComplete(const unsigned int PC) {
    std::map<unsigned int, InstructionNode*>::iterator it = instructionHistory.find(PC);
    if (it != instructionHistory.end()) {
        // second is used to access the node out of the pair
        return it->second->completed;
    }
}

