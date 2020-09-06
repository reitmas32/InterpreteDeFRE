#pragma once 

#include <string>
#include <vector>

#define LEN_INSTUCTION 4
#define NUM_OPERANDS_MAX 2

/**!< Funcion para controlar el cursor*/
inline static void gotoxy( short x, short y ){
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

    /**
     * @brief Destroy the Instruction object
     * 
     */
    ~Instruction(){}

    /**
     * @brief decodifica la instruccion que se le pase como parametro
     * 
     * @param instruction 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> decodeInstruction(std::string instruction);

    /**
     * @brief Imprime la instruciion
     * 
     */
    void Print();

    /**
     * @brief Imprime el codigo de la instruccion en una coordenada especifica en pantalla
     * 
     * @param x 
     * @param y 
     */
    void PrintCode( short x, short y );
};
