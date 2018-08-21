#include "stdafx.h"
#include "clear.h"
#include "console.h"

using namespace std;

Clear::Clear() {
	this->m_name = "clear";
	this->m_description = "";
}

void Clear::run(string input) {
	Command::run(input);
	system("cls");
}

