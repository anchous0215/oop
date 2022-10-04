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
	int m[5];
	for (int i = 0; i < a; i++) {
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
		for (int j = 0; j < 9; j++) {
			if (check(m, 5, j) == 0) {
				do {
					cells[i][j].num = rand() % 10 + j * 10;
				} while (cells[i][j].num == 0);
			}
		}
	}
}

Loto::Loto() noexcept :a(3){
	srand(static_cast<unsigned int>(time(NULL)));
	int m[5];
	for (int i = 0; i < a; i++) {
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
		for (int j = 0; j < 9; j++) {
			if (check(m, 5, j) == 0) {
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
		for (int j = 0; j < 9; j++) {
			if (cells[i][j].num == 0) {
				if (j == 0) {
					out << " ";
				}
				else {
					out << "  ";
				}
			}
			else {
				out << cells[i][j].num;
			}
			if (i < 8) {
				out << "|";
			}
		}
		out << std::endl;
	}
	return out;
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
		for (int i = 0; i < 9; i++) {
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

void Loto::set_b(int b) {
	if ((b < 1) || (b > 90)) {
		throw std::exception("invalid number of bochonok\n");
	}
	for (int j = 0; j < a; j++) {
		for (int i = 0; i < 9; i++) {
			if (cells[j][i].num == b) {
				cells[j][i].bo = 1;
			}
		}
	}
}

int Loto::full() const noexcept{
	int s = 0;
	for (int j = 0; j < a; j++) {
		int k = 0;
		for (int i = 0; i < 9; i++) {
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

void Loto::del() {
	int s;
	while (full() != 0) {
		s = full();
		Cell t;
		for (int i = s; i < a; i++) {
			for(int j = 0; j < 9; j++) {
				t = cells[i][j];
				cells[i][j] = cells[i + 1][j];
				cells[i + 1][j] = t;
			}
		}
		a--;
	}
}

int* Loto::free(int& c) const {
	int* mas = new int[50];
	for (int i = 0; i < 50; i++) {
		mas[i] = 0;
	}
	int k = 0;
	for (int j = 0; j < a; j++) {
		for (int i = 0; i < 9; i++) {
			if ((cells[j][i].num != 0) && (cells[j][i].bo == 0) && (check(mas, 50, cells[j][i].num) != 0)) {
				mas[k] = cells[j][i].num;
				k++;
			}
		}
	}
	c = k;
	return mas;
}

bool check(const int mas[], int i, int c) noexcept{
	for (int j = 0; j < i; j++) {
		if (mas[j] == c) {
			return 0;
		}
	}
	return 1;
}
