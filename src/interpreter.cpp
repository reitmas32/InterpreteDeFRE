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

    if (source.is_open())
    {

        while (getline(source, line))
        {
            tmpInstruct = Instruction(line);
            std::cout << "IP: " << this->ip << '\n';
            tmpInstruct.Print();
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
    if (instruction.operation == "I")
    {
        this->data[instruction.operands[0]] = this->data[instruction.operands[0]] + 1;
        this->ip++;
    }
    else if (instruction.operation == "D")
    {
        if (this->data[instruction.operands[0]] != 0)
            this->data[instruction.operands[0]] = this->data[instruction.operands[0]] - 1;
        this->ip++;
    }
    else if (instruction.operation == "<-")
    {
        for (auto c : instruction.operands[1])
        {
            if (c == '[')
            {
                std::string op;
                for (size_t i = 1; i < instruction.operands[1].size() - 1; i++)
                {
                    op += instruction.operands[1][i];
                }
                this->data[instruction.operands[0]] = this->data[op];
                break;
            }
            else
            {
                this->data[instruction.operands[0]] = stoi(instruction.operands[1]);
            }
        }

        this->ip++;
    }
    else if (instruction.operation == "G")
    {
        if (this->data[instruction.operands[0]] != 0)
        {

            this->ip = this->labels[instruction.operands[1]];
        }
        else
        {
            this->ip++;
        }
    }

    /*
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
    */
    return true;
}

void Interpreter::runCode()
{

    this->ip = 0;

    while (this->code[this->ip].label != "END")
    {
        this->runInstruction();
    }
}

void Interpreter::runCodeDebug()
{

    this->ip = 0;

    while (this->code[this->ip].label != "END")
    {
        std::cout << "IP: " << this->ip << " ";
        for (std::string i : this->code[this->ip].code)
        {
            std::cout << i << ' ';
        }
        std::cout << '\n';
        this->runInstruction();
        std::getchar();
    }
}
