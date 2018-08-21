#pragma once

#include "stdafx.h"
#include "command.h"

using namespace std;

class Config : public Command {

public:
	Config();
	void run(string input);

};
