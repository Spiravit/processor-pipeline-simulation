#include <deque>
#include <array>

#include "InstructionNode.h"

/**
 * @brief 
 * InstructionWindow is a class that represent the current instructions 
 * being executed by the CPU and what stages they are in
 */
class InstructionWindow {
public:
    InstructionWindow(int pipelineWidth);
    
    // methods to switch instructions between stages
    bool modeToIF(InstructionNode* instructionNode);
    bool moveIFtoID();
    bool moveIDtoEX();
    bool moveEXtoMEM();
    bool moveMEMtoWB();
    bool moveWBtoDONE();
private: 

    // 1st dimension is the stage (IF, ID, EX, MEM, WB)
    // 2nd dimension is the pipeline width
    std::array<std::deque<InstructionNode>, 5> instructionWindow;

    // variables used to determine if an incoming 
    // node must be denied an instruction switch
    bool usingIALU = false; // integer ALU
    bool usingFPU = false; // floating point unit
    bool usingBEU = false; // branch execution unit (probably not needed)
    bool usingCRP = false; // cache read(load) port 
    bool usingCWP = false; // cache write(store) port
    bool executingBranch = false; // if a branch is being executed 

    // instructionWindow indexes for each stage
    const int IF = 0; // instruction fetch
    const int ID = 1; // instruction decode
    const int EX = 2; // execute
    const int MEM = 3; // memory read(load) or write(store)
    const int WB = 4; // write back
};

InstructionWindow::InstructionWindow(int pipelineWidth) {
    instructionWindow = std::array<std::deque<InstructionNode>, 5>();

    for(int i = 0; i < 5; i++) {
        instructionWindow[i] = std::deque<InstructionNode>();
    }
}

/**
 * @brief
 * adds the given node to the instruction fetch stage
 * @param instructionNode
 * the node to be added
 * @return 
 * returns false if adding the node to the stage failed, true otherwise
*/
bool InstructionWindow::modeToIF(InstructionNode* instructionNode) {
    // if IF full (instructionWindow[IF].size() == pipelineWidth), return false
    // if executingBranch is true, return false

    // push given node to instructionWindow[IF]

    // if node is a branch, set executingBranch to true
    return false;
}

/**
 * @brief
 * removes the next node from the instruction fetch stage and 
 * adds it to the instruction decode stage
 * @return 
 * returns false if adding the node to the stage failed, true otherwise
*/
bool InstructionWindow::moveIFtoID() {
    // if IF empty, return false
    // if ID full, return false
    return false;
}

/**
 * @brief
 * removes the next node from the instruction decode stage and 
 * adds it to the execute stage
 * @return 
 * returns false if adding the node to the stage failed, true otherwise
*/
bool InstructionWindow::moveIDtoEX() {
    // if ID empty, return false
    // if EX full, return false

    // if usingIALU is true, return false
    // if usingFPU is true, return false

    // check node dependancies, if any havent finished EX stage then return

    // pop node from instructionWindow[ID] and push it to instructionWindow[EX]

    // set usingIALU true if instruction node is a integer type
    // set usingFPU true if instruction node is a float type
    return false;
}

/**
 * @brief
 * removes the next node from the execute stage and 
 * adds it to the memory read(store) or write(load) stage
 * @return 
 * returns false if adding the node to the stage failed, true otherwise
*/
bool InstructionWindow::moveEXtoMEM() {
    // if EX empty, return false
    // if MEM full, return false

    // set usingIALU, usingFPU, executingBranch false based on instruction node type

    // if load type node and usingCRP is true, return false
    // if store type node and usingCWP is true, return false

    // pop node from instructionWindow[EX] and push it to instructionWindow[MEM]

    // set usingCRP or usingCWP true based on whether the node is a load or store type
    return false;
}

/**
 * @brief
 * removes the next node from the read(store) or write(load) stage and 
 * adds it to the memory write back stage
 * @return 
 * returns false if adding the node to the stage failed, true otherwise
*/
bool InstructionWindow::moveMEMtoWB() {
    // if MEM empty, return false
    // if WB full, return false

    // pop node from instructionWindow[MEM] and push it to instructionWindow[WB]

    // set usingCRP or usingCWP false based on whether the node is a load or store type
    return false;
}

/**
 * @brief
 * removes the next node from the write back stage
 * @return 
 * returns false if adding the node to the stage failed, true otherwise
*/
bool InstructionWindow::moveWBtoDONE() {
    // if WB empty, return false
    return false;
}
