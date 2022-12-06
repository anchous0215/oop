#pragma once
#include <iostream>
#include <map>
#include "Vector.h"
#include <vector>
#include <string>
using namespace std;

/// @brief envirenment descriptor, save size and elements
class environment_descriptor {
private:
	int high;
	int might;
	///@brief map environment elements
	map <struct coord, class environment_elem&> elements;
public:
	/**
	* @brief кconstructor for environment descriptor
	* @param x - weight
	* @param y - high
	*/
	environment_descriptor(int x = 10, int y = 10);
	///@brief getter for size of environment descriptor
	int* get_size() const noexcept;
	/**
	* @brief setter for size of environment descriptor
	* @param x - weight
	* @param y - high
	*/
	void set_size(int high, int might);
	/**
	* @brief get environment element
	* @param coords - coordinats of element
	*/
	environment_elem& get_cell(struct coord coords) const;
	/**
	* @brief get type of element
	* @param c - coordinats of element
	*/
	char get_cell_type(struct coord c) const noexcept;
	/**
	* @brief insert element in descriptor
	* @param c - coordinats of element
	* @param elem  - element
	*/
	void insert_elem(struct coord c, class environment_elem& elem);
	/**
	* @brief delete elemet from descriptor
	* @param c - coordinats of element
	*/
	void del_elem(struct coord c);
	/**
	* @brief output operator for environment descriptor
	* @param s - output stream
	* @param l - environment descriptor
	*/
	friend std::ostream& operator <<(std::ostream& s, const environment_descriptor& l);
	friend class scan_elem;
};

///@brief strust for soordinats
struct coord {
	int x;
	int y;
	bool operator <(const coord& a) const;
	bool operator ==(const coord& a) const;
	bool operator !=(const coord& a) const;
};

///@brief Artificial intelligence which maganes modules
class AI {
private:
	class environment_descriptor* desc;
public:
	/**
	* @brief constructor for AI
	* @param desc - environment descriptor
	*/
	AI(class environment_descriptor* desc) noexcept;
	/**
	* @brief find and kill enemies
	*/
	void destroy_all_enemy();
	/**
	* @brief kill enemies
	* @param desc - environment descriptor
	*/
	void kill_enemy();
	void move_moduls() noexcept;
	/**
	* @brief get coordinates in which moduls shoud move
	* @param m - modul ehich will move
	*/
	struct coord move_in(class mobil_platform& m) noexcept;
};

///@brief class which save the AI and manages the environment descriptor
class security_system {
private:
	class environment_descriptor* descriptor;
	class AI* ai;
public:
	/**
	* @brief constructor for security system
	* @param desc - environment descriptor
	* @param ai - AI
	*/
	security_system(class environment_descriptor* desc, class AI* ai) noexcept;
	/**
	* @brief start the work of programm
	*/
	void work() noexcept;
	/**
	* @brief move all enemies
	*/
	void move_enemy() noexcept;
	/**
	* @brief check if enemies in the enveronment descriptor
	*/
	int check() noexcept;
};

///@brief parent class for all elements in environment descriptor and it is simple let
class environment_elem {
protected:
	struct coord coords = { 0, 0 };
public:
	/**
	* @brief getter for coordinates of element
	*/
	struct coord get_coords() const noexcept;
	/**
	* @brief setter for coordinates of element
	* @param c - coordinates
	*/
	inline void set_coord(struct coord c) noexcept;
	/**
	* @brief get type of element, for let return 1
	* @param c - coordinates
	*/
	inline virtual int get_val() const noexcept;
	/**
	* @brief virtal function for assigment the environment descriptor for element. Here it do nothing
	* @param c - coordinates
	*/
	inline virtual void set_desc(environment_descriptor& d) noexcept {};
};

///@brief class for element which can see the environment descriptor and move
class scan_elem : public environment_elem {
protected:
	class environment_descriptor* desc = nullptr;
public:
	/**
	* @brief get the environment descriptor of element
	*/
	environment_descriptor* get_desc() const;
	/**
	* @brief set the environment descriptor of element
	*/
	inline virtual void set_desc(class environment_descriptor& d) noexcept override;
	/**
	* @brief move element in certain coordinates
	* @param c - coordinates
	*/
	virtual void move(struct coord c);
	virtual int get_val() const noexcept = 0;
};

///@brief algorithm for move of enemy
class algoritm {
public:
	/**
	* @brief algorithm for move
	* @param c - coordinates of enemy
	* @param c - environment descriptor of enemy
	*/
	static struct coord algor(struct coord c, class environment_descriptor* d) noexcept;
	friend class enemy;
};

