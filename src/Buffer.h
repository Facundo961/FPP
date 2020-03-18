#pragma once
#include <cstdlib>

class Buffer
{
	unsigned long long offset = 0;
	unsigned char* pointer = nullptr;

public:
	explicit Buffer(const size_t size) : pointer(static_cast<unsigned char*>(malloc(size)))
	{
	}

	~Buffer()
	{
		free(pointer);
	}
	
	void push_back(const unsigned char a)
	{
		pointer[offset] = a;
		offset += 1;
	}

	void push_back(const unsigned short a)
	{
		pointer[offset] = a;
		offset += 2;
	}

	void push_back(const unsigned int a)
	{
		pointer[offset] = a;
		offset += 4;
	}

	unsigned char* data() const { return pointer; }
	size_t size() const { return offset; }
};
