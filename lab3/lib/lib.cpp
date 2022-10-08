#include "Header.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>

Loto::Loto(int aa) {
	if (aa < 1) {
		throw std::exception("invalid number of lines\n");
	}
	a = aa;
	srand(static_cast<unsigned int>(time(NULL)));
	constexpr int mm = 5;
	int m[mm] = {-1, -1, -1, -1, -1};
	for (int i = 0; i < a; i++) {
		int s = 0;
		for (int j = 0; j < mm; j++) {
			do {
				s = rand() % 9;
			} while (check(m, mm, s) == 0);
			m[j] = s;
		}
		for (int j = 0; j < b; j++) {
			if (check(m, mm, j) == 0) {
				do {
					cells[i][j].num = rand() % 10 + j * 10;
				} while (cells[i][j].num == 0);
			}
		}
	}
}

Loto::Loto() noexcept :a(3){
	srand(static_cast<unsigned int>(time(NULL)));
	constexpr int mm = 5;
	int m[mm] = { -1, -1, -1, -1, -1 };
	for (int i = 0; i < a; i++) {
		int s = 0;
		for (int j = 0; j < mm; j++) {
			do {
				s = rand() % 9;
			} while (check(m, 5, s) == 0);
			m[j] = s;
		}
		for (int j = 0; j < b; j++) {
			if (check(m, mm, j) == 0) {
				do {
					cells[i][j].num = rand() % 10 + j * 10;
				} while (cells[i][j].num == 0);
			}
		}
	}
}

int Loto::get_a() const noexcept{
	return a;
}

std::ostream& Loto::show(std::ostream& out) const{
	for (int i = 0; i < a; i++){
		for (int j = 0; j < b; j++) {
			if (cells[i][j].num == 0) {
				if (j == 0) {
					out << "  ";
				}
				else {
					out << "   ";
				}
			}
			else {
				out << cells[i][j].num;
				if (cells[i][j].bo != 0) {
					out<<"!";
				}
				else {
					output(" ");
				}
			}
			if (i < b-1) {
				out << "|";
			}
		}
		out << std::endl;
	}
	return out;
}

int Loto::get_cell(int i, int j) const noexcept {
	return cells[i][j].num;
}

int constexpr Loto::get_b() const noexcept {
	return b;
}

int Loto::choice(std::istream& inc) const {
	int b; 
	inc >> b;
	if ((in(inc).peek() != '\n') || (b < 1) || (b > 90)) {
		throw std::exception("invalid number of bochonok\n");
	}
	return b;
}

int Loto::count(int b) const noexcept{
	int k = 0;
	for (int j = 0; j < a; j++) {
		for (int i = 0; i < b; i++) {
			if (cells[j][i].num == b){
				k++;
			}
		}
	}
	return k;
}

bool Loto::empt(int s, int c) const noexcept{
	return(cells[s-1][c-1].bo);
}

void Loto::set_b(int bb) {
	if ((bb < 1) || (bb > 90)) {
		throw std::exception("invalid number of bochonok\n");
	}
	for (int j = 0; j < a; j++) {
		for (int i = 0; i < b; i++) {
			if (cells[j][i].num == bb) {
				cells[j][i].bo = 1;
			}
		}
	}
}

int Loto::full() const noexcept{
	int s = 0;
	for (int j = 0; j < a; j++) {
		int k = 0;
		for (int i = 0; i < b; i++) {
			if ((cells[j][i].num != 0) && (cells[j][i].bo != 0)) {
				k++;
			}
		}
		if (k == 5) {
			return (s);
		}
		s++;
	}
	return 0;
}

void Loto::del() noexcept{
	int s = 0;
	while (full() != 0) {
		s = full();
		Cell t;
		for (int i = s; i < a; i++) {
			for(int j = 0; j < b; j++) {
				t = cells[i][j];
				cells[i][j] = cells[i + 1][j];
				cells[i + 1][j] = t;
			}
		}
		a--;
	}
}

void Loto::free(int& c, int(&mas)[50]) const noexcept{
	for (int i = 0; i < 50; i++) {
		mas[i] = 0;
	}
	int k = 0;
	for (int j = 0; j < a; j++) {
		for (int i = 0; i < b; i++) {
			if ((cells[j][i].num != 0) && (cells[j][i].bo == 0) && (check(mas, 50, cells[j][i].num) != 0)) {
				mas[k] = cells[j][i].num;
				k++;
			}
		}
	}
	c = k;
}

bool check(const int mas[], int i, int c) noexcept{
	for (int j = 0; j < i; j++) {
		if (mas[j] == c) {
			return 0;
		}
	}
	return 1;
}

Loto& Loto::operator !() noexcept{
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (cells[i][j].num != 0) {
				cells[i][j].bo = !cells[i][j].bo;
			}
		}
	}
	return *this;
}

std::ostream& operator <<(std::ostream& out, const Loto& l){
	const int a = l.a;
	constexpr int b = l.b;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (l.cells[i][j].num == 0) {
				if (j == 0) {
					out << "  ";
				}
				else {
					out << "   ";
				}
			}
			else {
				out << l.cells[i][j].num;
				if (l.empt(i + 1, j + 1) != 0) {
					out << "!";
				}
				else {
					output(" ");
				}
			}
			if (i < b - 1) {
				out << "|";
			}
		}
		out << std::endl;
	}
	return out;
}

Loto& Loto::operator +=(int num) noexcept{
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (cells[i][j].num != 0) {
				cells[i][j].num += num;
			}
		}
	}
	return *this;
}

Loto Loto::operator +(const Loto& l2) {
	Loto ll(a + l2.a);
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			ll.cells[i][j] = cells[i][j];
		}
	}
	for (int i = 0; i < l2.a; i++) {
		for (int j = 0; j < b; j++) {
			ll.cells[i + a][j] = l2.cells[i][j];
		}
	}
	return ll;
}

Loto& Loto::operator --(int d) noexcept {
	Loto temp = *this;
	for (int i = 0; i < this->a; i++) {
		for (int j = 0; j < this->b; j++) {
			if (this->cells[i][j].num != 0) {
				this->cells[i][j].num--;
			}
		}
	}
	return temp;
}

Loto& Loto::operator --() noexcept {
	for (int i = 0; i < this->a; i++) {
		for (int j = 0; j < this->b; j++) {
			if (this->cells[i][j].num != 0) {
				this->cells[i][j].num--;
			}
		}
	}
	return *this;
}
