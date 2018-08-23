#include "stdafx.h"
#include "changeid.h"
#include "console.h"

using namespace std;

ChangeID::ChangeID() {
	this->m_name = "changeid";
	this->m_description = I18n::get_word("cmd_change_id_desc");
}

void ChangeID::run(string input) {
	Command::run(input);
	string new_id;
	cout << ConsoleColors::colorize(LIGHTGRAY) + I18n::get_word("cmd_change_id_text");
	ConsoleColors::reset();
	getline(cin, new_id);
	Console::get_discord_instance().change_id(new_id);
}