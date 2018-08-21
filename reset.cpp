#include "stdafx.h"
#include "reset.h"
#include "console.h"

using namespace std;

Reset::Reset() {
	this->m_name = "reset";
	this->m_description = "Réinitialise la configuration";
}

void Reset::run(string input) {
	string answer;
	cout << "Etes-vous sur ? (y/n) : ";
	getline(cin, answer);
	switch (answer.c_str()[0]) {
	case 'y':
		JSONWrapper::set_file_content("{}");
		cout << "Vous devez redemarrer ce programme." << endl;
		getline(cin, answer);
		exit(0);
		break;
	default:
		break;
	}
}