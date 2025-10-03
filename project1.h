#ifndef __PROJECT1_H__
#define __PROJECT1_H__

#include <math.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;
/**
 * Helper Functions for String Processing
 */

const string WHITESPACE = " \n\r\t\f\v";

// Remove all whitespace from the left of the string
string ltrim(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

// Remove all whitespace from the right of the string
string rtrim(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

vector<string> split(const string &s, const string &split_on)
{
    vector<string> split_terms;
    int cur_pos = 0;
    while (cur_pos != string::npos)
    {
        int new_pos = s.find_first_not_of(split_on, cur_pos);
        cur_pos = s.find_first_of(split_on, new_pos);
        if (new_pos == -1 && cur_pos == -1)
            break;
        split_terms.push_back(s.substr(new_pos, cur_pos - new_pos));
    }
    return split_terms;
}

// Remove all comments and leading/trailing whitespace
string clean(const string &s)
{
    return rtrim(ltrim(s.substr(0, s.find('#'))));
}

/**
 * How to write raw binary to a file in C++
 */
void write_binary(int value, ofstream &outfile)
{
    // cout << hex << value << endl; //Useful for debugging
    outfile.write((char *)&value, sizeof(int));
}

// Get line Number

/**
 * Helper methods for instruction encoding
 */

// Utility function for encoding an arithmetic "R" type function
// terms[0] = instruction; terms[1] = rd; terms[2] = rs; terms[3] = rt
int encode_Rtype(int opcode, int rs, int rt, int rd, int shftamt, int funccode)
{
    return (opcode << 26) + (rs << 21) + (rt << 16) + (rd << 11) + (shftamt << 6) + funccode;
}
// Hint: What other instruction types need to be encoded?

// I-format
int encode_Itype(int opcode, int rs, int rt, int addr_const)
{
    // If num is negative, remove 16bits of preceding 1's
    if (addr_const < 0)
    {
        addr_const = addr_const & 0b00000000000000001111111111111111;
    }
    // cout << ((opcode << 26) + (rs << 21) + (rt << 16) + immediate) << endl;
    return (opcode << 26) + (rs << 21) + (rt << 16) + addr_const;
}

// J-format
int encode_Jtype(int opcode, int address)
{
    return (opcode << 26) + address;
}

/**
 * Register name map
 */
static unordered_map<string, int> registers{
    {"$zero", 0}, {"$0", 0}, {"$at", 1}, {"$1", 1}, {"$v0", 2}, {"$2", 2}, {"$v1", 3}, {"$3", 3}, {"$a0", 4}, {"$4", 4}, {"$a1", 5}, {"$5", 5}, {"$a2", 6}, {"$6", 6}, {"$a3", 7}, {"$7", 7}, {"$t0", 8}, {"$8", 8}, {"$t1", 9}, {"$9", 9}, {"$t2", 10}, {"$10", 10}, {"$t3", 11}, {"$11", 11}, {"$t4", 12}, {"$12", 12}, {"$t5", 13}, {"$13", 13}, {"$t6", 14}, {"$14", 14}, {"$t7", 15}, {"$15", 15}, {"$s0", 16}, {"$16", 16}, {"$s1", 17}, {"$17", 17}, {"$s2", 18}, {"$18", 18}, {"$s3", 19}, {"$19", 19}, {"$s4", 20}, {"$20", 20}, {"$s5", 21}, {"$21", 21}, {"$s6", 22}, {"$22", 22}, {"$s7", 23}, {"$23", 23}, {"$t8", 24}, {"$24", 24}, {"$t9", 25}, {"$25", 25}, {"$k0", 26}, {"$26", 26}, {"$k1", 27}, {"$27", 27}, {"$gp", 28}, {"$28", 28}, {"$sp", 29}, {"$29", 29}, {"$s8", 30}, {"$30", 30}, {"$ra", 31}, {"$31", 31}};

// Enum for instructionTypes
enum InstructionType
{
    ADD,
    ADDI,
    SUB,
    MULT,
    DIV,
    MFLO,
    MFHI,
    SLL,
    SRL,
    LW,
    SW,
    SLT,
    BEQ,
    BNE,
    J,
    JAL,
    JR,
    JALR,
    SYSCALL,
    LA,
    MOV,
    LI,
    SGE,
    SGT,
    SLE,
    SEQ,
    SNE,
    BGE,
    BGT,
    BLE,
    BLT,
    ABS,
    AND,
    OR,
    NOR,
    XOR,
    ANDI,
    ORI,
    XORI,
    LUI,
    UNKNOWN
};

// Map each instruction to each enum
static unordered_map<string, InstructionType> instruction_map{
    {"add", ADD}, {"addi", ADDI}, {"sub", SUB}, {"mult", MULT}, {"div", DIV}, {"mflo", MFLO}, {"mfhi", MFHI}, {"sll", SLL}, {"srl", SRL}, {"lw", LW}, {"sw", SW}, {"slt", SLT}, {"beq", BEQ}, {"bne", BNE}, {"j", J}, {"jal", JAL}, {"jr", JR}, {"jalr", JALR}, {"syscall", SYSCALL}, {"la", LA}, {"mov", MOV}, {"li", LI}, {"sge", SGE}, {"sgt", SGT}, {"sle", SLE}, {"seq", SEQ}, {"sne", SNE}, {"bge", BGE}, {"bgt", BGT}, {"ble", BLE}, {"blt", BLT}, {"abs", ABS}};

// R-Type Instructions
int add(const vector<string> &terms)
{
    return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 32);
}

int sub(const vector<string> &terms)
{
    return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 34);
}

