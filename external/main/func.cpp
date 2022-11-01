#include "func.h"

void menu() {
	const char* mes = "HEllo!\n This programm can help you create your own trains and chose the seat in generated train";
	output(mes);
	int choice = -1;
	do {
		mes = "chose than you want to do:\n";
		output(mes);
		mes = "1 - create your own trains\n";
		output(mes);
		mes = "2 - chose the seats from generate trains\n";
		output(mes);
		mes = "0 - quite\n";
		output(mes);
		get_num(choice, "Enter your choice: ");
		switch (choice) {
		case 1:
			persons_create();
			break;
		case 2:
			chose_seats();
			break;
		}
	} while (choice != 0);
}

void persons_create() {
	int count = 0;
	Train trains[100];
	const char* mes = "How many trains do you want to create?(0 < count < 100): ";
	do {
		get_num(count, mes);
	} while ((count < 0) && (count > 100));
	for (int i = 0; i < count; i++) {
		trains[i] = create_train();
	}
	char choice = 'n';
	mes = "Do you want see your trains?(y/n): ";
	get_num(choice, mes);
	if ((choice == 'Y') || (choice == 'y')) {
		for (int i = 0; i < count; i++) {
			out() << trains[i];
		}
	}
}

Train create_train() {
	Train tr;
	set_from_wher(tr);
	in() >> tr;
	change_train(tr);
	return tr;
}

void set_from_wher(Train& tr) {
	string from = "";
	const char* mes = "Enter city where from train will start: ";
	get_num(from, mes);
	string wher = "";
	mes = "Enter the city where train will finish: ";
	get_num(wher, mes);
	while (from == wher) {
		output("Train can't start and finish in the same places!\n");
		const char* mes = "Enter city where from train will start: ";
		get_num(from, mes);
		mes = "Enter the city where train will finish: ";
		get_num(wher, mes);
	}
	tr.set_from(from);
	tr.set_wher(wher);
}

void change_train(Train& tr) {
		char choice = 'n';
	do {
		const char* mes = "Do you want change your train?(y/n): ";
		out() << tr;
		get_num(choice, mes);
		if ((choice == 'n') || (choice == 'N')) {
			break;
		}
		change(tr);
	} while ((choice == 'y') || (choice == 'Y'));
}

void change(Train& tr) {
	int choice = 0;
	do {
		output("your train:\n");
		out() << tr;
		const char* mes = "What do you want to change?\n";
		output(mes);
		mes = "1 - from\n";
		output(mes);
		mes = "2 - where\n";
		output(mes);
		mes = "3 - reserved seats\n";
		output(mes);
		mes = "4 - add carriage\n";
		output(mes);
		mes = "5 - change carriage\n";
		output(mes);
		mes = "6 - delete last carriages\n";
		output(mes);
		mes = "0 - nothing\n";
		output(mes);
		get_num(choice, "Enter your choice: ");
		switch (choice) {
		case 1:
			change_from(tr);
			break;
		case 2:
			change_where(tr);
			break;
		case 3:
			reserved_seats(tr);
			break;
		case 4:
			add_carriage(tr);
			break;
		case 5:
			change_carriage(tr);
			break;
		case 6:
			delete_carriages(tr);
			break;
		}
	} while (choice != 0);
}

void change_from(Train& tr) {
	const char* mes = "Enter your city: ";
	string city = "";
	get_num(city, mes);
	if (city == tr.get_wher()) {
		do {
			output("Train can't start and finish in the same places!\n");
			get_num(city, mes);
		} while (city == tr.get_wher());
	}
	tr.set_from(city);
}

void change_where(Train& tr) {
	const char* mes = "Enter your city: ";
	string city = "";
	get_num(city, mes);
	if (city == tr.get_from()) {
		do {
			output("Train can't start and finish in the same places!\n");
			get_num(city, mes);
		} while (city == tr.get_from());
	}
	tr.set_wher(city);
}

void reserved_seats(Train& tr) {
	const char* mes = "Enter carrige in which you want reserve seat: ";
	int choice = 0;
	do {
		get_num(choice, mes);
	} while ((choice < 1) || (choice > tr.get_train_length()));
	out() << "you have " << tr.number_of_reserved_seats(choice) << " reserved seats\n";
	mes = "How many seats do you want reseved too: ";
	int count = 0;
	get_num(count, mes);
	if (tr.get_carriages(choice).capacity < tr.get_carriages(choice).capacity + count) {
		output("carriage don't have so many empty seats, please chose another\n");
		get_num(count, mes);
	}
	tr.reserved_seat(choice, count);
}

void add_carriage(Train& tr) {
	Carriage car = create_carriage();
	tr.add_carriage(car);
}

Carriage create_carriage() {
	Carriage car;
	const char* mes = "Enter capacity of your new carriage: ";
	int cap = 0;
	get_num(cap, mes);
	mes = "Enter busy seats in you new carriage: ";
	int busy = 0;
	get_num(busy, mes);
	car.busy = busy;
	car.capacity = cap;
	return car;
}

void change_carriage(Train& tr) {
	Carriage car;
	const char* mes = "Enter number of carriage that you want change: ";
	int number = 0;
	get_num(number, mes);
	car = create_carriage();
	tr.set_carriage(number, car);
}

