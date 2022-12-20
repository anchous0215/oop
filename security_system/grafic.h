#include <SFML/Graphics.hpp>
#include "../security_system/Header.h"
#include <string>
using namespace sf;
#pragma warning(disable : 4996)


template <class T>
void output(T a, std::ostream& out = std::cout) {
    out << a;
}

template <class T>
void input(T& a, std::istream& in = std::cin) {
    in >> a;
}

inline std::ostream& out(std::ostream& out = std::cout) noexcept {
    return out;
}

inline std::istream& in(std::istream& in = std::cin) noexcept {
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

template <class T>
void test(T& h, const char* mes, int high, int less) {
    bool test = true;
    get_num(h, mes);
    do {
        if ((h < less) || (h > high)) {
            test = false;
            output("Please, enter correct choice\n");
            get_num(h, mes);
        }
        else {
            test = true;
        }
    } while (!test);
}

environment_descriptor get_size() {
    int x, y;
    test(x, "Enter might of descriptor: ", 100, 1);
    test(y, "Enter high of descriptor: ", 100, 1);
    environment_descriptor d(x, y);
    return d;
}

void get_lets(environment_descriptor& d, int x, int y) {
    srand(static_cast<unsigned int>(time(NULL)));
    int count = d.get_size()[0] * d.get_size()[1];
    for (int i = 0; i < x*y/5; i++) {
        int k = 0;
        environment_elem* e = new environment_elem;
        while (k != 1) {
            int x = rand() % d.get_size()[0] + 1;
            int y = rand() % d.get_size()[1] + 1;
            if (d.get_cell_type({ x, y }) == ' ') {
                d.insert_elem({ x, y }, *e);
                k = 1;
            }
        }
    }
}


void set_moduls(modul_platform* mod, int type) {
    net_modul* net = new net_modul;
    sensor* sens = new sensor(type, 3, 1, 5, 1);
    armament* ar = new armament(3, 2, 3, 1, 5, 1);
    mod->insert_modul(*net);
    mod->insert_modul(*sens);
    mod->insert_modul(*ar);
}

int get_platforms(environment_descriptor& d, int x, int y) {
    srand(static_cast<unsigned int>(time(NULL)));
    int count = d.get_size()[0] * d.get_size()[1] / 3;
    for (int i = 0; i < x*y/30; i++) {
        int k = 0;
        static_platform* e = new static_platform;
        while (k != 1) {
            int x = rand() % d.get_size()[0] + 1;
            int y = rand() % d.get_size()[1] + 1;
            if (d.get_cell_type({ x, y }) == ' ') {
                d.insert_elem({ x, y }, *e);
                set_moduls(e, 1);
                k = 1;
            }
        }
    }
    for (int i = 0; i < x*y/30; i++) {
        srand(static_cast<unsigned int>(time(NULL)));
        int k = 0;
        mobil_platform* e = new mobil_platform;
        while (k != 1) {
            int x = rand() % d.get_size()[0] + 1;
            int y = rand() % d.get_size()[1] + 1;
            if (d.get_cell_type({ x, y }) == ' ') {
               d.insert_elem({ x, y }, *e);
                 set_moduls(e, 1);
                k = 1;
            }
        }
    }
    return x*y/20;
}

void set_enemy(environment_descriptor& d, int count) {
    srand(static_cast<unsigned int>(time(NULL)));
    algoritm a;
    for (int i = 0; i < count; i++) {
      int k = 0;
        enemy* e = new enemy(a);
          while (k != 1) {
            int x = rand() % d.get_size()[0] + 1;
            int y = rand() % d.get_size()[1] + 1;
            if (d.get_cell_type({ x, y }) == ' ') {
                d.insert_elem({ x, y }, *e);
                k = 1;
            }
        }
    }
}

void erase(environment_descriptor& d) {
    for (int i = 1; i <= d.get_size()[0]; i++) {
        for (int j = 1; j <= d.get_size()[1]; j++) {
            if (d.get_cell_type({ i, j }) != ' ') {
                if ((d.get_cell_type({ i, j }) == 's') || (d.get_cell_type({ i, j }) == 'm')) {
                    modul_platform* plat = static_cast <modul_platform*>(d.get_cell({ i, j }));
                    for (auto i : plat->get_moduls()) {
                        delete i;
                    }
                }
                delete d.get_cell({ i, j });
            }
        }
    }
}
