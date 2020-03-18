#include "File.h"

File::File(const std::string& file)
{
	auto line_start = file.begin();
	std::string::const_iterator line_end{};

	size_t i = 0;

	for (auto& c : file)
	{
		if (c == '\n')
		{
			line_end = file.begin() + i;

			lines.emplace_back(line_start, line_end);

			line_start = file.begin() + i + 1;
		}

		++i;
	}
}
