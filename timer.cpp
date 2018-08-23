#include "stdafx.h"
#include "timer.h"
#include "console.h"

using namespace std;

Timer::Timer() {
	this->m_name = "timer";
	this->m_description = I18n::get_word("cmd_timer_desc");
}

void Timer::run(string input) {
	Command::run(input);
	if (Console::get_discord_instance().is_timer_on()) {
		Console::get_discord_instance().toggle_timer(off, 0);
		return;
	}
	cout << ConsoleColors::colorize(LIGHTGRAY) + I18n::get_word("cmd_timer_choose_mode");
	ConsoleColors::reset();
	string chosen_mode;
	getline(cin, chosen_mode);
	if (!(chosen_mode == "start" || chosen_mode == "end")) return;
	if (chosen_mode == "start") {
		Console::get_discord_instance().toggle_timer(start, 0);
	}
	else {
		cout << ConsoleColors::colorize(LIGHTGRAY) + I18n::get_word("cmd_timer_choose_stop");
		ConsoleColors::reset();
		string timer_end;
		getline(cin, timer_end);
		Console::get_discord_instance().toggle_timer(countdown, stoi(timer_end));
	}
}