int mult(const vector<string> &terms)
{
    return encode_Rtype(0, registers[terms[1]], registers[terms[2]], 0, 0, 24);
}

int div(const vector<string> &terms)
{
    return encode_Rtype(0, registers[terms[1]], registers[terms[2]], 0, 0, 26);
}

int mflo(const vector<string> &terms)
{
    return encode_Rtype(0, 0, 0, registers[terms[1]], 0, 18);
}

int mfhi(const vector<string> &terms)
{
    return encode_Rtype(0, 0, 0, registers[terms[1]], 0, 16);
}

int sll(const vector<string> &terms)
{
    return encode_Rtype(0, 0, registers[terms[2]], registers[terms[1]], stoi(terms[3]), 0);
}

int srl(const vector<string> &terms)
{
    return encode_Rtype(0, 0, registers[terms[2]], registers[terms[1]], stoi(terms[3]), 2);
}

int slt(const vector<string> &terms)
{
    return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int jr(const vector<string> &terms)
{
    return encode_Rtype(0, registers[terms[1]], 0, 0, 0, 8);
}

int jalr(const vector<string> &terms)
{
    if (terms.size() == 2)
    {
        return encode_Rtype(0, registers[terms[1]], 0, registers["$ra"], 0, 9);
    }
    else
    {
        return encode_Rtype(0, registers[terms[1]], 0, registers[terms[2]], 0, 9);
    }
}

int syscall(const vector<string> &terms)
{
    return encode_Rtype(0, 0, 0, 26, 0, 12);
}

int mov(const vector<string> &terms)
{
    return encode_Rtype(0, registers[terms[2]], 0, registers[terms[1]], 0, 32);
}

// TODO
int sge(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int sgt(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int sle(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int seq(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int sne(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int bge(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int bgt(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int ble(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int blt(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int abs(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int mips_and(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int mips_or(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int mips_nor(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int mips_xor(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}





// I-Type Instructions
int addi(const vector<string> &terms)
{
    return encode_Itype(8, registers[terms[2]], registers[terms[1]], stoi(terms[3]));
}

int lw(const vector<string> &terms)
{
    int offset = stoi(terms[2]);
    return encode_Itype(35, registers[terms[3]], registers[terms[1]], offset);
}

int sw(const vector<string> &terms)
{
    int offset = stoi(terms[2]);
    return encode_Itype(43, registers[terms[3]], registers[terms[1]], offset);
}

int beq(const vector<string> &terms, int curr_line_num, const map<string, int> &instruction_labels_lines)
{
    int offset = instruction_labels_lines.at(terms[3]) - (curr_line_num + 1);
    return encode_Itype(4, registers[terms[1]], registers[terms[2]], offset);
}

int bne(const vector<string> &terms, int curr_line_num, const map<string, int> &instruction_labels_lines)
{
    int offset = instruction_labels_lines.at(terms[3]) - (curr_line_num + 1);
    return encode_Itype(5, registers[terms[1]], registers[terms[2]], offset);
}

int la(const vector<string> &terms, const map<string, int> &static_label_lines)
{
    return encode_Itype(8, 0, registers[terms[1]], static_label_lines.at(terms[2]));
}

int li(const vector<string> &terms)
{
    return encode_Itype(8, 0, registers[terms[1]], stoi(terms[2]));
}

// TODO
int andi(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int ori(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int xori(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}

int lui(const vector<string> &terms)
{
    return 0;
    // return encode_Rtype(0, registers[terms[2]], registers[terms[3]], registers[terms[1]], 0, 42);
}




// J-Type Instructions
int j(const vector<string> &terms, const map<string, int> &instruction_labels_lines)
{
    int line_number = instruction_labels_lines.at(terms[1]);
    return encode_Jtype(2, line_number);
}

int jal(const vector<string> &terms, const map<string, int> &instruction_labels_lines)
{
    int line_number = instruction_labels_lines.at(terms[1]);
    return encode_Jtype(3, line_number);
}

#endif
