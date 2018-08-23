#include "stdafx.h"
#include "console.h"
#include "windows.h"

using namespace std;

void on_exit() {
	cout << "Leaving..." << endl;
	getchar();
	Discord_Shutdown();
}

int main() {
	Console c;
	atexit(on_exit);
	return 0;
}

