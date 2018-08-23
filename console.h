#pragma once

#include "discord.h"

using namespace std;

class Console {
	public:
		Console();
		~Console();
		static Discord& get_discord_instance();
		static JSONWrapper& get_i18n_jsonw();
		static JSONWrapper& get_config_jsonw();
		static string get_drpt_ascii();
		static string chosen_lang();
	private:
		static void init_i18n();
		static void init_config();
		static JSONWrapper config_json_wrapper;
		static JSONWrapper i18n_json_wrapper;
};