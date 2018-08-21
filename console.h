#pragma once

#include "discord.h"

using namespace std;

class Console {
	public:
		Console();
		~Console();
		static Discord& get_discord_instance();
		static string get_drpt_ascii();
};