#include "stdafx.h"
#include "command.h"
#include "party.h"
#include "console.h"

using namespace std;

Party::Party() {
	this->m_name = "party";
	this->m_description = I18n::get_word("cmd_party_desc");
	this->m_has_party = false; /* by default in discord.h */
}

void Party::run(string input) {
	Command::run(input);

	if (!this->m_has_party) {
		string party_in;
		cout << ConsoleColors::colorize(LIGHTGRAY) + I18n::get_word("cmd_party_in_text");
		ConsoleColors::reset();
		getline(cin, party_in);

		string party_max;
		cout << ConsoleColors::colorize(LIGHTGRAY) + I18n::get_word("cmd_party_max_text");
		ConsoleColors::reset();
		getline(cin, party_max);

		string party_description;
		cout << ConsoleColors::colorize(LIGHTGRAY) + I18n::get_word("cmd_party_desc_text");
		ConsoleColors::reset();
		getline(cin, party_description);

		Console::get_discord_instance().set_party_in(stoi(party_in));
		Console::get_discord_instance().set_party_max(stoi(party_max));
		Console::get_discord_instance().set_party_description(party_description);
	}

	this->m_has_party = !this->m_has_party;

	Console::get_discord_instance().set_in_party(this->m_has_party);

	Console::get_discord_instance().send_presence(Console::get_discord_instance().get_presence_text());

	/* cannot wrap Console::get_discord_instance() into a variable because it's static */
}

