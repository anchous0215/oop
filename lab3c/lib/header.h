#pragma once
#include <iostream>
#include <sstream>

struct Cell {
	int num = 0;
	bool bo = 0;
};

struct Line {
	static constexpr int b = 9;
	int s;
	Cell cells[b];
	Line* next = nullptr;
};

class Loto {
private:
	static constexpr int b = 9;
	int a;
	Line* lines;
public:
	Loto() noexcept;
	explicit Loto(int a);
	~Loto();
	int get_cell(int i, int j) const noexcept;
	int get_a() const noexcept;
	int choice(std::istream& in = std::cin) const;
	int count(int b) const noexcept;
	bool empt(int s, int c) const noexcept; 
	void set_bochonok(int b);
	int full() const noexcept;
	void del() noexcept;
	int* free(int& c) const noexcept;
	bool operator !() noexcept;
	Loto operator +(const Loto& l1) const;
	Loto& operator --() noexcept;
	Loto operator --(int d) noexcept;
	Cell* operator [](int s) noexcept;
	const Cell* operator [](int s) const noexcept;
	Loto& operator +=(int num) noexcept;
	operator int() const noexcept { return a; };
	friend std::ostream& operator <<(std::ostream& s, const Loto& l);
	Loto(const Loto& l) noexcept;
	Loto& operator =(const Loto& l);
	Loto(Loto&& l) noexcept;
	Loto& operator=(Loto&& l) noexcept;
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
