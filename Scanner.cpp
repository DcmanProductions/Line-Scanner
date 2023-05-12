// LFInteractive LLC. - All Rights Reserved
#include "Scanner.h"
#include <iostream>
#include <fstream>
#include "FileTypeList.h"
#include "Logger.h"
using std::string;
using std::vector;
namespace fs = std::filesystem;

static FileTypeList* types = new FileTypeList();

vector<FileType*>* Scanner::scan(string path)
{
	return Scanner::scan(path, "");
}

vector<FileType*>* Scanner::scan(string path, string filter)
{
	get_files(path, filter);
	return types->get();
}

void Scanner::print(vector<FileType*>* types)
{
	std::sort(types->begin(), types->end(), [](const FileType* a, const FileType* b)
		{
			return a->lines > b->lines;
		});
	for (int i = 0; i < types->size(); i++)
	{
		FileType* type = types->at(i);
		Logger::log.info("Extension: {}", type->extension);
		Logger::log.info("\tFiles: {}", type->files);
		Logger::log.info("\tLines: {}", type->lines);
		Logger::log.info("\tBytes: {}", type->bytes);
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
				types->add(parse_file(entry.path()));
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
	type->extension = filepath.extension().string();
	type->bytes = fs::file_size(filepath);
	type->lines = Scanner::get_lines(filepath);
	type->files = 1;
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