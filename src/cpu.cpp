#include "cpu.h"
#include <iostream>
#include <iomanip>

// Constructor
CPUSimulator::CPUSimulator(int memorySize) : 
    memory(memorySize, 0), 
    programCounter(0), 
    running(false),
    zeroFlag(false),
    carryFlag(false) {
    
    // Initialize registers
    registers["AX"] = 0;
    registers["BX"] = 0;
    registers["CX"] = 0;
    registers["DX"] = 0;
    registers["SP"] = memorySize - 1; // Stack pointer
}

// Load program into memory
void CPUSimulator::loadProgram(const std::vector<int>& program) {
    for (size_t i = 0; i < program.size() && i < memory.size(); ++i) {
        memory[i] = program[i];
    }
    programCounter = 0;
    running = true;
}

// Execute single instruction
void CPUSimulator::executeInstruction() {
    if (!running || programCounter >= memory.size()) {
        running = false;
        return;
    }
    
    int opcode = memory[programCounter];
    
    switch (opcode) {
        case LOAD: {
            std::string reg = getRegisterName(memory[programCounter + 1]);
            int value = memory[programCounter + 2];
            registers[reg] = value;
            programCounter += 3;
            std::cout << "LOAD " << reg << ", " << value << std::endl;
            break;
        }
        
        case STORE: {
            std::string reg = getRegisterName(memory[programCounter + 1]);
            int addr = memory[programCounter + 2];
            if (addr < memory.size()) {
                memory[addr] = registers[reg];
            }
            programCounter += 3;
            std::cout << "STORE " << reg << ", [" << addr << "]" << std::endl;
            break;
        }
        
        case ADD: {
            std::string reg1 = getRegisterName(memory[programCounter + 1]);
            std::string reg2 = getRegisterName(memory[programCounter + 2]);
            int result = registers[reg1] + registers[reg2];
            registers[reg1] = result;
            updateFlags(result);
            programCounter += 3;
            std::cout << "ADD " << reg1 << ", " << reg2 << std::endl;
            break;
        }
        
        case SUB: {
            std::string reg1 = getRegisterName(memory[programCounter + 1]);
            std::string reg2 = getRegisterName(memory[programCounter + 2]);
            int result = registers[reg1] - registers[reg2];
            registers[reg1] = result;
            updateFlags(result);
            programCounter += 3;
            std::cout << "SUB " << reg1 << ", " << reg2 << std::endl;
            break;
        }
        
        case MUL: {
            std::string reg1 = getRegisterName(memory[programCounter + 1]);
            std::string reg2 = getRegisterName(memory[programCounter + 2]);
            int result = registers[reg1] * registers[reg2];
            registers[reg1] = result;
            updateFlags(result);
            programCounter += 3;
            std::cout << "MUL " << reg1 << ", " << reg2 << std::endl;
            break;
        }
        
        case DIV: {
            std::string reg1 = getRegisterName(memory[programCounter + 1]);
            std::string reg2 = getRegisterName(memory[programCounter + 2]);
            if (registers[reg2] != 0) {
                int result = registers[reg1] / registers[reg2];
                registers[reg1] = result;
                updateFlags(result);
            } else {
                std::cout << "Division by zero error!" << std::endl;
                running = false;
            }
            programCounter += 3;
            std::cout << "DIV " << reg1 << ", " << reg2 << std::endl;
            break;
        }
        
        case JMP: {
            int addr = memory[programCounter + 1];
            programCounter = addr;
            std::cout << "JMP " << addr << std::endl;
            break;
        }
        
        case JEQ: {
            std::string reg1 = getRegisterName(memory[programCounter + 1]);
            std::string reg2 = getRegisterName(memory[programCounter + 2]);
            int addr = memory[programCounter + 3];
            if (registers[reg1] == registers[reg2]) {
                programCounter = addr;
            } else {
                programCounter += 4;
            }
            std::cout << "JEQ " << reg1 << ", " << reg2 << ", " << addr << std::endl;
            break;
        }
        
        case JNE: {
            std::string reg1 = getRegisterName(memory[programCounter + 1]);
            std::string reg2 = getRegisterName(memory[programCounter + 2]);
            int addr = memory[programCounter + 3];
            if (registers[reg1] != registers[reg2]) {
                programCounter = addr;
            } else {
                programCounter += 4;
            }
            std::cout << "JNE " << reg1 << ", " << reg2 << ", " << addr << std::endl;
            break;
        }
        
        case CMP: {
            std::string reg1 = getRegisterName(memory[programCounter + 1]);
            std::string reg2 = getRegisterName(memory[programCounter + 2]);
            int result = registers[reg1] - registers[reg2];
            updateFlags(result);
            programCounter += 3;
            std::cout << "CMP " << reg1 << ", " << reg2 << std::endl;
            break;
        }
        
        case PRINT: {
            std::string reg = getRegisterName(memory[programCounter + 1]);
            std::cout << "PRINT " << reg << ": " << registers[reg] << std::endl;
            programCounter += 2;
            break;
        }
        
        case HALT: {
            running = false;
            std::cout << "HALT - CPU stopped" << std::endl;
            break;
        }
        
        default: {
            std::cout << "Unknown instruction: " << opcode << std::endl;
            running = false;
            break;
        }
    }
}

