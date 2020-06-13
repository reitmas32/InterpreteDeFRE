InterpreteDeFRE

Para ejecutar el programa si cuenta con MAKE FILE introduzca la siguiente instruccion
make app
cd bin
./app D ../assets/suma.fre
para interactuar con el programa ingrese un enter

Si no cuenta con MAKE FILE ejecute la instruccion
g++ -Wall -std=c++11 -o bin/Dapp src/main.cpp src/interpreter.cpp src/instruction.cpp -L.
cd bin
./app D ../assets/suma.fre
para interactuar con el programa ingrese un enter

los codigos .fre deben ir en la carpeta assets
