#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class security_system {
private:
	class environment_descriptor descriptor;;
	class AI;
};

class AI {
private:
	class environment_descriptor descriptor;
public:
	void destroy_all_enemy(class environment_descriptor descriptor);
};

class environment_descriptor {
private:
	map <struct coord, class environment_elem> elements;
	int high;
	int might;
public:
	int get_size() const noexcept;
	void set_size(int high, int might);
	class environment_elem get_cell_type() const noexcept;
	void set_cell_type(int high, int might);
};

struct coord {
	int x;
	int y;
};

class environment_elem {
private:
	struct coords;
public:
	int get_x() const noexcept;
	int get_y() const noexcept;
	void set_coords(int x, int y);
};

class enemy : public environment_elem {
private:
	class algoritm algoritm;
public:
	void move_with_algoritm(class algoritm algorithm) noexcept;
};

class algoritm {
private:
	void algor(environment_descriptor descriptor);
	class environment_descriptor descriptor;
};

class modul_platform : public environment_elem {
protected:
	string description;
	int count_slots;
	vector <class modul> moduls;
public:
	void add_modul(class modul);
	void del_modul(class modul);
	virtual void func() = 0;
};

class static_platform : public modul_platform {
private:
	int energy_supply;
};

class mobil_platform : public modul_platform {
private:
	int speed;
public:
	void move();
};

class modul {
protected:
	bool turn;
	int energy_consum;
	int slots_count;
	int radius;
public:
	void turn_off();
	void turn_on();
	virtual void func() = 0;
};

class coord_modul :public modul {
protected:
	class environment_elem elem;
public:
	void func() = 0;
};

class net_modul : public coord_modul {
private:
	int max_conect;
	vector <class net_modul> nets;
	vector <class static_platform> platforms;
	int energy_supply;
public:
	vector <class net_moduls> get_partners(class environment_descriptor descriptor);
	vector <class net_moduls> get_neib_parents(vector <class net_moduls> moduls);
	vector <class net_moduls> send_neib_parents();
	void set_conect(class net_modul);
};

class sensor : public coord_modul {
private:
	bool type;
public:
	class environment_elem info(class environment_descriptor descriptor) const noexcept;
};

class armament :public modul {
private:
	bool energy_type;
	int energy_time;
	bool mode;
public:
	void fire(class enemy enemy);
	void energy_on();
	void energy_off();
};
