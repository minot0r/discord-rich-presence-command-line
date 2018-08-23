#pragma once
#include "stdafx.h"

using namespace std;

class I18n {

	public:
		static bool fetch_languages();
		static vector<string> get_supported_languages();
		static string get_word(string const& id);
	private:
		static vector<string> supported_languages;

};