#include "stdafx.h"
#include "console.h"
#include "discord.h"

using namespace std;


Console::Console() {
	ConsoleColors::reset();

	if (JSONWrapper::file_exists()) {
		cout << ConsoleColors::colorize(GREEN) << "Fichier config.json trouve. Importation des donnees." << endl << endl;
		ConsoleColors::reset();
	}
	else {
		cout << ConsoleColors::colorize(LIGHTRED) << "Fichier config.json non trouve. Nouveau fichier cree." << endl << endl;
		ConsoleColors::reset();
		JSONWrapper::set_file_content("{}");
	}
	this->get_discord_instance().import_config();

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