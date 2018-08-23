#pragma once
#include "stdafx.h"
#include "command.h"
#include "timermode.h"
#include "include\discord_rpc.h"
#include <time.h>

using namespace std;

class Discord {

	public:

		Discord();
		~Discord();
		void initialize();
		void set_in_party(bool state);
		void set_party_in(int in);
		void set_party_max(int max);
		void set_party_description(string description);
		void set_image(string image);
		void set_image_text(string text);
		void toggle_timer(TimerMode mode, int optional_end);
		void change_id(string new_app_id);
		string get_presence_text();
		bool is_timer_on();
		void send_presence(const string &details);
		void on_command(const string& input);
		void import_config();
		void view_config();

	private:
		string m_app_id = "477569979110391809";
		vector<Command*> commands;
		string m_actual_description;
		string m_party_description;
		string m_actual_image;
		string m_image_text;
		int m_timer_mode;
		int m_timer_end;
		bool m_has_timer = false;
		bool m_has_description = true;
		bool m_is_in_party = false;
		int m_party_in = 1;
		int m_party_max = 4;
		

};