#pragma once
#include "stdafx.h"
#include "command.h"

using namespace std;

class Party : public Command {

	public:
		Party();
		void run(string input);

	private:
		bool m_has_party;

};
