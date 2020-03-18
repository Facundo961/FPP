#pragma once

#include <string>

#include "File.h"
#include "Body.h"

struct LexContext
{
	std::string* string = 0;
	size_t CurrentChar = 0;
};

class Lexer
{
	enum class CharacterType : unsigned char
	{
		Character, Number, Symbol, NewLine, WhiteSpace
	};

	static CharacterType charType(char c)
	{
		switch (c)
		{
		case 'a' | 'A': return CharacterType::Character;
		case 'b' | 'B': return CharacterType::Character;
		case 'c' | 'C': return CharacterType::Character;
		case 'd' | 'D': return CharacterType::Character;
		case 'e' | 'E': return CharacterType::Character;
		case 'f' | 'F': return CharacterType::Character;
		case 'g' | 'G': return CharacterType::Character;
		case 'h' | 'H': return CharacterType::Character;
		case 'i' | 'I': return CharacterType::Character;
		case 'j' | 'J': return CharacterType::Character;
		case 'k' | 'K': return CharacterType::Character;
		case 'l' | 'L': return CharacterType::Character;
		case 'm' | 'M': return CharacterType::Character;
		case 'n' | 'N': return CharacterType::Character;
		case 'o' | 'O': return CharacterType::Character;
		case 'p' | 'P': return CharacterType::Character;
		case 'q' | 'Q': return CharacterType::Character;
		case 'r' | 'R': return CharacterType::Character;
		case 's' | 'S': return CharacterType::Character;
		case 't' | 'T': return CharacterType::Character;
		case 'u' | 'U': return CharacterType::Character;
		case 'v' | 'V': return CharacterType::Character;
		case 'w' | 'W': return CharacterType::Character;
		case 'x' | 'X': return CharacterType::Character;
		case 'y' | 'Y': return CharacterType::Character;
		case 'z' | 'Z': return CharacterType::Character;
		case '0': return CharacterType::Number;
		case '1': return CharacterType::Number;
		case '2': return CharacterType::Number;
		case '3': return CharacterType::Number;
		case '4': return CharacterType::Number;
		case '5': return CharacterType::Number;
		case '6': return CharacterType::Number;
		case '7': return CharacterType::Number;
		case '8': return CharacterType::Number;
		case '9': return CharacterType::Number;
		case '/': return CharacterType::Symbol;
		case ';': return CharacterType::Symbol;
		case '(': return CharacterType::Symbol;
		case ')': return CharacterType::Symbol;
		case '{': return CharacterType::Symbol;
		case '}': return CharacterType::Symbol;
		case '<': return CharacterType::Symbol;
		case '>': return CharacterType::Symbol;
		case '\n': return CharacterType::NewLine;
		case ' ': return CharacterType::WhiteSpace;
		}
	}

	static unsigned long long stringToNumber(const std::string& string)
	{
		unsigned long long i{ 1 };
		unsigned long long result{ 0 };
		unsigned char number{ 0 };
		for (auto& c : string)
		{
			switch (c)
			{
			case '0': number = 0; break;
			case '1': number = 1; break;
			case '2': number = 2; break;
			case '3': number = 3; break;
			case '4': number = 4; break;
			case '5': number = 5; break;
			case '6': number = 6; break;
			case '7': number = 7; break;
			case '8': number = 8; break;
			case '9': number = 9; break;
			}

			result += number * i;

			i *= 10;
		}

		return result;
	}

	void makeSimbolFromCharacterString();
	void makeSimbolFromNumberString();
	void makeSimbolFromSymbolString();

	Lexer();
	void preProcess(FileView& file);
	void stripComments(FileView& file);
	void doIfs(FileView& file);
	void doDefines(FileView& file);

	std::vector<Body*> bodies;
	std::vector<std::string> bodyEntryStrings;
public:
	void Process(class SimbolTree& simbolTree, std::string& string);
};

