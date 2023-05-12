// LFInteractive LLC. - All Rights Reserved

/// Default
#include <iostream>
#include "Scanner.h"
int main(int length, char* args[])
{
	if (length > 0)
	{
		vector<FileType*>* files;
		if (length > 1)
		{
			files = Scanner::scan(string(args[0]), string(args[1]));
		}
		else
		{
			files = Scanner::scan(string(args[0]));
		}
		Scanner::print(files);
		return 0;
	}

	return 2;
}