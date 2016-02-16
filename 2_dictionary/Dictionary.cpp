#include "stdafx.h"
#include "Dictionary.h"


CDictionary::CDictionary()
{
}

void CDictionary::Load(std::istream & istream)
{
}

void CDictionary::Save(std::ostream & ostream)
{
}

bool CDictionary::HasTranslation(std::string const & phrase) const
{
	bool hasTranslation = m_dictionaryMap.find(phrase) != m_dictionaryMap.end();
	return hasTranslation;
}

bool CDictionary::AddTranslation(std::string const & phrase, std::string const & translation)
{
	if (!HasTranslation(phrase))
	{
		m_dictionaryMap[phrase] = translation;
		return true;
	}
	return false;
}

std::string CDictionary::Translate(std::string const & phrase)
{
	if (HasTranslation(phrase))
	{
		return m_dictionaryMap[phrase];
	}
	throw new std::exception("No translation");
}

std::string TrimAndConvertToLowercase(std::string const & phrase)
{
	return "";
}
