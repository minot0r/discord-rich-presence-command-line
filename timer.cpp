#include "stdafx.h"
#include "timer.h"
#include "console.h"

using namespace std;

Timer::Timer() {
	this->m_name = "timer";
	this->m_description = "Permet d'activer/desactiver le timer\nMode start: Le timer commence comme un chronomètre\nMode end: Le timer s'arrête a un moment précis";
}

void Timer::run(string input) {
	Command::run(input);
	if (Console::get_discord_instance().is_timer_on()) {
		Console::get_discord_instance().toggle_timer(off, 0);
		return;
	}
	cout << ConsoleColors::colorize(LIGHTGRAY) + "Choisir le mode (start/end) : ";
	ConsoleColors::reset();
	string chosen_mode;
	getline(cin, chosen_mode);
	if (!(chosen_mode == "start" || chosen_mode == "end")) return;
	if (chosen_mode == "start") {
		Console::get_discord_instance().toggle_timer(start, 0);
	}
	else {
		cout << ConsoleColors::colorize(LIGHTGRAY) + "S'arreter dans (min) : ";
		ConsoleColors::reset();
		string timer_end;
		getline(cin, timer_end);
		Console::get_discord_instance().toggle_timer(countdown, stoi(timer_end));
	}
}