class enemy : public scan_elem {
public:
	/**
	* @brief constructor for enemy
	* @param al - algorithm
	*/
	enemy(class algoritm& al) noexcept;
	static class algoritm alg;
	/**
	* @brief move the enemy
	*/
	void move() noexcept;
	/**
	* @brief return type of element, for enemy return 3
	*/
	inline virtual int get_val() const noexcept override;
};

///@brief abstruct class for modul's platform
class modul_platform : public scan_elem {
protected:
	///@brief description of modul
	string description;
	int empty_slots;
	///@brief modul which are in platform
	Vector <class modul*> moduls;
public:
	/**
	* @brief constructor for platform
	* @param str - description
	* @param slots - count of slots for moduls
	*/
	modul_platform(string str = "", int slots = 15);
	/**
	* @brief getter for moduls in platform
	*/
	Vector <class modul*> get_moduls() const noexcept;
	/**
	* @brief add modul in platform
	* @param m - modul
	*/
	void insert_modul(class modul& m);
	/**
	* @brief delete modul from platform
	* @param m - modul
	*/
	void del_modul(class modul& m) noexcept;
	/**
	* @brief find near enemies and kill them
	*/
	void scan_kill() noexcept;
	/**
	* @brief less the energy of moduls
	*/
	void less_energy() noexcept;
	/**
	* @brief get type of element, for modul platform it return 2
	* @param m - modul
	*/
	inline virtual int get_val()  const noexcept override;
	/**
	* @brief complete virtual function
	*/
	virtual int get_plat() const noexcept = 0;
};

///@brief static platform which have energy supply
class static_platform : public modul_platform {
private:
	int energy_supply;
public:
	/**
	* @brief constructor for static platform
	* @param energy - energy supply
	* @param str - description
	* @param slots - count of slots
	*/
	static_platform(int energy = 10, string str = "", int slots = 15);
	/**
	* @brief empty function because static platform can't move
	*/
	virtual void move(struct coord c) override {};
	/**
	* @brief return type of modul platform
	*/
	inline virtual int get_plat() const noexcept override;
};


///@brief mobil platform which can move and have speed
class mobil_platform : public modul_platform {
private:
	coord prev_c = { 0, 0 };
	int speed;
public:
	/**
	* @brief constructor for static platform
	* @param sp - speed
	* @param str - description
	* @param slots - count of slots
	*/
	mobil_platform(int sp = 2, string str = "", int slots = 15);
	/**
	* @brief return previously coordinates of platform
	*/
	coord get_prev() const noexcept;
	/**
	* @brief return type of modul platform
	*/
	inline virtual int get_plat() const noexcept override;
};

///@brief abstruct class for moduls
class modul {
protected:
	const int energy_consum;
	///@brief turn on or turn of
	bool turn;
	const int slots_count;
	///@brief radius of action
	const int radius;
public:
	/**
	* @brief constructor for modul
	* @param cons - energy consum
	* @param turn - turn on or turn of
	* @param slots - count of slots
	* @param r - radius
	*/
	modul(int cons = 2, bool turn = 1, int slots = 5, int r = 2);
	int get_consum() const noexcept;
	bool get_turn() const noexcept;
	void turn_off() noexcept;
	void turn_on() noexcept;
	inline int get_slots() const noexcept;
	int get_radius() const noexcept;
	/**
	* @brief complete virtual function
	*/
	virtual void set_platform(class modul_platform& p)  = 0;
	/**
	* @brief complete virtual function
	*/
	virtual void unset_platform() noexcept = 0;
	/**
	* @brief complete virtual function
	*/
	virtual int get_type() const noexcept = 0;
	bool operator ==(const modul& a) const noexcept;
};


///@brief abstruct class for moduls which can see the environment descriptor
class coord_modul : public modul {
protected:
	class modul_platform* plat = nullptr;
public:
	/**
	* @brief constructor for coord modul
	* @param cons - energy consum
	* @param turn - turn on or turn of
	* @param slots - count of slots
	* @param r - radius
	*/
	coord_modul(int cons = 3, bool turn = 1, int slots = 5, int r = 2);
	modul_platform* get_platform() const noexcept;
	/**
	* @brief set the platform in which modul is
	* @param p - platform
	*/
	inline virtual void set_platform(class modul_platform& p) override;
	/**
	* @brief delete platform when modul delete from platform
	*/
	inline virtual void unset_platform() noexcept override;
	/**
	* @brief return the environment elements in radius action of modul
	*/
	virtual vector <class environment_elem*> scan() const;
	/**
	* @brief complete virtual function
	*/
	virtual void func() const noexcept = 0;
};


