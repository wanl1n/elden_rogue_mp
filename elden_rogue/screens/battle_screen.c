#include "chara_creation_screen.h"
#include "title_screen.h"
#include "roundtable_screen.h"
#include "areas_screen.h"
#include "battle_screen.h"

#include "../driver.h"

#include "../config/settings.h"
#include "../utility/colors.h"


void displayBattleScreen(Player* pPlayer, Enemy sEnemy) {
	//system("cls");
	printHeader("BATTLE TIME", 11);
	printf("\t\t[NAME]: %s\n", pPlayer->strName);
	printPlayerHealth(pPlayer->nPlayerHP, pPlayer->nPlayerMaxHP);
	printf("%d", pPlayer->nPlayerHP);
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
	
	//displayBattleScreen(pPlayer, sEnemy);

	int nPlayerTurn = 1;
	int nPlayerMove;
	int nDodgeTurn;

	//var for move attack sub-options
	int nPhysicalDamage;
	int nSorceryDamage;
	int nIncantationDamage;

	int nDodgeRate;
	//Initialized these variables (previously initialized inside the switch case)
	int nDodgeRandom;
	int nHealRandom;
	int nEnemyType;

	while(pPlayer->nPlayerHP > 0 && sEnemy.nHP > 0){
		displayBattleScreen(pPlayer, sEnemy);
		if (nPlayerTurn == 1) {
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
							nPlayerTurn = 0;
							printInputTag();
							break;

						case ATTACK_SORCERY:
							nSorceryDamage = attackSor(sEnemy, pPlayer);
							sEnemy.nHP -= nSorceryDamage;
							printf ("%s dealt %d damage !", pPlayer->strName, nSorceryDamage);
							nPlayerTurn = 0;
							printInputTag();
							break;

						case ATTACK_INCANTATION:
							nIncantationDamage = attackInc(sEnemy, pPlayer);
							sEnemy.nHP -= nIncantationDamage;
							printf ("%s dealt %d damage !", pPlayer->strName, nIncantationDamage);
							nPlayerTurn = 0;
							printInputTag();
							break;
					} //end ng switch attack

					break;

				case MOVE_DODGE:
					printf("%d", nDodgeRandom);
					//Initialized this outside the switch
					nDodgeRandom = getRandomBetween(1, 100);
					nDodgeRate = getDodgeRate(sEnemy, pPlayer);

						if(nDodgeRandom >= nDodgeRate){
							printSystemMessage("Successfully Dodged");
							nDodgeTurn = 1;
							nPlayerTurn = 0;
						}
						if(nDodgeRandom <= nDodgeRate){
							printSystemMessage("Failed to Dodge");
							nDodgeTurn = 2;
							nPlayerTurn = 0;
						}
					break;

				case MOVE_POTION:
					if(pPlayer->nPotions > 0 && pPlayer->nPlayerHP == pPlayer->nPlayerMaxHP){ //full health wt pots
							pPlayer->nPlayerHP = pPlayer->nPlayerMaxHP;
							printSystemMessage("Your Health is still at Maximum number!. Input a different number.");
							nPlayerTurn = 0;
							//loop later on kay player turn
					}
					if(pPlayer->nPotions > 0 && pPlayer->nPlayerHP < pPlayer->nPlayerMaxHP){ //bawas health wt pots
						//Initialized this outside the switch
						nHealRandom = getRandomBetween(1, 100);

						if(nHealRandom <= 25){
							int nHealing = pPlayer->nPlayerHP + (pPlayer->nPlayerMaxHP * 0.25);
							pPlayer->nPlayerHP += nHealing;
							if(pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP){
								pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP;
							pPlayer->nPotions -= 1;
							printf("%s healed %d Health!\n", pPlayer->strName, nHealing);
							nPlayerTurn = 0;
							}
						}
						else{
							int nHealingTwo = pPlayer->nPlayerHP + (pPlayer->nPlayerMaxHP * 0.50);
							pPlayer->nHealth += nHealingTwo;
							if(pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP){
								pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP;
							pPlayer->nPotions -= 1;
							printf("%s healed %d Health!\n", pPlayer->strName, nHealingTwo);
							nPlayerTurn = 0;
							}
						}
					}
					if(pPlayer->nPotions <= 0 && pPlayer->nPlayerHP < pPlayer->nPlayerMaxHP){ //bawas health no pots
						printSystemMessage("You Do Not Have Any Potions Left. Input a different number.");
						pPlayer->nPotions = 0;
						nPlayerTurn = 0;
						//loop later on kay player turn
					}

					if(pPlayer->nPotions <= 0 && pPlayer->nPlayerHP == pPlayer->nPlayerMaxHP){ //full health wt no pots
						pPlayer->nPlayerHP = pPlayer->nPlayerMaxHP;
						printSystemMessage("Your Health is still at Maximum number and with no Potions left!. Input a different number.");
						nPlayerTurn = 0;
						//loop later on kay player turn
					}
					break;

				case MOVE_SKIP:
					break;
			} //end ni switch
		} //end ni player turn

		if(sEnemy.nHP <= 0){
			sEnemy.nHP = 0;
			return 1;
		}

		if(nPlayerTurn == 0 && (nPlayerMove == 3 && nDodgeTurn == 1)){
			printf ("%s dodged %s attack !\n", pPlayer->strName, sEnemy.strName);
			nPlayerTurn = 1;
		}

		if(nPlayerTurn == 0 && (nPlayerMove == 3 && nDodgeTurn == 2)){
				switch(sEnemy.nType){
					case 1:
						printf("Enemy is thinking of its move.");
						sEnemy.nAtk = getRandomBetween(70, 80) * nAreaNo;
						pPlayer->nPlayerHP -= sEnemy.nAtk;
						printf ("%s dealt %d damage !\n", sEnemy.strName, sEnemy.nAtk);
						nPlayerTurn = 1;
						break;
					case 2:
						sEnemy.nAtk = getRandomBetween(110, 120)* nAreaNo;
						pPlayer->nPlayerHP -= sEnemy.nAtk;
						printf ("%s dealt %d damage !\n", sEnemy.strName, sEnemy.nAtk);
						nPlayerTurn = 1;
						break;
					case 3:
						sEnemy.nAtk = getRandomBetween(120, 130)* nAreaNo;
						pPlayer->nPlayerHP -= sEnemy.nAtk;
						printf ("%s dealt %d damage !\n", sEnemy.strName, sEnemy.nAtk);
						nPlayerTurn = 1;
						break;
				} // end ni switch
		} //end ni if

		if(pPlayer->nPlayerHP <= 0){
			return 0;
		}
	} //end ng lahat
}

int attackPhy(Enemy sEnemy, Player* pPlayer){
	int nPhysicalDamage = (pPlayer->nStrength + pPlayer->sEquippedWeapon.nStr) * (1 - sEnemy.fPhysDef);
	return nPhysicalDamage;
}

int attackSor(Enemy sEnemy, Player* pPlayer){
	int nSorceryDamage = (pPlayer->nIntelligence + pPlayer->sEquippedWeapon.nInt) * (1 - sEnemy.fSorcDef);
	return nSorceryDamage;
}

int attackInc(Enemy sEnemy, Player* pPlayer){
	int nIncantationDamage = (pPlayer->nFaith + pPlayer->sEquippedWeapon.nFth) * (1 - sEnemy.fIncanDef);
	return nIncantationDamage;
}

int getDodgeRate(Enemy sEnemy, Player* pPlayer){
	int nDodgeRate = (20 +((pPlayer->nEndurance + pPlayer->sEquippedWeapon.nEnd) / 2));
	return nDodgeRate;
}