#include "Lexer.h"

#include "SimbolTree.h"

void Lexer::preProcess(std::string& string)
{
	stripComments(string);
	doIfs(string);
	doDefines(string);
}

void Lexer::Process(SimbolTree& simbolTree, std::string& string)
{
	preProcess(string);

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
