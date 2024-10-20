#pragma once

enum Element {
	none, fire, magic, lighting
};

enum EntityType {
	living, monster, player
};

static const char* elementNames[] = {
	"none", "fire", "magic", "lighting"
};

static const char* entityTypes[] = {
	"living", "monster", "player"
};

struct LivingEntity {
	double* healthPoints;
	double movementSpeed;
};

struct MonsterEntity {
	LivingEntity entity;
	double baseDamage;
	double elementDamage;
	Element weakness;
	Element damageType;
};

struct Armor {
	double baseDefence;
	double elementDefence;
	Element defenceType;
};

struct Weapon {
	Element damageType;
	double baseDamage;
	double elementDamage;
};


struct PlayerEntity {
	LivingEntity entity;
	Armor equippedArmor;
	Weapon equippedWeapon;
};

static LivingEntity livingEntityCreateInstance(double* healthPoints, double movementSpeed);

static LivingEntity livingEntityInput(EntityType type);
static void livingEntityOutput(LivingEntity livingEntity, EntityType type);
static void livingEntityHurt(LivingEntity livingEntity, double damage);
static int isDead(LivingEntity livingEntity);
static MonsterEntity monsterEntityCreateInstance(double* healthPoints, double movementSpeed, double baseDamage, double elementDamage, Element damageType, Element weakness);
static MonsterEntity monsterEntityInput();
static void monsterEntityHurt(MonsterEntity monster, double baseDamage, double elementDamage, Element damageType);
static void monsterEntityAttack(MonsterEntity monster, PlayerEntity player);
static void monsterEntityOutput(MonsterEntity monsterEntity);

static Armor armorCreateInstance(double baseDefence, double elementDefence, Element defenceType);
static Armor armorInput();

static void armorOutput(Armor armor);

static Weapon weaponCreateInstance(double baseDamage, double elementDamage, Element damageType);

static Weapon weaponInput();

static void weaponOutput(Weapon weapon);
static PlayerEntity playerEntityCreateInstance(double* healthPoints, double movementSpeed, Weapon equippedWeapon, Armor equippedArmor);

static PlayerEntity playerEntityInput();
static void playerEntityOutput(PlayerEntity entity);
static void playerEntityHurt(PlayerEntity player, double damage);
static void playerEntityAttack(PlayerEntity player, MonsterEntity monster);