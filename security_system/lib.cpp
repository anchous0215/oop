#include "Header.h"
using namespace std;

// environment_descriptor
environment_descriptor::environment_descriptor(int x, int y) : might(x), high(y) {
	if ((x < 1) || (y < 1)) {
		throw exception("invalid size\n");
	}
}

int* environment_descriptor::get_size() const noexcept {
	int size[2];
	size[0] = might;
	size[1] = high;
	return size;
}

void environment_descriptor::set_size(int m, int h) {
	if (m < 1) {
		throw exception("invalid might\n");
	}
	if (h < 1) {
		throw exception("invalid high\n");
	}
	might = m;
	high = h;
}

environment_elem& environment_descriptor::get_cell(struct coord coords) const {
	if (elements.count(coords) == 0) {
		throw exception("This cell empty");
	}
	else {
		return elements.at(coords);
	}
}

int environment_descriptor::get_cell_type(coord c) const noexcept {
	if (elements.count(c) == 0) {
		return 0;
	}
	else {
		environment_elem& el = elements.at(c);
		return elements.at(c).get_val();
	}
}

void environment_descriptor::insert_elem(coord coords, environment_elem& elem) {
	if (elements.count(coords) != 0) {
	throw exception("This place is busy\n");
}
if ((coords.x < 1) || (coords.y < 1) || (coords.x > might) || (coords.y > high)) {
	throw exception("This place is not exsist\n");
}
elem.set_coord(coords);
elem.set_desc(*this);
elements.insert(pair <coord, environment_elem&>(coords, elem));
}

void environment_descriptor::del_elem(struct coord c) {
	if (get_cell_type(c) == 0) {
		throw exception("This cell is empty");
	}
	else {
		elements.erase(c);
	}
}


//AI
AI::AI(environment_descriptor& desc) noexcept:
desc(desc) {};

void AI::destroy_all_enemy(class environment_descriptor& descriptor) {
	kill_enemy();
	//move_moduls();
}

void AI::kill_enemy() {
	for (int i = 1; i <= desc.get_size()[1]; i++) {
		for (int j = 1; j <= desc.get_size()[0]; j++) {
			if (desc.get_cell_type({ j, i }) == 2) {
				modul_platform* plat = static_cast <modul_platform*>(&(desc.get_cell({ i, j })));
				plat->scan_kill();
			}
		}
		cout << "\n";
	}
}



//security_system
security_system::security_system(environment_descriptor& desc, AI& ai) noexcept:
	descriptor(desc), ai(ai) {}; 



