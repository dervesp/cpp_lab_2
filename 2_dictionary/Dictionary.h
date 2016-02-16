#pragma once
#include <iostream>;
#include <string>;
#include <map>;

class CDictionary
{
public:
	CDictionary(std::string const & filename);

	void Load();
	void Save();

	bool HasTranslate(std::string const & phrase) const;
	void AddTranslate(std::string const & phrase, std::string const & translation);
	std::string Translate(std::string const & phrase);

private:
	std::string m_filename;
	std::map<std::string, std::string> m_dictionaryMap;

};


std::string TrimAndConvertToLowercase(std::string const & phrase);

