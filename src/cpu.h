#ifndef CPU_SIMULATOR_H
#define CPU_SIMULATOR_H

#include <vector>
#include <map>
#include <string>

class CPUSimulator {
private:
    // CPU Components
    std::vector<int> memory;        // Main memory
    std::map<std::string, int> registers; // CPU registers
    int programCounter;             // Program counter
    bool running;                   // CPU running state
    
    // Instruction opcodes
    enum OpCode {
        LOAD = 1,    // LOAD reg, value
        STORE = 2,   // STORE reg, addr
        ADD = 3,     // ADD reg1, reg2
        SUB = 4,     // SUB reg1, reg2
        MUL = 5,     // MUL reg1, reg2
        DIV = 6,     // DIV reg1, reg2
        JMP = 7,     // JMP addr
        JEQ = 8,     // JEQ reg1, reg2, addr
        JNE = 9,     // JNE reg1, reg2, addr
        CMP = 10,    // CMP reg1, reg2
        PRINT = 11,  // PRINT reg
        HALT = 12    // HALT
    };
    
    // Flags
    bool zeroFlag;
    bool carryFlag;
    
    // Helper methods
    std::string getRegisterName(int regCode);
    void updateFlags(int result);
    
public:
    // Constructor
    CPUSimulator(int memorySize = 1024);
    
    // Core methods
    void loadProgram(const std::vector<int>& program);
    void executeInstruction();
    void run();
    void step();
    void displayState();
    
    // Getters for testing/debugging
    int getRegisterValue(const std::string& regName) const;
    int getMemoryValue(int address) const;
    int getProgramCounter() const;
    bool isRunning() const;
    bool getZeroFlag() const;
    bool getCarryFlag() const;
};

#endif // CPU_SIMULATOR_H