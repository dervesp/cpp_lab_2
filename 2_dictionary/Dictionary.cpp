#include "stdafx.h"
#include "Dictionary.h"


CDictionary::CDictionary(std::string const & filename)
	: m_filename(filename)
{
}

void CDictionary::Load()
{
}

void CDictionary::Save()
{
}

bool CDictionary::HasTranslate(std::string const & phrase) const
{
	return false;
}

void CDictionary::AddTranslate(std::string const & phrase, std::string const & translation)
{
}

std::string CDictionary::Translate(std::string const & phrase)
{
	return "";
}

std::string TrimAndConvertToLowercase(std::string const & phrase)
{
	return "";
}
