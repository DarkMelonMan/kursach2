#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include "Structures.h"

static LivingEntityStruct livingEntityCreateInstance(char* name, double* healthPoints, double movementSpeed) {
	LivingEntityStruct livingEntity;
	livingEntity.name = name;
	livingEntity.healthPoints = healthPoints;
	livingEntity.movementSpeed = movementSpeed;
	return livingEntity;
}

static LivingEntityStruct livingEntityInput(EntityType type) {
	char* name = (char*)calloc(20, sizeof(char));
	double* healthPoints = (double*)malloc(sizeof(double));
	double movementSpeed;
	while (getchar() != '\n');
	printf("Enter a name of %s entity: ", entityTypes[type]);
	do {
		fgets(name, 20, stdin);
	} while (strlen(name) == 0);
	name[strlen(name) - 1] = '\0';
	printf("\nHealth points of %s entity input: ", name);
	do {
		scanf("%lf", healthPoints);
		if (*healthPoints <= 0)
			printf("\nHealth points of %s entity can't be <= 0. Try again: ", name);
	} while (*healthPoints <= 0);
	printf("\nMovement speed of %s entity input: ", name);
	do {
		scanf("%lf", &movementSpeed);
		if (movementSpeed <= 0)
			printf("\nMovement speed of %s entity can't be <= 0. Try again: ", name);
	} while (movementSpeed <= 0);
	return livingEntityCreateInstance(name, healthPoints, movementSpeed);
}

static void livingEntityOutput(LivingEntityStruct livingEntity) {
	printf("\n\n%s health points = %g, movement speed = %g", livingEntity.name, *livingEntity.healthPoints, livingEntity.movementSpeed);
	if (isDead(livingEntity))
		printf("\n%s is dead!", livingEntity.name);
}

static void livingEntityHurt(LivingEntityStruct livingEntity, double damage) {
	*livingEntity.healthPoints -= damage;
	isDead(livingEntity);
}

static int isDead(LivingEntityStruct livingEntity) {
	if (*livingEntity.healthPoints <= 0) {
		*livingEntity.healthPoints = 0;
		return 1;
	}
	else return 0;
}

static MonsterEntityStruct monsterEntityCreateInstance(char* name, double* healthPoints, double movementSpeed, double baseDamage, double elementDamage, Element damageType, Element weakness) {
	MonsterEntityStruct monsterEntity;
	monsterEntity.entity = livingEntityCreateInstance(name, healthPoints, movementSpeed);
	monsterEntity.baseDamage = baseDamage;
	monsterEntity.elementDamage = elementDamage;
	monsterEntity.damageType = damageType;
	monsterEntity.weakness = weakness;
	return monsterEntity;
}

static MonsterEntityStruct monsterEntityInput() {
	LivingEntityStruct entity = livingEntityInput(monster);
	double baseDamage;
	double elementDamage = 0;
	int damageType;
	int weakness;
	printf("\nBase damage of %s entity input: ", entity.name);
	do {
		scanf("%lf", &baseDamage);
		if (baseDamage <= 0)
			printf("\nBase damage can't be <= 0. Try again: ");
	} while (baseDamage <= 0);
	printf("Elemental type of damage of %s entity input (0 - none, 1 - fire, 2 - magic, 3 - lighting): ", entity.name);
	do {
		scanf("%d", &damageType);
		if (damageType < 0 || damageType > 3)
			printf("\nDamage type must be between 0 and 3. Try again: ");
	} while (damageType < 0 || damageType > 3);

	if (damageType != 0) {
		printf("\nElemental damage of %s entity input: ", entity.name);
		do {
			scanf("%lf", &elementDamage);
			if (elementDamage < 0)
				printf("\nElemental damage can't be < 0. Try again: ");
		} while (elementDamage < 0);
	}

	printf("%s entity weakness to elemental type of damage input (0 - none, 1 - fire, 2 - magic, 3 - lighting): ", entity.name);
	do {
		scanf("%d", &weakness);
		if (weakness < 0 || weakness > 3)
			printf("\nWeakness type must be between 0 and 3. Try again: ");
	} while (weakness < 0 || weakness > 3);
	return monsterEntityCreateInstance(entity.name, entity.healthPoints, entity.movementSpeed, baseDamage, elementDamage, (Element)damageType, (Element)weakness);
}

static void monsterEntityHurt(MonsterEntityStruct monster, double baseDamage, double elementDamage, Element damageType) {
	double damage = baseDamage;
	if (monster.weakness == damageType && monster.weakness != none)
		damage += elementDamage;
	else if (monster.weakness != none)
		damage += elementDamage * 0.5;
	livingEntityHurt(monster.entity, damage);
}

static void monsterEntityAttack(MonsterEntityStruct monster, PlayerEntityStruct player) {
	if (!isDead(monster.entity)) {
		double damage = monster.baseDamage * (1 - player.equippedArmor.baseDefence / 100);
		double elementDamage = 0;
		if (player.equippedArmor.defenceType == monster.damageType && monster.damageType != none)
			elementDamage = monster.elementDamage * (1 - player.equippedArmor.elementDefence / 100);
		else if (monster.damageType != none) elementDamage = monster.elementDamage;
		damage += elementDamage;
		playerEntityHurt(player, damage);
	}
}
static void monsterEntityOutput(MonsterEntityStruct monsterEntity) {
	printf("%s entity base damage = %g\n%s entity elemental damage = %g\n%s entity damage type: %s\n%s entity weakness: %s", monsterEntity.entity.name, monsterEntity.baseDamage, monsterEntity.entity.name, monsterEntity.elementDamage, monsterEntity.entity.name, elementNames[monsterEntity.damageType], monsterEntity.entity.name, elementNames[monsterEntity.weakness]);
	livingEntityOutput(monsterEntity.entity);
}

