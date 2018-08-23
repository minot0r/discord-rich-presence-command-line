#include "stdafx.h"
#include "reset.h"
#include "console.h"

using namespace std;

Reset::Reset() {
	this->m_name = "reset";
	this->m_description = I18n::get_word("cmd_reset_desc");
}

void Reset::run(string input) {
	string answer;
	cout << I18n::get_word("cmd_reset_are_you_sure");
	getline(cin, answer);
	switch (answer.c_str()[0]) {
	case 'y':
		cout << I18n::get_word("cmd_reset_restart") << endl;
		Console::get_config_jsonw().set_file_content("{}");
		getchar();
		exit(0);
		break;
	default:
		break;
	}
}