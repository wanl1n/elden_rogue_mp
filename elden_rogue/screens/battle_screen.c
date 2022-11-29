#include "chara_creation_screen.h"
#include "title_screen.h"
#include "roundtable_screen.h"
#include "areas_screen.h"
#include "battle_screen.h"

#include "../driver.h"

#include "../config/settings.h"
#include "../utility/colors.h"


void displayBattleScreen(Player* pPlayer, Enemy sEnemy) {
	printHeader("BATTLE TIME", 11);
	printf("\t\t[NAME]: %s\n", pPlayer->strName);
	printPlayerHealth(pPlayer->nHealth, pPlayer->nPlayerMaxHP);
	printf("%d", pPlayer->nHealth);
	printf("\t\t[POTIONS]: %d\n", pPlayer->nPotions);
	//player sprite

	printf("\t\t[ENEMY NAME]: %s\n", sEnemy.strName);
	printPlayerHealth(sEnemy.nHP, sEnemy.nMaxHP);
	printf("%d", sEnemy.nHP);
	printf("\t\t[INCOMING ENEMY DAMAGE]: %d\n", 1);
	//ENEMY sprite

	printOption(1, "ATTACK");
	printOption(2, "DODGE");
	printOption(3, "POTION");
	printOption(4, "SKIP");

	//system messages
	printInputTag();
}

//Made this integer type.
int openBattleScreen(Enemy sEnemy, Player* pPlayer, int nAreaNo) {
	
	displayBattleScreen(pPlayer, sEnemy);

	int nPlayerTurn = 1;
	int nPlayerMove;

	//var for move attack sub-options
	int nPhysicalDamage;
	int nSorceryDamage;
	int nIncantationDamage;

	int nDodgeRate;
	//Initialized these variables (previously initialized inside the switch case)
	int nDodgeRandom;
	int nHealRandom;
	int nEnemyType;

	while (nPlayerTurn == 1 && pPlayer->nHealth > 0 || sEnemy.nHP > 0) {
		nPlayerMove = scanIntInput(1, 4);

		switch(nPlayerMove) {

			case MOVE_ATTACK:
				printOption(1, "PHYSICAL");
				printOption(2, "SORCERY");
				printOption(3, "INCANTATION");
				printInputTag();
				nPlayerMove = scanIntInput(1, 4);

				switch(nPlayerMove){

					case ATTACK_PHYSICAL:
						nPhysicalDamage = attackPhy(sEnemy, pPlayer);
						sEnemy.nHP -= nPhysicalDamage;
						printf ("%s dealt %d damage !", pPlayer->strName, nPhysicalDamage);
						printInputTag();
						break;

					case ATTACK_SORCERY:
						nSorceryDamage = attackSor(sEnemy, pPlayer);
						sEnemy.nHP -= nSorceryDamage;
						printf ("%s dealt %d damage !", pPlayer->strName, nSorceryDamage);
						printInputTag();
						break;

					case ATTACK_INCANTATION:
						nIncantationDamage = attackInc(sEnemy, pPlayer);
						sEnemy.nHP -= nIncantationDamage;
						printf ("%s dealt %d damage !", pPlayer->strName, nIncantationDamage);
						printInputTag();
						break;
				}

				break;

			case MOVE_DODGE:

				//Initialized this outside the switch
				nDodgeRandom = getRandomBetween(1, 100);
				nDodgeRate = getDodgeRate(sEnemy, pPlayer);

				//base 20% chance dodge rate
				if(nDodgeRandom <= nDodgeRate){
					printSystemMessage("Failed to Dodge");
				}
				break;

			case MOVE_POTION:

				//Initialized this outside the switch
				nHealRandom = getRandomBetween(1, 100);

				if(nHealRandom <= 25){
					pPlayer->nPlayerMaxHP += (pPlayer->nHealth * 0.25);
					pPlayer->nPotions -= 1;
				} else{
					pPlayer->nPlayerMaxHP += (pPlayer->nHealth * 0.50);
					pPlayer->nPotions -= 1;
				}
				
				if(pPlayer->nPotions <= 0){
					printSystemMessage("You Do Not Have Any Potions Left. Input a different number.");
					//loop later on kay player turn
				}

				break;

			case MOVE_SKIP:
				break;
		}
	} //end ni player turn
	while(nPlayerTurn == 0 && pPlayer->nHealth > 0 || sEnemy.nHP > 0){
		if(nPlayerMove == 3 && nDodgeRandom >= nDodgeRate){
			printf ("%s dodged %s attack !", pPlayer->strName, sEnemy.strName);
		}

		switch(nEnemyType){
		case 1:
			sEnemy.nAtk = getRandomBetween(70, 80) * nAreaNo;
			pPlayer->nHealth -= sEnemy.nAtk;
			printf ("%s dealt %d damage !", sEnemy.strName, sEnemy.nAtk);
			break;
		case 2:
			sEnemy.nAtk = getRandomBetween(110, 120)* nAreaNo;
			pPlayer->nHealth -= sEnemy.nAtk;
			printf ("%s dealt %d damage !", sEnemy.strName, sEnemy.nAtk);
			break;
		case 3:
			sEnemy.nAtk = getRandomBetween(120, 130)* nAreaNo;
			pPlayer->nHealth -= sEnemy.nAtk;
			printf ("%s dealt %d damage !", sEnemy.strName, sEnemy.nAtk);
			break;
		}
		if(pPlayer->nHealth <= 0){
			return 0;
		}
		else if(sEnemy.nHP <= 0){
			return 1;
		}

	}

	//return 0;//placeholder return (delete later)
}

//result make 1 win 0 lose
/*int displayAtk(Enemy sEnemy, pPlayer* pPlayer){
	printOption(1, "PHYSICAL");
	printOption(2, "SORCERY");
	printOption(3, "INCANTATION");
	printInputTag();
}*/

int attackPhy(Enemy sEnemy, Player* pPlayer){
	int nPhysicalDamage = (pPlayer->nStrength + pPlayer->pEquippedWeapon->nStr) * (1 - sEnemy.fPhysDef);
	return nPhysicalDamage;
}

int attackSor(Enemy sEnemy, Player* pPlayer){
	int nSorceryDamage = (pPlayer->nIntelligence + pPlayer->pEquippedWeapon->nInt) * (1 - sEnemy.fSorcDef);
	return nSorceryDamage;
}

int attackInc(Enemy sEnemy, Player* pPlayer){
	int nIncantationDamage = (pPlayer->nFaith + pPlayer->pEquippedWeapon->nFth) * (1 - sEnemy.fIncanDef);
	return nIncantationDamage;
}

int getDodgeRate(Enemy sEnemy, Player* pPlayer){
	int nDodgeRate = (20 +((pPlayer->nEndurance + pPlayer->pEquippedWeapon->nEnd) / 2)) / 100;
	return nDodgeRate;
}