# 🔧 MIPS Assembler - CMSC301 Project

A complete MIPS assembler implementation that translates MIPS assembly language into binary machine code. This project demonstrates low-level computer architecture concepts including instruction encoding, memory management, and assembly language processing.

## 🚀 Features

### ✨ Instruction Support
- **R-Type Instructions**: `add`, `sub`, `mult`, `div`, `mflo`, `mfhi`, `slt`, `sll`, `srl`
- **I-Type Instructions**: `addi`, `lw`, `sw`, `beq`, `bne`  
- **J-Type Instructions**: `j`, `jal`, `jr`
- **System Calls**: `syscall`

### 🎯 Advanced Features
- **Label Resolution**: Automatic handling of instruction and data labels
- **Static Memory Management**: `.word` directive support with label references
- **Multi-file Assembly**: Process multiple `.asm` files in a single run
- **Comment Stripping**: Automatic removal of comments and whitespace
- **Binary Output**: Generates separate instruction and static memory binaries
- **Binary Analysis**: Included `readbytes` utility for examining binary output

## 📁 Project Structure

```
Checkpoint 1/
├── project1.h              # Header with encoding functions and utilities
├── project1.cpp            # Main assembler implementation
├── readbytes.cpp           # Binary file analysis utility
├── Makefile                # Build configuration
├── Testcases/
│   ├── Assembly/           # Test assembly files
│   │   ├── test1.asm
│   │   ├── test2.asm
│   │   └── ...
│   └── GoldBinaries/       # Expected binary outputs
│       ├── test1_inst.bin
│       ├── test1_static.bin
│       └── ...
└── README.md              # This file
```

## 🛠 Build & Usage

### Prerequisites
- C++ compiler with C++11 support
- Make utility

### Building the Assembler
```bash
make
```
This creates the main executable:
- `assemble` - The main assembler

### Building the Binary Analyzer (Manual Compilation Required)
The `readbytes` utility must be compiled separately:
```bash
g++ -std=c++17 readbytes.cpp -o readbytes
```

### Running the Assembler
```bash
./assemble input1.asm [input2.asm ...] static_output.bin instruction_output.bin
```

### Analyzing Binary Output
```bash
# First compile readbytes if not already done
g++ -std=c++17 readbytes.cpp -o readbytes

# View instruction binary in hex format
./readbytes instruction_output.bin

# View static memory binary
./readbytes static_output.bin
```

### Complete Workflow Example
```bash
# Build everything
make
g++ -std=c++17 readbytes.cpp -o readbytes

# Assemble the code
./assemble Testcases/Assembly/test1.asm static.bin inst.bin

# Examine the generated binaries
echo "=== Instruction Memory ==="
./readbytes inst.bin

echo "=== Static Memory ==="
./readbytes static.bin

# Compare with expected output
echo "=== Comparing with Gold Standard ==="
./readbytes Testcases/GoldBinaries/test1_inst.bin
./readbytes Testcases/GoldBinaries/test1_static.bin
```

## 🧪 Testing & Debugging

### Quick Setup for Testing
```bash
# One-time setup
make
g++ -std=c++17 readbytes.cpp -o readbytes

# Now you can test any assembly file
./assemble Testcases/Assembly/test1.asm static.bin inst.bin
./readbytes inst.bin
```

### Comprehensive Testing Workflow
```bash
# Test and verify in one command (assumes readbytes is compiled)
./assemble Testcases/Assembly/test2.asm static.bin inst.bin && \
echo "Generated:" && ./readbytes inst.bin && \
echo "Expected:" && ./readbytes Testcases/GoldBinaries/test2_inst.bin
```

### Using `readbytes` for Debugging
The `readbytes` utility is essential for:
- **Verifying instruction encoding**: Check if your R/I/J-type encodings are correct
- **Debugging static memory**: Ensure label references resolve to correct values
- **Comparing outputs**: Side-by-side comparison with gold standard binaries
- **Understanding binary format**: Learn how MIPS instructions look in machine code

### Example Debug Session
```bash
# Compile readbytes first
g++ -std=c++17 readbytes.cpp -o readbytes

# If your test fails, use readbytes to investigate
./assemble Testcases/Assembly/test1.asm static.bin inst.bin

# Check what you generated vs expected
echo "Your output:"
./readbytes inst.bin
echo "Expected output:"  
./readbytes Testcases/GoldBinaries/test1_inst.bin

# Look for differences in specific instructions
diff <(./readbytes inst.bin) <(./readbytes Testcases/GoldBinaries/test1_inst.bin)
```

