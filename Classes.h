#pragma once
#include <iostream>
#include "Util.h"
using namespace std;

/// <summary>
/// Класс живых существ, надкласс для классов монстров и игроков
/// </summary>
class LivingEntity {
protected:
	string name;
	double healthPoints;
	double movementSpeed;

	/// <summary>
	/// Получить урон
	/// </summary>
	/// <param name="damage">Получаемый игроком урон</param>
	void hurt(double damage);
	
	/// <summary>
	/// Ввод всех полей
	/// </summary>
	void inputLivingEntityFields();

public:
	
	LivingEntity(string name, double healthPoints, double movementSpeed);
	LivingEntity();
	~LivingEntity() {};
	/// <summary>
	/// Вывод на экран всех полей
	/// </summary>
	void Print();
};

class Armor {
private:
	double baseDefence;
	double elementDefence;
	Element defenceType;
	/// <summary>
	/// Ввод всех полей
	/// </summary>
	void inputArmorFields();
public:
	
	/// <summary>
	/// Получить значение базовой защиты
	/// </summary>
	/// <returns>Базовая защита брони</returns>
	double getBaseDefence();
	
	/// <summary>
	/// Получить значение стихийной защиты
	/// </summary>
	/// <returns>Стихийная защита брони</returns>
	double getElementDefence();
	
	/// <summary>
	/// Получить тип стихийной защиты
	/// </summary>
	/// <returns>Тип стихийной защиты</returns>
	double getDefenceType();
	Armor();
	Armor(double baseDefence, double elementDefence, Element defenceType);
	
	/// <summary>
	/// Вывод на экран всех полей
	/// </summary>
	void Print();
};
class Weapon {
private:
	Element damageType;
	double baseDamage;
	double elementDamage;
	
	/// <summary>
	/// Ввод всех полей
	/// </summary>
	void inputWeaponFields();
public:
	Weapon(double baseDamage, double elementDamage, Element damageType);
	Weapon();

	/// <summary>
	/// Получить базовый урон
	/// </summary>
	/// <returns>Базовый урон оружия</returns>
	double getBaseDamage();

	/// <summary>
	/// Получить стихийный урон
	/// </summary>
	/// <returns>Стихийный урон орежия</returns>
	double getElementDamage();

	/// <summary>
	/// Получить тип стихийного урона
	/// </summary>
	/// <returns>Тип стихийного урона оружия</returns>
	Element getDamageType();
	
	/// <summary>
	/// Вывод всех полей
	/// </summary>
	void Print();
};

class MonsterEntity;

class PlayerEntity : public LivingEntity {
private:
	Armor* armor;
	Weapon* weapon;

	/// <summary>
	/// Ввод всех полей
	/// </summary>
	void inputPlayerEntityFields();
public:
	PlayerEntity(string name, double healthPoints, double movementSpeed, Armor* armor, Weapon* weapon);
	PlayerEntity();

	/// <summary>
	/// Получить объект брони игрока
	/// </summary>
	/// <returns>Обхект брони игрока</returns>
	Armor* getArmor();
	
	/// <summary>
	/// Получить объект оружия игрока
	/// </summary>
	/// <returns>Объект оружия игрока</returns>
	Weapon* getWeapon();

	/// <summary>
	/// Получить урон
	/// </summary>
	/// <param name="baseDamage">Базовый урон</param>
	/// <param name="elementDamage">Стихийный урон</param>
	/// <param name="damageType">Тип стихийного урона</param>
	void Hurt(double baseDamage, double elementDamage, Element damageType);
	
	/// <summary>
	/// Атаковать монстра
	/// </summary>
	/// <param name="monster">Указатель на объект монстра</param>
	void AttackMonster(MonsterEntity* monster);
	
	/// <summary>
	/// Вывод на экран всех полей
	/// </summary>
	void Print();
};

class MonsterEntity : public LivingEntity {
private:
	double baseDamage;
	double elementDamage;
	Element weakness;
	Element damageType;
	
	/// <summary>
	/// Ввод всех полей
	/// </summary>
	void inputMonsterEntityFields();
public:
	MonsterEntity(string name, double healthPoints, double movementSpeed, double baseDamage, double elementDamage, Element weakness, Element damageType);
	MonsterEntity();

	/// <summary>
	/// Получить урон
	/// </summary>
	/// <param name="baseDamage">Базовый урон</param>
	/// <param name="elementDamage">Стихийный урон</param>
	/// <param name="damageType">Тип стихийного урона</param>
	void Hurt(double baseDamage, double elementDamage, Element damageType);
	
	/// <summary>
	/// Атаковать игрока
	/// </summary>
	/// <param name="player">Указатель на объект игрока</param>
	void AttackPlayer(PlayerEntity* player);
	void Print();
};
