#pragma once 

#include <string>
#include <vector>

#define LEN_INSTUCTION 4
#define NUM_OPERANDS_MAX 2

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
    inline static std::vector<std::string> operators {"G", "I", "<-", "D"}; 

    uint8_t find_operator();

    std::vector<std::string> code ;
    std::vector<std::string> operands;
    std::string operation{""};
    std::string label {""};

    Instruction(){}
    Instruction(std::string instruction);
    ~Instruction(){}

    std::vector<std::string> decodeInstruction(std::string instruction);
    bool getTypeInstruction();
    void Print();
};
