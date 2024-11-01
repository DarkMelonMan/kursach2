#include "Classes.h"

void LivingEntity::hurt(double damage) {
	healthPoints -= damage;
	if (healthPoints <= 0) {
		healthPoints = 0;
		cout << endl << name << " entity is dead";
	}
}
void LivingEntity::inputLivingEntityFields() {
	cout << endl << "Enter a name for a new entity: ";
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
}

LivingEntity::LivingEntity(string name, double healthPoints, double movementSpeed) {
	this->name = name;
	this->healthPoints = healthPoints;
	this->movementSpeed = movementSpeed;
}

LivingEntity::LivingEntity() { 
	inputLivingEntityFields();
}

void LivingEntity::Print() {
	cout << endl << endl << name << " entity:";
	cout << endl << "Health points: " << healthPoints;
	cout << endl << "Movement speed: " << movementSpeed;
}

void Armor::inputArmorFields()
{
	int defenceType;
	cout << endl << "Enter base defence of a new armor: ";
	do {
		cin >> baseDefence;
		if (baseDefence <= 0)
			cout << endl << "Invalid base defence. Try again: ";
	} while (baseDefence <= 0);
	cout << endl << "Enter elemental type of defence of a new armor (0 - none, 1 - fire, 2 - magic, 3 - lighting): ";
	do {
		cin >> defenceType;
		if (defenceType < 0 || defenceType > 3)
			cout << endl << "Invalid type of defence. Try again: ";
	} while (defenceType < 0 || defenceType > 3);
	this->defenceType = (Element)defenceType;
	if (this->defenceType != none) {
		cout << endl << "Enter elemental defence of a new armor: ";
		do {
			cin >> elementDefence;
			if (elementDefence <= 0)
				cout << endl << "Invalid elemental defence. Try again: ";
		} while (elementDefence <= 0);
	}
	else elementDefence = 0;
	cout << endl << "New armor created!";
}

double Armor::getBaseDefence(){
	return this->baseDefence;
}

double Armor::getElementDefence() {
	return this->elementDefence;
}

double Armor::getDefenceType() {
	return this->defenceType;
}

Armor::Armor()
{
	inputArmorFields();
}

Armor::Armor(double baseDefence, double elementDefence, Element defenceType)
{
	this->baseDefence = baseDefence;
	this->elementDefence = elementDefence;
	this->defenceType = defenceType;
}

void Armor::Print()
{
	cout << endl << "Player armor:";
	cout << endl << "Base defence: " << this->baseDefence;
	cout << endl << "Elemental type of defence: " << elementNames[(int)defenceType];
	cout << endl << "Elemental defence: " << this->elementDefence;
}

Weapon::Weapon(double baseDamage, double elementDamage, Element damageType) {
	this->baseDamage = baseDamage;
	this->elementDamage = elementDamage;
	this->damageType = damageType;
}

void Weapon::inputWeaponFields() {
	int damageType;
	cout << endl << "Enter base damage of a new weapon: ";
	do {
		cin >> baseDamage;
		if (baseDamage <= 0)
			cout << endl << "Invalid base damage. Try again: ";
	} while (baseDamage <= 0);
		cout << endl << "Enter elemental type of damage of a new weapon (0 - none, 1 - fire, 2 - magic, 3 - lighting): ";
	do {
		cin >> damageType;
		if (damageType < 0 || damageType > 3)
			cout << endl << "Invalid type of damage. Try again: ";
	} while (damageType < 0 || damageType > 3);
	this->damageType = (Element)damageType;
	if (this->damageType != none) {
		cout << endl << "Enter elemental damage of a new weapon: ";
		do {
			cin >> elementDamage;
			if (elementDamage <= 0)
				cout << endl << "Invalid elemental damage. Try again: ";
		} while (elementDamage <= 0);
	}
	else elementDamage = 0;
	cout << endl << "New weapon created!";
}

Weapon::Weapon() {
	inputWeaponFields();
}

double Weapon::getBaseDamage()
{
	return this->baseDamage;
}

double Weapon::getElementDamage()
{
	return this->elementDamage;
}

Element Weapon::getDamageType()
{
	return this->damageType;
}

void Weapon::Print()
{
	cout << endl << "Player weapon:";
	cout << endl << "Base damage: " << this->baseDamage;
	cout << endl << "Elemental type of damage: " << elementNames[(int)damageType];
	cout << endl << "Elemental damage: " << this->elementDamage;
}

void MonsterEntity::inputMonsterEntityFields() {
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

MonsterEntity::MonsterEntity() {
	inputMonsterEntityFields();
}

 MonsterEntity::MonsterEntity(string name, double healthPoints, double movementSpeed, double baseDamage, double elementDamage, Element weakness, Element damageType) {
	this->name = name;
	this->healthPoints = healthPoints;
	this->movementSpeed = movementSpeed;
	this->baseDamage = baseDamage;
	this->elementDamage = elementDamage;
	this->weakness = weakness;
	this->damageType = damageType;
}

PlayerEntity::PlayerEntity() {
	 inputPlayerEntityFields();
}

void PlayerEntity::inputPlayerEntityFields() {
	weapon = new Weapon();
	armor = new Armor();
	cout << endl << name << " player entity created!";
}

PlayerEntity::PlayerEntity(string name, double healthPoints, double movementSpeed, Armor* armor, Weapon* weapon) {
	this->name = name;
	this->healthPoints = healthPoints;
	this->movementSpeed = movementSpeed;
	this->armor = armor;
	this->weapon = weapon;
}

Armor* PlayerEntity::getArmor() {
	return this->armor;
}

Weapon* PlayerEntity::getWeapon()
{
	return this->weapon;
}

void MonsterEntity::Hurt(double baseDamage, double elementDamage, Element damageType) {
	double damage = baseDamage;
	if (this->weakness == damageType && this->weakness != none)
		damage += elementDamage;
	else if (this->weakness != none)
		damage += elementDamage * 0.5;
	LivingEntity::hurt(damage);
}

void PlayerEntity::Hurt(double baseDamage, double elementDamage, Element damageType) {
	double damage = baseDamage * (1 - this->getArmor()->getBaseDefence() / 100);
	if (this->getArmor()->getDefenceType() == damageType && damageType != none)
		damage += elementDamage * (1 - this->getArmor()->getElementDefence() / 100);
	else if (damageType != none) damage += elementDamage;
	LivingEntity::hurt(damage);
}

void PlayerEntity::AttackMonster(MonsterEntity* monster)
{
	monster->Hurt(getWeapon()->getBaseDamage(), getWeapon()->getElementDamage(), getWeapon()->getDamageType());
}

void PlayerEntity::Print()
{
	LivingEntity::Print();
	getArmor()->Print();
	getWeapon()->Print();
}

void MonsterEntity::AttackPlayer(PlayerEntity* player) {
	player->Hurt(this->baseDamage, this->elementDamage, this->damageType);
}

void MonsterEntity::Print(){
	LivingEntity::Print();
	cout << endl << "Base damage: " << baseDamage;
	cout << endl << "Elemental type of damage: " << damageType;
	cout << endl << "Elemental weakness type: " << weakness;
	if (damageType != none)
		cout << endl << "Elemental damage: " << elementDamage;
}
