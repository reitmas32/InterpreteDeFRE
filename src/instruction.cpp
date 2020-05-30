#include <iostream>

#include <instruction.hpp>

Instruction::Instruction(std::string instruction)
{
    this->code = this->decodeInstruction(instruction);

    uint8_t index = this->find_operator();
    

    if(this->operation == "I" || this->operation == "D"){
        this->operands.emplace_back(this->code[index - 1]);
    }else if(this->operation == "<-" || this->operation == "G")
    {
        this->operands.emplace_back(this->code[index - 1]);
        this->operands.emplace_back(this->code[index + 1]);
    }
    
    if(index > 1 ){
        this->label = this->code[index - 2];
    }

/*
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
    */
}
/*
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
*/
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
    std::cout<<"instruction: ";
    for (std::string i : this->code) { std::cout<< i<<' '; }
    std::cout<<'\n';

    std::cout<<"Label: "<<this->label<<'\n';
    std::cout<<"operation: "<<this->operation<<'\n';
    std::cout<<"operands: ";
    for (std::string i : this->operands) { std::cout<< i<<' '; }
    std::cout<<'\n';

    std::cout<<'\n';
}

uint8_t Instruction::find_operator(){   
    for (std::size_t i = 0; i < this->code.size(); i++)
    {
        std::string op = this->code[i];
        for (std::string op_s : operators)
        {
            if(op == op_s){
                this->operation = op;
                return i;
            }
        }
        
    }
    return 0;
}