#include "InstructionQueue.h"

class Simulator {
public:
    Simulator(InstructionQueue* instructionQueue);
    void start();

private:
    void printResults();

    InstructionQueue* instructionQueue;

    unsigned int instructionCycleCount = 0;
    // instruction type counts
    unsigned int integerCount = 0;
    unsigned int floatingPointCount = 0;
    unsigned int branchCount = 0;
    unsigned int loadCount = 0;
    unsigned int storeCount = 0;
};

Simulator::Simulator(InstructionQueue* instructionQueue) {
    this->instructionQueue = instructionQueue;
}

void Simulator::start() {
    // repeat until InstuctionQueue and InstructionWindow are empty
        // call moveWBtoDONE() in a while loop until it returns false
        // call moveMEMtoWB() in a while loop until it returns false
        // call moveEXtoMEM() in a while loop until it returns false
        // call moveIDtoEX() in a while loop until it returns false
        // call moveIFtoID() in a while loop until it returns false
        // call modeToIF(InstructionNode* instructionNode) in a while loop until it returns false or until InstructionQueue is empty
            // if true is returned, pop node from InstructionQueue
            // increment count of instruction type
        // increment instructionCycleCount 
    
    // print results at the end of the simulation 
    printResults();
}

void Simulator::printResults() {
    unsigned int total = integerCount + floatingPointCount + branchCount + loadCount + storeCount;

    if (total == 0) {
        std::cout << "No instructions were executed" << std::endl;
        return;
    }

    std::cout << "Total Instructions: " << total << std::endl;
    std::cout << "Integer Instructions: " << (integerCount / total) * 100 << std::endl;
    std::cout << "Floating Point Instructions: " << (floatingPointCount / total) * 100 << "%" << std::endl;
    std::cout << "Branch Instructions: " << (branchCount / total) * 100 << "%" << std::endl;
    std::cout << "Load Instructions: " << (loadCount / total) * 100 << "%" << std::endl;
    std::cout << "Store Instructions: " << (storeCount / total) * 100 << "%" << std::endl;
    std::cout << "Total Cycles: " << instructionCycleCount << "%" << std::endl;
}