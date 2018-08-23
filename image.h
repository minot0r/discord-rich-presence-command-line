#pragma once

#include "stdafx.h"
#include "command.h"

class Image : public Command {

public:
	Image();
	void run(string input);

};