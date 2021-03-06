#include "stdafx.h"
#include "config.h"
#include "console.h"

using namespace std;

Config::Config() {
	this->m_name = "config";
	this->m_description = I18n::get_word("cmd_config_desc");
}

void Config::run(string input) {
	Command::run(input);
	Console::get_discord_instance().view_config();
}

