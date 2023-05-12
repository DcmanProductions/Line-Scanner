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
	/**
	 * This scans through all files and subdirectories in a path
	 *
	 * @param path This is the starting path of the scan
	 */
	static vector<FileType*>* scan(string path);
	/**
	 * This scans through all files and subdirectories in a path with a filter
	 *
	 * @param path This is the starting path of the scan
	 * @param filter This will filter the results by the extension
	 */
	static vector<FileType*>* scan(string path, string filter);
	/**
	 * This will print the values of the FileTypes to the console using spdlog
	 *
	 * @param types This is the array of types
	 */
	static void print(vector<FileType*>* types);
private:
	static void get_files(string path, string filter);
	static FileType* parse_file(fs::path filepath);
	static int get_lines(fs::path filepath);
};