//coord
bool coord:: operator <(const coord& a) const {
	if (x < a.x) {
		return true;
	}
	else if ((x == a.x)) {
		if (y < a.y) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool coord:: operator ==(const coord& a) const {
	if ((x == a.x) && (y == a.y)) {
		return true;
	}
	else {
		return false;
	}
}



//environment_elem
coord environment_elem::get_coords() const noexcept {
	return coords;
}

void environment_elem::set_coord(coord c) noexcept {
	coords = c;
}

int environment_elem::get_val()  const noexcept {
	return 1;
}



//scan_elem
environment_descriptor* scan_elem::get_desc() const {
	if (desc == nullptr) {
		throw exception("This platform don't have environment descriptor");
	}
	else {
		return desc;
	}
}

void scan_elem::set_desc(environment_descriptor& d) noexcept {
	desc = &d;
}

void scan_elem:: move(coord c) {
	if (!insize(c, *desc)) {
		throw exception("this place is not excist\n");
	}
	if (desc->elements.count(c) > 0) {
		throw exception("this place is busy\n");
	}
	desc->elements.insert(pair <coord, environment_elem&>(c, *this));
	desc->elements.erase(coords);
	coords = c;
}




//algoritm
coord algoritm::algor(coord c, environment_descriptor& d) noexcept {
	if ((c.x + 1 != d.get_size()[0]) && (d.get_cell_type({ c.x + 1, c.y }) == 0)) {
		return{ c.x + 1, c.y };
	}
	else if ((c.y + 1 != d.get_size()[1]) && (d.get_cell_type({ c.x, c.y + 1 }) == 0)) {
		return{ c.x, c.y + 1};
	}
	else if ((c.x - 1 != 0) && (d.get_cell_type({ c.x - 1, c.y }) == 0)) {
		return{ c.x - 1, c.y};
	}
	else if ((c.y - 1 != 0) && (d.get_cell_type({ c.x, c.y - 1 }) == 0)) {
		return{ c.x, c.y - 1 };
	}
	else {
		return c;
	}
}



//enemy
enemy::enemy(algoritm& al) noexcept {
	alg = al;
}

int enemy::get_val() const noexcept {
	return 3;
}



//modul_platform
modul_platform::modul_platform(string str, int slots) {
	if (slots < 1) {
		throw exception("invalid number of slots\n");
	}
	description = str;
	empty_slots = slots;
}

vector <modul*> modul_platform::get_moduls() const noexcept {
	return moduls;
}

void modul_platform::insert_modul(modul& m) {
	if (empty_slots < m.get_slots()) {
		throw exception("Too much slots\n");
	}
	int supply = 0;
	int consum = 0;
	for (int i = 0; i < moduls.size(); i++) {
		consum += moduls[i]->get_consum();
		if (moduls[i]->get_type() == 1) {
			net_modul* n = static_cast <net_modul*>(moduls[i]);
			supply += n->get_supply();
		}
	}
	if (m.get_type() == 1) {
		net_modul* n = static_cast <net_modul*>(&m);
		supply += n->get_supply();
	}
	consum += m.get_consum();
	if (supply < consum) {
		throw exception("Too much energy consum for this platform\n");
	}
	moduls.push_back(&m);
	empty_slots -= m.get_slots();
	m.set_platform(*this);
}

void modul_platform::del_modul(modul& m) noexcept{
	for (int i = 0; i < moduls.size(); i++) {
		if (moduls[i] == &m) {
			moduls.erase(moduls.begin() + i);
			m.unset_platform();
		}
	}
}

void modul_platform::scan_kill() noexcept {
	vector <enemy*> en;
	for (int i = 0; i < moduls.size(); i++) {
		vector <environment_elem*> elems;
		if (moduls[i]->get_type() == 2) {
			sensor* s = static_cast <sensor*>(moduls[i]);
			elems = s->scan();
			for (int j = 0; j < elems.size(); j++) {
				if (elems[j]->get_val() == 3) {
					enemy* e = static_cast <enemy*>(elems[j]);
					if (find(en.begin(), en.end(), e) == en.end()) {
						en.push_back(e);
					}
				}
			}
		}
	}
	for (int i = 0; i < moduls.size(); i++) {
		if (moduls[i]->get_type() == 3) {
			armament* ar = static_cast <armament*>(moduls[i]);
			for (int j = 0; j < en.size(); j++) {
				if (inradius(get_coords(), ar->get_radius(), en[j]->get_coords())) {
					ar->fire(*en[j]);
				}
			}
		}
	}
}

void modul_platform::less_energy() noexcept {
	for (int i = 0; i < moduls.size(); i++) {
		if (moduls[i]->get_type() == 3) {
			armament* a = static_cast <armament*>(moduls[i]);
			if (a->get_energy_type() == 0) {
				if (a->get_energy() >= a->get_norm_consum()) {
					a->set_energy(a->get_energy() - a->get_norm_consum());
				}
				else {
					a->energy_on();
					a->set_energy(a->get_energy() + a->get_consum());
					a->set_time(1);
				}
			}
			else {
				if (a->get_time() == a->get_en_time()) {
					a->energy_off();
					a->set_time(0);
					a->set_energy(a->get_energy() - a->get_norm_consum());
				}
				else {
					int time = a->get_time();
					time++;
					a->set_energy(a->get_energy() + a->get_consum());
					a->set_time(time);
				}
			}
		}
	}
}

int modul_platform::get_val()  const noexcept {
	return 2;
}



//static_platform
static_platform::static_platform(int energy, string str, int slots) : modul_platform(str, slots) {
	if (energy < 1) {
		throw exception("invalid energy_supply\n");
	}
	energy_supply = energy;
}

void static_platform::move(struct coord c) {
	throw exception("This is static platform");
}

int static_platform::get_plat() const noexcept {
	return 1;
}



//mobil_platform
mobil_platform::mobil_platform(int sp, string str, int slots) : modul_platform(str, slots) {
	if (sp < 1) {
		throw exception("invalid speed\n");
	}
	speed = sp;
}

int mobil_platform::get_plat() const noexcept {
	return 2;
}



//modul
modul::modul(int cons, bool turn, int slots, int r) :
	energy_consum(cons), turn(turn), slots_count(slots), radius(r) {
	if (cons < 1) {
		throw exception("invalid energy_consum\n");
	}
	if (slots < 1) {
		throw exception("invalid number of slots\n");
	}
	if (r < 1) {
		throw exception("invalid radius\n");
	}
}

int modul::get_consum() const noexcept {
	return energy_consum;
}

bool modul::get_turn() const noexcept {
	return turn;
}

void modul::turn_on() noexcept {
	turn = 1;
}

void modul::turn_off() noexcept {
	turn = 0;
}

int modul::get_slots() const noexcept {
	return slots_count;
}

int modul::get_radius() const noexcept {
	return radius;
}

bool modul::operator ==(const modul& a) const noexcept{
	if (this == &a) {
		return true;
	}
	else {
		return false;
	}
}



//coord_modul
coord_modul::coord_modul(int cons, bool turn, int slots, int r) : 
	modul(cons, turn, slots, r) {};

modul_platform* coord_modul::get_platform() const noexcept {
	return plat;
}

void coord_modul::set_platform(modul_platform& p) {
	if (plat != nullptr) {
		throw exception("this modul is busy\n");
	}
	plat = &p;
}

void coord_modul::unset_platform() noexcept {
	plat = nullptr;
}

vector <environment_elem*> coord_modul::scan() const {
	vector <environment_elem*> e;
	if (plat->get_desc() == nullptr) {
		throw exception("This platform doesn't have environment descriptor");
	}
	for (int i = plat->get_coords().x - radius; i <= plat->get_coords().x + radius; i++) {
		for (int j = plat->get_coords().y - radius; j <= plat->get_coords().y + radius; j++) {
			coord c = { i, j };
			if (insize(c, *plat->get_desc()) && (plat->get_desc()->get_cell_type(c) != 0) && ( !(plat->get_coords() == c) )) {
				e.push_back(&(plat->get_desc()->get_cell({ i, j })));
			}
		}
	}
	return e;
}



//net_modul
net_modul::net_modul(int con, int sup, int cons, bool turn, int slots, int r) : coord_modul(cons, turn, slots, r) {
	if (con < 1) {
		throw exception("invalid number of max connect\n");
	}
	if (sup < 1) {
		throw exception("invalid number of max energy supply\n");
	}
	connect = con;
	energy_supply = sup;
}

int net_modul::get_supply() const noexcept {
	return energy_supply;
}

void net_modul::set_platform(modul_platform& p) {
	coord_modul::set_platform(p);
	if (p.get_plat() == 1) {
		stat_plat = static_cast<static_platform*>(&p);
	}
	else {
		vector <environment_elem*> e = scan();
		for (int i = 0; i < e.size(); i++) {
			int type = e[i]->get_val();
			if (type == 2) {
				environment_elem* elem = e[i];
				modul_platform* plat = static_cast<modul_platform*>(elem);
				int type_plat = plat->get_plat();
				if (type_plat == 1) {
					stat_plat = static_cast<static_platform*>(plat);
				}
			}
		}
	}
	if (stat_plat == nullptr) {
		vector <net_modul*> mods = update();
		for (int i = 0; i < mods.size(); i++) {
			if (set_conect(*mods[i])) {
				stat_plat = mods[0]->get_stat_plat();
				break;
			}
		}
	}
	if (stat_plat == nullptr) {
		vector <net_modul*>	mods = get_neib_par();
		for (int i = 0; i < mods.size(); i++) {
			if (set_conect(*mods[i])) {
				stat_plat = mods[0]->get_stat_plat();
				break;
			}
		}
	}
	if (stat_plat == nullptr) {
		coord_modul::unset_platform();
		throw exception("This net modul doesn't have static_platform and it won't work");
	}
}

void net_modul::unset_platform() noexcept {
	coord_modul::unset_platform();
	stat_plat = nullptr;
}

static_platform* net_modul::get_stat_plat() const noexcept {
	return stat_plat;
}

vector <net_modul*> net_modul::update() const noexcept {
	vector <net_modul*> mods;
	vector <environment_elem*> e = scan();
	for (int i = 0; i < e.size(); i++) {
		if (e[i]->get_val() == 2) {
			modul_platform* plat = static_cast<modul_platform*>(e[i]);
			vector <modul*> m = plat->get_moduls();
			for (int j = 0; j < m.size(); j++) {
				if ((m[j]->get_type() == 1) && (this != m[j])) {
					net_modul* mod = static_cast<net_modul*>(m[j]);
					mods.push_back(mod);
				}
			}
		}
	}
	return mods;
}

vector <net_modul*> net_modul::get_neib_par() {
	vector <net_modul*> neibours;
	vector <net_modul*> mods = update();
	for (int i = 0; i < mods.size(); i++) {
		vector <net_modul*> neibs = mods[i]->update();
		for (int j = 0; j < neibs.size(); j++) {
			if (this != neibs[j]) {
				neibours.push_back(neibs[j]);
			}
		}
	}
	return neibours;
}

bool net_modul::set_conect(net_modul& m) noexcept {
	vector <net_modul*> mod = update();
	vector <net_modul*> neib = get_neib_par();
	if (find(nets.begin(), nets.end(), &m) != nets.end()) {
		return true;
	}
	else if (find(mod.begin(), mod.end(), &m) != mod.end()) {
		if (connect >= 1) {
			m.conection(this, 1);
			nets.push_back(&m);
			connect -= 1;
			return true;
		}
	}
	else if (find(neib.begin(), neib.end(), &m) != neib.end()) {
		if (connect >= 2) {
			m.conection(this, 2);
			nets.push_back(&m);
			connect -= 2;
			return true;
		}
	}
		return false;
}

bool net_modul::conection(net_modul* mod, int count) {
	if ((count > 2) || (count < 0)) {
		throw exception("Incorrect count of connect");
	}
	if (connect < count) {
		return false;
	}
	nets.push_back(mod);
	connect -= count;
	return true;
}


void net_modul::unset_conect(class net_modul& m) noexcept {
	vector <net_modul*> mod = update();
	vector <net_modul*> neib = get_neib_par();
	if (find(mod.begin(), mod.end(), &m) != mod.end()) {
		m.unconection(this, 1);
		remove(nets.begin(), nets.end(), &m);
		connect -= 1;
	}
	if (find(neib.begin(), neib.end(), &m) != neib.end()) {
		m.unconection(this, 2);
		remove(nets.begin(), nets.end(), &m);
		connect -= 2;
	}
}

void net_modul::unconection(class net_modul* m, int count) {
	if ((count > 2) || (count < 0)) {
		throw exception("Incorrect count of connect");
	}
	else {
		remove(nets.begin(), nets.end(), m);
		connect -= count;
	}
}

int net_modul::get_type() const noexcept {
	return 1;
}



//sensor
sensor::sensor(bool t, int cons, bool turn, int slots, int r) : coord_modul(cons, turn, slots, r) {
	type = t;
}

int sensor::get_type() const noexcept {
	return 2;

}vector <environment_elem*> sensor::scan() const {
	vector <environment_elem*> e;
	if (type == 1) {
		e = coord_modul::scan();
	}
	else {
		if (plat->get_desc() == nullptr) {
			throw exception("This platform doesn't have environment descriptor");
		}
		int x = plat->get_coords().x;
		int y = plat->get_coords().y;
		for(int i = plat->get_coords().y - 1; i >= plat->get_coords().y - radius + 1; i--){
			if ((insize({x, i}, *plat->get_desc())) && (plat->get_desc()->get_cell_type({x, i}) == 0) && (insize({ x, i - 1 }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({x, i - 1}) != 0)) {
				e.push_back(&plat->get_desc()->get_cell({ x, i - 1 }));
			}
		}
		for (int i = plat->get_coords().y + 1; i <= plat->get_coords().y + radius - 1; i++) {
			if ((insize({ x, i }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ x, i }) == 0) && (insize({ x, i + 1 }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ x, i + 1 }) != 0)) {
				e.push_back(&plat->get_desc()->get_cell({ x, i + 1 }));
			}
		}
		for (int i = plat->get_coords().x - 1; i >= plat->get_coords().x - radius + 1; i--) {
			if ((insize({ i, y }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ i, y }) == 0) && (insize({ i - 1, y }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ i - 1, y }) != 0)) {
				e.push_back(&plat->get_desc()->get_cell({ i - 1, x }));
			}
		}
		for (int i = plat->get_coords().x + 1; i <= plat->get_coords().x + radius - 1; i++) {
			if ((insize({ i, y }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ i, y }) == 0) && (insize({ i + 1, y }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ i + 1, y }) != 0)) {
				e.push_back(&plat->get_desc()->get_cell({ i + 1, y }));
			}
		}
		if ((insize({ x, y - 1 }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ x, y - 1 }) != 0)) {
			e.push_back(&plat->get_desc()->get_cell({ x, y - 1 }));
		}
		if ((insize({ x, y + 1 }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ x, y + 1 }) != 0)) {
			e.push_back(&plat->get_desc()->get_cell({ x, y + 1 }));
		}
		if ((insize({ x - 1, y }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ x - 1, y }) != 0)) {
			e.push_back(&plat->get_desc()->get_cell({ x - 1, y }));
		}
		if ((insize({ x + 1, y }, *plat->get_desc())) && (plat->get_desc()->get_cell_type({ x + 1, y }) != 0)) {
			e.push_back(&plat->get_desc()->get_cell({ x + 1, y }));
		}
		for (int i = plat->get_coords().x - 1, k = 0; i >= plat->get_coords().x - radius; i--, k++) {
			for (int j = plat->get_coords().y - 1; j >= plat->get_coords().y - radius; j--) {
				if ((insize({ i, j }, *plat->get_desc())) && ((plat->get_desc()->get_cell_type({ x - k, j }) == 0) || ((plat->get_desc()->get_cell_type({ i, y - k }) == 0))) && (plat->get_desc()->get_cell_type({ i, j }) != 0)) {
					e.push_back(&plat->get_desc()->get_cell({ i, j }));
				}
			}
		}
		for (int i = plat->get_coords().x + 1, k = 0; i <= plat->get_coords().x + radius; i++, k++) {
			for (int j = plat->get_coords().y - 1; j >= plat->get_coords().y - radius; j--) {
				if ((insize({ i, j }, *plat->get_desc())) && ((plat->get_desc()->get_cell_type({ x + k, j }) == 0) || ((plat->get_desc()->get_cell_type({ i, y - k }) == 0))) && (plat->get_desc()->get_cell_type({ i, j }) != 0)) {
					e.push_back(&plat->get_desc()->get_cell({ i, j }));
				}
			}
		}
		for (int i = plat->get_coords().x + 1, k = 0; i <= plat->get_coords().x + radius; i++, k++) {
			for (int j = plat->get_coords().y + 1; j <= plat->get_coords().y + radius; j++) {
				if ((insize({ i, j }, *plat->get_desc())) && ((plat->get_desc()->get_cell_type({ x + k, j }) == 0) || ((plat->get_desc()->get_cell_type({ i, y + k }) == 0))) && (plat->get_desc()->get_cell_type({ i, j }) != 0)) {
					e.push_back(&plat->get_desc()->get_cell({ i, j }));
				}
			}
		}
		for (int i = plat->get_coords().x - 1, k = 0; i >= plat->get_coords().x - radius; i--, k++) {
			for (int j = plat->get_coords().y + 1; j <= plat->get_coords().y + radius; j++) {
				if ((insize({ i, j }, *plat->get_desc())) && ((plat->get_desc()->get_cell_type({ x - k, j }) == 0) || ((plat->get_desc()->get_cell_type({ i, y + k }) == 0))) && (plat->get_desc()->get_cell_type({ i, j }) != 0)) {
					e.push_back(&plat->get_desc()->get_cell({ i, j }));
				}
			}
		}
	}
	return e;
}



