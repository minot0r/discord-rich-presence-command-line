#include "stdafx.h"
#include "presence.h"
#include "console.h"

using namespace std;

Presence::Presence() {
	this->m_name = "presence";
	this->m_description = I18n::get_word("cmd_presence_desc");
}

void Presence::run(string input) {
	Command::run(input);
	string presence;
	cout << ConsoleColors::colorize(LIGHTGRAY) + I18n::get_word("cmd_presence_desc_text");
	ConsoleColors::reset();
	getline(cin, presence);
	Console::get_discord_instance().send_presence(presence);
}

