#include "stdafx.h"
#include "command.h"

using namespace std;

Command::Command() {

}

string Command::get_name() {
	return this->m_name;
}

string Command::get_description() {
	return this->m_description;
}

void Command::run(string input) {
	cout << ConsoleColors::colorize(DARKGRAY) + I18n::get_word("cmd_help");
	cout << ConsoleColors::colorize(LIGHTGRAY) + this->m_description << endl;
	/* calls subclass m_description thanks c++ */
}