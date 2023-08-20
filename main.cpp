#include <iostream>
#include <list>
#include <vector>
#include <string>

namespace player {
	std::string name;
	std::string playerClass;
	int health[2] = {};
	int damage;
	int intelligence;
	namespace XP {
		int level = 1;
		float xp = 0.0;
		float levelUp = 50.0;
	}
}

namespace setupFuncs {
	void assignment(int Health, std::string PlayerClass, int Damage, int Intelligence) {
		player::health[0] = Health;
		player::health[1] = Health;
		player::playerClass = PlayerClass;
		player::damage = Damage;
		player::intelligence = Intelligence;
	}

	void playerSetup() {
		std::cout << "\nwelcome to the class setup!";
		std::cout << "\ninput your name: ";
		std::cin >> player::name;
		int inp = 0;
		do {
			std::cout << "\nwhat class do you wish to choose, [1] warrior, [2] archer, [3] wizard: ";
			std::cin >> inp;
			switch (inp) {
			case 1:
				assignment(100, "warrior", 25, 10);
				break;
			case 2:
				assignment(50, "archer", 15, 25);
				break;
			case 3:
				assignment(65, "wizard", 20, 15);
				break;
			}
		} while (inp > 3 || inp < 1);
	}
//end of setupFuncs
}

void death() {
	const std::string possbileDeaths[4] = { " was slain", " was murdered", " was torn apart", " was slaughtered" };
	srand(time(NULL));
	std::cout << player::name << " was" << possbileDeaths[rand() % 3];
}

namespace genericBattle {
	const std::string possibleNames[4] = { "margaret thatcher", "the bread man", "scomo in a mcdonalds", "kids fattening center" };
	class enemy {
	public:
		int health[2] = {};
		int damage;
		std::string name;
		bool alive = false;
		enemy(int extraDifficulty, int nameSelector) {
			health[0] = health[1] = 35 * player::XP::level + extraDifficulty;
			damage = 10 + extraDifficulty + player::XP::level * 5;
			name = possibleNames[nameSelector];
		}
		enemy() {} //default constructor
	};
	enemy enemies[4];
	bool battle(int enemyCount, bool defended) {
		int inp = 0;
		for (int i = 0; i < 4; i++) {
			if (enemies[i].alive) {
				std::cout << "\n" << enemies[i].name << " health = " << enemies[i].health[0] << "/" << enemies[i].health[1];
				if (defended) {
					enemies[i].damage += 5 * player::XP::level;
				}
			}
		}
		std::cout << "\n" << player::name << " health = " << player::health[0] << "/" << player::health[1];
		while (inp > 3 || inp < 1) {
			std::cout << "\ndo you wish to attack [1], defend [2] or do nothing [3]? ";
			std::cin >> inp;
			int inp2 = 0;
			switch (inp) {
			case 1:
				while (inp2 < 1 || inp2 > enemyCount) {
					std::cout << "\nwhat enemy do you wish to target (represented as an integer): ";
					std::cin >> inp2;
					if (inp2 > enemyCount || inp2 < 1) {
						std::cout << "\ninvalid response";
					}
					else {
						enemies[inp2-1].health[0] -= player::damage;
						if (enemies[inp2-1].health[0] <= 0) {
							enemies[inp2-1].alive = false;
						}
					}
				}
				std::cout << "\nyou attacked";
				break;
			case 2:
				for (int i = 0; i < enemyCount; i++) {
					if (enemies[i].alive) {
						enemies[i].damage -= 5 * player::XP::level;
					}
				}
				defended = true;
				std::cout << "\nyou defended";
				break;
			case 3:
				std::cout << "\nyou did nothing... why?";
				break;
			default:
				std::cout << "\ninvalid response";
				break;
			}
		}
		for (int i = 0; i < enemyCount; i++) {
			if (enemies[i].alive && rand() % 10 > 4) {
				player::health[0] -= enemies[i].damage;
				std::cout << player::name << " was attacked by " << enemies[i].name;
			}
		}
		if (player::health[0] <= 0) { //checks if player is alive
			death();
			return false;
		}
		//start if all enemies are dead
		int count = 0;
		for (int i = 0; i < enemyCount; i++) {
			if (!enemies[i].alive) {
				count++;
			}
		}
		if (count == enemyCount) {
			std::cout << "\nyou won!";
			return true;
		}
		else {
			battle(enemyCount, defended);
		}
		//end
	}
	void start(int enemyCount, int extraDifficulty) {
		for (int i = 0; i < enemyCount; i++) {
			enemies[i] = enemy(0,1);
			enemies[i].alive = true;
		}
		if (battle(enemyCount, false)) {
			std::cout << "you big kill minster energy drin";
		}
	}
}

void intro() {
	std::cout << "\nyou wake up in a dark room, theres nothing but a door and a crusty bed";
	{
		//start block
		bool hasLooked = false;
		std::string inp;
		while (true) {
			std::cout << "\ndo you wish to [bed] inspect the bed or [door] open the door? ";
			std::cin >> inp;
			if (inp == "bed") {
				if (hasLooked) {
					std::cout << "\nyou found nothing but disease";
				}
				else {
					std::cout << "\nyou found nothing but disease, however you did get an uncanny feeling in your chest";
					hasLooked = true;
				}
			}
			else if (inp == "door") {
				if (hasLooked) {
					std::cout << "\nyou try to open the door but fail\nyou suddenly hear a loud grunt from behind you, you turn around and see a giant monster!\n";
					genericBattle::start(1,0);
					break;
				}
				else {
					std::cout << "\nyou try to open the door but fail";
				}
			}
			else {
				std::cout << "\ninvalid response";
			}
		}
		//end block
	}
}

int main() {
	std::cout << "welcome!";
	std::string inp;
	while (inp != "start" && inp != "quit") {
		std::cout << "\ndo you wish to start or quit? ";
		std::cin >> inp;
		if (inp == "start") {
			std::cout << "\nstarting...";
			setupFuncs::playerSetup();
			intro();
			return 0;
		}
		else if (inp == "quit") {
			std::cout << "\nquitting...";
			return 1;
		}
		else {
			std::cout << "\ninvalid response";
		}
	}
	return 0;
}
