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

struct LivingEntity {
	double* healthPoints;
	double movementSpeed;
};

/// <summary>
/// Структура монстров, содержащая: поле живого существа, базового урона, 
/// стихийного урона, уязвимости к определённой стихии и типа элементального урона.
/// </summary>

struct MonsterEntity {
	LivingEntity entity;
	double baseDamage;
	double elementDamage;
	Element weakness;
	Element damageType;
};

/// <summary>
/// Структура брони, содержащая: поле базовой защиты, стихийной защиты
/// и типа стихийной защиты
/// </summary>


struct Armor {
	double baseDefence;
	double elementDefence;
	Element defenceType;
};

/// <summary>
/// Структура оружия, содержащая: поле базового урона, стихийного урона
/// и типа стихийного урона
/// </summary>

struct Weapon {
	Element damageType;
	double baseDamage;
	double elementDamage;
};

/// <summary>
/// Структура игрока, содержащая поля: живой сущности, брони и оружия
/// </summary>

struct PlayerEntity {
	LivingEntity entity;
	Armor equippedArmor;
	Weapon equippedWeapon;
};

/// <summary>
/// Функция создания новой живой сущности
/// </summary>

static LivingEntity livingEntityCreateInstance(double* healthPoints, double movementSpeed);

/// <summary>
/// Функция ввода полей живой сущности
/// </summary>

static LivingEntity livingEntityInput(EntityType type);

/// <summary>
/// Функция вывода полей живой сущности
/// </summary>

static void livingEntityOutput(LivingEntity livingEntity, EntityType type);

/// <summary>
/// Функция получения урона живой сущностью
/// </summary>

static void livingEntityHurt(LivingEntity livingEntity, double damage);

/// <summary>
/// Функция проверки сущности, жива ли она
/// </summary>

static int isDead(LivingEntity livingEntity);

/// <summary>
/// Функция создания нового монстра
/// </summary>

static MonsterEntity monsterEntityCreateInstance(double* healthPoints, double movementSpeed, double baseDamage, double elementDamage, Element damageType, Element weakness);

/// <summary>
/// Функция ввода полей монстра
/// </summary>

static MonsterEntity monsterEntityInput();

/// <summary>
/// Функция получения урона монстром
/// </summary>

static void monsterEntityHurt(MonsterEntity monster, double baseDamage, double elementDamage, Element damageType);

/// <summary>
/// Функция атаки монстром игрока
/// </summary>

static void monsterEntityAttack(MonsterEntity monster, PlayerEntity player);

/// <summary>
/// Функция вывода полей монстра
/// </summary>

static void monsterEntityOutput(MonsterEntity monsterEntity);

/// <summary>
/// Функция создания новой брони
/// </summary>

static Armor armorCreateInstance(double baseDefence, double elementDefence, Element defenceType);

/// <summary>
/// Функция ввода полей брони
/// </summary>

static Armor armorInput();

/// <summary>
/// Функция вывода полей брони
/// </summary>

static void armorOutput(Armor armor);

/// <summary>
/// Функция создания нового оружия
/// </summary>

static Weapon weaponCreateInstance(double baseDamage, double elementDamage, Element damageType);

/// <summary>
/// Функция ввода полей оружия
/// </summary>

static Weapon weaponInput();

/// <summary>
/// Функция вывода полей оружия
/// </summary>

static void weaponOutput(Weapon weapon);

/// <summary>
/// Функция создания нового игрока
/// </summary>

static PlayerEntity playerEntityCreateInstance(double* healthPoints, double movementSpeed, Weapon equippedWeapon, Armor equippedArmor);

/// <summary>
/// Функция ввода полей игрока
/// </summary>

static PlayerEntity playerEntityInput();

/// <summary>
/// Функция вывода полей игрока
/// </summary>

static void playerEntityOutput(PlayerEntity entity);

/// <summary>
/// Функция получения урона игроком
/// </summary>

static void playerEntityHurt(PlayerEntity player, double damage);

/// <summary>
/// Функция атаки игроком монстра
/// </summary>

static void playerEntityAttack(PlayerEntity player, MonsterEntity monster);
