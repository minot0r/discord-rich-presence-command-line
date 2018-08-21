#pragma once
#include "stdafx.h"
#include "command.h"

using namespace std;

class ChangeID : public Command {

public:
	ChangeID();
	void run(string input);

};
