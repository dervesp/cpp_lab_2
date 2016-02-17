// 2_dicitionary.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Dictionary.h"

void loadFromFile(std::string const & filename, CDictionary & dictionary)
{
	std::ifstream file;
	file.open(filename);
	if (file.is_open())
	{
		dictionary.Load(file);
		file.close();
	}
}

bool saveToFile(std::string const & filename, CDictionary & dictionary)
{
	std::ofstream file;
	file.open(filename);
	if (file.is_open())
	{
		dictionary.Save(file);
		file.close();
		return true;
	}
	std::cout << "Error while savin gto file" << std::endl;
	return false;
}

enum class ReaderState
{
	Reading,
	WaitingForTranslate,
	WaitingForSave,
	Exiting
};

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: 2_dictionary <dictionary filename>" << std::endl;
		return 1;
	}

	CDictionary dictionary = CDictionary();
	std::string filename = argv[1];
	loadFromFile(filename, dictionary);

	std::string line;
	std::string phrase;
	bool wasChanges = false;
	ReaderState state = ReaderState::Reading;
	while (state != ReaderState::Exiting && std::getline(std::cin, line))
	{
		switch (state)
		{
		case ReaderState::Reading:
			if (line == "...")
			{
				if (wasChanges)
				{
					std::cout << "Dictionary was changed. Enter Y or y to save changes." << std::endl;
					state = ReaderState::WaitingForSave;
				}
				else
				{
					state = ReaderState::Exiting;
				}
			}
			else if (!dictionary.HasTranslation(line))
			{
				std::cout << "Unknown word \"" << line << "\" Enter translation or empty string to cancel." << std::endl;
				state = ReaderState::WaitingForTranslate;
				phrase = line;
			}
			else
			{
				std::cout << dictionary.Translate(line) << std::endl;
			}
			break;
		case ReaderState::WaitingForTranslate:
			if (!line.empty())
			{
				dictionary.AddTranslation(phrase, line);
				wasChanges = true;
			}
			state = ReaderState::Reading;
			break;
		case ReaderState::WaitingForSave:
			if (line == "Y" || line == "y")
			{
				if (saveToFile(filename, dictionary))
				{
					std::cout << "Changes saved. Goodbye!" << std::endl;
				}
			}
			state = ReaderState::Exiting;
			break;
		}
	}
}

