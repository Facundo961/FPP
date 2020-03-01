#include "Lexer.h"

#include "SimbolTree.h"

void Lexer::Process(SimbolTree& simbolTree, std::string& string)
{
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

			break;

		case CharacterType::Number:
			while (charType(string[i]) == CharacterType::Number)
			{
				++i;
			}

			break;

		case CharacterType::Symbol: break;
		case CharacterType::NewLine: break;
		case CharacterType::WhiteSpace: break;
		}
	}
}
