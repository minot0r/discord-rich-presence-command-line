#include "stdafx.h"
#include "console.h"
#include "discord.h"
#include "i18n.h"

using namespace std;

JSONWrapper Console::i18n_json_wrapper("config/language.json");
JSONWrapper Console::config_json_wrapper("config/config.json");

Console::Console() {
	ConsoleColors::reset();
	init_i18n();
	init_config();

	this->get_discord_instance().initialize();

	this->get_discord_instance().view_config();
	string input;
	cout << ConsoleColors::colorize(LIGHTGRAY) + "[>] ";
	ConsoleColors::reset();
	while (getline(cin, input)) {
		this->get_discord_instance().on_command(input);
		cout << ConsoleColors::colorize(LIGHTGRAY) + "[>] ";
		ConsoleColors::reset();
	}
}


Console::~Console() {
}

Discord& Console::get_discord_instance() {
	static Discord discord;
	return discord;
}

JSONWrapper & Console::get_i18n_jsonw() {
	return i18n_json_wrapper;
}

JSONWrapper & Console::get_config_jsonw() {
	return config_json_wrapper;
}

string Console::get_drpt_ascii() {
	return
		"/ $$$$$$$  / $$$$$$$  / $$$$$$$ / $$$$$$$$\\\n"
		"| $$__  $$ | $$__  $$ | $$__  $$| __  $$__/\n"
		"| $$  \\ $$ | $$  \\ $$ | $$  \\$$     | $$\n"
		"| $$  | $$ | $$$$$$$/ | $$$$$$$/    | $$\n"
		"| $$  | $$ | $$__  $$ | $$____/     | $$\n"
		"| $$  | $$ | $$  \\ $$ | $$          | $$\n"
		"| $$$$$$$/ | $$ | $$  | $$          | $$\n"
		"| _______/ |__/  |__/ |__/          |__ /";
}

string Console::chosen_lang() {
	string lang;
	config_json_wrapper.get_json("language", lang);
	return lang;
}

void Console::init_i18n() {
	if (!I18n::fetch_languages()) {
		cout << ConsoleColors::colorize(LIGHTRED) << "File language.json not found or empty, try to reinstall DRPT." << endl;
		getchar();
		exit(0);
	}
}

void Console::init_config() {
	bool found;
	string lang;
	found = config_json_wrapper.get_json("language", lang);
	vector<string> languages = I18n::get_supported_languages();

	if (config_json_wrapper.file_exists() && found && find(languages.begin(), languages.end(), lang) != languages.end()) {
		cout << ConsoleColors::colorize(GREEN) << I18n::get_word("file_imported") << endl << endl;
		ConsoleColors::reset();
	}
	else {
		cout << ConsoleColors::colorize(LIGHTRED) << "File config.json is corrupted, or you're using this for the first time." << endl << endl;
		ConsoleColors::reset();
	
		string langs;
		for (unsigned int i = 0; i < languages.size(); i++) {
			if (i == languages.size() - 1) {
				langs += languages[i];
			}
			else {
				langs += languages[i] + ", ";
			}
		}
		string chosen_lang;
		while (!(find(languages.begin(), languages.end(), chosen_lang) != languages.end())) {
			cout << "Choose your language (" << langs << ") : ";
			getline(cin, chosen_lang);
		}

		config_json_wrapper.set_json("language", chosen_lang);
		system("cls");
	}
	get_discord_instance().import_config();
}