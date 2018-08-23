#include "stdafx.h"
#include "jsonwrapper.h"
#include <fstream>
#include "include\rapidjson\document.h"
#include "include\rapidjson\writer.h"
#include "include\rapidjson\stringbuffer.h"

using namespace std;
using namespace rapidjson;

JSONWrapper::JSONWrapper(string const& file_path) {
	this->m_actual_file = file_path;
}

void JSONWrapper::set_actual_file(const string& file) {
	this->m_actual_file = file;
}

string JSONWrapper::get_file_content() {
	string line;
	string content("");
	ifstream config_file(this->m_actual_file);
	if (config_file.is_open()) {
		while (getline(config_file, line)) {
			content += line + "\n";
		}
		config_file.close();
	}
	if (content == "") {
		content = "{}";
		JSONWrapper::set_file_content(content);
	}
	return content;
}

void JSONWrapper::set_file_content(string const& content) {
	ofstream config_file(this->m_actual_file);
	if (config_file.is_open()) {
		config_file << content;
		config_file.close();
	}
}

bool JSONWrapper::file_exists() {
	struct stat buffer;
	return (stat(this->m_actual_file.c_str(), &buffer) == 0);
}

bool JSONWrapper::get_json(string const& key, string& var) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());
	
	if (!json[key.c_str()].IsNull()) {
		Value& result = json[key.c_str()];
		var = result.GetString();
		return true;
	}
	return false;
}


bool JSONWrapper::get_json(string const& key, bool& var) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());

	if (!json[key.c_str()].IsNull()) {
		Value& result = json[key.c_str()];
		var = result.GetBool();
		return true;
	}
	return false;
}

bool JSONWrapper::get_json(string const& key, int& var) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());

	if (!json[key.c_str()].IsNull()) {
		Value& result = json[key.c_str()];
		var = result.GetInt();
		return true;
	}
	return false;
}

bool JSONWrapper::get_json_array(string const & key, vector<string>& var) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());

	if (!json[key.c_str()].IsNull()) {
		Value& result = json[key.c_str()];
		for (SizeType i = 0; i < result.Size(); i++)
			var.push_back(result[i].GetString());
		
		return true;
	}
	return false;
}

bool JSONWrapper::get_json_in_map(string const& map_key, string const& key, string& var) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());

	if (!json[map_key.c_str()][key.c_str()].IsNull()) {
		Value& result = json[map_key.c_str()][key.c_str()];
		var = result.GetString();
		return true;
	}
	return false;
}

/*bool JSONWrapper::get_value_in_json_array(string const & array_key, string const & key, string const & value_key, string & var) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());

	if (!json[array_key.c_str()].IsNull()) {
		Value& json_array = json[array_key.c_str()];
		for (SizeType i = 0; i < json_array.Size(); i++)
			if (json_array[i].GetString() == key) {
				Value& result = json_array[value_key.c_str()];
				var = result.GetString();
				return true;
			}
		return false;
		
	}
	return false;
}*/

void JSONWrapper::set_json(string const& key, string const& value) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());

	
	if (json[key.c_str()].IsNull()) {
		json.AddMember(StringRef(key.c_str()), StringRef(value.c_str()), json.GetAllocator());
	}
	else {
		Value& set = json[key.c_str()];
		set.SetString(StringRef(value.c_str()));
	}
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	json.Accept(writer);
	set_file_content(buffer.GetString());
}

void JSONWrapper::set_json(string const& key, bool const& value) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());


	if (json[key.c_str()].IsNull()) {
		json.AddMember(StringRef(key.c_str()), value, json.GetAllocator());
	}
	else {
		Value& set = json[key.c_str()];
		set.SetBool(value);
	}
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	json.Accept(writer);
	set_file_content(buffer.GetString());
}

void JSONWrapper::set_json(string const& key, int const& value) {
	string content = get_file_content();
	Document json;
	json.Parse(content.c_str());


	if (json[key.c_str()].IsNull()) {
		json.AddMember(StringRef(key.c_str()), value, json.GetAllocator());
	}
	else {
		Value& set = json[key.c_str()];
		set.SetInt(value);
	}
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	json.Accept(writer);
	set_file_content(buffer.GetString());
}