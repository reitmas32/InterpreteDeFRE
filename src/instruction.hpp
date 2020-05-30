#pragma once 

#include <string>
#include <vector>

#define LEN_INSTUCTION 4

enum class Instructions{
    l_Inc,
    l_Dec,
    l_Goto,
    Inc,
    Dec,
    Goto,
    Asig,
    l_Asig
};

class Instruction
{
public:

    std::string label {""};
    std::string var {""};
    std::string gotoLabel {""};
    std::string operation {""};
    int val;
    std::string instruc;
    Instructions type;

    Instruction(){}
    Instruction(std::string instruction);
    ~Instruction(){}

    std::vector<std::string> decodeInstruction(std::string instruction);
    bool getTypeInstruction();
    void Print();
};
