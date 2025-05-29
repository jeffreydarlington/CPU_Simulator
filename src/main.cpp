#include "./cpu.h"
#include <iostream>
// Example program: Calculate factorial of 5
std::vector<int> createFactorialProgram() {
    return {
        // Load 5 into AX (number to calculate factorial)
        1, 0, 5,        // LOAD AX, 5
        
        // Load 1 into BX (result accumulator)
        1, 1, 1,        // LOAD BX, 1
        
        // Load 1 into CX (decrement value)
        1, 2, 1,        // LOAD CX, 1
        
        // Loop start (address 9)
        // Multiply BX by AX
        5, 1, 0,        // MUL BX, AX
        
        // Subtract 1 from AX
        4, 0, 2,        // SUB AX, CX
        
        // Compare AX with CX
        10, 0, 2,       // CMP AX, CX (comparing with 1, since we want to stop when AX becomes 1)
        
        // Jump if not equal to loop start
        9, 0, 2, 9,     // JNE AX, CX, 9
        
        // Print result
        11, 1,          // PRINT BX
        
        // Halt
        12              // HALT
    };
}

// Example program: Simple arithmetic
std::vector<int> createArithmeticProgram() {
    return {
        // Load 10 into AX
        1, 0, 10,       // LOAD AX, 10
        
        // Load 5 into BX
        1, 1, 5,        // LOAD BX, 5
        
        // Add BX to AX
        3, 0, 1,        // ADD AX, BX
        
        // Print result (should be 15)
        11, 0,          // PRINT AX
        
        // Subtract BX from AX
        4, 0, 1,        // SUB AX, BX
        
        // Print result (should be 10)
        11, 0,          // PRINT AX
        
        // Multiply AX by BX
        5, 0, 1,        // MUL AX, BX
        
        // Print result (should be 50)
        11, 0,          // PRINT AX
        
        // Halt
        12              // HALT
    };
}

// Example program: Simple loop (count from 1 to 5)
std::vector<int> createCountingProgram() {
    return {
        // Load 1 into AX (counter)
        1, 0, 1,        // LOAD AX, 1
        
        // Load 5 into BX (limit)
        1, 1, 5,        // LOAD BX, 5
        
        // Load 1 into CX (increment)
        1, 2, 1,        // LOAD CX, 1
        
        // Loop start (address 9)
        // Print current counter
        11, 0,          // PRINT AX
        
        // Add 1 to counter
        3, 0, 2,        // ADD AX, CX
        
        // Compare counter with limit
        10, 0, 1,       // CMP AX, BX
        
        // Jump if not equal to loop start
        9, 0, 1, 9,     // JNE AX, BX, 9
        
        // Print final value
        11, 0,          // PRINT AX
        
        // Halt
        12              // HALT
    };
}

void printMenu(){
    std::cout << "\n=== CPU Simulator Menu ===" << std::endl;
    std::cout << "1. Run Arithmetic Program" << std::endl;
    std::cout << "2. Run Factorial Program (5!)" << std::endl;
    std::cout << "3. Run Counting Program (1 to 5)" << std::endl;
    std::cout << "4. Step-by-step Execution Demo" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice (1-5): ";
}

void runStepByStepDemo(){
    std::cout << "\n=== Step-by-step Execution Demo ===" << std::endl;
    std::cout << "Program: LOAD AX, 42; PRINT AX; HALT" << std::endl;

    CPUSimulator cpu(1024);
    std::vector<int> simpleProg = {1, 0, 42, 11, 0, 12};
    cpu.loadProgram(simpleProg);

    std::cout << "\nInitial state:" << std::endl;
    cpu.displayState();

    std::cout << "\nPress Enter to execute each step..." << std::endl;
    std::cin.ignore();

    int stepCount = 1;
    while(cpu.isRunning()){
        std::cout << "\n--- Step " << stepCount++ << " ---" << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get();

        cpu.step();

        std::cout << "Register AX: " << cpu.getRegisterValue("AX") << std::endl;
        std::cout << "Program Counter: " << cpu.getProgramCounter() << std::endl;
        std::cout << "CPU Running: " << (cpu.isRunning() ? "Yes" : "No") << std::endl;
    }
    
    std::cout << "\nFinal state" << std::endl;
    cpu.displayState();
}

int main(){
    std::cout << "CPU Simulator" << std::endl;
    std::cout << "=============" << std::endl;
    std::cout << "A virtual CPU that can execute simple assembly-like programs." << std::endl;

    int choice;
    do
    {
        printMenu();
        std::cin >> choice;

        switch(choice){
            case 1:{
                std::cout << "\n--- Running Arithmetic Program ---" << std::endl;
                CPUSimulator cpu(1024);
                auto prog = createArithmeticProgram();
                cpu.loadProgram(prog);
                cpu.displayState();
                cpu.run();
                cpu.displayState();
                break;
            }
            case 2: {
                std::cout << "\n--- Running Factorial Program (5!) ---" << std::endl;
                CPUSimulator cpu(1024);
                auto prog = createFactorialProgram();
                cpu.loadProgram(prog);
                cpu.displayState();
                cpu.run();
                cpu.displayState();
                break;
            }
            
            case 3: {
                std::cout << "\n--- Running Counting Program (1 to 5) ---" << std::endl;
                CPUSimulator cpu(1024);
                auto prog = createCountingProgram();
                cpu.loadProgram(prog);
                cpu.displayState();
                cpu.run();
                cpu.displayState();
                break;
            }
            
            case 4: {
                runStepByStepDemo();
                break;
            }
            
            case 5: {
                std::cout << "Exiting CPU Simulator. Goodbye!" << std::endl;
                break;
            }
            
            default: {
                std::cout << "Invalid choice. Please enter 1-5." << std::endl;
                break;
            }
        }
    } while (choice != 5);
    
    return 0;
}