void delete_carriages(Train& tr) {
	out() << "You have " << tr.get_train_length() << " in your train";
	const char* mes = "How many carriages do you want to delete";
	int count = 0;
	do {
		get_num(count, mes);
	} while ((count < 0) || (count > tr.get_train_length()));
	int lenght = tr.get_train_length();
	tr.set_train_length(lenght - count);
}

void chose_seats() {
	Train trains[5];
	generate_trains(trains);
	Train tr = chose_train(trains);
	Carriage car = chose_carriage(tr);
	information(tr, car);
}

void generate_trains(Train* trains) {
	srand(static_cast<unsigned int>(time(NULL))); 
	chose_cities(trains); 
	agregate_lenght(trains);
	agregate_carriages(trains);
}

void chose_cities(Train* trains) {
	string cities[10] = { "Moscow", "Saint Petersburg", "Kazan", "Nizhny Novgorod", "Volgograd", "Vladivostok", "Samara", "Novosibirsk", "Ufa", "Ekanterenburg" };
	int random;
	for (int i = 0; i < 5; i++) {
		random = rand() % 10;
		trains[i].set_from(cities[random]);
	} 
	for (int i = 0; i < 5; i++) {
		do {
			random = rand() % 10;
		} while (trains[i].get_from() == cities[random]);
		trains[i].set_wher(cities[random]);
	}
}

void agregate_lenght(Train* trains) {
	int random = 0;
	for (int i = 0; i < 5; i++) {
		random = rand() % 10 + 1;
		trains[i].set_train_length(random);
	}
}

void agregate_carriages(Train* trains) {
	int random = 0;
	Carriage car = {0, 0};
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= trains[i].get_train_length(); j++) {
			random = rand() % 10 + 1;
			car.capacity = random;
			do {
				random = rand() % 10 + 1;
			} while (car.capacity < random);
			car.busy = random;
			trains[i].set_carriage(j, car);
		}
	}
}

Train chose_train(Train* trains) {
	Train tr;
	tr = chose_directions(trains);
	if (check_full(tr) == 0) {
		do {
			out() << "This train is full";
			tr = chose_directions(trains);
		} while (check_full == 0);
	}
	return tr;
}

string chose_from(Train* trains) {
	output("You should chose city where from you will start\n");
	for (int i = 0; i < 5; i++) {
		out() << i+1 << " - " << trains[i].get_from() << "\n";
	}
	int choice = 0;
	get_num(choice, "Make your choice: ");
	if ((choice < 1) || (choice > 5)) {
		do {
			output("Your choice is incorrect");
			get_num(choice, "Make your choice: ");
		} while ((choice < 1) || (choice > 5));
	}
	return(trains[choice - 1].get_from());
}

string chose_wher(Train* trains, string from) {
	output("You should chose city where you will finish\n");
	int mas[5] = { -1, -1, -1, -1, -1 };
	for (int i = 0; i < 5; i++) {
		if (trains[i].get_from() == from) {
			out() << i+1 << " - " << trains[i].get_wher() << "\n";
			mas[i] = i;
		}
	}
	int choice = 0;
	get_num(choice, "Make your choice: ");
	if (check(mas, 5, choice - 1) != 0) {
		do {
			output("Your choice is incorrect");
			get_num(choice, "Make your choice: ");
		} while (check(mas, 5, choice) != 0);
	}
	return(trains[choice - 1].get_wher());
}

bool check(const int mas[], int lenght, int num){
	for (int j = 0; j < lenght; j++) {
		if (mas[j] == num) {
			return 0;
		}
	}
	return 1;
}

Carriage chose_carriage(Train& tr) {
	out() << "This train have " << tr.get_train_length() << " carriages and " << tr.number_of_passenger() << " passengers\n";
	int car = 0;
	int choice = 0;
	get_num(choice, "Chose carriage: ");
	do {
		car = choice;
		out() << "This carriage have " << tr.get_carriages(car).capacity << " seats and " << tr.get_carriages(car).busy << " reserved seats\n";
		out() << "You can choice another carriage or enter 0\n";
		get_num(choice, "Make your choice: ");
	} while ((choice != 0) || (choice < 0) || (choice > tr.get_train_length()));
	tr.reserved_seat(car, 1);
	return (tr.get_carriages(car));
}

void information(Train& tr, Carriage& car) {
	out() << "You chose train which go from " << tr.get_from() << " to " << tr.get_wher() << "\n";
	out() << "In your carriage " << car.capacity << "seats and " << car.busy << "reserved seats\n";
	out() << "Good way!\n";
}

Train chose_directions(Train* trains) {
	string from;
	string wher;
	from = chose_from(trains);
	wher = chose_wher(trains, from);
	for (int i = 0; i < 5; i++) {
		if ((trains[i].get_from() == from) && (trains[i].get_wher() == wher)) {
			return trains[i];
		}
	}
}

bool check_full(Train& tr) {
	int count = 0;
	int count1 = 0;
	for (int i = 1; i <= tr.get_train_length(); i++) {
		count += tr.get_carriages(i).capacity;
		count1 += tr.number_of_reserved_seats(i);
	}
	if (count == count1) {
		return 0;
	}
	else {
		return 1;
	}
}
