#ifndef __PROJECT1_CPP__
#define __PROJECT1_CPP__

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
     * TODO: Almost all of this, it only works for adds
     */
    curr_line_num = 0;
    for (string inst : instructions)
    {
        vector<string> terms = split(inst, WHITESPACE + ",()");
        string inst_type = terms[0];
        // for debugging
        // cout << inst_type << endl;
        if (inst_type == "add")
        {
            int result = encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 32);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "addi")
        {
            int result = encode_Itype(8, registers[terms[2]], registers[terms[1]], stoi(terms[3]));
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "sub")
        {
            int result = encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 34);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "mult")
        {
            int result = encode_Rtype(0, registers[terms[1]], registers[terms[2]], 0, 0, 24);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "div")
        {
            int result = encode_Rtype(0, registers[terms[1]], registers[terms[2]], 0, 0, 26);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "mflo")
        {
            int result = encode_Rtype(0, 0, 0, registers[terms[1]], 0, 18);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "mfhi")
        {
            int result = encode_Rtype(0, 0, 0, registers[terms[1]], 0, 16);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "sll") // sll rd, rt, shamt
        {
            int result = encode_Rtype(0, 0, registers[terms[2]], registers[terms[1]], stoi(terms[3]), 0);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "srl")
        {
            int result = encode_Rtype(0, 0, registers[terms[2]], registers[terms[1]], stoi(terms[3]), 2);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "lw")
        {
            // cout << terms[3] << endl;
            int offset = stoi(terms[2]);
            int result = encode_Itype(35, registers[terms[3]], registers[terms[1]], offset);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "sw")
        {

            int offset = stoi(terms[2]);
            int result = encode_Itype(43, registers[terms[3]], registers[terms[1]], offset);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "slt")
        {
            int result = encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "beq")
        {
            int offset = instruction_labels_lines[terms[3]] - (curr_line_num + 1);
            // cout << offset << ": " << instructions[curr_line_num + offset] << endl;
            int result = encode_Itype(4, registers[terms[1]], registers[terms[2]], offset);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "bne")
        {
            int offset = instruction_labels_lines[terms[3]] - (curr_line_num + 1);
            // cout << offset << ": " << instructions[curr_line_num + offset] << endl;
            int result = encode_Itype(5, registers[terms[1]], registers[terms[2]], offset);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "j")
        {
            // terms[1] == Label
            // instruction_labels_lines[terms[1]] == Line Number of intruction after the Label
            int line_number = instruction_labels_lines[terms[1]];
            int result = encode_Jtype(2, line_number);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "jal")
        {
            // TODO: DEAL WITH $ra (no need I think cuz in pdf says so)
            int line_number = instruction_labels_lines[terms[1]];
            int result = encode_Jtype(3, line_number);
            // ra = curr_line_num + 1; // Set return address to line after jal
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "jr")
        {
            // Placeholder
            int result = encode_Rtype(0, registers[terms[1]], 0, 0, 0, 8);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "jalr")
        {
            int result;
            // jalr with 1 register
            if (terms.size() == 2)
            {
                result = encode_Rtype(0, registers[terms[1]], 0, registers["$ra"], 0, 9);
            }
            else
            {
                // jalr with 2 registers
                result = encode_Rtype(0, registers[terms[1]], 0, registers[terms[2]], 0, 9);
            }
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "syscall")
        {
            // 000000 00000 00000 11010 00000 001100
            int result = encode_Rtype(0, 0, 0, 26, 0, 12);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "la")
        {
            // Problematic
            // cout << terms[2] << endl;
            // cout << static_label_lines[terms[2]] << endl;

            int result = encode_Itype(8, 0, registers[terms[1]], static_label_lines[terms[2]]);
            // int result = 0;
            write_binary(result, inst_outfile);
        }
        else
        {
        }
        curr_line_num++;
    }

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

#endif
