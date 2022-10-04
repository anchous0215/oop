#pragma once
#include <iostream>
#include <sstream>

struct Cell{
	int num = 0;
	bool bo = 0;
};

class Loto {
private:
	int a;
	Cell cells[10][9];
public:
	Loto() noexcept;
	Loto(int a) ;
	int get_a() const noexcept;
	std::ostream& show(std::ostream& out = std::cout) const;
	int choice(std::istream& in = std::cin) const;
	int count(int b) const noexcept;
	bool empt(int s, int c) const noexcept;
	void set_b(int b);
	int full() const noexcept;
	void del();
	int* free(int& c) const;
};

template <class T>
void output(T a, std::ostream& out = std::cout) {
	out << a;
}

template <class T>
void input(T& a, std::istream& in = std::cin) {
	in >> a;
}

inline std::ostream& out (std::ostream& out = std::cout) noexcept{
	return out;
}

inline std::istream& in (std::istream& in = std::cin) noexcept{
	return in;
}

template <class T>
void get_num(T& a, const char* mes) {
	bool test = true;
	while (true) {
		output(mes);
		input(a);
		if (in().peek() == '\n') {
			break;
		}
		else {
			output("You chose incorrect number");
			out() << std::endl;
			in().clear();
			while (in().get() != '\n') {}
		}
	}
}

bool check(const int mas[], int i, int c) noexcept;
