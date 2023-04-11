#include "InstructionQueue.h"
#include "InstructionWindow.h"
#include "InstructionNode.h"


class Simulator {
public:
    Simulator(InstructionQueue* instructionQueue, int pipelineWidth);
    ~Simulator();

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

Simulator::~Simulator() {
    delete instructionWindow;
}

void Simulator::start() {
    InstructionNode* instructionNode = nullptr;
    if (!instructionQueue->isEmpty()) {
        instructionNode = instructionQueue->front();
    }

    while (!instructionQueue->isEmpty() || !instructionWindow->isEmpty()) {
        // move instructions through the pipeline
        // call moveWBtoDONE() until it returns false
        while (instructionWindow->moveWBtoDONE()) {}
        // call moveMEMtoWB() until it returns false
        while (instructionWindow->moveMEMtoWB()) {}
        // call moveEXtoMEM() until it returns false
        while (instructionWindow->moveEXtoMEM()) {}
        // call moveIDtoEX() until it returns false
        while (instructionWindow->moveIDtoEX()) {}
        // call moveIFtoID() until it returns false
        while (instructionWindow->moveIFtoID()) {} 
        // call moveToIF() until it returns false or the instructionQueue is empty
        while (instructionNode != nullptr && instructionWindow->moveToIF(instructionNode)) {
            instructionQueue->pop();
            
            // increment instruction type count
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
