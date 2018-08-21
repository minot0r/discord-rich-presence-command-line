#include "stdafx.h"
#include "jsonwrapper.h"
#include <fstream>
#include "include\rapidjson\document.h"
#include "include\rapidjson\writer.h"
#include "include\rapidjson\stringbuffer.h"

using namespace std;
using namespace rapidjson;


string JSONWrapper::get_file_content() {
	string line;
	string content("");
	ifstream config_file("config.json");
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
	ofstream config_file("config.json");
	if (config_file.is_open()) {
		config_file << content;
		config_file.close();
	}
}

bool JSONWrapper::file_exists() {
	struct stat buffer;
	return (stat("config.json", &buffer) == 0);
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