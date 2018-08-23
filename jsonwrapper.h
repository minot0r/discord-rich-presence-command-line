#pragma once
#include "stdafx.h"

using namespace std;

class JSONWrapper {
	public:
		JSONWrapper(string const& file_path);
		void set_actual_file(string const& file);
		string get_file_content();
		void set_file_content(string const& content);
		bool file_exists();
		bool get_json(string const& key, string& var);
		bool get_json(string const& key, bool& var);
		bool get_json(string const& key, int& var);
		bool get_json_array(string const& key, vector<string>& var);
		bool get_json_in_map(string const& map_key, string const& key, string& var);
		//bool get_value_in_json_array(string const& array_key, string const& key, string const& value_key, string& var);
		void set_json(string const& key, string const& value);
		void set_json(string const& key, bool const& value);
		void set_json(string const& key, int const& value);
	private:
		string m_actual_file;
};