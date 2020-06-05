#include <iostream>

#include "interpreter.hpp"



int main(int argc, char const *argv[])
{

    Interpreter interpreter = Interpreter();
    //Leemos el Programa
    interpreter.readCode(argv[2]);

    if (*argv[1] == 'R')
    {
        //Ejecutamos el Programa
        interpreter.runCode();
    }
    else if (*argv[1] == 'D')
    {
        //Ejecutamos el Programa en modo Debug
        interpreter.runCodeDebug();
    }

    return 0;
}
