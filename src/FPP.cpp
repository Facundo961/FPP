// FPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Compiler.h"
#include "Lexer.h"
#include "SimbolTree.h"
#include "Platform/Win32/EXECreator.h"
#include "Buffer.h"

int main(int argc, char* argv[])
{
    //std::cout << "Starting compilation!\n";
    //
    //SimbolTree tree;
    //
    //std::ifstream input;
    //input.open("main.fpp");
    //
    //std::string Code{ std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>() };
    //
    //Compiler compiler;
    //compiler.Compile(tree);

    //unsigned int null = 0;
	
    std::ofstream exe("test.exe", std::ios::binary);

    Buffer code{60};
    std::vector<unsigned char> data;
	
    EXECreator::CreateEXEInfo create_exe_info;
    create_exe_info.OutputFile = &exe;
    create_exe_info.Code = &code;
    create_exe_info.Data = &data;
    EXECreator::CreateEXE(create_exe_info);

    constexpr unsigned char push8bit = 0x6A;
    constexpr char push16bit = 0x68;
    constexpr unsigned short call = 0xFF15;
	
    ////////////// HEADER ////////////

    code.push_back(push8bit); code.push_back(static_cast<unsigned char>(0)); //push_back 0
    exe << push16bit << short(0x403000); //push_back window name string address
    exe << push16bit << short(0x403017); //push_back window content string address
    exe << push8bit << char(0); //push_back 0
    exe << call << 0x402070; //call MessageBox
    exe << push8bit << char(0); //push_back 0
    exe << call << 0x402068; //call ExitProcess

    exe << 0xBC200000;
    exe << 0;
    exe << 0;
    exe << 0x78200000;
    exe << 0x68200000;
    exe << 0x44200000;
    exe << 0;
    exe << 0;
    exe << 0xB5200000;
    exe << 0x70200000;
    exe << 0;
    exe << 0;
    exe << 0;
    exe << 0;
    exe << 0;
    exe << 0x4C200000;
    exe << 0;
    exe << 0x5A200000;
    exe << 0;
    exe << '0' << '0' << 'E' << 'x' << 'i' << 't' << 'P' << 'r' << 'o' << 'c' << 'e' << 's' << 's' << '0';
    exe << '0' << '0' << 'M' << 'e' << 's' << 's' << 'a' << 'g' << 'e' << 'B' << 'o' << 'x' << 'A' << '0';
    exe << 0x4C200000;
    exe << 0;
    exe << 0x5A200000;
    exe << 0;
    exe << "kernel32.dll";
    exe << "user32.dll";

    exe << "a simple PE executable";
    exe << "Hello world!";
}
