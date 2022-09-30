#include "Header.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>

Loto::Loto(int aa) {
	if (aa < 1) {
		throw std::exception("invalid number of lines\n");
	}
	a = aa;
	try{
		srand(static_cast<unsigned int>(time(NULL)));
		lines = new Line;
		lines->s = 1;
		lines->next = nullptr;
		for (int i = 1; i < a; i++) {
			Line* line = new Line;
			line->s = i + 1;
			line->next = lines;
			lines = line;
		}
		Line* tmp = lines;
		int m[5];
		for(int i = 0; i < a; i++) {
			for (int j = 0; j < 5; j++) {
				m[j] = -1;
			}
			int s;
			for (int j = 0; j < 5; j++) {
				do {
					s = rand() % 9;
				} while (check(m, 5, s) == 0);
				m[j] = s;
			}
			for(int j = 0; j < 9; j++) {
				if (check(m, 5, j) == 0) {
					do {
						tmp->cells[j].num = rand() % 10 + j * 10;
					} while (tmp->cells[j].num == 0);
				}
			}
			tmp = tmp->next;
		}
	}
	catch (std::bad_alloc& ba) {
		output("Error, memory allocation problem in constructor\n");
		output(ba.what());
	}
}

Loto::~Loto() {
	Line* tmp1 = lines;
	Line* tmp2 = lines;
	while (tmp2 != nullptr) {
		tmp1 = tmp2;
		tmp2 = tmp2->next;
		delete tmp1;
	}
}

int Loto::get_a() const {
	return a;
}

void Loto::show() const{
	int k = 1;
	Line* tmp = lines;
	while (tmp != nullptr) {
		for (int i = 0; i < 9; i++) {
			if (tmp->cells[i].num == 0) {
				if (i == 0) {
					output(" ");
				}
				else {
					output("  ");
				}
			}
			else {
				output(tmp->cells[i].num);
			}
			if (i < 8) {
				output("|");
			}
		}
		output("\n");
		tmp = tmp->next;
	}
}

int Loto::choice() const {
	int b;
	get_num(b, "Enter number of your bochonok: ");
	if ((b < 1) || (b > 90)) {
		throw std::exception("invalid number of bochonok\n");
	}
	return b;
}

int Loto::count(int b) const{
	int k = 0;
	Line* tmp = lines;
	while (tmp != nullptr) {
		for (int i = 0; i < 9; i++) {
			if (tmp->cells[i].num == b){
				k++;
			}
		}
		tmp = tmp->next;
	}
	return k;
}

bool Loto::empt(int s, int c) const {
	Line* tmp = lines;
	for (int i = 1; i < s; i++) {
		tmp = tmp->next;
	}
	return(tmp->cells[c-1].bo);
}

void Loto::set_b(int b) {
	if ((b < 1) || (b > 90)) {
		throw std::exception("invalid number of bochonok\n");
	}
	Line* tmp = lines;
	while (tmp != nullptr) {
		for (int i = 0; i < 9; i++) {
			if (tmp->cells[i].num == b) {
				tmp->cells[i].bo = 1;
			}
		}
		tmp = tmp->next;
	}
}

int Loto::full() const {
	Line* tmp = lines;
	int s = 1;
	while (tmp != nullptr) {
		int k = 0;
		for (int i = 0; i < 9; i++) {
			if ((tmp->cells[i].num != 0) && (tmp->cells[i].bo != 0)) {
				k++;
			}
		}
		if (k == 5) {
			return (s);
		}
		tmp = tmp->next;
		s++;
	}
	return 0;
}

void Loto::del() {
	int s;
	while (full() != 0) {
		s = full();
		Line* tmp = lines;
		Line* ptr = lines;
		std::cout << s;
		for (int i = 0; i < s-1; i++) {
			ptr = tmp;
			tmp = tmp->next;
		}
		if (lines == tmp) {
			lines = tmp->next;
		}
		else {
			ptr->next = tmp->next;
		}
		delete tmp;
	}
}

int* Loto::free(int& c) const {
	const int m = a * 9;
	int* mas = new int[m];
	for (int i = 0; i < m; i++) {
		mas[i] = 0;
	}
	Line* tmp = lines;
	int j = 0;
	while (tmp != nullptr) {
		for (int i = 0; i < 9; i++) {
			if ((tmp->cells[i].num != 0) && (tmp->cells[i].bo == 0) && (check(mas, m, tmp->cells[i].num) != 0)) {
				mas[j] = tmp->cells[i].num;
				j++;
			}
		}
		tmp = tmp->next;
	}
	c = j;
	return mas;
}

bool check(int mas[], int i, int c) {
	for (int j = 0; j < i; j++) {
		if (mas[j] == c) {
			return 0;
		}
	}
	return 1;
}
