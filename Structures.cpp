#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

struct LivingEntity {
	double healthPoints;
	double movementSpeed;
};
struct MonsterEntity {
	LivingEntity entity;
	double damage;
};
struct Item {
	char name[30];
};
struct WeaponItem {
	Item weapon;
	double damage;
};
struct Inventory {
	Item items[20];
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

void livingEntityOutput(LivingEntity livingEntity, int type) {
	char entityType[20];
	switch (type) {
	case 1:
		strcpy(entityType, "Living entity");
		break;
	case 2:
		strcpy(entityType, "Monster entity");
		break;
	case 3:
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
	livingEntityOutput(monsterEntity.entity, 2);
}

void playerEntityHurt(PlayerEntity player, double damage) {
	livingEntityHurt(player.entity, damage);
}
