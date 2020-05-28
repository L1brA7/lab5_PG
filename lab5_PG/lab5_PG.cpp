#include <iostream>
#include <string>
#include <fstream>
#include <tuple>

#pragma warning(disable : 4996)

using namespace std;

struct item {
	char name[20];
	char type[20];
	char charm[20];
	double rarity; //(%)
	int damage;
	int attack_speed; //(hps)
};

struct sweety {
	int mass;
	char name[20];
	char exp_date[20];
	int callor;
};

void inventory_info(item* inventory, int N);
void item_info(item item);
tuple<item*, int> read_inventory();

int main() {
	int number;
	cout << "Enter the number, or enter 0 to close - ";
	cin >> number;
	while (number) {
		if (number == 1) {
			item scarlet_devil;
			strcpy(scarlet_devil.name, "Scarlet Devil");
			strcpy(scarlet_devil.type, "Weapon");
			strcpy(scarlet_devil.charm, "Legendary");
			scarlet_devil.rarity = 0.1; //(%)
			scarlet_devil.damage = 1245;
			scarlet_devil.attack_speed = 30; //(hps)
			item_info(scarlet_devil);
		}
		if (number == 2) {
			item *inventory;
			int N;
			tie(inventory, N) = read_inventory();
			inventory_info(inventory, N);
			delete[] inventory;
		}
		if (number == 3) {
			
		}
		cout << "Enter the number, or enter 0 to close - ";
		cin >> number;
	}
}

void item_info(item item) {
	printf("\n");
	printf("\tItem info:\n");
	printf("\t%s\n", item.type);
	printf("\t%s %s\n", item.charm, item.name);
	printf("\tRarity - %.2f%c\n", item.rarity, '%');
	printf("\tDamage - %i\n", item.damage);
	printf("\tAttack speed - %i\n", item.attack_speed);
	printf("\n");
}

void inventory_info(item* inventory, int N) {
	for (int i = 0; i < N; i++) {
		item_info(inventory[i]);
	}
}

tuple <item *, int> read_inventory() {
	ifstream items;
	items.open("items.txt");
	int N = 0;
	char item_info[255];
	char *stat;
	while (items.getline(item_info, 255, '\n')) N++;
	item *inventory = new item[N];
	items.close();

	items.open("items.txt");
	int i = 0;
	while (items.getline(item_info, 255, '\n')) {
		stat = strtok(item_info, "/");
		strcpy(inventory[i].name, stat);
		stat = strtok(NULL, "/");
		strcpy(inventory[i].type, stat);
		stat = strtok(NULL, "/");
		strcpy(inventory[i].charm, stat);
		stat = strtok(NULL, "/");
		inventory[i].rarity = stod(stat);
		stat = strtok(NULL, "/");
		inventory[i].damage = stoi(stat);
		stat = strtok(NULL, "/");
		inventory[i].attack_speed = stoi(stat);
		i++;
	}
	items.close();
	return make_tuple(inventory, N);
}