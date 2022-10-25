#include <iostream>
#include "../lab3c/Header.h"
#include "func3.h"

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
		mes = "3 - check count with number of bochonok";
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
		mes = "9 - test unar operator";
		output(mes);
		out() << std::endl;
		mes = "10 - test binar operator";
		output(mes);
		out() << std::endl;
		mes = "11 -  test increment and dicrement";
		output(mes);
		out() << std::endl;
		mes = "12 - test []";
		output(mes);
		out() << std::endl;
		mes = "13 - test modific equal";
		output(mes);
		out() << std::endl;
		mes = "14 - test Loto to int";
		output(mes);
		out() << std::endl;
		mes = "15 - test in";
		output(mes);
		out() << std::endl;
		mes = "16 = check constructors";
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
			out() << loto;
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
		case 9:
			invers(loto);
			break;
		case 10:
			add();
			break;
		case 11:
			dic();
			break;
		case 12:
			scobs(loto);
			break;
		case 13:
			modific_eq(loto);
			output("Finish loto:\n");
			output(loto);
			break;
		case 14:
			to_int(loto);
			break;
		case 15:
			put(loto);
			break;
		case 16:
			prov(loto);
			break;
		default:
		{};
		}
	} while (dialog != 0);
}

void check(Loto& l) {
	int s, c;
	const char* mes = "Enter the row: ";
	do {
		test(s, mes);
	} while (s > l.get_a());
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
		l.set_bochonok(b);
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

void invers(Loto& l) {
	output("This function says have you empty stings or no\n");
	out() << l;
	bool a = !l;
	output(a);
	output("\n");
}

void add() {
	output("This function add first loto to second\n");
	Loto l1;
	output("First loto:\n");
	out() << l1;
	Loto l2;
	output("Second loto:\n");
	out() << l2;
	Loto ll = l1 + l2;
	output("Result loto:\n");
	out() << ll;
}

Loto& modific_eq(Loto& l) {
	output("This function add to each number in loto a number n\n");
	output("Your loto:\n");
	out() << l;
	int n;
	test(n, "Enter your number n: \n");
	l += n;
	return l;
}

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

void dic() {
	output("This function decreas all numbers in loto\n");
	Loto l;
	output("Your loto l:\n");
	out() << l;
	Loto l1 = l;
	Loto r1(--l1);
	output("Result with rl = --l:\n");
	out() << r1;
	output("l:\n");
	out() << l1;
	l1 = l;
	output("Result with rl = l--:\n");
	r1 = l1--;
	out() << r1;
	output("l:\n");
	out() << l1;
}

void scobs(Loto& l) {
	output("This function return string which number you should enter\n");
	const char* mes = "Enter numbrt of your string: ";
	const Loto ll;
	int s = 0;
	out() << ll;
	do {
		test(s, mes);
	} while ((s > ll.get_a()));
	Cell c[9];
	for (int i = 0; i < 9; i++) {
		c[i] = ll[s - 1][i];
		output(c[i].num);
		output(" ");
	}
	output("\n");
	for (int i = 0; i < 9; i++) {
		l[s - 1][i] = c[i];
	}
	out() << l;
}

void put(Loto& l) {
	out() << l;
	output("This function get numbers and put on them bochonki\n at first you shoud enter number od your numbers\n");
	input(l);
	output(l.full());
	output("Result:\n");
	out() << l;
}

std::istream& operator >>(std::istream& in, Loto& l) {
	int n = 0;
	constexpr int m = 50;
	int mas[m];
	input(n, in);
	for (int i = 0; i < n; i++) {
		input(mas[i], in);
		l.set_bochonok(mas[i]);
	}
	return in;
}

void to_int(Loto& l) noexcept {
	output("This function return number of lines of your loto\n");
	out() << l;
	out() << std::endl;
	int a = l;
	output(a);
	out() << std::endl;
}

void prov(Loto& l) {
	Loto l1 = l;
	Loto l2 = l1 + l;
	l2 = l1;
	l2 = l1+l;
}
