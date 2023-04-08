#include "InstructionQueue.h"
#include "InstructionWindow.h"

class Simulator {
public:
    Simulator(InstructionQueue* instructionQueue, int pipelineWidth);
    void start();

private:
    void printResults();

    InstructionQueue* instructionQueue;
    InstructionWindow* instructionWindow;

    unsigned int instructionCycleCount = 0;
    
    // instruction type counts
    unsigned int integerCount = 0;
    unsigned int floatingPointCount = 0;
    unsigned int branchCount = 0;
    unsigned int loadCount = 0;
    unsigned int storeCount = 0;
};

Simulator::Simulator(InstructionQueue* instructionQueue, int pipelineWidth) {
    this->instructionQueue = instructionQueue;
    this->instructionWindow = new InstructionWindow(pipelineWidth);
}

void Simulator::start() {
    // repeat until InstuctionQueue and InstructionWindow are empty
        // call instructionWindow.moveWBtoDONE() in a while loop until it returns false
        // call instructionWindow.moveMEMtoWB() in a while loop until it returns false
        // call instructionWindow.moveEXtoMEM() in a while loop until it returns false
        // call instructionWindow.moveIDtoEX() in a while loop until it returns false
        // call instructionWindow.moveIFtoID() in a while loop until it returns false
        // call instructionWindow.modeToIF(InstructionNode* instructionNode) in a while loop until it returns false or until InstructionQueue is empty
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