// LFInteractive LLC. - All Rights Reserved
#include "FileTypeList.h"

vector<FileType*>* types;

FileTypeList::FileTypeList()
{
	types = new vector<FileType*>();
}

void FileTypeList::add(FileType* type)
{
	auto found = false;
	for (int i = 0; i < types->size(); i++)
	{
		FileType* entry = types->at(i);
		if (entry->extension == type->extension)
		{
			entry->bytes += type->bytes;
			entry->lines += type->lines;
			entry->files += type->files;
			found = true;
			break;
		}
	}
	if (!found)
	{
		types->push_back(type);
	}
}

void FileTypeList::remove(FileType* type)
{
	auto it = std::find(types->begin(), types->end(), type);
	if (it != types->end())
	{
		types->erase(it);
	}
}

void FileTypeList::remove(int index)
{
	types->erase(types->begin() + index);
}

vector<FileType*>* FileTypeList::get()
{
	return types;
}