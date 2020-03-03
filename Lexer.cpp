#include "Lexer.h"

#include "SimbolTree.h"
#include "File.h"

Lexer::Lexer()
{
	bodies.emplace_back(new ClassBody());
}

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

	while (i < string.length()) //while we have not reached the end of the file
	{
		size_t currentBody = 0;

		{ //look for current body type
			std::vector<size_t> validBodies;

			size_t charsIntoBody = 0;
			size_t bodyStringIndex = 0;

			for (auto& e : bodyEntryStrings) //fill validBodies with the indeces of all bodies that could be
			{
				if (e[0] == string[i])
				{
					validBodies.push_back(bodyStringIndex);
				}

				bodyStringIndex++;
			}

			while(validBodies.size() > 1)//discard all bodies until correct/current one is found
			{
				for (size_t l = 0; l < validBodies.size(); ++l)
				{
					if (bodyEntryStrings[l][charsIntoBody] != string[i])
					{
						validBodies.erase(validBodies.begin() + l);
					}
				}

				charsIntoBody++;
				++i;
			}

			currentBody = validBodies[0];
		}

		i += bodies[currentBody]->Lex(file_view);
	}

}