static ArmorStruct armorCreateInstance(double baseDefence, double elementDefence, Element defenceType) {
	ArmorStruct armor;
	armor.baseDefence = baseDefence;
	armor.elementDefence = elementDefence;
	armor.defenceType = defenceType;
	return armor;
}

static ArmorStruct armorInput() {
	double baseDefence;
	double elementDefence = 0;
	Element defenceType;
	printf("\nBase defence of armor input (in %%): ");
	do {
		scanf("%lf", &baseDefence);
		if (baseDefence < 0 || baseDefence > 100)
			printf("\nBase defence must be between 0 and 100. Try again: ");
	} while (baseDefence < 0 || baseDefence > 100);
	printf("Elemental type of armor defence input (0 - none, 1 - fire, 2 - magic, 3 - lighting): ");
	do {
		scanf("%d", &defenceType);
		if (defenceType < 0 || defenceType > 3)
			printf("\nDefence type must be between 0 and 3. Try again: ");
	} while (defenceType < 0 || defenceType > 3);
	if (defenceType != 0) {
		printf("\nElemental defence of armor input (in %%): ");
		do {
			scanf("%lf", &elementDefence);
			if (elementDefence < 0 || elementDefence > 100)
				printf("\nElemental defence must be between 0 and 100. Try again: ");
		} while (elementDefence < 0 || elementDefence > 100);
	}
	return armorCreateInstance(baseDefence, elementDefence, defenceType);
}

static void armorOutput(ArmorStruct armor) {
	printf("\nBase armor defence = %g%%\nElemental armor defence = %g%%\nArmor defence type: %s", armor.baseDefence, armor.elementDefence, elementNames[armor.defenceType]);
}

static WeaponStruct weaponCreateInstance(double baseDamage, double elementDamage, Element damageType) {
	WeaponStruct weapon;
	weapon.baseDamage = baseDamage;
	weapon.elementDamage = elementDamage;
	weapon.damageType = damageType;
	return weapon;
}

static WeaponStruct weaponInput() {
	double baseDamage;
	double elementDamage = 0;
	Element damageType;
	printf("\nBase weapon damage input: ");
	do {
		scanf("%lf", &baseDamage);
		if (baseDamage <= 0)
			printf("\nDamage can't be <= 0. Try again: ");
	} while (baseDamage <= 0);
	printf("Elemental type of weapon damage input (0 - none, 1 - fire, 2 - magic, 3 - lighting): ");
	do {
		scanf("%d", &damageType);
		if (damageType < 0 || damageType > 3)
			printf("\nDamage type must be between 0 and 3. Try again: ");
	} while (damageType < 0 || damageType > 3);
	if (damageType != 0) {
		printf("\nElemental weapon damage input: ");
		do {
			scanf("%lf", &elementDamage);
			if (elementDamage < 0)
				printf("\nElemental damage can't be < 0. Try again: ");
		} while (elementDamage < 0);
	}
	return weaponCreateInstance(baseDamage, elementDamage, damageType);
}

static void weaponOutput(WeaponStruct weapon) {
	printf("\nBase damage of weapon = %g\nElemental damage of weapon = %g\nDamage type of weapon: %s", weapon.baseDamage, weapon.elementDamage, elementNames[weapon.damageType]);
}

static PlayerEntityStruct playerEntityCreateInstance(char* name, double* healthPoints, double movementSpeed, WeaponStruct equippedWeapon, ArmorStruct equippedArmor) {
	PlayerEntityStruct player;
	player.entity = livingEntityCreateInstance(name, healthPoints, movementSpeed);
	player.equippedWeapon = equippedWeapon;
	player.equippedArmor = equippedArmor;
	return player;
}

static PlayerEntityStruct playerEntityInput() {
	LivingEntityStruct playerEntity = livingEntityInput(player);
	WeaponStruct equippedWeapon = weaponInput();
	ArmorStruct equippedArmor = armorInput();
	return playerEntityCreateInstance(playerEntity.name, playerEntity.healthPoints, playerEntity.movementSpeed, equippedWeapon, equippedArmor);
}

static void playerEntityOutput(PlayerEntityStruct entity) {
	printf("\nPlayer armor:\n");
	armorOutput(entity.equippedArmor);
	printf("\n\nPlayer weapon:\n");
	weaponOutput(entity.equippedWeapon);
	livingEntityOutput(entity.entity);
}

static void playerEntityHurt(PlayerEntityStruct player, double damage) {
	livingEntityHurt(player.entity, damage);
}

static void playerEntityAttack(PlayerEntityStruct player, MonsterEntityStruct monster) {
	if (!isDead(player.entity))
		monsterEntityHurt(monster, player.equippedWeapon.baseDamage, player.equippedWeapon.elementDamage, player.equippedWeapon.damageType);
}
