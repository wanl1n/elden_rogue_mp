// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "roundtable_screen.h" //When the player dies.
#include "areas_screen.h" //When the player wins the battle.
#include "battle_screen.h" //Contains the constants used in Battle Screen.

#include "../driver.h" //Contains all the structure definitions.

#include "../config/settings.h" //Contains printing settings.
#include "../utility/colors.h" //Contains the colors used. 



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/*	openBattleScreen 	Opens the battle screen.
	
	@param sEnemy 		An Enemy variable that contains the enemy's stas.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param nAreaNo		An integer variable containing the area number.

	Pre-condition		sEnemy should contain complete stats.
						pPlayer should be initiated and all members 
						should have a value.
						nAreaNo should be an integer from 1-6.		   */
int openBattleScreen(Enemy sEnemy, Player* pPlayer, int nAreaNo) {

	int nPlayerTurn = 1;
	int nPlayerMove;
	int nDodgeTurn = 0;

	//var for move attack sub-options
	int nPhysicalDamage;
	int nSorceryDamage;
	int nIncantationDamage;

	int nDodgeRate;
	int nDodgeRandom;
	int nHealRandom;

	// While the battle is not yet over,
	while(pPlayer->nPlayerHP > 0 && sEnemy.nHP > 0){

		// Get the enemy's damage for that turn.
		switch(sEnemy.nType){

			case 1:
				sEnemy.nAtk = getRandomBetween(70, 80) * nAreaNo;
				break;

			case 2:
				sEnemy.nAtk = getRandomBetween(110, 120) * nAreaNo;
				break;

			case 3:
				sEnemy.nAtk = getRandomBetween(120, 130) * nAreaNo;						
				break;

		}	

		displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, 0, nAreaNo);

		if (nPlayerTurn) {

			nPlayerMove = scanIntInput(1, 4);

			switch(nPlayerMove) {

				case MOVE_ATTACK:

					printMultiple(" ", SCREEN_PADDING);
					printf("How do you want to attack?\n");
					printSubAttacks();

					nPlayerMove = scanIntInput(1, 4);

					switch(nPlayerMove){

						case ATTACK_PHYSICAL:

							nPhysicalDamage = attackPhy(sEnemy, pPlayer);
							sEnemy.nHP -= nPhysicalDamage;

							printMultiple(" ", SCREEN_PADDING);
							printf ("%s dealt %d damage !", pPlayer->strName, nPhysicalDamage);
							break;

						case ATTACK_SORCERY:

							nSorceryDamage = attackSor(sEnemy, pPlayer);
							sEnemy.nHP -= nSorceryDamage;

							printMultiple(" ", SCREEN_PADDING);
							printf ("%s dealt %d damage !", pPlayer->strName, nSorceryDamage);
							break;

						case ATTACK_INCANTATION:

							nIncantationDamage = attackInc(sEnemy, pPlayer);
							sEnemy.nHP -= nIncantationDamage;

							printMultiple(" ", SCREEN_PADDING);
							printf ("%s dealt %d damage !", pPlayer->strName, nIncantationDamage);
							break;

					} //end ng switch attack

					nPlayerTurn = 0;

					break;

				case MOVE_DODGE:

					displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, PLAYER_DODGE, nAreaNo);
					nDodgeRandom = getRandomBetween(1, 100);
					nDodgeRate = getDodgeRate(sEnemy, pPlayer);

					if(nDodgeRandom <= nDodgeRate){

						printSystemMessage("Successfully Dodged");
						nDodgeTurn = 1;

					} else {

						printSystemMessage("Failed to Dodge");
						nDodgeTurn = 0; 
					}

					nPlayerTurn = 0;
					break;

				case MOVE_POTION:

					// If Player has potions.
					if (pPlayer->nPotions > 0) {

						// If Player is at full health.
						if (pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP) {

							displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, PLAYER_POTION_FULL, nAreaNo);

						} else if (pPlayer->nPlayerHP < pPlayer->nPlayerMaxHP) {
							
							nHealRandom = getRandomBetween(1, 100);

							if(nHealRandom <= 25){

								int nHealing = pPlayer->nPlayerHP + (pPlayer->nPlayerMaxHP * 0.25);

								pPlayer->nPlayerHP += nHealing;
								
								if(pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP)
									pPlayer->nPlayerHP = pPlayer->nPlayerMaxHP;

								pPlayer->nPotions -= 1;
								
								displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, 0, nAreaNo);
								printMultiple(" ", SCREEN_PADDING);
								printf("%s healed %d Health!\n", pPlayer->strName, nHealing);

							} else {

								int nHealingTwo = pPlayer->nPlayerHP + (pPlayer->nPlayerMaxHP * 0.50);
								
								pPlayer->nPlayerHP += nHealingTwo;
								
								if(pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP)
									pPlayer->nPlayerHP = pPlayer->nPlayerMaxHP;

								pPlayer->nPotions -= 1;

								displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, 0, nAreaNo);
								printMultiple(" ", SCREEN_PADDING);
								printf("%s healed %d Health!\n", pPlayer->strName, nHealingTwo);								
							}

							nPlayerTurn = 0;
						}
					} else { // If player has no potions.

						displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, PLAYER_POTION_EMPTY, nAreaNo);
					}

					break;

				case MOVE_SKIP:

					displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, PLAYER_SKIP, nAreaNo);

					nPlayerTurn = 0;
					
					break;

			} //end ni switch

		} //end ni player turn

		// If Player has killed enemy. 
		if(sEnemy.nHP <= 0)
			return WIN; 

		if (!nPlayerTurn) {

			displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, ENEMY_ATTACK, nAreaNo);

			if (nDodgeTurn) {

				printMultiple(" ", SCREEN_PADDING);
				printf ("%s dodged %s's attack !\n", pPlayer->strName, sEnemy.strName);

			} else {
				
				displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, ENEMY_ATTACK, nAreaNo);

				pPlayer->nPlayerHP -= sEnemy.nAtk;
				printMultiple(" ", SCREEN_PADDING);
				printf ("%s dealt %d damage !\n", sEnemy.strName, sEnemy.nAtk);
			}

			nPlayerTurn = 1;
		}

		// If Enemy killed player.
		if(pPlayer->nPlayerHP <= 0)
			return LOSE;

	} //end ng lahat

	// Double check result
	if(sEnemy.nHP <= 0)
		return WIN; 
	else if(pPlayer->nPlayerHP <= 0)
		return LOSE;

	return 0;
}



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/*	attackPhy 			Gets the player's physical attack damage.
	
	@param sEnemy 		An Enemy variable that contains the enemy's stas.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	
	@return 			An integer value containing the player's physical
						damage.

	Pre-condition		sEnemy should contain complete stats.
						pPlayer should be initiated and all members 
						should have a value. 						   */
