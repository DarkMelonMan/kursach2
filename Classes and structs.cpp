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
		MonsterEntityStruct monsterEntity;
		PlayerEntityStruct player;
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
		printf("\nChoose class type:\n1)MonsterEntity\n2)PlayerEntity\n3)Exit\n");
		do {
			scanf("%d", &choice);
			if (choice < 1 || choice > 3)
				printf("Wrong choice. Try again: ");
		} while (choice < 1 || choice > 3);
		if (choice == 3)
			exit(0);
		cout << endl << "Create a new monster entity:" << endl;
		MonsterEntity* monsterEntity = new MonsterEntity();
		cout << endl << "Create a new player entity:" << endl;
		PlayerEntity* playerEntity = new PlayerEntity();
		LivingEntity* entities[] = { monsterEntity, playerEntity };
		switch (choice) {
		case 1:
			((MonsterEntity*)entities[0])->Print();
			cout << endl << "Before Attack" << endl;
			((PlayerEntity*)entities[1])->Print();
			((MonsterEntity*)entities[0])->AttackPlayer(((PlayerEntity*)entities[1]));
			cout << endl << "After Attack" << endl;
			((PlayerEntity*)entities[1])->Print();
			break;
		case 2:
			((PlayerEntity*)entities[1])->Print();
			cout << endl << "Before Attack" << endl;
			monsterEntity->Print();
			((PlayerEntity*)entities[1])->AttackMonster(monsterEntity);
			cout << endl << "After Attack" << endl;
			((MonsterEntity*)entities[0])->Print();
			break;
		default:
			break;
		}
		for (int i = 0; i < 2; i++)
			delete entities[i];
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
