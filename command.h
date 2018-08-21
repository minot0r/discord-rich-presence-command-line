#pragma once
#include "stdafx.h"

using namespace std;

class Command {

	public:
		Command();

		string get_name();
		string get_description();
		virtual void run(string input);

	protected:
		string m_name;
		string m_description;

};