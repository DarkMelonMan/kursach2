#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include "Structures.h"

static LivingEntity livingEntityCreateInstance(double* healthPoints, double movementSpeed) {
	LivingEntity livingEntity;
	livingEntity.healthPoints = healthPoints;
	livingEntity.movementSpeed = movementSpeed;
	return livingEntity;
}

static LivingEntity livingEntityInput(EntityType type) {
	double* healthPoints = (double*)malloc(sizeof(double));
	double movementSpeed;
	printf("\nHealth points of %s entity input: ", entityTypes[(int)type]);
	do {
		while (getchar() != '\n');
		scanf("%lf", healthPoints);
		if (*healthPoints <= 0)
			printf("\nHealth points of %s entity can't be <= 0. Try again: ", entityTypes[(int)type]);
	} while (*healthPoints <= 0);
	printf("\nMovement speed of %s entity input: ", entityTypes[(int)type]);
	do {
		scanf("%lf", &movementSpeed);
		if (movementSpeed <= 0)
			printf("\nMovement speed of %s entity can't be <= 0. Try again: ", entityTypes[(int)type]);
	} while (movementSpeed <= 0);
	return livingEntityCreateInstance(healthPoints, movementSpeed);
}

static void livingEntityOutput(LivingEntity livingEntity, EntityType type) {
	printf("\n\n%s health points = %g, movement speed = %g", entityTypes[(int)type], *livingEntity.healthPoints, livingEntity.movementSpeed);
	if (*livingEntity.healthPoints == 0)
		printf("\n%s is dead!", entityTypes[(int)type]);
}

static void livingEntityHurt(LivingEntity livingEntity, double damage) {
	*livingEntity.healthPoints -= damage;
}

static int isDead(LivingEntity livingEntity) {
	if (*livingEntity.healthPoints <= 0) {
		*livingEntity.healthPoints = 0;
		return 1;
	}
	else return 0;
}

static MonsterEntity monsterEntityCreateInstance(double* healthPoints, double movementSpeed, double baseDamage, double elementDamage, Element damageType, Element weakness) {
	MonsterEntity monsterEntity;
	monsterEntity.entity = livingEntityCreateInstance(healthPoints, movementSpeed);
	monsterEntity.baseDamage = baseDamage;
	monsterEntity.elementDamage = elementDamage;
	monsterEntity.damageType = damageType;
	monsterEntity.weakness = weakness;
	return monsterEntity;
}

static MonsterEntity monsterEntityInput() {
	LivingEntity entity = livingEntityInput(monster);
	double baseDamage;
	double elementDamage = 0;
	int damageType;
	int weakness;
	printf("\nBase damage of monster entity input: ");
	do {
		scanf("%lf", &baseDamage);
		if (baseDamage <= 0)
			printf("\nBase damage can't be <= 0. Try again: ");
	} while (baseDamage <= 0);
	printf("Elemental type of damage of monster entity input (0 - none, 1 - fire, 2 - magic, 3 - lighting): ");
	do {
		scanf("%d", &damageType);
		if (damageType < 0 || damageType > 3)
			printf("\nDamage type must be between 0 and 3. Try again: ");
	} while (damageType < 0 || damageType > 3);
	
	if (damageType != 0) {
		printf("\nElemental damage of monster entity input: ");
		do {
			scanf("%lf", &elementDamage);
			if (elementDamage < 0)
				printf("\nElemental damage can't be < 0. Try again: ");
		} while (elementDamage < 0);
	}
	
	printf("Monster entity weakness to elemental type of damage input (0 - none, 1 - fire, 2 - magic, 3 - lighting): ");
	do {
		scanf("%d", &weakness);
		if (weakness < 0 || weakness > 3)
			printf("\nWeakness type must be between 0 and 3. Try again: ");
	} while (weakness < 0 || weakness > 3);
	return monsterEntityCreateInstance(entity.healthPoints, entity.movementSpeed, baseDamage, elementDamage, (Element)damageType, (Element)weakness);
}

static void monsterEntityHurt(MonsterEntity monster, double baseDamage, double elementDamage, Element damageType) {
	double damage = baseDamage;
	if (monster.weakness == damageType)
		damage += elementDamage;
	else if (monster.weakness != none)
		damage += elementDamage * 0.5;
	livingEntityHurt(monster.entity, damage);
}

static void monsterEntityAttack(MonsterEntity monster, PlayerEntity player) {
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
static void monsterEntityOutput(MonsterEntity monsterEntity) {
	printf("Monster entity base damage = %g\nMonster entity elemental damage = %g\nMonster entity damage type: %s\nMonster entity weakness: %s", monsterEntity.baseDamage, monsterEntity.elementDamage, elementNames[monsterEntity.damageType], elementNames[monsterEntity.weakness]);
	livingEntityOutput(monsterEntity.entity, monster);
}

static Armor armorCreateInstance(double baseDefence, double elementDefence, Element defenceType) {
	Armor armor;
	armor.baseDefence = baseDefence;
	armor.elementDefence = elementDefence;
	armor.defenceType = defenceType;
	return armor;
}

static Armor armorInput() {
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

static void armorOutput(Armor armor) {
	printf("\nBase armor defence = %g%%\nElemental armor defence = %g%%\nArmor defence type: %s", armor.baseDefence, armor.elementDefence, elementNames[armor.defenceType]);
}

static Weapon weaponCreateInstance(double baseDamage, double elementDamage, Element damageType) {
	Weapon weapon;
	weapon.baseDamage = baseDamage;
	weapon.elementDamage = elementDamage;
	weapon.damageType = damageType;
	return weapon;
}

static Weapon weaponInput() {
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

static void weaponOutput(Weapon weapon) {
	printf("\nBase damage of weapon = %g\nElemental damage of weapon = %g\nDamage type of weapon: %s", weapon.baseDamage, weapon.elementDamage, elementNames[weapon.damageType]);
}

static PlayerEntity playerEntityCreateInstance(double* healthPoints, double movementSpeed, Weapon equippedWeapon, Armor equippedArmor) {
	PlayerEntity player;
	player.entity = livingEntityCreateInstance(healthPoints, movementSpeed);
	player.equippedWeapon = equippedWeapon;
	player.equippedArmor = equippedArmor;
	return player;
}

static PlayerEntity playerEntityInput() {
	LivingEntity playerEntity = livingEntityInput(player);
	Weapon equippedWeapon = weaponInput();
	Armor equippedArmor = armorInput();
	return playerEntityCreateInstance(playerEntity.healthPoints, playerEntity.movementSpeed, equippedWeapon, equippedArmor);
}

static void playerEntityOutput(PlayerEntity entity) {
	printf("\nPlayer armor:\n");
	armorOutput(entity.equippedArmor);
	printf("\n\nPlayer weapon:\n");
	weaponOutput(entity.equippedWeapon);
	livingEntityOutput(entity.entity, player);
}

static void playerEntityHurt(PlayerEntity player, double damage) {
	livingEntityHurt(player.entity, damage);
}

static void playerEntityAttack(PlayerEntity player, MonsterEntity monster) {
	if (!isDead(player.entity))
		monsterEntityHurt(monster, player.equippedWeapon.baseDamage, player.equippedWeapon.elementDamage, player.equippedWeapon.damageType);
}