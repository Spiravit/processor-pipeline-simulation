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
    void erase(unsigned long long PC);
    bool isComplete(const unsigned long long PC);
    
private:
    std::map<unsigned long long, InstructionNode*> instructionHistory;
};

InstructionHistory::InstructionHistory() {
    std::map<unsigned long long, InstructionNode*> instructionHistory = std::map<unsigned long long, InstructionNode*>();
}

InstructionHistory::~InstructionHistory() {
    for (std::map<unsigned long long, InstructionNode*>::iterator it = instructionHistory.begin(); it != instructionHistory.end(); ++it) {
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
        std::pair<unsigned long long, InstructionNode*>(
            instructionNode->PC,
            instructionNode
        )
    );
}

/**
 * remove and free a instruction from the history
*/
void InstructionHistory::erase(unsigned long long PC) {
    std::map<unsigned long long, InstructionNode*>::iterator it = instructionHistory.find(PC);

    if (it != instructionHistory.end()) { // if the instruction exists 
        instructionHistory.erase(it);
        //delete it->second;
        // TODO: fix this delete statement, it causes a crash
    }
}

/**
 * returns true/false if the instruction has completed and been retired
*/
bool InstructionHistory::isComplete(const unsigned long long PC) {
    std::map<unsigned long long, InstructionNode*>::iterator it = instructionHistory.find(PC);

    if (it != instructionHistory.end()) { // if the instruction exists
        // second is used to access the node out of the pair
        return it->second->completed;
    }
    
    return true; // ignore dependencies if instruction does not exist
}