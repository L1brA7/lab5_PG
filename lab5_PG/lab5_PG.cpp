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
tuple<sweety *, int, int> read_storage();
void sweety_info(sweety sweety);
void stock_info(sweety *sweeties, int N, bool THICCmode);
void sorter(sweety *stock, int N);

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
			scarlet_devil.damage = 41990;
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
			sweety *stock;
			int chocolate_mass, quantity;
			tie(stock, chocolate_mass, quantity) = read_storage();
			printf("\tAll sweeties:\n");
			stock_info(stock, quantity, 0);
			printf("\tMASS OF CHOCOLATE - %i grams\n", chocolate_mass);
			printf("\n\tTHICC 5k+ callory sweeties:\n");
			stock_info(stock, quantity, 1);
			delete[] stock;
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

void sweety_info(sweety sweety) {
	printf("\n");
	printf("\t<<%s>>\n", sweety.name);
	printf("\t%i grams\n", sweety.mass);
	printf("\t%i ccals per 100g\n", sweety.callor);
	printf("\tExpires: %s\n", sweety.exp_date);
	printf("\n");
}

void stock_info(sweety* sweeties, int N, bool THICCmode) {
	if (THICCmode) {
		for (int i = 0; i < N; i++) {
			if (sweeties[i].callor > 500)
				sweety_info(sweeties[i]);
		}
	}
	else {
		for (int i = 0; i < N; i++) {
			sweety_info(sweeties[i]);
		}
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

tuple <sweety*, int, int> read_storage() {
	int chocolate_mass = 0, prod_count = 0;
	ifstream prods;
	char prod_info[255];
	char *stat;
	prods.open("prods.txt");
	while (prods.getline(prod_info, 255, '\n')) prod_count++;
	sweety* stock = new sweety[prod_count];
	prods.close();

	prods.open("prods.txt");
	int i = 0;
	while (prods.getline(prod_info, 255, '\n')) {
		stat = strtok(prod_info, "/");
		stock[i].mass = stoi(stat);
		stat = strtok(NULL, "/");
		strcpy(stock[i].name, stat);
		stat = strtok(NULL, "/");
		strcpy(stock[i].exp_date, stat);
		stat = strtok(NULL, "/");
		stock[i].callor = stoi(stat);
		if(stock[i].callor >= 420 && stock[i].callor <= 600) {
			chocolate_mass += stock[i].mass;
		}
		i++;
	}
	sorter(stock, prod_count);
	prods.close();
	return make_tuple(stock, chocolate_mass, prod_count);
}

void sorter(sweety* stock, int N) {
	sweety temp;
	for (int i = 1; i <= N; i++) {
		for (int j = i - 1; j > 0; j--) {
			if (int(stock[j].name[0]) < int(stock[j - 1].name[0])) {
				temp = stock[j];
				stock[j] = stock[j - 1];
				stock[j - 1] = temp;
			}
		}
	}
}