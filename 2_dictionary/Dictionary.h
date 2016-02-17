#pragma once
#include <iostream>
#include <string>
#include <map>

class CDictionary
{
public:
	CDictionary();

	bool Load(std::istream & istream);
	void Save(std::ostream & ostream);

	bool HasTranslation(std::string const & phrase) const;
	void AddTranslation(std::string const & phrase, std::string const & translation);
	std::string Translate(std::string const & phrase);

private:
	std::map<std::string, std::string> m_dictionaryMap;

};


std::string ConvertToLowercase(std::string const & phrase);

