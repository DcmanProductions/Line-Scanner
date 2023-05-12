// LFInteractive LLC. - All Rights Reserved
#pragma once
#include "FileType.h"
#include <string>
#include <filesystem>
using std::string;
using std::vector;

namespace fs = std::filesystem;

class Scanner
{
public:
	static vector<FileType*>* scan(string path);
	static vector<FileType*>* scan(string path, string filter);
	static void print(vector<FileType*>* types);
private:
	static void get_files(string path, string filter);
	static FileType* parse_file(fs::path filepath);
	static int get_lines(fs::path filepath);
};
