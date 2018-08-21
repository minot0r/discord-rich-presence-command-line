#pragma once
#include "stdafx.h"
#include "windows.h"

using namespace std;

enum Color {
	BLACK = 0x0,
	BLUE = 0x1,
	GREEN = 0x2,
	CYAN = 0x3,
	RED = 0x4,
	MAGENTA = 0x5,
	BROWN = 0x6,
	LIGHTGRAY = 0x7,
	DARKGRAY = 0x8,
	LIGHTBLUE = 0x9,
	LIGHTGREEN = 0xA,
	LIGHTCYAN = 0xB,
	LIGHTRED = 0xC,
	LIGHTMAGENTA = 0xD,
	YELLOW = 0xE,
	WHITE = 0xF
};

class ConsoleColors {

	public:
		static string colorize(Color color) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
			return "";
		}

		static void reset() {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}

};

