#include <deque>
#include <array>

#include "InstructionNode.h"
#include "InstructionHistory.h"

/**
 * @brief
 * InstructionWindow is a class that represent the current instructions
 * being executed by the CPU and what stages they are in
 */
class InstructionWindow
{
public:
    InstructionWindow(int pipelineWidth);

    // methods to switch instructions between stages
    bool moveToIF(InstructionNode *instructionNode);
    bool moveIFtoID();
    bool moveIDtoEX();
    bool moveEXtoMEM();
    bool moveMEMtoWB();
    bool moveWBtoDONE();

    bool isEmpty();

private:
    int pipelineWidth;
    // 1st dimension is the stage (IF, ID, EX, MEM, WB)
    // 2nd dimension is the pipeline width
    std::array<std::deque<InstructionNode *>, 5> instructionWindow;

    InstructionHistory *instructionHistory;

    // variables used to determine if an incoming
    // node must be denied an instruction switch
    bool usingIALU = false;       // integer ALU
    bool usingFPU = false;        // floating point unit
    bool usingBEU = false;        // branch execution unit (probably not needed)
    bool usingCRP = false;        // cache read(load) port
    bool usingCWP = false;        // cache write(store) port
    bool executingBranch = false; // if a branch is being executed

    // instructionWindow indexes for each stage
    const int IF = 0;  // instruction fetch
    const int ID = 1;  // instruction decode
    const int EX = 2;  // execute
    const int MEM = 3; // memory read(load) or write(store)
    const int WB = 4;  // write back
};

InstructionWindow::InstructionWindow(int pipelineWidth)
{
    this->pipelineWidth = pipelineWidth;
    instructionWindow = std::array<std::deque<InstructionNode *>, 5>();
    for (int i = 0; i < 5; i++)
    {
        instructionWindow[i] = std::deque<InstructionNode *>();
    }

    InstructionHistory *instructionHistory = new InstructionHistory();
}

/**
 * @brief
 * adds the given node to the instruction fetch stage
 * @param instructionNode
 * the node to be added
 * @return
 * returns false if adding the node to the stage failed, true otherwise
 */
bool InstructionWindow::moveToIF(InstructionNode *instructionNode)
{
    if (instructionWindow[IF].size() >= this->pipelineWidth || executingBranch)
    {
        return false;
    }

    // Push the given node to the IF stage
    instructionWindow[IF].push_back(instructionNode);

    // Add the instructionNode to the instruction history
    instructionHistory->insert(instructionNode);

    // If the node is a branch instruction, set executingBranch to true
    if (instructionNode->isBranch())
    {
        executingBranch = true;
    }

    return true;
}

/**
 * @brief
 * removes the next node from the instruction fetch stage and
 * adds it to the instruction decode stage
 * @return
 * returns false if adding the node to the stage failed, true otherwise
 */
bool InstructionWindow::moveIFtoID()
{
    // if IF empty, return false || // if ID full, return false
    if (instructionWindow[IF].empty() || instructionWindow[ID].size() >= this->pipelineWidth)
    {
        return false;
    }

    // pop node from instructionWindow[IF] and push it to instructionWindow[ID]
    instructionWindow[ID].push_back(instructionWindow[IF].front());
    instructionWindow[IF].pop_front();
    
    return true;
}

/**
 * @brief
 * removes the next node from the instruction decode stage and
 * adds it to the execute stage
 * @return
 * returns false if adding the node to the stage failed, true otherwise
 */
bool InstructionWindow::moveIDtoEX()
{
    // if ID empty, return false || if EX full, return false
    if (instructionWindow[ID].empty() || instructionWindow[EX].size() >= this->pipelineWidth)
    {
        return false;
    }

    // if usingIALU is true || usingFPU is true, return false
    if (usingIALU || usingFPU)
    {
        return false;
    }

    InstructionNode *instructionNode = instructionWindow[ID].front();

    for (const unsigned int dependency : instructionNode->dependencies)
    {
        if (!instructionHistory->isComplete(dependency))
        {
            return false;
        }
    }

    // pop node from instructionWindow[ID] and push it to instructionWindow[EX]
    instructionWindow[EX].push_back(instructionWindow[ID].front());
    instructionWindow[ID].pop_front();
    // set usingIALU true if instruction node is a integer type
    if (instructionNode->isInteger())
    {
        usingIALU = true;
    }
    // set usingFPU true if instruction node is a float type
    if (instructionNode->isFloat())
    {
        usingFPU = true;
    }
    return true;
}

/**
 * @brief
 * removes the next node from the execute stage and
 * adds it to the memory read(store)/write(load) stage
 * @return
 * returns false if adding the node to the stage failed, true otherwise
 */
bool InstructionWindow::moveEXtoMEM()
{
    // if EX empty or if MEM full, return false
    if (instructionWindow[EX].empty() || instructionWindow[MEM].size() >= this->pipelineWidth)
    {
        return false;
    }

    // set usingIALU, usingFPU, executingBranch false based on instruction node type
    InstructionNode *instructionNode = instructionWindow[EX].front();

    // Reset usingIALU, usingFPU, and executingBranch flags based on the instruction node type
    if (instructionNode->isInteger())
    {
        usingIALU = false;
    }
    else if (instructionNode->isFloat())
    {
        usingFPU = false;
    }
    else if (instructionNode->isBranch())
    {
        executingBranch = false;
    }

    // if load type node and usingCRP is true, return false
    if (instructionNode->isLoad() && usingCRP)
    {
        return false;
    }
    else if (instructionNode->isStore() && usingCWP)
    {
        return false;
    }

    // if store type node and usingCWP is true, return false
    if (instructionNode->isLoad())
    {
        usingCRP = true;
    }
    else if (instructionNode->isStore())
    {
        usingCWP = true;
    }
    // pop node from instructionWindow[EX] and push it to instructionWindow[MEM]
    instructionWindow[MEM].push_back(instructionWindow[EX].front());
    instructionWindow[EX].pop_front();
    // set usingCRP or usingCWP true based on whether the node is a load or store type
    return true;
}

/**
 * @brief
 * removes the next node from the read(store) or write(load) stage and
 * adds it to the memory write back stage
 * @return
 * returns false if adding the node to the stage failed, true otherwise
 */
bool InstructionWindow::moveMEMtoWB()
{
    // if MEM empty, || WB full return false
    if (instructionWindow[MEM].empty() || instructionWindow[WB].size() >= this->pipelineWidth)
    {
        return false;
    }

    // pop node from instructionWindow[MEM] and push it to instructionWindow[WB]
    instructionWindow[WB].push_back(instructionWindow[MEM].front());
    instructionWindow[MEM].pop_front();

    InstructionNode *instructionNode = instructionWindow[MEM].front();

    // Reset usingCRP or usingCWP flags based on whether the node is a load or store type
    if (instructionNode->isLoad())
    {
        usingCRP = false;
    }
    else if (instructionNode->isStore())
    {
        usingCWP = false;
    }

    return true;
}

/**
 * @brief
 * removes the next node from the write back stage
 * @return
 * returns false if removing the node from the stage failed, true otherwise
 */
bool InstructionWindow::moveWBtoDONE()
{
    // if WB empty, return false
    if (instructionWindow[WB].empty())
    {
        return false;
    }
    instructionWindow[WB].front()->completed = true;
    instructionWindow[WB].pop_front();
    return false;
}

bool InstructionWindow::isEmpty()
{
    return (instructionWindow[IF].empty() && instructionWindow[ID].empty() && instructionWindow[EX].empty() && instructionWindow[MEM].empty() && instructionWindow[WB].empty());
}