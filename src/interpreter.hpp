#pragma once

#define SIZE_CODE 100

#include <string>
#include <map>

#include "instruction.hpp"
class Interpreter
{
public:
    int ip {0};
    int lenSource {0};
    std::map<std::string, int> data;
    std::map<std::string, int> labels;
    std::map<int, Instruction> code;
public:
    /**
     * @brief Construct a new Interpreter object
     * 
     */
    Interpreter();

    /**
     * @brief Destroy the Interpreter object
     * 
     */
    ~Interpreter(){}

    /**
     * @brief lee el codigo en la ruta especificada
     * 
     * @param file 
     * @return true 
     * @return false 
     */
    bool readCode(std::string file);

    /**
     * @brief Corre la instruccion a la que apunta el ip
     * 
     */
    void runInstruction();

    /**
     * @brief Corre todo el codigo
     * 
     */
    void runCode();

    /**
     * @brief Corre el codigo mostrando un mini debuger
     * 
     */
    void runCodeDebug();

    /**
     * @brief Imprime el sugmento de datos
     * 
     */
    void PrintData();
};
