#include "stdafx.h"
#include "../Dictionary.h"
#include <string>
#include <iostream>
#include <sstream>

struct DictionaryFixture
{
	CDictionary dictionary;

	void CheckTranslationExists(std::string const & phrase, std::string const & translation)
	{
		BOOST_CHECK(dictionary.HasTranslation(phrase));
		BOOST_CHECK_EQUAL(dictionary.Translate(phrase), translation);
	}
};

BOOST_AUTO_TEST_CASE(converting_to_lowercase_function_is_working)
{
	std::string expectedString = "test  test";
	BOOST_CHECK_EQUAL(ConvertToLowercase("test  test"), expectedString);
	BOOST_CHECK_EQUAL(ConvertToLowercase("test  TEST"), expectedString);
	BOOST_CHECK_EQUAL(ConvertToLowercase("TEST  test"), expectedString);
	BOOST_CHECK_EQUAL(ConvertToLowercase("TEST  TEST"), expectedString);
	BOOST_CHECK_EQUAL(ConvertToLowercase("teST  TEst"), expectedString);
}

BOOST_FIXTURE_TEST_SUITE(Dictionary, DictionaryFixture)
	BOOST_AUTO_TEST_CASE(can_add_new_translation)
	{
		std::string phrase = "test";
		std::string translation = "тест";
		BOOST_CHECK(!dictionary.HasTranslation(phrase));
		dictionary.AddTranslation(phrase, translation);
		CheckTranslationExists(phrase, translation);
	}

	BOOST_AUTO_TEST_CASE(can_load_from_stream)
	{
		BOOST_CHECK(!dictionary.HasTranslation("test phrase"));
		BOOST_CHECK(!dictionary.HasTranslation("next test phrase"));
		const std::string dictionaryString = R"(test phrase
тестовая фраза
next test phrase
следующая тестовая фраза
)";
		std::istringstream istream(dictionaryString);
		BOOST_CHECK(dictionary.Load(istream));
		CheckTranslationExists("test phrase", "тестовая фраза");
		CheckTranslationExists("next test phrase", "следующая тестовая фраза");
	}

	BOOST_AUTO_TEST_CASE(can_correctly_process_load_incorrect_data)
	{
		BOOST_CHECK(!dictionary.HasTranslation("test phrase2"));
		BOOST_CHECK(!dictionary.HasTranslation("next test phrase2"));
		const std::string dictionaryString = R"(test phrase2
тестовая фраза2
next test phrase2
)";
		std::istringstream istream(dictionaryString);
		BOOST_CHECK(!dictionary.Load(istream));
		CheckTranslationExists("test phrase2", "тестовая фраза2");
		BOOST_CHECK(!dictionary.HasTranslation("next test phrase2"));
	}

	BOOST_AUTO_TEST_CASE(can_save_to_stream)
	{
		BOOST_CHECK(!dictionary.HasTranslation("test phrase"));
		BOOST_CHECK(!dictionary.HasTranslation("next test phrase"));
		dictionary.AddTranslation("test phrase", "тестовая фраза");
		dictionary.AddTranslation("next test phrase", "следующая тестовая фраза");
		BOOST_CHECK(dictionary.HasTranslation("test phrase"));
		BOOST_CHECK(dictionary.HasTranslation("next test phrase"));

		std::ostringstream ostream;
		dictionary.Save(ostream);
		const std::string expectedDictionaryContent = R"(next test phrase
следующая тестовая фраза
test phrase
тестовая фраза
)";
		BOOST_CHECK_EQUAL(ostream.str(), expectedDictionaryContent);
	}
BOOST_AUTO_TEST_SUITE_END()