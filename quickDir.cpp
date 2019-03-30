#include "quickDir.h"


/*
	Creates an object that will hold information about a directory
	such as the folders and files in it.
*/
quickDir::quickDir(wchar_t* directory)
{
	try
	{
		exists = filesystem::is_directory(directory);
		location = directory;

		if (exists == true)
		{
			update();
		}
	}
	catch (...)
	{
		stringTools::out << "Failed to initialize." << stringTools::lineBreak;
		stringTools::out << "An invalid character may have been used." << stringTools::lineBreak;

	}
}

/*
	This deconstructor does not do anything.
*/
quickDir::~quickDir()
{
	std::wcout << L"Destroying" << L'\n';
}

/*
	Updates all of the references in this object to reflect any changes
	in the directory.
*/
void quickDir::update()
{
	names.clear();
	for (auto& entry: filesystem::directory_iterator(location))
	{
		names.push_back(entry);
	}
}

/*
	Gets the name of a reference at the index if possible.
*/
std::wstring quickDir::getReferenceName(int index)
{
	if (index >= 0 && index < names.size())
	{
		std::wstring temp = getReferenceFullPath(index);

		int pos = temp.find_last_of(L'\\', temp.size());

		return temp.substr(pos + 1, temp.size());
	}
	else
	{
		stringTools::out << "Out of bounds error" << stringTools::lineBreak;
		return L"";
	}
}

std::wstring quickDir::getReferenceFullPath(int index)
{
	if (index >= 0 && index < names.size())
	{
		return names[index].path().c_str();
	}
	else
	{
		stringTools::out << "Out of bounds error" << stringTools::lineBreak;
		return L"";
	}
}

/*
	Gets the file size of a reference at the index if possible.
	Returns an unsigned int.
*/
unsigned int quickDir::fileSize(int index)
{
	if (index >= 0 && index < names.size())
	{
		return filesystem::file_size(names[index]);
	}
	else
	{
		stringTools::out << "Out of bounds error" << stringTools::lineBreak;
		return 0;
	}
	return 0;
}

/*
	Returns a time_t that represents the last time it was changed.
*/
time_t quickDir::getLastChangeTime(int index)
{
	if (index >= 0 && index < names.size())
	{
		auto ftime = filesystem::last_write_time(names[index].path());

		std::time_t t = decltype(ftime)::clock::to_time_t(ftime);

		return t;
	}
	else
	{
		stringTools::out << "Out of bounds error" << stringTools::lineBreak;
		return 0;
	}
}

/*
	Determines if the particular reference at the specified index
	is another directory or not if possible.
*/
bool quickDir::referenceIsDirectory(int index)
{
	if (index >= 0 && index < names.size())
	{
		return filesystem::is_directory( names[index].path() );
	}
	else
	{
		stringTools::out << "Out of bounds error" << stringTools::lineBreak;
		return false;
	}
}

/*
	Renames a resource at the specified location.
	Changes the name to the new name specified.
	The new name should not contain the path.
*/
void quickDir::renameResource(wchar_t * newName, int index)
{
	if (index >= 0 && index < names.size())
	{
		std::wstring temp = getLocation();
		temp += L"\\";
		temp += newName;

		try
		{
			filesystem::rename(names[index], temp);
		}
		catch (...)
		{
			stringTools::out << "Error on Rename" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "Out of bounds error" << stringTools::lineBreak;
	}
}

/*
	Attempts to delete a resource at the specified location.
*/
void quickDir::deleteResource(int index)
{
	if (index >= 0 && index < names.size())
	{
		try
		{
			if (!this->referenceIsDirectory(index))
			{
				filesystem::remove(names[index]); //Just a file
			}
			else
			{
				filesystem::remove_all(names[index]); //A directory
			}
		}
		catch(...)
		{
			stringTools::out << "Error on delete" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "Out of bounds error" << stringTools::lineBreak;
	}
}

/*
	Copies the resource at the specified index to another file 
	with the specified name. The name can contain a path. If the directory
	ends with a / or \, then it will use the current name of the file.
	Otherwise, it will use the name and file extension you specify.
*/
void quickDir::copyResource(wchar_t * newName, int index)
{
	if (index >= 0 && index < names.size())
	{
		std::wstring oth = L"";
		oth += newName;
		
		if (oth.at(oth.size() - 1) == L'\\')
		{
			stringTools::out << "IS FOLDER" << stringTools::lineBreak;
			oth += getReferenceName(index);
		}
		
		try
		{
			filesystem::copy(names[index], oth);
		}
		catch (...)
		{
			stringTools::out << "Error on Copy" << stringTools::lineBreak;
		}
	}
	else
	{
		stringTools::out << "Out of bounds error" << stringTools::lineBreak;
	}
}

/*
	Attempts to get a reference with the specified name.
	Returns -1 if the reference does not exist.
*/
int quickDir::getReferenceLocation(wchar_t * name)
{
	int index = -1;
	for (int i = 0; i < names.size(); i++)
	{
		if ( std::wcscmp(name, getReferenceName(i).c_str() ) == 0 )
		{
			index = i;
			break;
		}
	}

	return index;
}

/*
	Gets the amount of references that are stored in this object.
*/
int quickDir::getSize()
{
	return names.size();
}

/*
	Gets all of the folders in this directory and returns them as
	a vector of wide character pointers.
*/
std::vector<wchar_t*> quickDir::getFolders()
{
	std::vector<wchar_t*> dirs = std::vector<wchar_t*>();

	for (int i = 0; i < getSize(); i++)
	{
		if (referenceIsDirectory(i))
		{
			dirs.push_back((wchar_t*)getReferenceFullPath(i).c_str());
		}
	}

	return dirs;
}

/*
	Gets all of the files in this directory and returns them as
	a vector of wide character pointers.
*/
std::vector<wchar_t*> quickDir::getFiles()
{
	std::vector<wchar_t*> files = std::vector<wchar_t*>();

	for (int i = 0; i < getSize(); i++)
	{
		if (!referenceIsDirectory(i))
		{
			files.push_back((wchar_t*)getReferenceFullPath(i).c_str());
		}
	}

	return files;
}

/*
	Determines whether or not this directory exists.
*/
bool quickDir::doesExist()
{
	return exists;
}

/*
	Creates a directory at this location if it does not exists.
*/
void quickDir::createDirectory()
{
	if(!doesExist())
		filesystem::create_directory(location);
}

/*
	Returns a string that represents the location of the directory
*/
wchar_t* quickDir::getLocation()
{
	return (wchar_t*)location.c_str();
}