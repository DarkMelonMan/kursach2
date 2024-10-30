#pragma once

/// <summary>
/// Перечисление типов стихийного урона: нестихийный, огонь, магия и молния
/// </summary>

enum Element {
	none, fire, magic, lighting
};

/// <summary>
/// Перечисление типов существ: живые существа, монстр и игрок
/// </summary>

enum EntityType {
	living, monster, player
};

/// <summary>
/// Строковые определния перечисления element
/// </summary>

static const char* elementNames[] = {
	"none", "fire", "magic", "lighting"
};

/// <summary>
/// Строковые определния перечисления entity
/// </summary>

static const char* entityTypes[] = {
	"living", "monster", "player"
};

/// <summary>
/// Структура живых существ, имеет динамическое поле очков здоровья
/// и статическое поле скорости передвижения
/// </summary>

struct LivingEntityStruct {
	char* name = NULL;
	double* healthPoints = NULL;
	double movementSpeed;
};

/// <summary>
/// Структура монстров, содержащая: поле живого существа, базового урона, 
/// стихийного урона, уязвимости к определённой стихии и типа элементального урона.
/// </summary>

struct MonsterEntityStruct {
	LivingEntityStruct entity;
	double baseDamage;
	double elementDamage;
	Element weakness;
	Element damageType;
};

/// <summary>
/// Структура брони, содержащая: поле базовой защиты, стихийной защиты
/// и типа стихийной защиты
/// </summary>


struct ArmorStruct {
	double baseDefence;
	double elementDefence;
	Element defenceType;
};

/// <summary>
/// Структура оружия, содержащая: поле базового урона, стихийного урона
/// и типа стихийного урона
/// </summary>

struct WeaponStruct {
	Element damageType;
	double baseDamage;
	double elementDamage;
};

/// <summary>
/// Структура игрока, содержащая поля: живой сущности, брони и оружия
/// </summary>

struct PlayerEntityStruct {
	LivingEntityStruct entity;
	ArmorStruct equippedArmor;
	WeaponStruct equippedWeapon;
};

/// <summary>
/// Функция создания новой живой сущности
/// </summary>

static LivingEntityStruct livingEntityCreateInstance(char* name, double* healthPoints, double movementSpeed);

/// <summary>
/// Функция ввода полей живой сущности
/// </summary>

static LivingEntityStruct livingEntityInput(EntityType type);

/// <summary>
/// Функция вывода полей живой сущности
/// </summary>

static void livingEntityOutput(LivingEntityStruct livingEntity);

/// <summary>
/// Функция получения урона живой сущностью
/// </summary>

static void livingEntityHurt(LivingEntityStruct livingEntity, double damage);

/// <summary>
/// Функция проверки сущности, жива ли она
/// </summary>

static int isDead(LivingEntityStruct livingEntity);

/// <summary>
/// Функция создания нового монстра
/// </summary>

static MonsterEntityStruct monsterEntityCreateInstance(char* name, double* healthPoints, double movementSpeed, double baseDamage, double elementDamage, Element damageType, Element weakness);

/// <summary>
/// Функция ввода полей монстра
/// </summary>

static MonsterEntityStruct monsterEntityInput();

/// <summary>
/// Функция получения урона монстром
/// </summary>

static void monsterEntityHurt(MonsterEntityStruct monster, double baseDamage, double elementDamage, Element damageType);

/// <summary>
/// Функция атаки монстром игрока
/// </summary>

static void monsterEntityAttack(MonsterEntityStruct monster, PlayerEntityStruct player);

/// <summary>
/// Функция вывода полей монстра
/// </summary>

static void monsterEntityOutput(MonsterEntityStruct monsterEntity);

/// <summary>
/// Функция создания новой брони
/// </summary>

static ArmorStruct armorCreateInstance(double baseDefence, double elementDefence, Element defenceType);

/// <summary>
/// Функция ввода полей брони
/// </summary>

static ArmorStruct armorInput();

/// <summary>
/// Функция вывода полей брони
/// </summary>

static void armorOutput(ArmorStruct armor);

/// <summary>
/// Функция создания нового оружия
/// </summary>

static WeaponStruct weaponCreateInstance(double baseDamage, double elementDamage, Element damageType);

/// <summary>
/// Функция ввода полей оружия
/// </summary>

static WeaponStruct weaponInput();

/// <summary>
/// Функция вывода полей оружия
/// </summary>

static void weaponOutput(WeaponStruct weapon);

/// <summary>
/// Функция создания нового игрока
/// </summary>

static PlayerEntityStruct playerEntityCreateInstance(char* name, double* healthPoints, double movementSpeed, WeaponStruct equippedWeapon, ArmorStruct equippedArmor);

/// <summary>
/// Функция ввода полей игрока
/// </summary>

static PlayerEntityStruct playerEntityInput();

/// <summary>
/// Функция вывода полей игрока
/// </summary>

static void playerEntityOutput(PlayerEntityStruct entity);

/// <summary>
/// Функция получения урона игроком
/// </summary>

static void playerEntityHurt(PlayerEntityStruct player, double damage);

/// <summary>
/// Функция атаки игроком монстра
/// </summary>

static void playerEntityAttack(PlayerEntityStruct player, MonsterEntityStruct monster);
