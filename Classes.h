#pragma once
#include <iostream>
using namespace std;

class LivingEntity {
protected:
	string name;
	double healthPoints;
	double movementSpeed;
	void hurt(double damage) {
		healthPoints -= damage;
		if (healthPoints < 0)
			healthPoints = 0;
		cout << endl << name << " entity is dead. Calling destructor";
		delete this;
	}
	void inputFields() {
		cout << "Enter a name for a new living entity: ";
		do {
			cin >> name;
			if (name.empty())
				cout << endl << "Invalid name. Try again: ";
		} while (name.empty());
		cout << endl << "Enter health points of " << name << " entity: ";
		do {
			cin >> healthPoints;
			if (healthPoints <= 0)
				cout << endl << "Invalid health points. Try again: ";
		} while (healthPoints <= 0);
		cout << endl << "Enter movement speed of " << name << " entity: ";
		do {
			cin >> movementSpeed;
			if (movementSpeed <= 0)
				cout << endl << "Invalid movement speed. Try again: ";
		} while (movementSpeed <= 0);
		cout << endl << name << " entity created!";
	}
public:
	LivingEntity(string name, double healthPoints, double movementSpeed) {
		this->name = name;
		this->healthPoints = healthPoints;
		this->movementSpeed = movementSpeed;
	}
	LivingEntity() {
		inputFields();
	}
	~LivingEntity() {};
	void PrintOnScreen() {
		cout << endl << endl << name << " - living entity:";
		cout << endl << "Health points: " << healthPoints;
		cout << endl << "Movement speed: " << movementSpeed;
	}
};

class MonsterEntity: LivingEntity {
private:
	double baseDamage;
	double elementDamage;
	Element weakness;
	Element damageType;
public:
	MonsterEntity(string name, double healthPoints, double movementSpeed, double baseDamage, double elementDamage, Element weakness, Element damageType) {
		this->name = name;
		this->healthPoints = healthPoints;
		this->movementSpeed = movementSpeed;
		this->baseDamage = baseDamage;
		this->elementDamage = elementDamage;
		this->weakness = weakness;
		this->damageType = damageType;
	}
	MonsterEntity() {
		inputFields();
		int weakness;
		int damageType;
		cout << endl << "Enter base damage of " << name << " monster entity: ";
		do {
			cin >> baseDamage;
			if (baseDamage <= 0)
				cout << endl << "Invalid base damage. Try again: ";
		} while (baseDamage <= 0);
		cout << endl << "Enter elemental weakness of " << name << " monster entity (0 - none, 1 - fire, 2 - magic, 3 - lighting): ";
		do {
			cin >> weakness;
			if (weakness < 0 || weakness > 3)
				cout << endl << "Invalid weakness type. Try again: ";
		} while (weakness < 0 || weakness > 3);
		this->weakness = (Element)weakness;
		cout << endl << "Enter elemental type of damage of " << name << " monster entity (0 - none, 1 - fire, 2 - magic, 3 - lighting): ";
		do {
			cin >> damageType;
			if (damageType < 0 || damageType > 3)
				cout << endl << "Invalid type of damage. Try again: ";
		} while (damageType < 0 || damageType > 3);
		this->damageType = (Element)damageType;
		if (this->damageType != none) {
			cout << endl << "Enter elemental damage of " << name << " monster entity: ";
			do {
				cin >> elementDamage;
				if (elementDamage <= 0)
					cout << endl << "Invalid elemental damage. Try again: ";
			} while (elementDamage <= 0);
		}
		else elementDamage = 0;
		cout << endl << name << " monster entity created!";
	}
	void hurt(double baseDamage, double elementDamage, Element damageType) {
		double damage = baseDamage;
		if (this->weakness == damageType && this -> weakness != none)
			damage += elementDamage;
		else if (this->weakness != none)
			damage += elementDamage * 0.5;
		LivingEntity::hurt(damage);
	}
	void AttackPlayer(PlayerEntity* player) {
		double damage = this->baseDamage * (1 - player->getArmor()->getBaseDefence() / 100);
		double elementDamage = 0;
		/*if (player.equippedArmor.defenceType == monster.damageType && monster.damageType != none)
			elementDamage = monster.elementDamage * (1 - player.equippedArmor.elementDefence / 100);
		else if (monster.damageType != none) elementDamage = monster.elementDamage;
		damage += elementDamage;
		playerEntityHurt(player, damage);*/
	}

};
class PlayerEntity : LivingEntity {
private:
	Armor* armor;
	Weapon* weapon;
public:
	PlayerEntity(string name, double healthPoints, double movementSpeed, Armor* armor, Weapon* weapon) {
		this->name = name;
		this->healthPoints = healthPoints;
		this->movementSpeed = movementSpeed;
		this->armor = armor;
		this->weapon = weapon;
	}
	PlayerEntity() {
		inputFields();
		
		cout << endl << name << " player entity created!";
	}
	Armor* getArmor() {
		return this->armor;
	}
};
class Armor {
private:
	double baseDefence;

public:
	double getBaseDefence() {
		return this->baseDefence;
	}
};
class Weapon {

};