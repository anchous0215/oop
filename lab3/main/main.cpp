#include "../lab3/Header.h"
#include <iostream>
#include "func.h"
#include<vld.h>

int main() {
	int a;
	bool test = 0;
	do {
		const char* mes = "\nEnter number of lines: ";
		get_num(a, mes);
		try {
			Loto loto(a);
			dialog(loto);
			test = 1;
		}
		catch (const std::exception& msg) {
			output(msg.what());
		}
	} while (test == 0);
	
	_CrtDumpMemoryLeaks();
	return 0;
};