int attackPhy(Enemy sEnemy, Player* pPlayer){
	int nPhysicalDamage = (pPlayer->nStrength + pPlayer->sEquippedWeapon.nStr) * (1 - sEnemy.fPhysDef);
	return nPhysicalDamage;
}

/*	attackSor 			Gets the player's sorcery attack damage.
	
	@param sEnemy 		An Enemy variable that contains the enemy's stas.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	
	@return 			An integer value containing the player's sorcery
						damage.

	Pre-condition		sEnemy should contain complete stats.
						pPlayer should be initiated and all members 
						should have a value. 						   */
int attackSor(Enemy sEnemy, Player* pPlayer){
	int nSorceryDamage = (pPlayer->nIntelligence + pPlayer->sEquippedWeapon.nInt) * (1 - sEnemy.fSorcDef);
	return nSorceryDamage;
}

/*	attackInc 			Gets the player's incantation attack damage.
	
	@param sEnemy 		An Enemy variable that contains the enemy's stas.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	
	@return 			An integer value containing the player's incantation
						damage.

	Pre-condition		sEnemy should contain complete stats.
						pPlayer should be initiated and all members 
						should have a value. 						   */
int attackInc(Enemy sEnemy, Player* pPlayer){
	int nIncantationDamage = (pPlayer->nFaith + pPlayer->sEquippedWeapon.nFth) * (1 - sEnemy.fIncanDef);
	return nIncantationDamage;
}

/*	getDodgeRate		Gets the player's dodge rate.
	
	@param sEnemy 		An Enemy variable that contains the enemy's stas.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	
	@return 			An integer value containing the player's dodge
						rate.

	Pre-condition		sEnemy should contain complete stats.
						pPlayer should be initiated and all members 
						should have a value. 						   */
