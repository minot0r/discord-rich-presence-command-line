#pragma once

#include "stdafx.h"
#include "command.h"

using namespace std;

class Timer : public Command {

public:
	Timer();
	void run(string input);

};