#pragma once
#include <string>

class Body
{
public:
	virtual std::string GetEnterString() const = 0;
	virtual std::string GetType() const = 0;

	virtual size_t Lex(struct FileView& lexContext) = 0;
};