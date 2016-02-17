#include "stdafx.h"
#include "Dictionary.h"
#include "boost/algorithm/string.hpp"


CDictionary::CDictionary()
{
}

bool CDictionary::Load(std::istream & istream)
{
	std::string line, phrase;
	bool firstInPair = true;
	while (std::getline(istream, line))
	{
		if (firstInPair)
		{
			phrase = line;
		}
		else
		{
			AddTranslation(phrase, line);
		}
		firstInPair = !firstInPair;
	}
	return firstInPair;
}

void CDictionary::Save(std::ostream & ostream)
{
	for (auto it = m_dictionaryMap.begin(); it != m_dictionaryMap.end(); ++it)
	{
		ostream << it->first << std::endl;
		ostream << it->second << std::endl;
	}
}

bool CDictionary::HasTranslation(std::string const & phrase) const
{
	bool hasTranslation = m_dictionaryMap.find(ConvertToLowercase(phrase)) != m_dictionaryMap.end();
	return hasTranslation;
}

void CDictionary::AddTranslation(std::string const & phrase, std::string const & translation)
{
	m_dictionaryMap[ConvertToLowercase(phrase)] = translation;
}

std::string CDictionary::Translate(std::string const & phrase)
{
	if (HasTranslation(phrase))
	{
		return m_dictionaryMap[ConvertToLowercase(phrase)];
	}
	throw new std::exception("No translation");
}

std::string ConvertToLowercase(std::string const & phrase)
{
	return boost::algorithm::to_lower_copy(phrase);
}
