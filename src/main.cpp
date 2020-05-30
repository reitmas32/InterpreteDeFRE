#include <iostream>

#include "interpreter.hpp"

int main(int argc, char const *argv[])
{
    
    Interpreter interpreter = Interpreter();

    //Leemos el Programa
    interpreter.readCode("../assets/resta.fre");
    ///Datos de entrada Suma
    std::map<std::string, int> dataIn;
    dataIn["X0"] = 39;
    dataIn["X1"] = 2;
    dataIn["X2"] = 1;
    dataIn["X3"] = 1;
    dataIn["X4"] = 1;

    if (*argv[1] == 'R')
    {
        //Ejecutamos el Programa
        interpreter.runCode(dataIn);
    }
    else if (*argv[1] == 'D')
    {
        //Ejecutamos el Programa en modo Debug
        interpreter.runCodeDebug(dataIn);
    }

    std::cout << '\n';
    for (auto i : interpreter.data)
    {
        std::cout << i.first << ": " << i.second << '\n';
    }

    return 0;
}
