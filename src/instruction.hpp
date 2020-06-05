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

/**!< Funcion para controlar el cursor*/
static void gotoxy( short x, short y ){
	printf("%c[%d;%df",0x1B, y, x );
}


class Instruction
{
public:
    inline static std::vector<std::string> operators {"G", "I", "<-", "D"}; 

    uint8_t find_operator();

    std::vector<std::string> code;
    std::vector<std::string> operands;
    std::string operation{""};
    std::string label {""};

    Instruction(){}
    /**
     * @brief Construct a new Instruction object
     * 
     * @param instruction 
     */
    Instruction(std::string instruction);
    ~Instruction(){}

    /**
     * @brief 
     * 
     * @param instruction 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> decodeInstruction(std::string instruction);
    bool getTypeInstruction();
    void Print();
    void PrintCode( short x, short y );
};
