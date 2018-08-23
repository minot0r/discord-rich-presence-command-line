#include "stdafx.h"
#include "i18n.h"
#include "console.h"

using namespace std;

vector<string> I18n::supported_languages({});


bool I18n::fetch_languages() {
	if (!Console::get_i18n_jsonw().file_exists()) return false;
	if (!Console::get_i18n_jsonw().get_json_array("languages", I18n::supported_languages)) return false;
	if (!I18n::supported_languages.size() > 0) return false;
	return true;
}

vector<string> I18n::get_supported_languages() {
	return I18n::supported_languages;
}

string I18n::get_word(string const& id) {
	string word;
	Console::get_i18n_jsonw().get_json_in_map(Console::chosen_lang(), id, word);
	return word;
}


