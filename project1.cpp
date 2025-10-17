#ifndef __PROJECT1_CPP__
#define __PROJECT1_CPP__
#define DEBUG true
#include "project1.h"

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

    /**
     * Phase 1:
     * Read all instructions, clean them of comments and whitespace DONE
     * TODO: Determine the numbers for all static memory labels
     * (measured in bytes starting at 0)
     * TODO: Determine the line numbers of all instruction line labels
     * (measured in instructions) starting at 0
     */

    // vector<string> instructions;
    // vector<string> static_memory;
    
    // int curr_line_num = 0;                     // Line number
    // map<string, int> instruction_labels_lines; // Label and what line number they correspond to ()
    // map<string, int> static_label_lines;
    // int memory_address = 0;

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
            // ASCII case
            else if (str.find(".asciiz") != string::npos)
            {
                smatch match;
                // If pattern is found
                if (regex_search(str, match, string_pattern))
                {
                    // If full match and capture group exist.
                    if (match.size() > 1)
                    {
                        string ascii_string = match[1].str(); // match[0] for capture group
                        vector<string> no_space = split(str, WHITESPACE);

                        string label = no_space[0];
                        label = label.substr(0, label.length() - 1); // clean up the colon in the end
                        static_label_lines[label] = memory_address;

                        // Store each character + null terminator
                        for (char c : ascii_string)
                        {
                            // convert the character to Ascii
                            static_memory.push_back(to_string((int)c));
                        }
                        static_memory.push_back("0"); // null terminator

                        int length = ascii_string.length() + 1; // +1 for null terminator
                        memory_address += (4 * length);
                    }
                }
                continue;
            }
            // Static Memory
            else if (str.find(".word") != string::npos)
            {
                vector<string> no_space = split(str, WHITESPACE + ",()");
                for (int i = 2; i < no_space.size(); i++)
                {
                    static_memory.push_back(no_space[i]);
                }

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
    vector<int> results;
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
            result = stoi(data);
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

        switch (type)
        {
        case ADD:
            result = add(terms);
            write_binary(result, inst_outfile);
            break;

        case ADDI:
            result = addi(terms);
            write_binary(result, inst_outfile);
            break;

        case SUB:
            result = sub(terms);
            write_binary(result, inst_outfile);
            break;

        case MULT:
            result = mult(terms);
            write_binary(result, inst_outfile);
            break;

        case DIV:
            result = div(terms);
            write_binary(result, inst_outfile);
            break;

        case MFLO:
            result = mflo(terms);
            write_binary(result, inst_outfile);
            break;

        case MFHI:
            result = mfhi(terms);
            write_binary(result, inst_outfile);
            break;

        case SLL:
            result = sll(terms);
            write_binary(result, inst_outfile);
            break;

        case SRL:
            result = srl(terms);
            write_binary(result, inst_outfile);
            break;

        case LW:
            result = lw(terms);
            write_binary(result, inst_outfile);
            break;

        case SW:
            result = sw(terms);
            write_binary(result, inst_outfile);
            break;

        case SLT:
            result = slt(terms);
            write_binary(result, inst_outfile);
            break;

        case BEQ:
            result = beq(terms, curr_line_num, instruction_labels_lines);
            write_binary(result, inst_outfile);
            break;

        case BNE:
            result = bne(terms, curr_line_num, instruction_labels_lines);
            write_binary(result, inst_outfile);
            break;

        case J:
            result = j(terms, instruction_labels_lines);
            write_binary(result, inst_outfile);
            break;

        case JAL:
            result = jal(terms, instruction_labels_lines);
            write_binary(result, inst_outfile);
            break;

        case JR:
            result = jr(terms);
            write_binary(result, inst_outfile);
            break;

        case JALR:
            result = jalr(terms);
            write_binary(result, inst_outfile);
            break;

        case SYSCALL:
            result = syscall(terms);
            write_binary(result, inst_outfile);
            break;

        case LA:
            result = la(terms, static_label_lines);
            write_binary(result, inst_outfile);
            break;

        case MOV:
            result = mov(terms);
            write_binary(result, inst_outfile);
            break;

        case LI:
            result = li(terms);
            write_binary(result, inst_outfile);
            break;

        case SGE:
            results = sge(terms);
            for (int r : results)
            {
                write_binary(r, inst_outfile);
            }
            break;

        case SGT:
            results = sgt(terms);
            for (int r : results)
            {
                write_binary(r, inst_outfile);
            }
            break;

        case SLE:
            results = sle(terms);
            for (int r : results)
            {
                write_binary(r, inst_outfile);
            }
            break;

            // case SEQ:
            //     result = seq(terms);
            //     write_binary(result, inst_outfile);
            //     break;

            // case SNE:
            //     result = sne(terms);
            //     write_binary(result, inst_outfile);
            //     break;

        case BGE:
            results = bge(terms);
            for (int r : results)
            {
                write_binary(r, inst_outfile);
            }
            break;

        case BGT:
            results = bgt(terms);
            for (int r : results)
            {
                write_binary(r, inst_outfile);
            }
            break;

        case BLE:
            results = ble(terms);
            for (int r : results)
            {
                write_binary(r, inst_outfile);
            }
            break;

        case BLT:
            results = blt(terms);
            for (int r : results)
            {
                write_binary(r, inst_outfile);
            }
            break;

            // case ABS:
            //     result = abs(terms);
            //     write_binary(result, inst_outfile);
            //     break;

        case AND:
            result = mips_and(terms);
            write_binary(result, inst_outfile);
            break;

        case OR:
            result = mips_or(terms);
            write_binary(result, inst_outfile);
            break;

        case NOR:
            result = mips_nor(terms);
            write_binary(result, inst_outfile);
            break;

        case XOR:
            result = mips_xor(terms);
            write_binary(result, inst_outfile);
            break;

        case ANDI:
            result = andi(terms);
            write_binary(result, inst_outfile);
            break;

        case ORI:
            result = ori(terms);
            write_binary(result, inst_outfile);
            break;

        case XORI:
            result = xori(terms);
            write_binary(result, inst_outfile);
            break;

        case LUI:
            result = lui(terms);
            write_binary(result, inst_outfile);
            break;

        case UNKNOWN:
        default:
            cerr << "Warning: Unknown instruction \"" << inst_type << "\" at line " << curr_line_num << "(0-based line counting)" << endl;
            break;
        }

        curr_line_num++;
    }

    if (DEBUG)
    {
        // Print map of labels and line nums
        cout << "\n\tLine Nums and Instruction labels MAP\n"
             << endl;
        for (int i = 0; i < instructions.size(); i++)
        {
            cout << i << ": " << instructions[i] << endl;
        }

        cout << "\n\tINSTRUCTION LABELS\n"
             << endl;
        // Print map of labels and line nums
        for (auto l : instruction_labels_lines)
        {
            cout << l.first << " --> " << l.second << endl;
        }

        cout << "\n\tSTATIC MEMORY LABELS\n"
             << endl;
        for (auto t : static_label_lines)
        {
            cout << t.second << " --> " << t.first << endl;
        }

        cout << "\n\tSTATIC MEMORY VALUES\n"
             << endl;
        for (int i = 0; i < static_memory.size(); i++)
        {
            cout << "address " << i * 4 << " --> " << static_memory[i] << endl;
        }
    }
}

#endif