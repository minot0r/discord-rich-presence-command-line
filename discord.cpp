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
#include "reset.h"
#include "windows.h"
#include "console.h"

using namespace std;

static void handleDiscordReady(const DiscordUser* connectedUser)
{
	cout << "handle someth" << endl;
	printf("\nDiscord: connected to user %s#%s - %s\n",
		connectedUser->username,
		connectedUser->discriminator,
		connectedUser->userId);
}

static void handleDiscordDisconnected(int errcode, const char* message)
{
	cout << "handle someth" << endl;
	printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}

static void handleDiscordError(int errcode, const char* message)
{
	cout << "handle someth" << endl;
	printf("\nDiscord: error (%d: %s)\n", errcode, message);
}

static void handleDiscordJoin(const char* secret)
{
	cout << "handle someth" << endl;
	printf("\nDiscord: join (%s)\n", secret);
}

static void handleDiscordSpectate(const char* secret)
{
	cout << "handle someth" << endl;
	printf("\nDiscord: spectate (%s)\n", secret);
}

static void handleDiscordJoinRequest(const DiscordUser* request)
{
	cout << "handle someth" << endl;
}


Discord::Discord() {
	cout << Console::get_drpt_ascii() << endl;
	SetConsoleTitle(L"Discord Rich Presence Tool Premium by minot0r#4365 v6");
	this->commands.push_back(new Presence());
	this->commands.push_back(new Party());
	this->commands.push_back(new Config());
	this->commands.push_back(new Timer());
	this->commands.push_back(new Clear());
	this->commands.push_back(new ChangeID());
	this->commands.push_back(new Reset());
}


Discord::~Discord() {
}

void Discord::initialize() {
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = handleDiscordReady;
	handlers.errored = handleDiscordError;
	handlers.disconnected = handleDiscordDisconnected;
	handlers.joinGame = handleDiscordJoin;
	handlers.spectateGame = handleDiscordSpectate;
	handlers.joinRequest = handleDiscordJoinRequest;

	Discord_Initialize(this->m_app_id.c_str(), &handlers, 1, nullptr);

	this->send_presence(this->m_actual_description);
}

void Discord::set_in_party(bool state) {
	this->m_is_in_party = state;
	JSONWrapper::set_json("party", state);
}

void Discord::set_party_in(int in) {
	this->m_party_in = in;
	JSONWrapper::set_json("party_in", in);
}

void Discord::set_party_max(int max) {
	this->m_party_max = max;
	JSONWrapper::set_json("party_max", max);
}

void Discord::set_party_description(string description) {
	this->m_party_description = (description == "") ? this->m_party_description : description;
	JSONWrapper::set_json("party_description", this->m_party_description);
}

void Discord::toggle_timer(TimerMode mode, int optional_end) {
	this->m_has_timer = !this->m_has_timer;
	this->m_timer_mode = mode;
	this->m_timer_end = optional_end;
	this->send_presence(this->get_presence_text());
}

void Discord::change_id(string new_app_id) {
	this->m_app_id = new_app_id;
	Discord_Shutdown();
	this->initialize();
	JSONWrapper::set_json("application_id", new_app_id);
}

string Discord::get_presence_text() {
	return this->m_actual_description;
}

bool Discord::is_timer_on() {
	return this->m_has_timer;
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
	
	if (this->m_is_in_party) {
		discordPresence.partyId = "1337";
		discordPresence.state = this->m_party_description.c_str();
		discordPresence.partySize = this->m_party_in;
		discordPresence.partyMax = this->m_party_max;
	}
	discordPresence.instance = 1;


	Discord_UpdatePresence(&discordPresence);

	this->m_actual_description = details;
	JSONWrapper::set_json("presence", details);
	
	//cout << "La présence à été définie en " << details << endl;
}

void Discord::on_command(const string& input) {
	for (int i = 0; i < this->commands.size(); i++) {
		if (input == this->commands[i]->get_name()) {
			this->commands[i]->run(input);
			return;
		}
	}
	cout << "Les commandes sont: presence, timer, party, changeid, config, clear, reset." << endl;
}

void Discord::import_config() {
	JSONWrapper::get_json("application_id", this->m_app_id);

	if (!JSONWrapper::get_json("presence", this->m_actual_description)) {
		this->m_actual_description = "Outil par minot0r#4365 (premium version)";
	}
	JSONWrapper::get_json("party", this->m_is_in_party);
	JSONWrapper::get_json("party_in", this->m_party_in);
	JSONWrapper::get_json("party_max", this->m_party_max);
	if (!JSONWrapper::get_json("party_description", this->m_party_description)) {
		this->set_party_description("Dans un groupe");
	}
}

void Discord::view_config() {
	cout << "Timer ";
	cout << (this->m_has_timer ? ConsoleColors::colorize(GREEN) + "oui" : ConsoleColors::colorize(RED) + "non") << endl;
	ConsoleColors::reset();
	cout << "En groupe ";
	cout << (this->m_is_in_party ? ConsoleColors::colorize(GREEN) + "oui" : ConsoleColors::colorize(RED) + "non");
	ConsoleColors::reset();
	cout << ", nom : ";
	cout << ConsoleColors::colorize(LIGHTGRAY) + this->m_party_description << endl;
	ConsoleColors::reset();
	cout << "Participants ";
	cout << ConsoleColors::colorize(LIGHTGRAY) << this->m_party_in;
	ConsoleColors::reset();
	cout << "/";
	cout << ConsoleColors::colorize(LIGHTGRAY) << this->m_party_max << endl;
	ConsoleColors::reset();
	cout << "Description : ";
	cout << ConsoleColors::colorize(MAGENTA) << this->m_actual_description << endl;
	ConsoleColors::reset();
}
