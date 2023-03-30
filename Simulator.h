class Simulator {
public:
    Simulator(params?);
    void start();
};

void Simulator::start() {
    // repeat until InstuctionQueue and InstructionWindow are empty
        // call moveWBtoDONE() in a while loop until it returns false
        // call moveMEMtoWB() in a while loop until it returns false
        // call moveEXtoMEM() in a while loop until it returns false
        // call moveIDtoEX() in a while loop until it returns false
        // call moveIFtoID() in a while loop until it returns false
        // call modeToIF(InstructionNode* instructionNode) in a while loop until it returns false or until InstructionQueue is empty
            // if true is returned, pop node from InstructionQueue
}