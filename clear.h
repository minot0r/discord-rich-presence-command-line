#pragma once

#include "stdafx.h"
#include "command.h"

class Clear : public Command {

public:
	Clear();
	void run(string input);

};
