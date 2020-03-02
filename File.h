#pragma once
#include <vector>
#include <string>


class File
{
	std::vector<std::string> lines;

	friend class FileView;
public:
	File(const std::string& file);

	void RemoveLine(const size_t lineIndex)
	{
		lines.erase(lines.begin() + lineIndex);
	}
};

class FileView
{
	File* file = nullptr;
	size_t line = 0;

public:
	FileView(File* file) : file(file)
	{}

	const std::string& GetNextLine()
	{
		auto& result_line = file->lines[line];
		++line;
		return result_line;
	}

	std::string& GetCurrentLine() { return file->lines[line]; }
	const std::string& GetCurrentLine() const { return file->lines[line]; }

	size_t GetLineNumber() const { return line; }

	File* GetFile() const { return file; }
};