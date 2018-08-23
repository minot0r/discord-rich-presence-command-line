#include "stdafx.h"
#include "image.h"

Image::Image() {
	this->m_name = "image";
	this->m_description = I18n::get_word("cmd_image_desc");
}

void Image::run(string input) {
	Command::run(input);
	vector<string> allowed = { "dev", "fps", "mmo", "moba", "shrug", "none" };
	string chosen_image;
	cout << I18n::get_word("cmd_image_image");
	getline(cin, chosen_image);
	if (!(find(allowed.begin(), allowed.end(), chosen_image) != allowed.end()) || chosen_image == "none") {
		Console::get_discord_instance().set_image("");
		return;
	}
	else {
		Console::get_discord_instance().set_image(chosen_image);
		string text;
		cout << I18n::get_word("cmd_image_text");
		getline(cin, text);
		Console::get_discord_instance().set_image_text(text);
	}

}