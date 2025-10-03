#ifndef __PROJECT1_CPP__
#define __PROJECT1_CPP__

// Switch to "true" for debugging
#define DEBUG false

#include "project1.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>

// Added Map
#include <map>
int ra; // Global return address (line number)

int main(int argc, char *argv[])
{
    if (argc < 4) // Checks that at least 3 arguments are given in command line
    {
        cerr << "Expected Usage:\n ./assemble infile1.asm infile2.asm ... infilek.asm staticmem_outfile.bin instructions_outfile.bin\n"
             << endl;
        exit(1);
    }
    // Prepare output files
    ofstream inst_outfile, static_outfile;
    static_outfile.open(argv[argc - 2], ios::binary);
    inst_outfile.open(argv[argc - 1], ios::binary);

    vector<string> instructions;
    vector<string> static_memory;
    /**
     * Phase 1:
     * Read all instructions, clean them of comments and whitespace DONE
     * TODO: Determine the numbers for all static memory labels
     * (measured in bytes starting at 0)
     * TODO: Determine the line numbers of all instruction line labels
     * (measured in instructions) starting at 0
     */

    int curr_line_num = 0;                     // Line number
    map<string, int> instruction_labels_lines; // Label and what line number they correspond to ()
    map<string, int> static_label_lines;
    int memory_address = 0;

    // For each input file:
    for (int i = 1; i < argc - 2; i++)
    {
        ifstream infile(argv[i]); //  open the input file for reading
        if (!infile)
        { // if file can't be opened, need to let the user know
            cerr << "Error: could not open file: " << argv[i] << endl;
            exit(1);
        }

        string str;
        while (getline(infile, str))
        {                     // Read a line from the file
            str = clean(str); // remove comments, leading and trailing whitespace
            if (str == "")
            { // Ignore empty lines
                continue;
            } // Static Memory
            else if (str.find(".word") != string::npos)
            {
                vector<string> no_space = split(str, WHITESPACE + ",()");
                // vector<int> values = {};
                for (int i = 2; i < no_space.size(); i++)
                {
                    static_memory.push_back(no_space[i]);
                }
                // cout << "|| len --> " << no_space.size() << endl << endl;

                string label = no_space[0];
                label = label.substr(0, label.length() - 1); // clean up the colon in the end

                int length = no_space.size() - 2;
                static_label_lines[label] = memory_address;
                memory_address += (4 * length);
                continue;
            }

            else if (str.rfind(":") == str.length() - 1)
            { // If label --> Map to line number of next instruction
                str = str.substr(0, str.length() - 1);
                // count << str << endl;
                instruction_labels_lines[str] = curr_line_num;
                continue;
            }
            else if (str.find(".") != string::npos)
            {
                continue; // Deal with Data
            }
            else
            {
                instructions.push_back(str); // TODO This will need to change for labels
            }

            curr_line_num++;
        }
        infile.close();
    }

    /** Phase 2
     * Process all static memory, output to static memory file
     * TODO: All of this
     */
    int result;
    for (string data : static_memory)
    {
        // check if the data is a reference to a label
        if (instruction_labels_lines.find(data) != instruction_labels_lines.end())
        {
            result = instruction_labels_lines[data] * 4; // Check document page 5 on why 7 * 4 = 28 for "f"
        }
        else if (static_label_lines.find(data) != static_label_lines.end())
        {
            result = static_label_lines[data];
        }
        else
        {
            // Otherwise, it's a number (decimal or hex?)
            result = stoi(data, nullptr, 0); // 0 --> auto-detect base
        }
        write_binary(result, static_outfile);
    }

    /** Phase 3
     * Process all instructions, output to instruction memory file
     * Using switch statement for cleaner code organization
     */
    curr_line_num = 0;
    for (string inst : instructions)
    {
        vector<string> terms = split(inst, WHITESPACE + ",()");
        string inst_type = terms[0];

        // Get instruction type enum
        InstructionType type = (instruction_map.find(inst_type) != instruction_map.end())
                                   ? instruction_map[inst_type]
                                   : UNKNOWN;

        int result = 0;

        switch (type)
        {
        case ADD:
            result = add(terms);
            break;

        case ADDI:
            result = addi(terms);
            break;

        case SUB:
            result = sub(terms);
            break;

        case MULT:
            result = mult(terms);
            break;

        case DIV:
            result = div(terms);
            break;

        case MFLO:
            result = mflo(terms);
            break;

        case MFHI:
            result = mfhi(terms);
            break;

        case SLL:
            result = sll(terms);
            break;

        case SRL:
            result = srl(terms);
            break;

        case LW:
            result = lw(terms);
            break;

        case SW:
            result = sw(terms);
            break;

        case SLT:
            result = slt(terms);
            break;

        case BEQ:
            result = beq(terms, curr_line_num, instruction_labels_lines);
            break;

        case BNE:
            result = bne(terms, curr_line_num, instruction_labels_lines);
            break;

        case J:
            result = j(terms, instruction_labels_lines);
            break;

        case JAL:
            result = jal(terms, instruction_labels_lines);
            break;

        case JR:
            result = jr(terms);
            break;

        case JALR:
            result = jalr(terms);
            break;

        case SYSCALL:
            result = syscall(terms);
            break;

        case LA:
            result = la(terms, static_label_lines);
            break;

        case MOV:
            result = mov(terms);
            break;

        case LI:
            result = li(terms);
            break;

        case SGE:
            result = sge(terms);
            break;

        case SGT:
            result = sgt(terms);
            break;

        case SLE:
            result = sle(terms);
            break;

        case SEQ:
            result = seq(terms);
            break;

        case SNE:
            result = sne(terms);
            break;

        case BGE:
            result = bge(terms);
            break;

        case BGT:
            result = bgt(terms);
            break;

        case BLE:
            result = ble(terms);
            break;

        case BLT:
            result = blt(terms);
            break;

        case ABS:
            result = abs(terms);
            break;

        case AND:
            result = mips_and(terms);
            break;

        case OR:
            result = mips_or(terms);
            break;

        case NOR:
            result = mips_nor(terms);
            break;

        case XOR:
            result = mips_xor(terms);
            break;

        case ANDI:
            result = andi(terms);
            break;

        case ORI:
            result = ori(terms);
            break;

        case XORI:
            result = xori(terms);
            break;

        case LUI:
            result = lui(terms);
            break;

        case UNKNOWN:
        default:
            cerr << "Warning: Unknown instruction \"" << inst_type << "\" at line " << curr_line_num << "(0-based line counting)" << endl;
            break;
        }

        write_binary(result, inst_outfile);

        curr_line_num++;
    }

    if (DEBUG)
    {
        // Print map of labels and line nums
        cout << "\n\tLine Nums and Instruction LABELS MAP\n"
             << endl;
        for (int i = 0; i < instructions.size(); i++)
        {
            cout << i << ": " << instructions[i] << endl;
        }

        cout << "\n\tLABELS\n"
             << endl;
        // Print map of labels and line nums
        for (auto l : instruction_labels_lines)
        {
            cout << l.first << " --> " << l.second << endl;
        }

        cout << "\n\tSTATIC MEMORY\n"
             << endl;
        for (auto t : static_label_lines)
        {
            cout << t.first << " --> " << t.second << endl;
        }

        cout << "\n\tSTATIC MEMORY Values\n"
             << endl;
        for (int i = 0; i < static_memory.size(); i++)
        {
            cout << static_memory[i] << endl;
        }
    }
}

#endif
