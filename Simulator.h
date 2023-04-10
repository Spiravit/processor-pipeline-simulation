#include "InstructionQueue.h"
#include "InstructionWindow.h"
#include "InstructionNode.h"


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
    InstructionNode* instructionNode = instructionQueue->front();

    while (!instructionQueue->isEmpty() || !instructionWindow->isEmpty()) {
        
        while (instructionWindow->moveWBtoDONE()) {}
        while (instructionWindow->moveMEMtoWB()) {}
        while (instructionWindow->moveEXtoMEM()) {}
        while (instructionWindow->moveIDtoEX()) {}
        while (instructionWindow->moveIFtoID()) {} 
        while (instructionNode != nullptr && instructionWindow->moveToIF(instructionNode)) {
            instructionQueue->pop();
            switch (instructionNode->instructionType) {
                case InstructionType::INTEGER:
                    integerCount++;
                    break;
                case InstructionType::FLOATING_POINT:
                    floatingPointCount++;
                    break;
                case InstructionType::BRANCH:
                    branchCount++;
                    break;
                case InstructionType::LOAD:
                    loadCount++;
                    break;
                case InstructionType::STORE:
                    storeCount++;
                    break;
                default :
                    throw "Invalid Instruction Type in Simulator::start()";

            }
            
            instructionNode = instructionQueue->front();
        }

        instructionCycleCount++;
        //instructionWindow->print(instructionCycleCount);
    }


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
    std::cout << "Integer Instructions: " << ((double)integerCount / (double)total) * 100 << "%" << std::endl;
    std::cout << "Floating Point Instructions: " << ((double)floatingPointCount / (double)total) * 100 << "%" << std::endl;
    std::cout << "Branch Instructions: " << ((double)branchCount / (double)total) * 100 << "%" << std::endl;
    std::cout << "Load Instructions: " << ((double)loadCount / (double)total) * 100 << "%" << std::endl;
    std::cout << "Store Instructions: " << ((double)storeCount / (double)total) * 100 << "%" << std::endl;
    std::cout << "Total Cycles: " << instructionCycleCount  << std::endl;
}
