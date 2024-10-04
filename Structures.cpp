#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS

enum EntityTypes {
	living = 1,
	monster = 2,
	player = 3
};

struct LivingEntity {
	double healthPoints;
	double movementSpeed;
};
struct MonsterEntity {
	LivingEntity entity;
	double damage;
};
struct Item {
	char *name;
};
struct WeaponItem {
	Item item;
	double damage;
};
struct Inventory {
	Item *items;
	int count;
};
struct PlayerEntity {
	LivingEntity entity;
	Inventory playerInventory;
	WeaponItem equippedWeapon;
};


LivingEntity createInstance(double healthPoints, double movementSpeed) {
	LivingEntity livingEntity;
	livingEntity.healthPoints = healthPoints;
	livingEntity.movementSpeed = movementSpeed;
	return livingEntity;
}

LivingEntity livingEntityInput() {
	double healthPoints;
	double movementSpeed;
	printf("Health points of living entity input: ");
	do {
		scanf("%lf", &healthPoints);
		if (healthPoints <= 0)
			printf("\nHealth points of living entity can't be <= 0. Try again: ");
	} while (healthPoints <= 0);
	printf("\nMovement speed of living entity input: ");
	do {
		scanf("%lf", &movementSpeed);
		if (movementSpeed <= 0)
			printf("\nMovement speed of living entity can't be <= 0. Try again: ");
	} while (movementSpeed <= 0);
	return createInstance(healthPoints, movementSpeed);
}

void livingEntityOutput(LivingEntity livingEntity, EntityTypes type) {
	char entityType[20];
	switch (type) {
	case (int)living:
		strcpy(entityType, "Living entity");
		break;
	case (int)monster:
		strcpy(entityType, "Monster entity");
		break;
	case (int)player:
		strcpy(entityType, "Player entity");
		break;
	}
	printf("%s health points = %lf, movement speed = %lf", entityType, livingEntity.healthPoints);
	if (livingEntity.healthPoints == 0)
		printf("\n%s is dead!", entityType);
}

void livingEntityHurt(LivingEntity livingEntity, double damage) {
	livingEntity.healthPoints -= damage;
	if (livingEntity.healthPoints <= 0)
		livingEntity.healthPoints = 0;
}

MonsterEntity createInstance(double healthPoints, double movementSpeed, double damage) {
	MonsterEntity monsterEntity;
	monsterEntity.entity = createInstance(healthPoints, movementSpeed);
	monsterEntity.damage = damage;
	return monsterEntity;
}

MonsterEntity MonsterEntityInput() {
	LivingEntity entity = livingEntityInput();
	double damage;
	printf("Damage of monster entity input: ");
	do {
		scanf("%lf");
		if (damage <= 0)
			printf("\nDamage can't be <= 0. Try again: ");
	} while (damage <= 0);
	return createInstance(entity.healthPoints, entity.movementSpeed, damage);
}

void monsterEntityHurt(MonsterEntity monster, double damage) {
	livingEntityHurt(monster.entity, damage);
}

void monsterEntityAttack(MonsterEntity monster, PlayerEntity player) {
	playerEntityHurt(player, monster.damage);
}

void monsterEntityOutput(MonsterEntity monsterEntity) {
	printf("Monster entity damage = %lf\n", monsterEntity.damage);
	livingEntityOutput(monsterEntity.entity, monster);
}

Item createInstance(char* name) {
	Item item;
	item.name = name;
	return item;
}

Item itemInput() {
	char* name = (char*)calloc(30, sizeof(char));
	printf("Item name input: ");
	do {
		fgets(name, 30, stdin);
		if (strlen(name) == 0)
			printf("\nTry again: ");
	} while (strlen(name) == 0);
	return createInstance(name);
}

void itemOutput(Item item) {
	printf("Item name: %s\n", item.name);
}

WeaponItem createInstance(char* name, double damage) {
	WeaponItem weapon;
	weapon.item = createInstance(name);
	weapon.damage = damage;
	return weapon;
}

WeaponItem weaponInput() {
	Item weapon = itemInput();
	double damage;
	printf("Damage of weapon input: ");
	do {
		scanf("%lf", &damage);
		if (damage <= 0)
			printf("\nDamage can't be <= 0. Try again: ");
	} while (damage <= 0);
	return createInstance(weapon.name, damage);
}

void weaponItemOutput(WeaponItem weapon) {
	itemOutput(weapon.item);
	printf("\nDamage of weapon = %lf", weapon.damage);
}

Inventory createInstance(Item *items, int count) {
	Inventory inventory;
	inventory.items = items;
	inventory.count = count;
	return inventory;
}

Inventory inventoryInput() {
	int count;
	printf("Count of inventory items input: ");
	do {
		scanf("%d", &count);
		if (count <= 0 || count > 20)
			printf("\nCount of inventory items must be between 1 and 20");
	} while (count <= 0 || count > 20);
	Item* items = (Item*) calloc(count, sizeof(Item));
	printf("Names of %d items input: ", count);
	for (int i = 0; i < count; i++)
		items[i] = itemInput();
	return createInstance(items, count);
}

void inventoryOutput(Inventory inventory) {
	for (int i = 0; i < inventory.count; i++)
		itemOutput(inventory.items[i]);
}

PlayerEntity createInstance(double healthPoints, double movementSpeed, Inventory playerInventory, WeaponItem equippedWeapon) {
	PlayerEntity player;
	player.entity = createInstance(healthPoints, movementSpeed);
	player.playerInventory = playerInventory;
	player.equippedWeapon = equippedWeapon;
	return player;
}

PlayerEntity playerEntityInput() {
	LivingEntity player = livingEntityInput();
	Inventory playerInventory = inventoryInput();
	WeaponItem equippedWeapon = weaponInput();
}

void playerEntityOutput(PlayerEntity entity) {
	printf("Player inventory:\n");
	inventoryOutput(entity.playerInventory);
	printf("Player weapon:\n");
	weaponItemOutput(entity.equippedWeapon);
	livingEntityOutput(entity.entity, player);
}

void playerEntityHurt(PlayerEntity player, double damage) {
	livingEntityHurt(player.entity, damage);
}

void playerEntityAttack(PlayerEntity player, MonsterEntity monster) {
	monsterEntityHurt(monster, player.equippedWeapon.damage);
}
