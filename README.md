# CPU_Simulator
# CPU Simulator

A virtual CPU simulator written in C++ that can execute simple assembly-like programs. This educational tool demonstrates fundamental CPU concepts including instruction execution, register management, memory operations, and program flow control.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Instruction Set](#instruction-set)
- [Getting Started](#getting-started)
- [Example Programs](#example-programs)
- [Code Structure](#code-structure)
- [Usage Examples](#usage-examples)
- [Technical Details](#technical-details)
- [Compilation](#compilation)
- [Contributing](#contributing)

## Overview

The CPU Simulator emulates a simple processor with:
- 5 general-purpose registers (AX, BX, CX, DX, SP)
- Configurable memory size (default: 1024 words)
- 12 instruction types covering arithmetic, logic, memory, and control flow
- Flag system for conditional operations
- Interactive execution modes (run all, step-by-step)

## Features

- **Complete Instruction Set**: Arithmetic, memory operations, jumps, and comparisons
- **Register Management**: Five 32-bit registers with stack pointer support
- **Memory System**: Linear memory model with bounds checking
- **Flag System**: Zero and carry flags for conditional operations
- **Interactive Execution**: Run programs continuously or step through instruction by instruction
- **Debug Information**: Real-time display of CPU state, registers, and memory
- **Example Programs**: Pre-built programs demonstrating various concepts

## Architecture

### CPU Components

```
┌─────────────────┐
│    Registers    │
│  AX, BX, CX,    │
│  DX, SP         │
├─────────────────┤
│  Program        │
│  Counter (PC)   │
├─────────────────┤
│    Flags        │
│  Zero, Carry    │
├─────────────────┤
│    Memory       │
│  (1024 words)   │
└─────────────────┘
```

### Registers

| Register | Purpose | Initial Value |
|----------|---------|---------------|
| AX | General purpose accumulator | 0 |
| BX | General purpose base | 0 |
| CX | General purpose counter | 0 |
| DX | General purpose data | 0 |
| SP | Stack pointer | Memory size - 1 |

### Memory Layout

- **Program Area**: Instructions loaded starting at address 0
- **Data Area**: Available for variable storage
- **Stack Area**: Grows downward from high memory addresses

## Instruction Set

The CPU supports 12 instruction types:

### Data Movement
- **LOAD reg, value**: Load immediate value into register
- **STORE reg, addr**: Store register value to memory address

### Arithmetic Operations
- **ADD reg1, reg2**: Add reg2 to reg1, store result in reg1
- **SUB reg1, reg2**: Subtract reg2 from reg1, store result in reg1
- **MUL reg1, reg2**: Multiply reg1 by reg2, store result in reg1
- **DIV reg1, reg2**: Divide reg1 by reg2, store result in reg1

### Control Flow
- **JMP addr**: Unconditional jump to address
- **JEQ reg1, reg2, addr**: Jump to address if reg1 equals reg2
- **JNE reg1, reg2, addr**: Jump to address if reg1 not equals reg2

### Comparison and I/O
- **CMP reg1, reg2**: Compare registers and set flags
- **PRINT reg**: Display register value
- **HALT**: Stop CPU execution

### Instruction Encoding

Instructions are encoded as sequences of integers:
- **Opcode**: First integer identifies the instruction type
- **Operands**: Following integers specify registers and values

Example:
```
LOAD AX, 42  →  [1, 0, 42]
ADD AX, BX   →  [3, 0, 1]
JEQ AX, BX, 10 → [8, 0, 1, 10]
```

### Register Encoding
- AX = 0, BX = 1, CX = 2, DX = 3, SP = 4

## Getting Started

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- Standard C++ library support

### Quick Start

1. **Clone or download the source files**:
   - `cpu.h` - Header file with class declaration
   - `cpu.cpp` - Implementation file
   - `main.cpp` - Main program with examples

2. **Compile the program**:
   ```bash
   g++ -o cpu_simulator main.cpp cpu.cpp
   ```

3. **Run the simulator**:
   ```bash
   ./cpu_simulator
   ```

4. **Choose from the menu options**:
   - Arithmetic demonstration
   - Factorial calculation
   - Counting loop
   - Step-by-step execution

## Example Programs

### 1. Arithmetic Program

Demonstrates basic arithmetic operations:

```cpp
std::vector<int> createArithmeticProgram() {
    return {
        1, 0, 10,       // LOAD AX, 10
        1, 1, 5,        // LOAD BX, 5
        3, 0, 1,        // ADD AX, BX      (AX = 15)
        11, 0,          // PRINT AX
        4, 0, 1,        // SUB AX, BX      (AX = 10)
        11, 0,          // PRINT AX
        5, 0, 1,        // MUL AX, BX      (AX = 50)
        11, 0,          // PRINT AX
        12              // HALT
    };
}
```

**Output**: 15, 10, 50

### 2. Factorial Program

Calculates 5! using a loop:

```cpp
std::vector<int> createFactorialProgram() {
    return {
        1, 0, 5,        // LOAD AX, 5      (number)
        1, 1, 1,        // LOAD BX, 1      (result)
        1, 2, 1,        // LOAD CX, 1      (decrement)
        // Loop start (address 9)
        5, 1, 0,        // MUL BX, AX      (BX *= AX)
        4, 0, 2,        // SUB AX, CX      (AX--)
        10, 0, 2,       // CMP AX, CX      (compare with 1)
        9, 0, 2, 9,     // JNE AX, CX, 9   (loop if AX != 1)
        11, 1,          // PRINT BX        (result)
        12              // HALT
    };
}
```

**Output**: 120 (5! = 5 × 4 × 3 × 2 × 1)

### 3. Counting Program

Counts from 1 to 5:

```cpp
std::vector<int> createCountingProgram() {
    return {
        1, 0, 1,        // LOAD AX, 1      (counter)
        1, 1, 5,        // LOAD BX, 5      (limit)
        1, 2, 1,        // LOAD CX, 1      (increment)
        // Loop start (address 9)
        11, 0,          // PRINT AX
        3, 0, 2,        // ADD AX, CX      (counter++)
        10, 0, 1,       // CMP AX, BX      (compare with limit)
        9, 0, 1, 9,     // JNE AX, BX, 9   (loop if not equal)
        11, 0,          // PRINT AX        (final value)
        12              // HALT
    };
}
```

**Output**: 1, 2, 3, 4, 5, 6

## Code Structure

### Class: CPUSimulator

#### Private Members
- `std::vector<int> memory`: Main memory storage
- `std::map<std::string, int> registers`: CPU registers
- `int programCounter`: Current instruction address
- `bool running`: CPU execution state
- `bool zeroFlag, carryFlag`: Condition flags

#### Public Methods

**Core Operations**:
- `CPUSimulator(int memorySize)`: Constructor
- `void loadProgram(const std::vector<int>& program)`: Load program into memory
- `void executeInstruction()`: Execute current instruction
- `void run()`: Execute until HALT or error
- `void step()`: Execute single instruction

**State Inspection**:
- `void displayState()`: Show complete CPU state
- `int getRegisterValue(const std::string& regName)`: Get register value
- `int getMemoryValue(int address)`: Get memory value
- `int getProgramCounter()`: Get current PC value
- `bool isRunning()`: Check if CPU is running

#### Private Helper Methods
- `std::string getRegisterName(int regCode)`: Convert register code to name
- `void updateFlags(int result)`: Update zero and carry flags

## Usage Examples

### Basic Usage

```cpp
#include "cpu.h"

int main() {
    // Create CPU with 1024 words of memory
    CPUSimulator cpu(1024);
    
    // Create a simple program
    std::vector<int> program = {
        1, 0, 42,    // LOAD AX, 42
        11, 0,       // PRINT AX
        12           // HALT
    };
    
    // Load and run program
    cpu.loadProgram(program);
    cpu.run();
    
    return 0;
}
```

### Step-by-Step Execution

```cpp
CPUSimulator cpu(1024);
cpu.loadProgram(program);

// Execute one instruction at a time
while (cpu.isRunning()) {
    std::cout << "Before: PC=" << cpu.getProgramCounter() << std::endl;
    cpu.step();
    std::cout << "After: AX=" << cpu.getRegisterValue("AX") << std::endl;
}
```

### Custom Program Creation

```cpp
std::vector<int> myProgram() {
    return {
        1, 0, 10,     // LOAD AX, 10
        1, 1, 20,     // LOAD BX, 20
        3, 0, 1,      // ADD AX, BX
        11, 0,        // PRINT AX
        12            // HALT
    };
}
```

## Technical Details

### Instruction Execution Cycle

1. **Fetch**: Read instruction from memory at PC address
2. **Decode**: Interpret opcode and extract operands
3. **Execute**: Perform the operation
4. **Update**: Modify registers, memory, or PC as needed

### Flag Updates

The zero and carry flags are updated by arithmetic operations:
- **Zero Flag**: Set when result equals zero
- **Carry Flag**: Set when result exceeds 16-bit range

### Error Handling

- **Division by Zero**: Stops execution with error message
- **Invalid Instructions**: Stops execution with unknown instruction error
- **Memory Bounds**: Checked for STORE operations

### Memory Management

- Linear memory model
- Program loaded starting at address 0
- Stack grows downward from high addresses
- Bounds checking prevents memory corruption

## Compilation

### Standard Compilation
```bash
g++ -o cpu_simulator main.cpp cpu.cpp
```

### With Debug Information
```bash
g++ -g -o cpu_simulator main.cpp cpu.cpp
```

### With Optimizations
```bash
g++ -O2 -o cpu_simulator main.cpp cpu.cpp
```

### Cross-Platform Notes
- Works on Linux, macOS, and Windows
- Uses standard C++ libraries only
- No external dependencies required

## Educational Value

This simulator demonstrates:

1. **CPU Architecture**: How processors execute instructions
2. **Assembly Programming**: Low-level programming concepts
3. **Computer Organization**: Memory, registers, and control flow
4. **Algorithm Implementation**: How high-level constructs map to machine code
5. **Debugging Skills**: Step-by-step program execution

## Extending the Simulator

### Adding New Instructions

1. Add opcode to enum in `cpu.h`
2. Implement case in `executeInstruction()` switch statement
3. Update documentation

### Example: Adding AND Instruction

```cpp
// In cpu.h enum
AND = 13,    // Bitwise AND

// In cpu.cpp executeInstruction()
case AND: {
    std::string reg1 = getRegisterName(memory[programCounter + 1]);
    std::string reg2 = getRegisterName(memory[programCounter + 2]);
    int result = registers[reg1] & registers[reg2];
    registers[reg1] = result;
    updateFlags(result);
    programCounter += 3;
    std::cout << "AND " << reg1 << ", " << reg2 << std::endl;
    break;
}
```

## Contributing

Contributions are welcome! Areas for improvement:

- Additional instruction types
- Enhanced debugging features
- Assembly language parser
- Graphical user interface
- Performance optimizations
- Extended register set

## License

This project is provided as educational material. Feel free to use, modify, and distribute for learning purposes.

---

**Author**: CPU Simulator Project  
**Language**: C++  
**Educational Focus**: Computer Architecture and Assembly Programming