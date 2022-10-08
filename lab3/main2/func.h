#include <iostream>
#include "../lab3/Header.h"

void dialog();
void invers(Loto& l);
void add();
void dic();
Loto& modific_eq(Loto& l);
void scobs(Loto& l);
void test(int& h, const char* mes);
void put(Loto& l);
std::istream& operator >>(std::istream& in, Loto& l);
void to_int(Loto& l) noexcept;
