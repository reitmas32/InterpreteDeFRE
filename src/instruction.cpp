#include <iostream>

#include "instruction.hpp"

Instruction::Instruction(std::string instruction)
{
    //Decodifica la instruccion 
    this->code = this->decodeInstruction(instruction);

    //Busca que operador tiene la instruccion
    uint8_t index = this->find_operator();
    
    //Si el operador es de incremento o decremento
    //almacenamos el operando anterior en la lista de operandos
    if(this->operation == "I" || this->operation == "D"){
        this->operands.emplace_back(this->code[index - 1]);
    }
    //Si el operador es de asignacion o salto
    //almacenamos el operando anterior y el sigueinte en la lista de operandos
    else if(this->operation == "<-" || this->operation == "G")
    {
        this->operands.emplace_back(this->code[index - 1]);
        this->operands.emplace_back(this->code[index + 1]);
    }
    
    //Si la instruccion tiene etiqueta la almacenamos en label
    if(index > 1 ){
        this->label = this->code[index - 2];
    }

}


std::vector<std::string> Instruction::decodeInstruction(std::string instuction)
{
    std::vector<std::string> codeInstruction;
    std::string labelTmp = "";
    codeInstruction.reserve(LEN_INSTUCTION);

    //para cada caracter de la instruccion
    for (auto c : instuction)
    {
        //Si el caracter no es el ' '
        //significa que no se leyo un atomo de la instruccion completo
        if (c != ' ')
        {
            //Guardamos el c en labelTmp
            labelTmp.push_back(c);
        }
        else
        {
            //Guadomos el atomo en el codigo de la instruccion
            codeInstruction.push_back(labelTmp);

            //Borramos labelTmp
            labelTmp.erase();
        }
    }

    //Guadamos el ultimo atomo
    codeInstruction.push_back(labelTmp);

    //Borramos labelTmp
    labelTmp.erase();

    //REgrsamos el codigo de la instruccion
    return codeInstruction;
}

void Instruction::Print(){
    //Impriminos la instruccion
    std::cout<<"instruction: ";
    for (std::string i : this->code) { std::cout<< i<<' '; }
    std::cout<<'\n';

    //Imprimimos su etiqueta 
    std::cout<<"Label: "<<this->label<<'\n';

    //Imprimimos su operacion
    std::cout<<"operation: "<<this->operation<<'\n';

    //IMprimimos sus operandos
    std::cout<<"operands: ";
    for (std::string i : this->operands) { std::cout<< i<<' '; }
    std::cout<<'\n';

    std::cout<<'\n';
}

uint8_t Instruction::find_operator(){  

    //para cada caracter de la instriccion 
    for (std::size_t i = 0; i < this->code.size(); i++)
    {
        std::string op = this->code[i];
        //Buscamos algun operador de los operandos
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

void Instruction::PrintCode( short x, short y ){
    //Colocamos el cursor en pantalla
    gotoxy(x, y);

    //impimicos el codigo de la instruccion
    for (std::string i : this->code) { std::cout<< i<<' '; }
    std::cout<<'\n';
}