//armament
armament::armament(int time, int norcon, int cons, bool turn, int slots, int r) : modul(cons, turn, slots, r) {
	if (time < 1) {
		throw exception("invalid time energy\n");
	}
	if (norcon < 1) {
		throw exception("invalid time energy consum\n");
	}
	energy_time = time;
	normal_consum = norcon;
	energy = energy_time * energy_consum;
}

int armament::get_energy_type() const noexcept {
	return energy_type;
}

void armament::energy_on() noexcept {
	energy_type = 1;
}

void armament::energy_off() noexcept {
	energy_type = 0;
}

int armament::get_en_time() const noexcept {
	return energy_time;
}

int armament::get_time() const noexcept {
	return time;
}

int armament::set_time(int t) {
	if ((t < 0) || (t > energy_time)) {
		throw exception("Inccorect time");
	}
	else {
		time = t;
	}
}

int armament::get_energy() const noexcept {
	return energy;
}

int armament::set_energy(int e) {
	if ((e < 0) || (e > energy_time*energy_consum)) {
		throw exception("Inccorect energy");
	}
	else {
		energy = e;
	}
}

int armament::get_norm_consum() const noexcept {
	return normal_consum;
}

void armament::fire(class enemy& enemy) const {
	if (enemy.get_desc() == nullptr) {
		throw exception("This enemy doesn't have environment descriptor");
	}
	if (energy_type == 0) {
		enemy.get_desc()->del_elem(enemy.get_coords());
	}
}

int armament::get_type() const noexcept {
	return 3;
}



//other
bool insize(coord c, environment_descriptor d) {
	if ((c.x > 0) && (c.y > 0) && (c.x <= d.get_size()[0]) && (c.y <= d.get_size()[1])) {
		return true;
	}
	else {
		return false;
	}
}

bool inradius(struct coord c1, int rad, struct coord c2) {
	int y1 = c1.y - rad;
	int y2 = c1.y + rad;
	int x1 = c1.x - rad;
	int x2 = c1.x + rad;
	if ((c2.y >= y1) && (c2.y <= y2) && (c2.x >= x1) && (c2.x <= x2)) {
		return true;
	}
	else {
		return false;
	}
}
