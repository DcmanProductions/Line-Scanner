// LFInteractive LLC. - All Rights Reserved
#include "Scanner.h"
#include "Logger.h"
#include <iostream>
#include <chrono>
#include <cstdlib>

void parse_path(string& path)
{
	if (path.front() == '"' && path.back() == '"')
	{
		path = path.substr(1, path.size() - 2);
	}
}
void parse_arguments(int length, char* args[], vector<string>& arguments)
{
	for (int i = 0; i < length; i++)
	{
		string argument = args[i];
		parse_path(argument);
		arguments.push_back(argument);
	}
}

int main(int length, char* args[])
{
	vector<string> arguments;
	parse_arguments(length, args, arguments);

	string path = "";
	string filter = "";
	if (length > 1)
	{
		path = string(args[1]);
		if (length > 2)
		{
			filter = string(args[2]);
		}
	}
	else
	{
		std::cout << "PATH: ";
		std::getline(std::cin, path);
		parse_path(path);
		std::cout << "FILTER (LEAVE BLANK for NONE): ";
		std::getline(std::cin, filter);
	}

	auto start = std::chrono::high_resolution_clock::now();
	Logger::log.info("Scanning '{}'", path);
	Logger::log.warn("This might take a moment");
	vector<FileType*>* files = Scanner::scan(path, filter);
	Scanner::print(files);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	Logger::log.info("Process finished after {}ms", duration);

#ifdef _WIN32
	std::system("pause");
#else
	std::system("read - p 'Press Enter to continue...' key");
#endif

	return 0;
}