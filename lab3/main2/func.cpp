#include <iostream>
#include "../lab3/Header.h"
#include "func2.h"


void dialog() {
	int dialog = 0;
	Loto l;
	do {
		const char* mes = "Enter what do you want make:";
		output(mes);
		out() << std::endl;
		mes = "1 - test unar operator";
		output(mes);
		out() << std::endl;
		mes = "2 - test binar operator";
		output(mes);
		out() << std::endl;
		mes = "3 -  test increment and dicrement";
		output(mes);
		out() << std::endl;
		mes = "4 - test []";
		output(mes);
		out() << std::endl;
		mes = "5 - test out";
		output(mes);
		out() << std::endl;
		mes = "6 - test modific equal";
		output(mes);
		out() << std::endl;
		mes = "7 - test ?";
		output(mes);
		out() << std::endl;
		mes = "8 = test in";
		output(mes);
		out() << std::endl;
		mes = "0 - quit";
		output(mes);
		out() << std::endl;
		get_num(dialog, "Enter your choice: ");
		switch (dialog) {
		case 1:
			invers(l);
			break;
		case 2:
			add();
			break;
		case 3:
			dic();
			break;
		case 4:
			scobs(l);
			break;
		case 5:
			output(l);
			output("\n");
			l.show();
			break;
		case 6:
			modific_eq(l);
			output("Finish loto:\n");
			output(l);
			break;
		case 7:
			to_int(l);
			break;
		case 8:
			put(l);
			break;
		}

	} while (dialog != 0);
}

void invers(Loto& l) {
	output("This function change empty and busy cells\n");
	output(l);
	const char* mes = "Enter number what you want put or enter 0 to quite: ";
	int ch = 0;
	do {
		get_num(ch, mes);
		try {
			l.set_b(ch);
			output(l);
		}
		catch (const std::exception& msg) {
			output(msg.what());
		}
	} while (ch != 0);
	!l;
	output(l);
}

void add() {
	output("This function add first loto to second\n");
	Loto l1;
	output("First loto:\n");
	output(l1);
	Loto l2;
	output("Second loto:\n");
	output(l2);
	Loto ll = l1 + l2;
	output("Result loto:\n");
	output(ll);
}

Loto& modific_eq(Loto& l) {
	output("This function add to each number in loto a number n\n");
	output("Your loto:\n");
	output(l);
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
	output(l);
	Loto ll = l;
	Loto rl = --ll;
	output("Result with rl = --l:\n");
	output(rl);
	output("l:\n");
	output(ll);
	ll = l;
	output("Result with rl = l--:\n");
	rl = ll--;
	output(rl);
	output("l:\n");
	output(ll);
}

void scobs(Loto& l) {
	output("This function return string? which number you should enter\n");
	const char* mes = "Enter numbrt of your string: ";
	int s = 0;
	output(l);
	do {
		test(s, mes);
	} while ((s > l.get_a()));
	Cell c[9];
	for (int i = 0; i < B; i++) {
		c[i] = l[s-1][i];
		output(c[i].num);
		output(" ");
	}
	output("\n");
}

void put(Loto& l) {
	output(l);
	output("This function get numbers and put on them bochonki\n at first you shoud enter number od your numbers\n");
	input(l);
	output("Result:\n");
	output(l);
}

std::istream& operator >>(std::istream& in, Loto& l) {
	int n = 0;
	constexpr int m = 50;
	int mas[m];
	input(n, in);
	for (int i = 0; i < n; i++) {
		input(mas[i], in);
		l.set_b(mas[i]);
	}
	return in;
}

void to_int(Loto& l) noexcept {
	output("This function return number of lines of your loto\n");
	output(l);
	out() << std::endl;
	int a = l;
	output(a);
	out() << std::endl;
}
