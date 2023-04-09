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
    
    InstructionNode* instructionNode = instructionQueue->front();

    while (!instructionQueue->isEmpty() || !instructionWindow->isEmpty()) {
        while (instructionWindow->moveWBtoDONE()) {
            //do something
        }
        while (instructionWindow->moveMEMtoWB()) {
            //do something
        }
        while (instructionWindow->moveEXtoMEM()) {
            //do something
        }
        while (instructionWindow->moveIDtoEX()) {
            //do something
        }
        while (instructionWindow->moveIFtoID()) {
            //do something
        } 
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
