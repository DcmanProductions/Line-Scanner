// LFInteractive LLC. - All Rights Reserved
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

struct File
{
	int lines;
	std::string extension;
	long characters;
	int files;
};

std::vector<File> GetLines(const std::vector<fs::path>& files)
{
	std::cout << "Calculating lines from " << files.size() << " files" << std::endl;
	std::vector<File> lines;
	for (const auto& file : files)
	{
		std::string text;
		std::ifstream ifs(file);
		std::getline(ifs, text, '\0');
		ifs.close();
		std::string extension = file.extension().string();
		auto iter = std::find_if(lines.begin(), lines.end(), [&](const File& f)
			{
				return f.extension == extension;
			});
		int numOfLines = std::count(text.begin(), text.end(), '\n');
		long characters = text.length();
		int numOfFiles = 1;
		if (iter != lines.end())
		{
			numOfLines += iter->lines;
			characters += iter->characters;
			numOfFiles += iter->files;
			lines.erase(iter);
		}
		lines.push_back({ numOfLines, extension, characters, numOfFiles });
	}
	std::sort(lines.begin(), lines.end(), [](const File& f1, const File& f2)
		{
			return f1.lines > f2.lines;
		});
	return lines;
}

int main()
{
	auto time = std::chrono::high_resolution_clock::now();
	std::vector<fs::path> files;
	for (const auto& entry : fs::recursive_directory_iterator(fs::current_path()))
	{
		if (entry.is_regular_file())
		{
			files.push_back(entry.path());
		}
	}
	auto lines = GetLines(files);
	for (const auto& line : lines)
	{
		std::cout << "\033[1;32m" << line.extension << ":\033[0m" << std::endl;
		std::cout << "\033[1;36m\t- " << line.lines << " Line(s)\033[0m" << std::endl;
		std::cout << "\033[1;33m\t- " << line.characters << " Character(s)\033[0m" << std::endl;
		std::cout << "\033[1;35m\t- " << line.files << " File(s)\033[0m" << std::endl;
	}
	auto span = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - time);
	std::cout << "Process finished after " << span.count() << "ms" << std::endl;
	return 0;
}