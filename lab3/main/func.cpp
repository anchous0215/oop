#include <iostream>
#include "../lab3/Header.h"
#include "func.h"


void test(int& h, const char* mes) {
	bool test = true;
	get_num(h, mes);
	do {
		if (h < 0) {
			test = false;
			output("Please, enter correct choice");
			get_num(h, mes);
		}
		else {
			test = true;
		}
	} while (!test);
}

void dialog(Loto& loto) {
	int dialog = 0;
	do {
		const char* mes = "Enter what do you want make:";
		output(mes);
		out() << std::endl;
		mes = "1 - know number of lines";
		output(mes);
		out() << std::endl;
		mes = "2 - show card";
		output(mes);
		out() << std::endl;
		mes = "3 - check number with number of bochonok";
		output(mes);
		out() << std::endl;
		mes = "4 - check is empty";
		output(mes);
		out() << std::endl;
		mes = "5 - set bochonok";
		output(mes);
		out() << std::endl;
		mes = "6 - know are there full lines";
		output(mes);
		out() << std::endl;
		mes = "7 - delete full lines";
		output(mes);
		out() << std::endl;
		mes = "8 - know empty cells";
		output(mes);
		out() << std::endl;
		mes = "0 - quit";
		output(mes);
		out() << std::endl;
		get_num(dialog, "Enter your choice: ");

		switch (dialog) {
		case 1:
			output(loto.get_a());
			out() << std::endl;
			break;
		case 2:
			loto.show();
			break;
		case 3:
			int b;
			try {
				b = loto.choice();
				out() << std::endl;
				output(loto.count(b));
				out() << std::endl;
			}
			catch (const std::exception& msg) {
				output(msg.what());
			}
			break;
		case 4:
			check(loto);
			break;
		case 5:
			set(loto);
			break;
		case 6:
			if (loto.full() == 0) {
				output("There are not full lines");
			}
			else {
				output("There are full lines");
			}
			out() << std::endl;
			break;
		case 7:
			loto.del();
			break;
		case 8:
			free(loto);
			break;
		}

	} while (dialog != 0);
}

void check(Loto& l) {
	int s, c;
	const char* mes = "Enter the row: ";
	test(s, mes);
	mes = "Enter the column: ";
	test(c, mes);
	bool n = l.empt(s, c);
	if (n == 0) {
		output("Cell is empty");
	}
	else {
		output("Cell isn't empty");
	}
	out() << std::endl;
}

void set(Loto& l) {
	int b;
	get_num(b, "Enter number of your bochonok: ");
	try {
		l.set_b(b);
	}
	catch (const std::exception& msg) {
		output(msg.what());
	}
}

void free(Loto& l) {
	int c = l.get_a() * 9;
	int* m = l.free(c);
	for (int i = 0; i < c; i++) {
		output(m[i]);
		if (i != c - 1) {
			output(", ");
		}
	}
	out() << std::endl;
	delete[] m;
}
