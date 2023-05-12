// LFInteractive LLC. - All Rights Reserved
#include "Scanner.h"
#include <iostream>
#include <fstream>
namespace fs = std::filesystem;

using std::string;
using std::vector;

static vector<FileType*>* types;

vector<FileType*>* Scanner::scan(string path)
{
	return Scanner::scan(path, "");
}

vector<FileType*>* Scanner::scan(string path, string filter)
{
	get_files(path, filter);
	return types;
}

void Scanner::print(vector<FileType*>* types)
{
	for (int i = 0; i < types->size(); i++)
	{
		FileType* type = types->at(i);
	}
}

void Scanner::get_files(string path, string filter)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (fs::is_regular_file(entry.path()))
		{
			if (filter.empty() || entry.path().extension().string() == filter)
			{
				types->push_back(parse_file(entry.path()));
			}
		}
		else if (fs::is_directory(entry.path()))
		{
			get_files(entry.path().string(), filter);
		}
	}
}

FileType* Scanner::parse_file(fs::path filepath)
{
	auto type = new FileType();
	type->path = filepath.string();
	type->name = filepath.filename().string();
	type->extension = filepath.extension().string();
	type->bytes = fs::file_size(filepath);
	type->lines = Scanner::get_lines(filepath);
	return type;
}

int Scanner::get_lines(fs::path filepath)
{
	std::ifstream file(filepath);
	if (file)
	{
		int count = 0;
		std::string line;
		while (std::getline(file, line))
		{
			count++;
		}
		return count;
	}
	return 0;
}