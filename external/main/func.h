#include"Header.h"
#include <string>
using namespace std;

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

void menu();
void persons_create();
Train create_train();
void set_from_wher(Train& tr);
void change_train(Train & tr);
void change(Train& tr);
void change_from(Train& tr);
void change_where(Train& tr);
void reserved_seats(Train& tr);
void add_carriage(Train& tr);
Carriage create_carriage();
void change_carriage(Train& tr);
void delete_carriages(Train& tr);
void chose_seats();
void generate_trains(Train* trains);
Train chose_train(Train* trains);
Carriage chose_carriage(Train& tr);
void information(Train& tr, Carriage& car);
void chose_cities(Train* trains);
void agregate_carriages(Train* trains);
string chose_from(Train* trains);
string chose_wher(Train* trains, string from);
bool check(const int mas[], int lenght, int num);
void agregate_lenght(Train* trains);
Train chose_directions(Train* trains);
bool check_full(Train& tr);
