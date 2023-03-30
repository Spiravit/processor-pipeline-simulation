#include <deque>

#include "InstructionNode.h"

/**
 * @brief
 * data structure to hold the instructions 
 * that have yet to be executed
*/
class InstructionQueue {
public:
    InstructionQueue();
    void push(InstructionNode* instructionNode);
    InstructionNode* pop();

private:
    std::deque<InstructionNode*> instructionQueue;
};

InstructionQueue::InstructionQueue() {
    instructionQueue = std::deque<InstructionNode*>();
}

/**
 * @brief
 * push to the queue
 * @param instructionNode
 * the instruction to be pushed to the start of the queue
*/
void InstructionQueue::push(InstructionNode* instructionNode) {
    instructionQueue.push_back(instructionNode);
}

/**
 * @brief
 * pop from the start of the queue
 * @return 
 * the popped instruction
*/
InstructionNode* InstructionQueue::pop() {
    InstructionNode* instructionNode = instructionQueue.front();
    instructionQueue.pop_front();
    return instructionNode;
}