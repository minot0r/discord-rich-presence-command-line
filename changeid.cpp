#include "stdafx.h"
#include "changeid.h"
#include "console.h"

using namespace std;

ChangeID::ChangeID() {
	this->m_name = "changeid";
	this->m_description = "Permet de changer d'application discord";
}

void ChangeID::run(string input) {
	string new_id;
	cout << ConsoleColors::colorize(LIGHTGRAY) + "Nouvel ID: ";
	ConsoleColors::reset();
	getline(cin, new_id);
	Console::get_discord_instance().change_id(new_id);
}