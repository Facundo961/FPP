#pragma once

#include <fstream>
#include <vector>

class EXECreator
{
public:
	struct CreateEXEInfo
	{
		std::ofstream* OutputFile;
		class Buffer* Code = nullptr;
		std::vector<unsigned char>* Data;
	};
	static void CreateEXE(const CreateEXEInfo& createExeInfo);
};
