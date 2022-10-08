#include "../lab3/Header.h"
#include <iostream>
#include "func2.h"

int main() {
	bool test = 0;
	do {
		try {
			dialog();
			test = 1;
		}
		catch (const std::exception& msg) {
			output(msg.what());
		}
	} while (test == 0);
	return 0;
};