### Analyzing Gold Standard Files
```bash
# Examine expected outputs to understand correct encoding
./readbytes Testcases/GoldBinaries/test1_inst.bin
./readbytes Testcases/GoldBinaries/test1_static.bin
```

## 📋 Assembly Language Format

### Data Section
```assembly
.data
    array: .word 1 2 3 4        # Static array
    ptr: .word array            # Label reference
```

### Text Section
```assembly
.text
.globl main
main:
    addi $s0, $zero, 10        # Load immediate
    add $t0, $s0, $s1          # Register arithmetic
    lw $t1, 4($sp)             # Load word
    beq $t0, $zero, end        # Conditional branch
    jal function               # Jump and link
end:
    syscall                    # System call
```

## 🏗 Architecture Overview

### Three-Phase Assembly Process

#### Phase 1: Parsing & Label Discovery
- Parse all input files
- Strip comments and whitespace
- Identify and map instruction labels to line numbers
- Identify and map static data labels to memory addresses

#### Phase 2: Static Memory Processing
- Resolve label references in `.word` directives
- Convert numeric values (decimal/hex) to binary
- Output static memory binary file

#### Phase 3: Instruction Encoding
- Encode each instruction using appropriate format (R/I/J-type)
- Resolve branch offsets and jump targets
- Output instruction binary file

### Instruction Encoding

#### R-Type Format
```
| opcode | rs | rt | rd | shamt | funct |
|   6    | 5  | 5  | 5  |   5   |   6   |
```

#### I-Type Format  
```
| opcode | rs | rt | immediate |
|   6    | 5  | 5  |    16     |
```

#### J-Type Format
```
| opcode |     address     |
|   6    |       26        |
```

## 🔍 Binary Analysis with `readbytes`

### Compilation Note
⚠️ **Important**: The `readbytes` utility requires manual compilation:
```bash
g++ -std=c++17 readbytes.cpp -o readbytes
```

### Understanding Output Format
```bash
$ ./readbytes inst.bin
00000000: 20100064    # addi $s0, $zero, 100
00000004: 02002020    # add $a0, $s0, $0  
00000008: 0c000007    # jal f
0000000c: 02001020    # add $v0, $s0, $0
```

Each line shows:
- **Memory address** (hexadecimal)
- **Instruction encoding** (32-bit hex value)
- **Optional comment** (if you add instruction tracing)

### Common Debugging Patterns
- **Wrong opcode**: First 6 bits incorrect
- **Register mixup**: Check rs, rt, rd fields
- **Immediate issues**: Sign extension or bit masking problems
- **Branch offsets**: PC-relative calculation errors

## 🧪 Test Cases Include
- **Basic Arithmetic**: Addition, subtraction, multiplication
- **Memory Operations**: Load/store with various addressing modes
- **Control Flow**: Branches, jumps, function calls
- **Complex Programs**: Loops, recursion, data structure access

## 🔍 Key Implementation Details

### Register Mapping
Complete support for MIPS register naming conventions:
- `$zero`, `$at`, `$v0-$v1`, `$a0-$a3`, `$t0-$t9`, `$s0-$s7`, `$k0-$k1`, `$gp`, `$sp`, `$ra`
- Numeric equivalents: `$0-$31`

### Label Resolution
- **Instruction Labels**: Resolved to line numbers (×4 for byte addressing)
- **Data Labels**: Resolved to memory offsets in static data section
- **Forward References**: Supported through two-pass assembly

### Error Handling
- File I/O error detection
- Invalid register name detection
- Label resolution failure handling
- Malformed instruction detection

## 🐛 Debugging Features

### Built-in Diagnostics
```cpp
// Enable debug output in source
cout << "Line " << curr_line_num << ": " << instruction << endl;
```

### Memory Dump
The assembler outputs both instruction and static memory maps for debugging.

## 📝 Development Notes

### Recent Improvements
- ✅ Fixed I-type instruction encoding for negative immediates
- ✅ Corrected load/store instruction parsing  
- ✅ Implemented proper branch offset calculation
- ✅ Added comprehensive `.gitignore` for build artifacts
- ✅ Integrated `readbytes` utility for binary analysis

### Known Limitations
- Limited to subset of MIPS instruction set
- No macro expansion support
- No optimization passes

## 👥 Contributors

**David Nathanson** - CMSC301 Fall 2025
**Martin Sang** - CMSC301 Fall 2025

## 📄 License

This project is part of academic coursework and is subject to university academic integrity policies.

---

*Built with ❤️ for Computer Architecture & Organization*

**Pro Tip**: Always compile `readbytes` first (`g++ -std=c++17 readbytes.cpp -o readbytes`) and use it to verify your binary output matches the expected results! 🔍