#pragma once
#include "stdafx.h"
#include "command.h"

using namespace std;

class Presence : public Command {

	public:
		Presence();
		void run(string input);

}; 
