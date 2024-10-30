#define _CRT_SECURE_NO_WARNINGS
#include "Structures.cpp"
#include "Classes.h"

void chooseStruct() {
	int choice;
	do {
		printf("\nChoose struct type:\n1)MonsterEntity\n2)PlayerEntity\n3)Exit\n");
		do {
			scanf("%d", &choice);
			if (choice < 1 || choice > 3)
				printf("Wrong choice. Try again: ");
		} while (choice < 1 || choice > 3);
		MonsterEntity monsterEntity;
		PlayerEntity player;
		if (choice != 3) {
			monsterEntity = monsterEntityInput();
			player = playerEntityInput();
		}
		switch (choice) {
		case 1:
			monsterEntityOutput(monsterEntity);
			printf("\n\nBEFORE MONSTER ATTACK\n");
			playerEntityOutput(player);
			monsterEntityAttack(monsterEntity, player);
			printf("\n\nAFTER MONSTER ATTACK\n");
			playerEntityOutput(player);
			break;
		case 2:
			playerEntityOutput(player);
			printf("\n\nBEFORE PLAYER ATTACK\n");
			monsterEntityOutput(monsterEntity);
			playerEntityAttack(player, monsterEntity);
			printf("\n\nAFTER PLAYER ATTACK\n");
			monsterEntityOutput(monsterEntity);
			break;
		default:
			break;
		}
	} while (choice != 3);
}

void chooseClass() {
	int choice;
	do {
		printf("\nChoose struct type:\n1)MonsterEntity\n2)PlayerEntity\n3)Exit\n");
		do {
			scanf("%d", &choice);
			if (choice < 1 || choice > 3)
				printf("Wrong choice. Try again: ");
		} while (choice < 1 || choice > 3);
		LivingEntity* entity = new LivingEntity();		
		switch (choice) {
		case 1:
			entity->PrintOnScreen();
			break;
		case 2:
			break;
		default:
			break;
		}
	} while (choice != 3);
}

int main()
{
	int testChoice;
	do {
		printf("\nChoose test type:\n1)Structures\n2)Classes\n3)Exit\n");
		do {
			scanf("%d", &testChoice);
			if (testChoice < 1 || testChoice > 3)
				printf("Wrong choice. Try again: ");
		} while (testChoice < 1 || testChoice > 3);
		switch (testChoice) {
		case 1:
			chooseStruct();
			break;
		case 2:
			chooseClass();
			break;
		default:
			exit(0);
		}
	} while (testChoice != 3);

	
}
