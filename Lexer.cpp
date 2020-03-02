#include "Lexer.h"

#include "SimbolTree.h"
#include "File.h"

void Lexer::preProcess(FileView& file)
{
	stripComments(file);
	doIfs(file);
	doDefines(file);
}

void Lexer::stripComments(FileView& file)
{
	auto a = file.GetCurrentLine().find("//");
	if (a != file.GetCurrentLine().npos)
	{
		file.GetCurrentLine().erase(file.GetCurrentLine().begin() + a, file.GetCurrentLine().end());
	}

	//auto b = file.GetCurrentLine().find("/*");
	//if (b != file.GetCurrentLine().npos)
	//{
	//	file.GetCurrentLine().erase(file.GetCurrentLine().begin() + a, file.GetCurrentLine().end());
	//}
}

void Lexer::Process(SimbolTree& simbolTree, std::string& string)
{
	File file(string);

	FileView file_view(&file);

	preProcess(file_view);

	unsigned long long i{ 0 };

	while(i < string.length())
	{
		switch (charType(string[i]))
		{
		case CharacterType::Character:
			while (charType(string[i]) == CharacterType::Character)
			{
				++i;
			}

			makeSimbolFromCharacterString();

			break;

		case CharacterType::Number:
			while (charType(string[i]) == CharacterType::Number)
			{
				++i;
			}

			makeSimbolFromNumberString();

			break;

		case CharacterType::Symbol:
			while (charType(string[i]) == CharacterType::Symbol)
			{
				++i;
			}

			makeSimbolFromSymbolString();

			break;
		case CharacterType::NewLine: break;
		case CharacterType::WhiteSpace: break;
		}
	}
}
