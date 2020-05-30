#include <iostream>

#include "interpreter.hpp"

int main(int argc, char const *argv[])
{

    Interpreter interpreter = Interpreter();
    //Leemos el Programa
    interpreter.readCode("../assets/mult.fre");
    ///Datos de entrada Suma
    std::map<std::string, int> dataIn;
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

    std::cout << '\n';
    for (auto i : interpreter.data)
    {
        std::cout << i.first << ": " << i.second << '\n';
    }

    return 0;
}
