#include "../lab3c/Header.h"
#include <iostream>
#include "func3.h"
#include<vld.h>

int main() {
	int d;
	bool test = 0;
	do {
		const char* mes = "\nEnter number of lines: ";
		get_num(d, mes);
		try {
			Loto loto(d);
			dialog(loto);
			test = 1;
		}
		catch (const std::exception& msg) {
			output(msg.what());
		}
	} while (test == 0);
	Loto l;
	_CrtDumpMemoryLeaks();
	return 0;
};
