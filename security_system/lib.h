#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class environment_descriptor {
private:
	int high;
	int might;
	map <struct coord, class environment_elem&> elements;
public:
	environment_descriptor(int x = 10, int y = 10);
	int* get_size() const noexcept;
	void set_size(int high, int might);
	environment_elem& get_cell(struct coord coords) const;
	int get_cell_type(struct coord c) const noexcept;
	void insert_elem(struct coord c, class environment_elem& elem);
	void del_elem(struct coord c);
	friend class scan_elem;
};

class AI {
private:
	class environment_descriptor desc;
public:
	AI(class environment_descriptor& desc) noexcept;
	void destroy_all_enemy(class environment_descriptor& descriptor);
	void kill_enemy();
	void move_moduls() noexcept;
};

class security_system {
private:
	class environment_descriptor descriptor;
	class AI ai;
public:
	security_system(class environment_descriptor& desc, class AI& ai) noexcept;
};

struct coord {
	int x;
	int y;
	bool operator <(const coord& a) const;
	bool operator ==(const coord& a) const;
};

class environment_elem {
protected:
	struct coord coords = { 0, 0 };
public:
	struct coord get_coords() const noexcept;
	inline void set_coord(struct coord c) noexcept;
	inline virtual int get_val() const noexcept;
	inline virtual void set_desc(environment_descriptor& d) noexcept {};
};

class scan_elem : public environment_elem {
protected:
	class environment_descriptor* desc = nullptr;
public:
	environment_descriptor* get_desc() const;
	inline virtual void set_desc(class environment_descriptor& d) noexcept override;
	virtual void move(struct coord c);
	virtual int get_val() const noexcept = 0;
};

class algoritm {
public:
	static struct coord algor(struct coord c, class environment_descriptor& d) noexcept;
	friend class enemy;
};

class enemy : public scan_elem {
public:
	enemy(class algoritm& al) noexcept;
	static class algoritm alg;
	inline virtual int get_val() const noexcept override;
};

class modul_platform : public scan_elem {
protected:
	string description;
	int empty_slots;
	vector <class modul*> moduls;
public:
	modul_platform(string str = "", int slots = 15);
	vector <class modul*> get_moduls() const noexcept;
	void insert_modul(class modul& m);
	void del_modul(class modul& m) noexcept;
	void scan_kill() noexcept;
	void less_energy() noexcept;
	inline virtual int get_val()  const noexcept override;
	virtual int get_plat() const noexcept = 0;
};

class static_platform : public modul_platform {
private:
	int energy_supply;
public:
	static_platform(int energy = 10, string str = "", int slots = 15);
	virtual void move(struct coord c) override;
	inline virtual int get_plat() const noexcept override;
};

class mobil_platform : public modul_platform {
private:
	int speed;
public:
	mobil_platform(int sp = 2, string str = "", int slots = 15);
	inline virtual int get_plat() const noexcept override;
};

class modul {
protected:
	const int energy_consum;
	bool turn;
	const int slots_count;
	const int radius;
public:
	modul(int cons = 2, bool turn = 1, int slots = 5, int r = 2);
	int get_consum() const noexcept;
	bool get_turn() const noexcept;
	void turn_off() noexcept;
	void turn_on() noexcept;
	inline int get_slots() const noexcept;
	int get_radius() const noexcept;
	virtual void set_platform(class modul_platform& p)  = 0;
	virtual void unset_platform() noexcept = 0;
	virtual int get_type() const noexcept = 0;
	bool operator ==(const modul& a) const noexcept;
};

class coord_modul : public modul {
protected:
	class modul_platform* plat = nullptr;
public:
	coord_modul(int cons = 3, bool turn = 1, int slots = 5, int r = 2);
	modul_platform* get_platform() const noexcept;
	inline virtual void set_platform(class modul_platform& p) override;
	inline virtual void unset_platform() noexcept override;
	virtual vector <class environment_elem*> scan() const;
	virtual void func() const noexcept = 0;
};

class net_modul : public coord_modul {
private:
	int connect;
	int energy_supply;
	vector <class net_modul*> nets;
	vector <class static_platform*> platforms;
	class static_platform* stat_plat = nullptr;
public:
	net_modul(int con = 5, int sup = 10, int cons = 3, bool turn = 1, int slots = 5, int r = 2);
	int get_supply() const noexcept;
	void set_platform(class modul_platform& p) override;
	virtual void unset_platform() noexcept override;
	inline class static_platform* get_stat_plat() const noexcept;
	vector <class net_modul*> update() const noexcept;
	vector <class net_modul*> get_neib_par();
	bool set_conect(class net_modul& m) noexcept;
	bool conection(class net_modul* mod, int count);
	void unset_conect(class net_modul& m) noexcept;
	void unconection(class net_modul* m, int count);
	virtual int get_type() const noexcept override;
	virtual void func() const noexcept override {};
};

class sensor : public coord_modul {
private:
	bool type;
public:
	sensor(bool t = 1, int cons = 3, bool turn = 1, int slots = 5, int r = 2);
	virtual vector <class environment_elem*> scan() const override;
	virtual int get_type() const noexcept override;
	virtual void func() const noexcept override {};
};

class armament :public modul {
private:
	bool energy_type = 0;
	int energy_time;
	int time = 0;
	int energy;
	int normal_consum;
public:
	armament(int time = 3, int norcon = 2, int cons = 3, bool turn = 1, int slots = 5, int r = 2);
	int get_energy_type() const noexcept;
	void energy_on() noexcept;
	void energy_off() noexcept;
	int get_en_time() const noexcept;
	int get_time() const noexcept;
	int set_time(int t);
	int get_energy() const noexcept;
	int set_energy(int e);
	int get_norm_consum() const noexcept;
	void fire(class enemy& enemy) const;
	virtual void set_platform(class modul_platform& p) {};
	virtual void unset_platform() noexcept {};
	virtual int get_type() const noexcept override;
};

bool insize(struct coord c, class environment_descriptor d);
bool inradius(struct coord c1, int rad, struct coord c2);
