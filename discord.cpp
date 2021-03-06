#include "stdafx.h"
#include <fstream>
#include "discord.h"
#include "command.h"
#include "presence.h"
#include "party.h"
#include "config.h"
#include "timer.h"
#include "clear.h"
#include "changeid.h"
#include "image.h"
#include "reset.h"
#include "windows.h"
#include "console.h"

using namespace std;

Discord::Discord() {
	cout << Console::get_drpt_ascii() << endl;
	SetConsoleTitle(L"Discord Rich Presence Tool Premium by minot0r#4365 v7");
	this->commands.push_back(new Presence());
	this->commands.push_back(new Party());
	this->commands.push_back(new Config());
	this->commands.push_back(new Timer());
	this->commands.push_back(new Clear());
	this->commands.push_back(new ChangeID());
	this->commands.push_back(new Reset());
	this->commands.push_back(new Image());
}


Discord::~Discord() {
}

void Discord::initialize() {
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));

	Discord_Initialize(this->m_app_id.c_str(), &handlers, 1, nullptr);

	this->send_presence(this->m_actual_description);
}

void Discord::set_in_party(bool state) {
	this->m_is_in_party = state;
	Console::get_config_jsonw().set_json("party", state);
}

void Discord::set_party_in(int in) {
	this->m_party_in = in;
	Console::get_config_jsonw().set_json("party_in", in);
}

void Discord::set_party_max(int max) {
	this->m_party_max = max;
	Console::get_config_jsonw().set_json("party_max", max);
}

void Discord::set_party_description(string description) {
	this->m_party_description = (description == "") ? this->m_party_description : description;
	Console::get_config_jsonw().set_json("party_description", this->m_party_description);
}

void Discord::set_image(string image) {
	this->m_actual_image = image;
	this->send_presence(this->get_presence_text());
	Console::get_config_jsonw().set_json("image", image);
}

void Discord::set_image_text(string text) {
	this->m_image_text = text;
	this->send_presence(this->get_presence_text());
	Console::get_config_jsonw().set_json("image_text", text);
}

void Discord::toggle_timer(TimerMode mode, int optional_end) {
	this->m_has_timer = !this->m_has_timer;
	this->m_timer_mode = mode;
	this->m_timer_end = optional_end;
	this->send_presence(this->get_presence_text());
	Console::get_config_jsonw().set_json("timer", this->m_has_timer);
	Console::get_config_jsonw().set_json("timer_mode", mode);
}

void Discord::change_id(string new_app_id) {
	this->m_app_id = new_app_id;
	Discord_Shutdown();
	this->initialize();
	Console::get_config_jsonw().set_json("application_id", new_app_id);
}

string Discord::get_presence_text() {
	return this->m_actual_description;
}

bool Discord::is_timer_on() {
	return this->m_has_timer;
}

bool Discord::is_default_app_id() {
	return (this->m_app_id == "477569979110391809");
}

void Discord::send_presence(const string &details) {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = details.c_str();
	if (this->m_has_timer && this->m_timer_mode == start) {
		discordPresence.startTimestamp = time(0);
	}
	else if (this->m_has_timer && this->m_timer_mode == countdown) {
		discordPresence.endTimestamp = time(0) + 60 * this->m_timer_end;
	}
	discordPresence.largeImageKey = this->m_actual_image.c_str();
	discordPresence.largeImageText = this->m_image_text.c_str();
	if (this->m_is_in_party) {
		discordPresence.partyId = "1337";
		discordPresence.state = this->m_party_description.c_str();
		discordPresence.partySize = this->m_party_in;
		discordPresence.partyMax = this->m_party_max;
	}
	discordPresence.instance = 1;


	Discord_UpdatePresence(&discordPresence);

	this->m_actual_description = details;
	Console::get_config_jsonw().set_json("presence", details);
	
	//cout << "La présence à été définie en " << details << endl;
}

void Discord::on_command(const string& input) {
	for (int i = 0; i < this->commands.size(); i++) {
		if (input == this->commands[i]->get_name()) {
			this->commands[i]->run(input);
			return;
		}
	}
	cout << I18n::get_word("global_commands") << endl;
}

void Discord::import_config() {
	Console::get_config_jsonw().get_json("application_id", this->m_app_id);

	if (!Console::get_config_jsonw().get_json("presence", this->m_actual_description)) {
		this->m_actual_description = I18n::get_word("global_default_presence");
	}
	Console::get_config_jsonw().get_json("timer", this->m_has_timer);
	Console::get_config_jsonw().get_json("timer_mode", this->m_timer_mode);
	Console::get_config_jsonw().get_json("party", this->m_is_in_party);
	Console::get_config_jsonw().get_json("party_in", this->m_party_in);
	Console::get_config_jsonw().get_json("party_max", this->m_party_max);
	Console::get_config_jsonw().get_json("image", this->m_actual_image);
	Console::get_config_jsonw().get_json("image_text", this->m_image_text);
	if (!Console::get_config_jsonw().get_json("party_description", this->m_party_description)) {
		this->set_party_description(I18n::get_word("global_default_group_text"));
	}
}

void Discord::view_config() {
	cout << I18n::get_word("global_config_timer");
	cout << (this->m_has_timer ? ConsoleColors::colorize(GREEN) + I18n::get_word("global_config_yes") : ConsoleColors::colorize(RED) + I18n::get_word("global_config_no")) << endl;
	ConsoleColors::reset();
	cout << I18n::get_word("global_config_in_group");
	cout << (this->m_is_in_party ? ConsoleColors::colorize(GREEN) + I18n::get_word("global_config_yes") : ConsoleColors::colorize(RED) + I18n::get_word("global_config_no"));
	ConsoleColors::reset();
	cout << I18n::get_word("global_config_group_name");
	cout << ConsoleColors::colorize(LIGHTGRAY) + this->m_party_description << endl;
	ConsoleColors::reset();
	cout << I18n::get_word("global_config_contributors");
	cout << ConsoleColors::colorize(LIGHTGRAY) << this->m_party_in;
	ConsoleColors::reset();
	cout << "/";
	cout << ConsoleColors::colorize(LIGHTGRAY) << this->m_party_max << endl;
	ConsoleColors::reset();
	cout << I18n::get_word("global_config_description");
	cout << ConsoleColors::colorize(MAGENTA) << this->m_actual_description << endl;
	ConsoleColors::reset();
}
