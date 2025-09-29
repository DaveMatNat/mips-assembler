#ifndef __PROJECT1_CPP__
#define __PROJECT1_CPP__

#include "project1.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>

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

    /**
     * Phase 1:
     * Read all instructions, clean them of comments and whitespace DONE
     * TODO: Determine the numbers for all static memory labels
     * (measured in bytes starting at 0)
     * TODO: Determine the line numbers of all instruction line labels
     * (measured in instructions) starting at 0
     */

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
            }
            instructions.push_back(str); // TODO This will need to change for labels
        }
        infile.close();
    }

    /** Phase 2
     * Process all static memory, output to static memory file
     * TODO: All of this
     */

    /** Phase 3
     * Process all instructions, output to instruction memory file
     * TODO: Almost all of this, it only works for adds
     */
    for (string inst : instructions)
    {
        vector<string> terms = split(inst, WHITESPACE + ",()");
        string inst_type = terms[0];
        // for debugging
        cout << inst_type << endl;
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
            int result = encode_Rtype(0, 0, registers[terms[2]],registers[terms[1]], stoi(terms[3]), 0);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "srl")
        {
            int result = encode_Rtype(0, 0, registers[terms[2]],registers[terms[1]], stoi(terms[3]), 2);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "lw")
        {
            int result = encode_Itype(35, 0, registers[terms[1]], registers[terms[2]]);
            write_binary(result, inst_outfile); 
        }
        else if (inst_type == "sw")
        {
            int result = encode_Itype(43, 0, registers[terms[1]], registers[terms[2]]);
            write_binary(result, inst_outfile); 
        }
        else if (inst_type == "slt")
        {
            int result = encode_Rtype(0, registers[terms[2]],registers[terms[3]], registers[terms[1]],0, 42);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "beq")
        {
            int result = encode_Itype(4, registers[terms[1]], registers[terms[2]], registers[terms[3]]);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "bne")
        {
            int result = encode_Itype(5, registers[terms[1]], registers[terms[2]], registers[terms[3]]);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "j")
        {
            // registers[terms[1]] == Label
            
            int result = encode_Jtype(2, registers[terms[1]]);
            write_binary(result, inst_outfile);
        }
        else if (inst_type == "jal")
        {
        }
        else if (inst_type == "jr")
        {
        }
        else if (inst_type == "jalr")
        {
        }
        else if (inst_type == "syscall")
        {
            // 000000 00000 00000 11010 00000 001100
            int result = encode_Rtype(0, 0, 0, 26, 0, 12);
            write_binary(result, inst_outfile);
        }
        else
        {
        }
    }
}

#endif
