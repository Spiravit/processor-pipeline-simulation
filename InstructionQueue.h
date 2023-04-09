#include <deque>

#include "InstructionNode.h"

#ifndef INSTRUCTIONQUEUE_H
#define INSTRUCTIONQUEUE_H

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
    InstructionNode* front();

    bool isEmpty();

    std::deque<InstructionNode*> getInstructionQueue();
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

/**
 * @brief
 * reference to the first node of queue
 * @return 
 * the popped instruction
*/
InstructionNode* InstructionQueue::front() {
    InstructionNode* instructionNode = instructionQueue.front();
    return instructionNode;
}



/**
 * @brief
 * only really here for the print method in the FileReader class
 * and it should not be used anywhere else
 * @return 
 * the instruction queue (well its really a deque)
*/
std::deque<InstructionNode*> InstructionQueue::getInstructionQueue() {
    return instructionQueue;
}


/**
 * @brief
 * check if there is instruction
 * @return 
 * returns true if the queue is empty
*/
bool InstructionQueue::isEmpty() {
    return instructionQueue.empty();
}


#endif
