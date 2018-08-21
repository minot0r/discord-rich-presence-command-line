#include "stdafx.h"
#include "presence.h"
#include "console.h"

using namespace std;

Presence::Presence() {
	this->m_name = "presence";
	this->m_description = "Change la description de DRP (Discord Rich Presence)";
}

void Presence::run(string input) {
	Command::run(input);
	string presence;
	cout << ConsoleColors::colorize(LIGHTGRAY) + "Nouvelle description : ";
	ConsoleColors::reset();
	getline(cin, presence);
	Console::get_discord_instance().send_presence(presence);
}

