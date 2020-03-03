// FPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Compiler.h"
#include "Lexer.h"
#include "SimbolTree.h"

int main(int argc, char* argv[])
{
    std::cout << "Starting compilation!\n";

    SimbolTree tree;

    std::ifstream input;
    input.open("main.fpp");

    std::string code{ std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>() };

    Compiler compiler;
    compiler.Compile(tree);


}