// Run the CPU until halt or error
void CPUSimulator::run() {
    std::cout << "\n=== CPU Execution Started ===" << std::endl;
    while (running) {
        std::cout << "PC=" << programCounter << ": ";
        executeInstruction();
    }
    std::cout << "=== CPU Execution Finished ===" << std::endl;
}

// Step through one instruction
void CPUSimulator::step() {
    if (running) {
        std::cout << "PC=" << programCounter << ": ";
        executeInstruction();
    }
}

// Display CPU state
void CPUSimulator::displayState() {
    std::cout << "\n=== CPU State ===" << std::endl;
    std::cout << "Program Counter: " << programCounter << std::endl;
    std::cout << "Running: " << (running ? "Yes" : "No") << std::endl;
    std::cout << "Flags: Zero=" << zeroFlag << ", Carry=" << carryFlag << std::endl;
    
    std::cout << "\nRegisters:" << std::endl;
    for (const auto& reg : registers) {
        std::cout << "  " << reg.first << ": " << reg.second << std::endl;
    }
    
    std::cout << "\nMemory (first 20 locations):" << std::endl;
    for (int i = 0; i < 20 && i < memory.size(); ++i) {
        std::cout << "  [" << std::setw(2) << i << "]: " << memory[i] << std::endl;
    }
    std::cout << std::endl;
}

// Helper method to convert register codes to names
std::string CPUSimulator::getRegisterName(int regCode) {
    switch (regCode) {
        case 0: return "AX";
        case 1: return "BX";
        case 2: return "CX";
        case 3: return "DX";
        case 4: return "SP";
        default: return "AX";
    }
}

// Helper method to update CPU flags
void CPUSimulator::updateFlags(int result) {
    zeroFlag = (result == 0);
    carryFlag = (result > 65535 || result < -32768); // Simple carry detection
}

// Getter methods for testing/debugging
int CPUSimulator::getRegisterValue(const std::string& regName) const {
    auto it = registers.find(regName);
    return (it != registers.end()) ? it->second : 0;
}

int CPUSimulator::getMemoryValue(int address) const {
    return (address >= 0 && address < memory.size()) ? memory[address] : 0;
}

int CPUSimulator::getProgramCounter() const {
    return programCounter;
}

bool CPUSimulator::isRunning() const {
    return running;
}

bool CPUSimulator::getZeroFlag() const {
    return zeroFlag;
}

bool CPUSimulator::getCarryFlag() const {
    return carryFlag;
}