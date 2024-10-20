#define _CRT_SECURE_NO_WARNINGS
#include "Structures.cpp"

int main()
{
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