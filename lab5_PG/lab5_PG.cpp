#include <iostream>

using namespace std;

struct item {
	const char *type;
	const char *name;
	const char *charm;
	double rarity; //(%)
	int damage;
	int attack_speed; //(hps)
	const char *on_hit_effect;
	bool unbreakable;
};


int main() {
	int number;
	cout << "Enter the number, or enter 0 to close - ";
	cin >> number;
	while (number) {
		if (number == 1) {
			item scarlet_devil;

			scarlet_devil.type = "Weapon";
			scarlet_devil.name = "Scarlet Devil";
			scarlet_devil.charm = "Legendary";
			scarlet_devil.rarity = 0.1; //(%)
			scarlet_devil.damage = 1245;
			scarlet_devil.attack_speed = 30; //(hps)
			scarlet_devil.on_hit_effect = "Bleeding";
			scarlet_devil.unbreakable = true;

			printf("Item info:\n");
			printf("%s\n", scarlet_devil.type);
			printf("%s %s\n", scarlet_devil.charm, scarlet_devil.name);
			printf("Rarity - %f%\n", scarlet_devil.rarity);
			printf("Damage - %i\n", scarlet_devil.damage);
			printf("Attack speed - %i\n", scarlet_devil.attack_speed);
			printf("On hit effect - %s\n", scarlet_devil.on_hit_effect);
		}
		if (number == 2) {}
		if (number == 3) {}
		cout << "Enter the number, or enter 0 to close - ";
		cin >> number;
	}
}