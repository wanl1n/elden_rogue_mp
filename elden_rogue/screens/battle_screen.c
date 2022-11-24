#include "chara_creation_screen.h"
#include "title_screen.h"
#include "roundtable_screen.h"
#include "areas_screen.h"
#include "battle_screen.h"

#include "../driver.h"

#include "../config/settings.h"
#include "../utility/colors.h"


void displayBattleScreen(Player* pPlayer, Enemy* pEnemy) {
	printHeader("BATTLE TIME", 11);
	printf("\t\t[NAME]: %s\n", pPlayer->strName);
	printPlayerHealth(pPlayer->nHealth, pPlayer->nPlayerMaxHP);
	printf("%d", pPlayer->nHealth);
	printf("\t\t[POTIONS]: %d\n", pPlayer->nPotions);
	//player sprite

	printf("\t\t[ENEMY NAME]: %s\n", pEnemy->strName);
	printPlayerHealth(pEnemy->nHP, pEnemy->nHP);
	printf("%d", pEnemy->nHP);
	printf("\t\t[INCOMING ENEMY DAMAGE]: %d\n", 1);
	//ENEMY sprite

	printOption(1, "ATTACK");
	printOption(2, "DODGE");
	printOption(3, "POTION");
	printOption(4, "SKIP");

	//system messages
}

void openBattleScreen(Enemy sEnemy, Player* pPlayer) {
	
	displayBattleScreen(pPlayer, sEnemy);

	int nPlayerTurn = 1;
	int nPlayerMove;

	while (pPlayer->nHealth > 0 || sEnemy.nHP > 0) {
		nPlayerMove = scanIntInput(1, 4);

		switch(nPlayerMove) {
			case MOVE_ATTACK:

				break;
			case MOVE_DODGE:

				break;
			case MOVE_POTION:
				
				break;
			case MOVE_SKIP:
				break;
		}
	}

	

}