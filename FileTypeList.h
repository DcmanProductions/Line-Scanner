// LFInteractive LLC. - All Rights Reserved
#pragma once
#include "FileType.h"
#include <vector>
using std::vector;

class FileTypeList
{
public:
	FileTypeList();
	/**
	 * This will add unique types to the vector and combine types with the same extension
	 * @param type - The filetype that should be added
	 */
	void add(FileType* type);
	/**
	 * This will remove item from array
	 * @param type - the filetype to remove
	 */
	void remove(FileType* type);
	/**
	 * This will remove item from array
	 * @param index - the index of the filetype to remove
	 */
	void remove(int index);
	/**
	 * Returns the array of filetypes
	 *
	 * @return the array of filetypes
	 */
	vector<FileType*>* get();
};
