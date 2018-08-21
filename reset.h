#pragma once

#include "stdafx.h"
#include "command.h"

using namespace std;

class Reset : public Command {

public:
	Reset();
	void run(string input);

};
