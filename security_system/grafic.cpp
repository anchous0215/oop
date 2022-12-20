
#include "grafic.h"
#include <windows.h>

using namespace sf;


int main(){
    environment_descriptor d = get_size();
    get_lets(d, d.get_size()[0], d.get_size()[1]);
    int plats = get_platforms(d, d.get_size()[0], d.get_size()[1]);
    set_enemy(d, plats);
    AI ai(&d);
    security_system ss(&d, &ai);

    int x = d.get_size()[0];
    int y = d.get_size()[1];
    int wight = 64;
    int high = 64;
    Texture en;
    Texture l;
    Texture s;
	Texture m;
    Texture w;
    en.loadFromFile("pes.png");
    l.loadFromFile("let.jpg");
    s.loadFromFile("stat.png");
	m.loadFromFile("mab.png");
   w.loadFromFile("br.jpg");
	Sprite white;
	white.setTexture(w);
	Sprite let;
	let.setTexture(l);
	Sprite stat;
	stat.setTexture(s);
	Sprite mob;
	mob.setTexture(m);
	Sprite enem;
	enem.setTexture(en);
    sf::RenderWindow app(sf::VideoMode(64*x, 64*y), L"SFML window");
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
		}
		app.clear(Color::White);
		for (int j = 1; j <= y; j++) {
			for (int i = 1; i <= x; i++) {
				white.setPosition((i - 1) * wight, (j - 1) * high);
				app.draw(white);
			}
		}
		for (int j = 1; j <= y; j++) {
			for (int i = 1; i <= x; i++) {
				char t = d.get_cell_type({ i, j });
				if (t == '-') {
					let.setPosition((i - 1) * wight, (j - 1) * high);
					app.draw(let);
				}
				if (t == 'e') {
					enem.setPosition((i - 1) * wight, (j - 1) * high);
					app.draw(enem);
				}
				if ((t == 's')) {
					stat.setPosition((i - 1) * wight, (j - 1) * high);
					app.draw(stat);
				}
				if ((t == 'm')) {
					mob.setPosition((i - 1) * wight, (j - 1) * high);
					app.draw(mob);
				}
			}
		}
		app.display();
		Sleep(1000);
		while (ss.check()) {
			ss.get_ai()->destroy_all_enemy();
			app.clear(Color::White);
			for (int j = 1; j <= y; j++) {
				for (int i = 1; i <= x; i++) {
					white.setPosition((i - 1) * wight, (j - 1) * high);
					app.draw(white);
				}
			}
			for (int j = 1; j <= y; j++) {
				for (int i = 1; i <= x; i++) {
					char t = d.get_cell_type({ i, j });
					if (t == '-') {
						let.setPosition((i - 1) * wight, (j - 1) * high);
						app.draw(let);
					}
					if (t == 'e') {
						enem.setPosition((i - 1) * wight, (j - 1) * high);
						app.draw(enem);
					}
					if ((t == 's')) {
						stat.setPosition((i - 1) * wight, (j - 1) * high);
						app.draw(stat);
					}
					if ((t == 'm')) {
						mob.setPosition((i - 1) * wight, (j - 1) * high);
						app.draw(mob);
					}
				}
			}
			app.display();
			Sleep(1000);
			ss.move_enemy();
			app.clear(Color::White);
			for (int j = 1; j <= y; j++) {
				for (int i = 1; i <= x; i++) {
					white.setPosition((i - 1) * wight, (j - 1) * high);
					app.draw(white);
				}
			}
			for (int j = 1; j <= y; j++) {
				for (int i = 1; i <= x; i++) {
					char t = d.get_cell_type({ i, j });
					if (t == '-') {
						let.setPosition((i - 1) * wight, (j - 1) * high);
						app.draw(let);
					}
					if (t == 'e') {
						enem.setPosition((i - 1) * wight, (j - 1) * high);
						app.draw(enem);
					}
					if ((t == 's')) {
						stat.setPosition((i - 1) * wight, (j - 1) * high);
						app.draw(stat);
					}
					if ((t == 'm')) {
						mob.setPosition((i - 1) * wight, (j - 1) * high);
						app.draw(mob);
					}
				}
			}
			app.display();
			Sleep(1000);
		}
	}
	erase(d);
    return 0;
}
