<div align="center"><h1>Pipeline Processor</h1></div>
<div align="center"><h3>Trace Driven Simulation</h3></div>
<div align="center"><img src="https://user-images.githubusercontent.com/67299491/231928463-b122bf04-d97c-4601-97dd-7f2a96442346.png" width=300 height=300 style="vertical-align:middle"></div>


</br>




<pre><div align="center"><img style="margin-right: 5px;" src="https://img.shields.io/badge/c-++-blue"/> <img src="https://img.shields.io/badge/%20%20valgrind-white"/> <img src="https://img.shields.io/badge/%20%20Contributers-3-3"/> </pre> 



# Table of Content:
- [Trace files](#trace-files)
- [Tracking Dependencies](#tracking-dependencies)
- [Running the project](#running-the-project)
- [Results](#results)
- [Two factor analysis](#two-factor-analysis)





## Trace files
This simulator will consume a trace with the following format: Each line represents an instruction with comma separated values representing the following:

- Instruction program counter (PC): A hexadecimal value representing the instruction address.
- Instruction type: A value between 1 and 5:
        - Integer instruction: An instruction that uses the integer ALU
        - Floating point instruction: An instruction that uses the floating point unit
        - Branch: An instruction that transfers control to the next instruction in the trace.
        - Load: An instruction that reads a value from memory.
        - Store: An instruction that writes a value to memory.
- A list of PC values for instructions that the current instruction depends on. Some instructions don’t have any dependences, so this list will be empty. Other instructions depend on 1-4 other instructions. Note that PC values correspond to static instructions, and the trace could have multiple dynamic instructions with the same PC value. For dependences, an instruction is dependent on the last instance of the dynamic instruction with that PC value. 

## Tracking Dependencies

Each instruction can execute as long as its dependences are satisfied. The simulator tracks for each instruction that fall into the following three categories:

- Structural hazards: Another instruction in the same cycle is using the same functional unit. An integer instruction cannot execute in the same cycle as another integer instruction. A floating point instruction cannot execute in the same cycle as another floating point instruction. A branch instruction cannot execute in the same cycle as another branch instruction. A load instruction cannot go to the MEM stage in the same cycle as another load instruction. A store instruction cannot go to the MEM stage in the same cycle as another store instruction.
- Control hazards: A branch instruction halts instruction fetch until the cycle after the branch executes (finishes EX stage).
- Data hazards: An instruction cannot go to EX until all its data dependences are satisfied. A dependence on an integer or floating point instruction is satisfied after they finish the EX stage. A dependence on a load or store is satisfied after they finish the MEM stage.


## Running the project
- Clone the repo
- Open the project is VS code (or your favorite editor)
- Run make
- Run 
    ```./proj path_to_trace_file start_instruction_# instruction_count pipeline_width```



## Results 

![image](https://user-images.githubusercontent.com/67299491/231927630-68496272-8c21-4f8c-bff8-634a7c637832.png)


## Two factor analysis

![image](https://user-images.githubusercontent.com/67299491/231927733-4394e404-4e52-49bd-9b91-7caaec4e18f3.png)


![image](https://user-images.githubusercontent.com/67299491/231927764-b32512b2-a413-4f99-bb30-af5a669e1690.png)


![image](https://user-images.githubusercontent.com/67299491/231927783-58d16600-4f10-4087-b8f8-84bd66ff3a0d.png)


![image](https://user-images.githubusercontent.com/67299491/231927810-1ce5c09e-9251-4627-8e88-359e5a0e23ad.png)