int getDodgeRate(Enemy sEnemy, Player* pPlayer){
	int nDodgeRate = (20 +((pPlayer->nEndurance + pPlayer->sEquippedWeapon.nEnd) / 2));
	return nDodgeRate;
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/*	displayBattleScreen 	Displays the battle screen.

	@param sEnemy 		An Enemy variable that contains the enemy's stas.
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param nTurn 		An integer variable that contains the current turn.
	@param nPrompt 		An integer variable that contains the prompt number.

	Pre-condition		sEnemy should contain complete stats.
						pPlayer should be initiated and all members 
						should have a value. 
						nTurn should be either 1 or 0.
						nPrompt should be 1 to 5.					   */
void displayBattleScreen(Player* pPlayer, Enemy sEnemy, int nTurn, int nPrompt, int nArea) {

	//Sleep(3000);

	system("cls");

	printHeader("BATTLE TIME", 11);

	//ENEMY sprite
	printf("\t\t[ENEMY NAME]: %s\n", sEnemy.strName);
	printPlayerHealth(sEnemy.nHP, sEnemy.nMaxHP);
	printf("%d\n", sEnemy.nHP);

	switch(nArea){
		case STORMVEIL:
			printf("   █    █     \e[1;97m;;;;\e[0m       \e[1;93m█\e[0m █   \n");
			printf("  █ █  █ █   ██████     \e[1;93m███\e[0m █ ██\n");
			printf("     █   █  \e[1;97m;\e[0m█    █\e[1;97m;\e[0m     \e[1;93m█\e[0m   █  █\n");
			printf("   ██ █   █\e[1;97m;;\e[0m█    █\e[1;97m;;\e[0m  ██\e[1;93m;\e[0m█ █   \n");
			printf(" ██  █ █ █ \e[1;97m;;;\e[0m████\e[1;97m;;;\e[0m █ █\e[1;93m;\e[0m██  ██\n");
			printf(" █    █ █ █ ██    ██ █ ██ █  █  █\n");
			printf("   ██  █ ███\e[1;93m;\e[0m     \e[1;93m;\e[0m ███ █ █ █  \n");
			printf("  █  █ ██ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ ██ ███\n");
			printf(" █    █ █ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ █ █   █\n");
			printf("       ██ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ ██    \n");
			printf("\n");
			break;
		case RAYA_LUCARIA:
			printf("             \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m██\e[0m    \e[1;93m;\e[0m \e[1;94m███\e[0m\n");
			printf("\e[1;93m   ███\e[0m      \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█   █   █\e[0m \e[1;93m;\e[0m \n");
			printf("\e[1;93m  █   █\e[0m    \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█   █\e[0m\e[1;93m;\e[0m \e[1;94m█   █\e[0m     \n");
			printf("\e[1;93m █ ;   █\e[0m    █   █        ███ ;\n");
			printf("\e[1;93m █ ;   █\e[0m    █   █         █\n");
			printf("\e[1;93m  █   █\e[0m    \e[1;91m█ ███ █\e[0m       ███\n");
			printf("\e[1;93m   ███\e[0m   ██       ██      █\e[1;93m:\e[0m    \n");
			printf("\e[1;94m         █         █\e[0m     \e[1;93m:\e[0m█    \n");
			printf("\e[1;94m         █         █\e[0m      █\e[1;93m:\e[0m   \n");
			printf("\e[1;94m         █         █\e[0m     \e[1;93m:\e[0m█    \n");
			printf("\n");
			break;
		case REDMANE_CASTLE:
			printf("     █     \e[1;91m;:;;;:;     █\n");
			printf("   ██     \e[1;91m;:;:::;:;     ██ \n");
			printf("  █\e[1;93m:\e[0m █   \e[1;91m;\e[0m\e[1;93m█\e[0m\e[1;91m;:\e[0m\e[1;93m███\e[0m\e[1;91m:;\e[0m\e[1;93m█\e[0m\e[1;91m;\e[0m   █ \e[1;93m:\e[0m█\n");
			printf(" █\e[1;93m:\e[0m  █   \e[1;91m:;\e[0m\e[1;93m██   ██\e[1;91m;:\e[0m   █  \e[1;93m:\e[0m█ \n");
			printf(" █\e[1;93m:\e[0m  █    \e[1;91m:;\e[0m\e[1;93m█   █\e[1;91m;:\e[0m    █  \e[1;93m:\e[0m█\n");
			printf("  █\e[1;93m:\e[0m █\e[1;93m███\e[0m \e[1;91m██ ███ ██\e[0m \e[1;93m████\e[0m \e[1;93m:\e[0m█\n");
			printf("   █\e[1;93m:\e[0m█   \e[1;93m█         █\e[0m   █\e[1;93m:\e[0m█    \n");
			printf("   ██;\e[1;93m███\e[0m;         ;\e[1;93m███\e[0m;██  \n");
			printf("    ██;;;           ;;; ██   \n");
			printf("     █ \e[1;93m█             \e[1;93m█\e[0m  █     \n");
			printf("\n");
			break;

		case VOLCANO_MANOR:
			printf("\e[1;92m        ██████      \e[0m \e[1;91m  ;█; \e[0m\n");
			printf("\e[1;92m       █      █     \e[0m \e[1;91m ;██; \e[0m\n");
			printf("\e[1;92m      █        █    \e[0m \e[1;91m ;██; \e[0m\n");
			printf("\e[1;92m       █      █     \e[0m \e[1;91m ;██; \e[0m\n");
			printf("\e[1;92m        ██████      \e[0m \e[1;91m ;██; \e[0m\n");
			printf("\e[1;92m     ███ █,,,██  █  \e[0m \e[1;91m ;██; \e[0m\n");
			printf("\e[1;92m    █   █,,\e[1;93m█\e[0m\e[1;92m,,█ █ █\e[0m  \e[1;91m ;██; \e[0m\n");
			printf("\e[1;92m   █  █  ,,,,█ ██  █\e[0m \e[1;91m██████\e[0m\n");
			printf("\e[1;92m   █   ██████   █  █\e[0m \e[1;91m  ██  \e[0m\n");
			printf("\e[1;92m    █          █ █ █\e[0m \e[1;91m  ██  \e[0m\n");
			printf("\e[1;92m     ████████████ █ \e[0m \e[1;91m  ██  \e[0m\n");
			printf("\n");
			break;

		case LEYNDELL_CAPITAL:
			printf("     █  █ █;;;;;;;█ █   \n");
			printf("    █    █;█;███;█;█    \n");
			printf("   ██    ;█;█   █;█;   \n");
			printf("  ███   █;;██   ██;;█  \n");
			printf("  ██   █ ;;;█   █;;; █  \n");
			printf(" ██   ██ ;██ ███ ██; ██\n");
			printf("  ██ █  ██         ██  █    \n");
			printf(" ██   █   █████████   █\n");
			printf("  ██   █ ;    █    ; █  \n");
			printf("  :█:   █ ; ; █;  ; █        \n");
			printf("\n");
			break;	
	}

	printf("\t\t[INCOMING ENEMY DAMAGE]: %d\n", sEnemy.nAtk);
	
	printf("\t\t[NAME]: %s\n", pPlayer->strName);
	printPlayerHealth(pPlayer->nPlayerHP, pPlayer->nPlayerMaxHP);
	printf("%d", pPlayer->nPlayerHP);

	printf("\n    ██   \n");
	printf("   ████  \n");
	printf("  █\e[1;91m████\e[0m█ \n");
	printf("   ████  \n");

	printf("\t[POTIONS]: %d\n\n\n", pPlayer->nPotions);
	
	if (nTurn) {
		printHeader("PLAYER TURN", 11);
		printOption(1, "ATTACK");
		printOption(2, "DODGE");
		printOption(3, "POTION");
		printOption(4, "SKIP");
	} else {
		printHeader("ENEMY TURN", 10);
	}

	printf("\n\n");

	switch(nPrompt) {

 		case PLAYER_DODGE:

 			printMultiple(" ", SCREEN_PADDING);
			printf("Attempting to dodge.\n");

			break;

 		case PLAYER_POTION_FULL:

 			printMultiple(" ", SCREEN_PADDING);
			printf("You're still at full health. Try something else.\n");
			
			break;

 		case PLAYER_POTION_EMPTY:

 			printMultiple(" ", SCREEN_PADDING);
			printf("You Do Not Have Any Potions Left. Input a different number.\n");

			break;

 		case PLAYER_SKIP:

 			printMultiple(" ", SCREEN_PADDING);
			printf("You skipped your turn.\n");

			break;

 		case ENEMY_ATTACK:

 			printMultiple(" ", SCREEN_PADDING);
			printf("Enemy is trying to attack\n");
			break;
		default:
			break;
	}
}

/* 	printSubAttacks 	Prints the subcategories of attacks.		   */
void printSubAttacks() {
	printOption(1, "PHYSICAL");
	printOption(2, "SORCERY");
	printOption(3, "INCANTATION");
}