#include "Header.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>

Loto::Loto(int aa) {
	if (aa < 1) {
		throw std::exception("invalid number of lines\n");
	}
	a = aa;
	try {
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
		constexpr int mm = 5;
		Line* tmp = lines;
		int m[mm];
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < mm; j++) {
				m[j] = -1;
			}
			int s;
			for (int j = 0; j < mm; j++) {
				do {
					s = rand() % b;
				} while (check(m, mm, s) == 0);
				m[j] = s;
			}
			for (int j = 0; j < b; j++) {
				if (check(m, mm, j) == 0) {
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

Loto::Loto() noexcept :a(3){
	srand(static_cast<unsigned int>(time(NULL)));
	lines = nullptr;
	for (int i = 0; i < a; i++) {
		Line* line = new Line;
		line->s = i + 1;
		line->next = lines;
		lines = line;
	}
	constexpr int mm = 5;
	Line* tmp = lines;
	int m[mm];
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < mm; j++) {
			m[j] = -1;
		}
		int s;
		for (int j = 0; j < mm; j++) {
			do {
				s = rand() % b;
			} while (check(m, mm, s) == 0);
			m[j] = s;
		}
		for (int j = 0; j < b; j++) {
			if (check(m, mm, j) == 0) {
				do {
					tmp->cells[j].num = rand() % 10 + j * 10;
				} while (tmp->cells[j].num == 0);
			}
		}
		tmp = tmp->next;
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

int Loto::get_cell(int i, int j) const noexcept {
	Line* tmp = lines;
	for (int k = 0; k < i; k++) {
		tmp = tmp->next;
	}
	return (tmp->cells[j].num);
}

int Loto::get_a() const noexcept{
	return a;
}

int Loto::choice(std::istream& inc) const {
	int bb;
	get_num(bb, "Enter number of your bochonok: ");
	if ((in(inc).peek() != '\n') || (bb < 1) || (bb > b * 10)) {
		throw std::exception("invalid number of bochonok\n");
	}
	return bb;
}

int Loto::count(int b) const noexcept{
	int k = 0;
	Line* tmp = lines;
	while (tmp != nullptr) {
		for (int i = 0; i < b; i++) {
			if (tmp->cells[i].num == b) {
				k++;
			}
		}
		tmp = tmp->next;
	}
	return k;
}

bool Loto::empt(int s, int c) const noexcept{
	Line* tmp = lines;
	for (int i = 1; i < s; i++) {
		tmp = tmp->next;
	}
	return(tmp->cells[c - 1].bo);
}

void Loto::set_bochonok(int bb) {
	if ((bb < 1) || (bb > b * 10)) {
		throw std::exception("invalid number of bochonok\n");
	}
	Line* tmp = lines;
	while (tmp != nullptr) {
		for (int i = 0; i < b; i++) {
			if (tmp->cells[i].num == bb) {
				tmp->cells[i].bo = 1;
			}
		}
		tmp = tmp->next;
	}
}

int Loto::full() const noexcept{
	Line* tmp = lines;
	int s = 1;
	while (tmp != nullptr) {
		int k = 0;
		for (int i = 0; i < b; i++) {
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

void Loto::del() noexcept{
	int s;
	while (full() != 0) {
		s = full();
		Line* tmp = lines;
		Line* ptr = lines;
		std::cout << s;
		for (int i = 0; i < s - 1; i++) {
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
		a--;
	}
}

int* Loto::free(int& c) const noexcept{
	const int m = a * b;
	int* mas = new int[m];
	for (int i = 0; i < m; i++) {
		mas[i] = 0;
	}
	Line* tmp = lines;
	int j = 0;
	while (tmp != nullptr) {
		for (int i = 0; i < b; i++) {
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

bool Loto::operator !() noexcept {
	if (full() == 0) {
		return false;
	}
	else {
		return true;
	}
}

Loto Loto::operator +(const Loto& l2) const {
	Loto ll(a + l2.a);
	Line* tmp1 = ll.lines;
	Line* tmp2 = lines;
	while(tmp2 != nullptr) {
		for (int j = 0; j < b; j++) {
			tmp1->cells[j] = tmp2->cells[j];
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	tmp2 = l2.lines;
	for (int i = 0; i < l2.a; i++) {
		for (int j = 0; j < b; j++) {
			tmp1->cells[j] = tmp2->cells[j];
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return ll;
}

Loto& Loto::operator --() noexcept {
	Line* tmp = lines;
	for (int i = 0; i < this->a; i++) {
		for (int j = 0; j < this->b; j++) {
			if (tmp->cells[j].num != 0) {
				tmp->cells[j].num--;
			}
		}
		tmp = tmp->next;
	}
	return *this;
}

Loto Loto::operator --(int d) noexcept {
	Loto temp = *this; output("!");
	Line* tmp = lines;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (tmp->cells[j].num != 0) {
				tmp->cells[j].num--;
			}
		}
		tmp = tmp->next;
	}
	return temp;
}

Cell* Loto::operator [](int s) noexcept {
	Line* tmp = lines;
	for (int i = 0; i < s; i++) {
		tmp = tmp->next;
	}
	return (&tmp->cells[0]);
}

const Cell* Loto::operator [](int s) const noexcept {
	Line* tmp = lines;
	for (int i = 0; i < s; i++) {
		tmp = tmp->next;
	}
	return (&tmp->cells[0]);
}

Loto& Loto:: operator +=(int num) noexcept {
	Line* tmp = lines;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (tmp->cells[j].num != 0) {
				tmp->cells[j].num += num;
			}
		}
		tmp = tmp->next;
	}
	return *this;
}

std::ostream& operator <<(std::ostream& out, const Loto& l) {
	const int a = l.a;
	constexpr int b = l.b;
	Line* tmp = l.lines;
	for (int j = 0; j < a; j++) {
		for (int i = 0; i < b ; i++) {
			if (tmp->cells[i].num == 0) {
				if (i == 0) {
					out << "  ";
				}
				else {
					out << "   ";
				}
			}
			else {
				out << tmp->cells[i].num;
				if (tmp->cells[i].bo != 0) {
					out << "!";
				}
				else {
					out << " ";
				}
			}
			if (i < l.b - 1) {
				out << "|";
			}
		}
		out << "\n";
		tmp = tmp->next;
	}
	return out;
}

bool check(int mas[], int i, int c) {
	for (int j = 0; j < i; j++) {
		if (mas[j] == c) {
			return 0;
		}
	}
	return 1;
}

Loto::Loto(const Loto& l) noexcept {
	a = l.a;
	lines = nullptr;
	for (int i = 0; i < l.a; i++) {
		Line* line = new Line;
		line->s = i + 1;
		line->next = lines;
		lines = line;
	}
	Line* tmp1 = l.lines;
	Line* tmp2 = lines;
	for (int i = 0; i < l.a; i++) {
		for (int j = 0; j < b; j++) {
			tmp2->cells[j] = tmp1->cells[j];
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	output("copy constructor\n");
}

Loto& Loto::operator =(const Loto& l) {
	if (this != &l) {
		Line* tmp1 = lines;
		Line* tmp2 = lines;
		while (tmp2 != nullptr) {
			tmp1 = tmp2;
			tmp2 = tmp2->next;
			delete tmp1;
		}
		lines = nullptr;
		if ((a = l.a) != 0) {
			for (int i = 0; i < l.a; i++) {
				Line* line = new Line;
				line->s = i + 1;
				line->next = lines;
				lines = line;
			}
			Line* tmp1 = l.lines;
			Line* tmp2 = lines;
			for (int i = 0; i < l.a; i++) {
				for (int j = 0; j < b; j++) {
					tmp2->cells[j] = tmp1->cells[j];
				}
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
		}
	}
	output("copy =\n");
	return *this;
}

Loto::Loto(Loto&& l) noexcept : a(l.a), lines(l.lines) {
	l.lines = nullptr;
	output("move conctructor\n");
}

Loto& Loto::operator=(Loto&& l)noexcept{
	if (&l == this) {
		return *this;
	}
	Line* tmp1 = lines;
	Line* tmp2 = lines;
	while (tmp2 != nullptr) {
		tmp1 = tmp2;
		tmp2 = tmp2->next;
		delete tmp1;
	}
	a = l.a;
	lines = l.lines;
	l.lines = nullptr;
	output("move =\n");
	return *this;
}
