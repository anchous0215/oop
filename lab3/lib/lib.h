#pragma once
#include <iostream>
#include <sstream>

struct Cell{
	int num = 0;
	bool bo = 0;
};

struct Line {
	int s;
	Cell cells[9];
	Line* next = nullptr;
};

class Loto {
private:
	int a;
	Line* lines;
public:
	Loto(int a = 3);
	~Loto();
	int get_a() const;
	void show() const;
	int choice() const;
	int count(int b) const;
	bool empt(int s, int c) const;
	void set_b(int b);
	int full() const;
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

inline std::ostream& out(std::ostream& out = std::cout) {
	return out;
}

inline std::istream& in(std::istream& in = std::cin) {
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

bool check(int mas[], int i, int c);
