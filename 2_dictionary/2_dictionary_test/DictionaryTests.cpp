#include "stdafx.h"
#include "../Dictionary.h"
#include <string>

struct DictionaryFixture
{
	CDictionary dictionary;
};

BOOST_FIXTURE_TEST_SUITE(Dictionary, DictionaryFixture)

	BOOST_AUTO_TEST_CASE(can_save_translation)
	{
		std::string phrase = "test";
		std::string translation = "тест";
		BOOST_CHECK(!dictionary.HasTranslation(phrase));
		BOOST_CHECK(dictionary.AddTranslation(phrase, translation));
		BOOST_CHECK(dictionary.HasTranslation(phrase));
		BOOST_CHECK_EQUAL(dictionary.Translate(phrase), translation);
	}
BOOST_AUTO_TEST_SUITE_END()