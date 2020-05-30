#include <iostream>
#include <fstream>

#include "interpreter.hpp"

Interpreter::Interpreter()
{
    this->data["X0"] = 0;
    this->data["X1"] = 0;
    this->data["X2"] = 0;
    this->data["X3"] = 0;
    this->data["X4"] = 0;
    this->data["X5"] = 0;
    this->data["X6"] = 0;
    this->data["X7"] = 0;
    this->data["X8"] = 0;
    this->data["X9"] = 0;

    this->data["Y0"] = 0;
    this->data["Y1"] = 0;
    this->data["Y2"] = 0;
    this->data["Y3"] = 0;
    this->data["Y4"] = 0;
    this->data["Y5"] = 0;
    this->data["Y6"] = 0;
    this->data["Y7"] = 0;
    this->data["Y8"] = 0;
    this->data["Y9"] = 0;

    this->data["Z0"] = 0;
    this->data["Z1"] = 0;
    this->data["Z2"] = 0;
    this->data["Z3"] = 0;
    this->data["Z4"] = 0;
    this->data["Z5"] = 0;
    this->data["Z6"] = 0;
    this->data["Z7"] = 0;
    this->data["Z8"] = 0;
    this->data["Z9"] = 0;
}

bool Interpreter::readCode(std::string file)
{
    std::string line;
    std::ifstream source(file);
    Instruction tmpInstruct;
    this->ip = 0;
    if (source.is_open())
    {
        while (getline(source, line))
        {
            tmpInstruct = Instruction(line);
            //std::cout<<"IP: "<<this->ip;
            //tmpInstruct.Print();
            if (tmpInstruct.label != "")
            {
                this->labels[tmpInstruct.label] = this->ip;
            }
            this->code[this->ip] = tmpInstruct;
            this->ip++;
            this->lenSource++;
        }
        source.close();
    }

    else
        std::cout << "Unable to open file";

    return 0;
}

bool Interpreter::runInstruction()
{
    Instruction instruction = this->code[this->ip];
    switch (instruction.type)
    {
    case Instructions::Inc:
        this->data[instruction.var] = this->data[instruction.var] + 1;
        this->ip++;
        break;
    case Instructions::Dec:
        if (this->data[instruction.var] != 0)
            this->data[instruction.var] = this->data[instruction.var] - 1;
        this->ip++;
        break;
    case Instructions::Goto:
        if (this->data[instruction.var] != 0){
            this->ip = this->labels[instruction.gotoLabel];
        }
            
        break;
    case Instructions::l_Inc:
        this->data[instruction.var] = this->data[instruction.var] + 1;
        this->ip++;
        break;
    case Instructions::l_Dec:
        if (this->data[instruction.var] != 0)
            this->data[instruction.var] = this->data[instruction.var] - 1;
        this->ip++;
        break;
    case Instructions::l_Goto:
        if (this->data[instruction.var] != 0){
            this->ip = this->labels[instruction.gotoLabel];
        }else{
            this->ip++;
        }
            
        break;

    default:
        break;
    }
    return true;
}

void Interpreter::runCode(std::map<std::string, int> dataIn)
{
    for (auto v : dataIn)
    {
        this->data[v.first] = v.second;
    }
    this->ip = 0;
    while (this->code[this->ip].label != "END")
    {
        this->runInstruction();
    }

}

void Interpreter::runCodeDebug(std::map<std::string, int> dataIn)
{
    for (auto v : dataIn)
    {
        this->data[v.first] = v.second;
    }
    this->ip = 0;
    while (this->code[this->ip].label != "END")
    {
        std::cout<<"IP: "<<this->ip<<" "<<this->code[this->ip].instruc<<'\n';
        this->runInstruction();
        std::getchar();
    }

}