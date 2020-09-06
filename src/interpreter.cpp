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

    //abrimos el codigo
    if (source.is_open())
    {
        //Mientras aun haya lineas por leer 
        while (getline(source, line))
        {
            //Busca los comentarios y salto de linea
            if ((line[0] == '/' && line[1] == '/' )|| !line[0])
                continue;
            
            //Crea una instruccion de cada linae
            tmpInstruct = Instruction(line);

            //Sila instruccion tiene label
            if (tmpInstruct.label != "")
            {
                //Almacena en las labels el ip junto con la etiqueta de la instruccion
                this->labels[tmpInstruct.label] = this->ip;
            }

            //almacena la instruccion con el ip en el que se encuentra
            this->code[this->ip] = tmpInstruct;

            //aumenta el ip
            this->ip++;

            //aumenta el numero de lineas del codigo
            this->lenSource++;
        }

        //cierra el codigo
        source.close();
    }

    else
        std::cout << "Unable to open file";

    return 0;
}

void Interpreter::runInstruction()
{

    Instruction instruction = this->code[this->ip];

    //Si la operacion es el incremento
    if (instruction.operation == "I")
    {
        //Busca la variable y la aumenta
        this->data[instruction.operands[0]] = this->data[instruction.operands[0]] + 1;

        //aumenta el ip
        this->ip++;
    }

    //si la operacion es el decremento
    else if (instruction.operation == "D")
    {
        //si la variable no vale 0
        if (this->data[instruction.operands[0]] != 0)
            //decrementa la variable
            this->data[instruction.operands[0]] = this->data[instruction.operands[0]] - 1;

        //aumenta el ip
        this->ip++;
    }

    //si la instruccion es la asignacion
    else if (instruction.operation == "<-")
    {
        //para cada caracter del los operandos
        for (auto c : instruction.operands[1])
        {
            //busca si la asignacion es de variable a variable
            if (c == '[')
            {
                std::string op;
                //obtiene la varable que se asignara
                for (size_t i = 1; i < instruction.operands[1].size() - 1; i++)
                {
                    op += instruction.operands[1][i];
                }

                //asigna el valor del operando dos al uno
                this->data[instruction.operands[0]] = this->data[op];
                break;
            }
            //si la asignacion es de valor a variable
            else
            {
                //cambia el valor de la variable
                this->data[instruction.operands[0]] = stoi(instruction.operands[1]);
            }
        }
        //aumenta el ip
        this->ip++;
    }
    //si la operacion es salto
    else if (instruction.operation == "G")
    {
        //si el valor de la variable no es cero
        if (this->data[instruction.operands[0]] != 0)
        {
            //cambia el valor del ip
            this->ip = this->labels[instruction.operands[1]];
        }
        else
        {
            //aumenta el ip
            this->ip++;
        }
    }
}

void Interpreter::runCode()
{
    //inicializa el valor del ip
    this->ip = 0;

    //mientras exista una operacion
    while (this->code[this->ip].operation != "")
    {
        //ejecuta la linea
        this->runInstruction();
    }
}

void Interpreter::runCodeDebug()
{
    //coordenada y
    int y = 3;

    //imprime el codigo
    for (auto i : this->code)
    {
        i.second.PrintCode(6, y);
        y++;
    }

    //inicializa el valor de ip
    this->ip = 0;
    
    //mientras exista una operacion
    while (this->code[this->ip].operation != "")
    {
        y = 0;

        //coloca el cursor en pantalla
        gotoxy(30, 3);

        //imprime el ip
        std::cout << "IP: " << this->ip << " ";

        //imprime el valor de ip en cada instruccion
        for (auto i : this->code)
        {
            gotoxy(1, y + 3);
            std::cout<<"  "<<y<< ":";
            y++;
        }

        //imprime un indicador de la instruccion que esta por ejecutarse
        gotoxy(1, this->ip + 3);
        std::cout << ">";
        std::cout << '\n';
        
        //Imprime el segmento de datos
        this->PrintData();

        //ejecuta la instruccion
        this->runInstruction();

        //espera un enter
        std::getchar();
    }
}

void Interpreter::PrintData()
{
    short y = 3;
    short x = 0;

    //Para cada variable del segmento de datos
    for (auto d : this->data)
    {
        //Imprime el valor de la variable
        gotoxy(55 + x * 10, y);
        std::cout << d.first << ": " << d.second;

        y += 2;

        if (y >= 23)
        {
            y = 3;
            x++;
        }
    }
}