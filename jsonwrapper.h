#pragma once
#include "stdafx.h"

using namespace std;

class JSONWrapper {
	public:
		static string get_file_content();
		static void set_file_content(string const& content);
		static bool file_exists();
		static bool get_json(string const& key, string& var);
		static bool get_json(string const& key, bool& var);
		static bool get_json(string const& key, int& var);
		static void set_json(string const& key, string const& value);
		static void set_json(string const& key, bool const& value);
		static void set_json(string const& key, int const& value);
	private:
		
};