///@brief modul ehich have energy supply and can have the net with other net moduls
class net_modul : public coord_modul {
private:
	///@brief count of possible connection
	int connect;
	int energy_supply;
	///@brief moduls with which have connection
	vector <class net_modul*> nets;
	class static_platform* stat_plat = nullptr;
public:
	/**
	* @brief constructor for net modul
	* @param con - max count of connection
	* @param sup - energy supply
	* @param cons - energy consum
	* @param turn - turn on or turn of
	* @param slots - count of slots
	* @param r - radius
	*/
	net_modul(int con = 5, int sup = 10, int cons = 3, bool turn = 1, int slots = 5, int r = 10);
	int get_supply() const noexcept;
	/**
	* @brief platforn can't set if modul haven't static platform in connect
	* @param p - platform
	*/
	void set_platform(class modul_platform& p) override;
	/**
	* @brief unset platform and static platform
	*/
	virtual void unset_platform() noexcept override;
	/**
	* @brief return modul's static platform
	*/
	inline class static_platform* get_stat_plat() const noexcept;
	/**
	* @brief return net moduls in radius action
	*/
	vector <class net_modul*> update() const noexcept;
	/**
	* @brief return neibour net moduls of net moduls in radius action
	*/
	vector <class net_modul*> get_neib_par();
	/**
	* @brief return can we have connect in net modul
	* @param m - modul with which will connect
	*/
	bool set_conect(class net_modul& m) noexcept;
	/**
	* @brief return can we have connect with net modul and set it if yes
	* @param m - modul with which will connect
	* @param count - count of connection
	*/
	bool conection(class net_modul* mod, int count);
	/**
	* @brief unset the connect in net modul
	* @param m - modul with which will connect
	*/
	void unset_conect(class net_modul& m) noexcept;
	/**
	* @brief unset the connect with net modul
	* @param m - modul with which will connect
	* @param count - count of connection
	*/
	void unconection(class net_modul* m, int count);
	/**
	* @brief return type of modul, for net modul it is 1
	*/
	virtual int get_type() const noexcept override;
	virtual void func() const noexcept override {};
};


///@brief sensor can return the environment elements and have a type of sensor
class sensor : public coord_modul {
private:
	bool type;
public:
	/**
	* @brief constructor sensor
	* @param t - type of sensor
	* @param cons - energy consum
	* @param turn - turn on or turn of
	* @param slots - count of slots
	* @param r - radius
	*/
	sensor(bool t = 1, int cons = 3, bool turn = 1, int slots = 5, int r = 2);
	/**
	* @brief return the environment elements
	*/
	virtual vector <class environment_elem*> scan() const override;
	/**
	* @brief return type of modul, for net modul it is 2
	*/
	virtual int get_type() const noexcept override;
	virtual void func() const noexcept override {};
};

///@brief armament can kill enemies and have energy type
class armament :public modul {
private:
	bool energy_type = 0;
	///@brief charging time
	int energy_time;
	///@brief past time
	int time = 0;
	///@brief count of energy
	int energy;
	///@brief power consum withount charging
	int normal_consum;
public:
	/**
	* @brief constructor of armament
	* @param time - time of charging
	* @param norcon - power consum withount charging
	* @param cons - energy consum
	* @param turn - turn on or turn of
	* @param slots - count of slots
	* @param r - radius
	*/
	armament(int time = 3, int norcon = 2, int cons = 3, bool turn = 1, int slots = 5, int r = 2);
	int get_energy_type() const noexcept;
	void energy_on() noexcept;
	void energy_off() noexcept;
	/**
	* @brief return time of energy time
	*/
	int get_en_time() const noexcept;
	/**
	* @brief return current time
	*/
	int get_time() const noexcept;
	/**
	* @brief set current time
	*/
	int set_time(int t);
	int get_energy() const noexcept;
	int set_energy(int e);
	int get_norm_consum() const noexcept;
	/**
	* @brief kill enemy
	* @param enemy - enemy
	*/
	void fire(class enemy& enemy) const;
	/**
	* @brief function override because armament doesn't know it's platform
	*/
	virtual void set_platform(class modul_platform& p) {};
	/**
	* @brief function override because armament doesn't know it's platform
	*/
	virtual void unset_platform() noexcept {};
	/**
	* @brief return type of modul, for net modul it is 2
	*/
	virtual int get_type() const noexcept override;
};

/**
	* @brief return if element in size of environment descriptor
	* @param c - coordinates
	* @param d - descriptor
	*/
bool insize(struct coord c, class environment_descriptor d);
/**
	* @brief return if element in radius action of modul
	* @param c1 - coordinates of modul
	* @param r - radius
	* @param c2 - coordinates of element
	*/
bool inradius(struct coord c1, int rad, struct coord c2);
