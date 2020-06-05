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
    Interpreter();
    ~Interpreter(){}

    bool readCode(std::string file);

    bool runInstruction();

    void runCode();

    void runCodeDebug();

    void PrintData();
};
