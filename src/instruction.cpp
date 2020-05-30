#include <iostream>

#include <instruction.hpp>

Instruction::Instruction(std::string instruction)
{
    this->instruc = instruction;
    std::vector<std::string> codeInstruction = this->decodeInstruction(instruction);

    if (codeInstruction.size() == 2)
    {
        this->var = codeInstruction[0];
        this->operation = codeInstruction[1];
        this->getTypeInstruction();
    }
    else if (codeInstruction.size() == 3)
    {
        if (codeInstruction[1] == "G")
        {
            this->var = codeInstruction[0];
            this->operation = codeInstruction[1];
            this->gotoLabel = codeInstruction[2];
            this->getTypeInstruction();
        }
        else
        {
            this->label = codeInstruction[0];
            this->var = codeInstruction[1];
            this->operation = codeInstruction[2];
            this->getTypeInstruction();
        }
    }
    else if (codeInstruction.size() == 4)
    {
        this->label = codeInstruction[0];
        this->var = codeInstruction[1];
        this->operation = codeInstruction[2];
        this->gotoLabel = codeInstruction[3];
        this->getTypeInstruction();
    }
    else
    {
        std::cout << "Error Instruction: incomplete instruction" << '\n';
    }
}

bool Instruction::getTypeInstruction()
{
    if (this->label == "")
    {
        if (this->operation == "I")
        {
            this->type = Instructions::Inc;
        }
        else if (this->operation == "D")
        {
            this->type = Instructions::Dec;
        }
        else if (this->operation == "G")
        {
            this->type = Instructions::Goto;
        }
        else
        {
            std::cout << "Error Instruction: incomplete instruction" << '\n';
        }
    }
    else
    {
        if (this->operation == "I")
        {
            this->type = Instructions::l_Inc;
        }
        else if (this->operation == "D")
        {
            this->type = Instructions::l_Dec;
        }
        else if (this->operation == "G")
        {
            this->type = Instructions::l_Goto;
        }
        else
        {
            std::cout << "Error Instruction: incomplete instruction" << '\n';
        }
    }
    return true;
}

std::vector<std::string> Instruction::decodeInstruction(std::string instuction)
{
    std::vector<std::string> codeInstruction;
    std::string labelTmp = "";

    codeInstruction.reserve(LEN_INSTUCTION);

    for (auto c : instuction)
    {
        if (c != ' ')
        {
            labelTmp.push_back(c);
        }
        else
        {
            codeInstruction.push_back(labelTmp);
            labelTmp.erase();
        }
    }

    codeInstruction.push_back(labelTmp);
    labelTmp.erase();

    return codeInstruction;
}

void Instruction::Print(){
    std::cout<<"instruction: "<<this->instruc<<'\n';
    std::cout<<"Label: "<<this->label<<'\n';
    std::cout<<"var: "<<this->var<<'\n';
    std::cout<<"operation: "<<this->operation<<'\n';
    std::cout<<"gotoLabel: "<<this->gotoLabel<<'\n';
    std::cout<<'\n';
}