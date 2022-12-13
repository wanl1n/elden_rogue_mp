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
	int nEldenThroneStage = 0;

	//variables for move attack sub-options
	int nPhysicalDamage;
	int nSorceryDamage;
	int nIncantationDamage;

	int nDodgeRate;
	int nDodgeRandom;
	int nHealRandom;

	//if youre in EldenThroneStage 1 then the enemy name is Radagon
	//if youre in EldenThroneStage 2 then the enemy name is Elden Beast
	if (!strcmp(sEnemy.strName, "RADAGON OF THE GOLDEN ORDER")) {
		nEldenThroneStage = 1;
	} else if (!strcmp(sEnemy.strName, "THE ELDEN BEAST")) {
		nEldenThroneStage = 2;
	}

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

		//prints the display battle screen
		displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, 0, nAreaNo, nEldenThroneStage);

		// conditions for player turn
		if (nPlayerTurn) {

			nPlayerMove = scanIntInput(1, 4);

			switch(nPlayerMove) {

				case MOVE_ATTACK: // attack or 1 is what the player inputted

					printMultiple(" ", SCREEN_PADDING);
					printf("How do you want to attack?\n");
					printSubAttacks();

					nPlayerMove = scanIntInput(1, 4);

					switch(nPlayerMove){

						case ATTACK_PHYSICAL: // player chose physical attack

							nPhysicalDamage = attackPhy(sEnemy, pPlayer);
							sEnemy.nHP -= nPhysicalDamage;

							printMultiple(" ", SCREEN_PADDING);
							printf ("%s dealt %d damage !", pPlayer->strName, nPhysicalDamage);
							break;

						case ATTACK_SORCERY: //player chose sorcery attack

							nSorceryDamage = attackSor(sEnemy, pPlayer);
							sEnemy.nHP -= nSorceryDamage;

							printMultiple(" ", SCREEN_PADDING);
							printf ("%s dealt %d damage !", pPlayer->strName, nSorceryDamage);
							break;

						case ATTACK_INCANTATION: //player chose sorcery incantation

							nIncantationDamage = attackInc(sEnemy, pPlayer);
							sEnemy.nHP -= nIncantationDamage;

							printMultiple(" ", SCREEN_PADDING);
							printf ("%s dealt %d damage !", pPlayer->strName, nIncantationDamage);
							break;

					} 

					//this reverts to enemy turn
					nPlayerTurn = 0;

					break;

				case MOVE_DODGE: //player chose 2 or dodge

					displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, PLAYER_DODGE, nAreaNo, nEldenThroneStage);
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

				case MOVE_POTION: // player chose 3 or potions

					// If Player has potions.
					if (pPlayer->nPotions > 0) {

						// If Player is at full health.
						if (pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP) {

							displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, PLAYER_POTION_FULL, nAreaNo, nEldenThroneStage);

						} else if (pPlayer->nPlayerHP < pPlayer->nPlayerMaxHP) {
							
							nHealRandom = getRandomBetween(1, 100); //gets a random number between 1 - 100

							if(nHealRandom <= 25){ //if the number chosen was 1 - 25 then heal 25% of player's max health

								int nHealing = pPlayer->nPlayerHP + (pPlayer->nPlayerMaxHP * 0.25);

								pPlayer->nPlayerHP += nHealing;
								
								if(pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP) // if player health exceeds to their max health, leave the number as their max health
									pPlayer->nPlayerHP = pPlayer->nPlayerMaxHP;

								pPlayer->nPotions -= 1;
								
								displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, 0, nAreaNo, nEldenThroneStage);
								printMultiple(" ", SCREEN_PADDING);
								printf("%s healed %d Health!\n", pPlayer->strName, nHealing);

							} else { //if the number chosen was 26 - 100 then heal 50% of player's max health

								int nHealingTwo = pPlayer->nPlayerHP + (pPlayer->nPlayerMaxHP * 0.50);
								
								pPlayer->nPlayerHP += nHealingTwo;
								
								if(pPlayer->nPlayerHP >= pPlayer->nPlayerMaxHP) // if player health exceeds to their max health, leave the number as their max health
									pPlayer->nPlayerHP = pPlayer->nPlayerMaxHP;

								pPlayer->nPotions -= 1;

								displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, 0, nAreaNo, nEldenThroneStage);
								printMultiple(" ", SCREEN_PADDING);
								printf("%s healed %d Health!\n", pPlayer->strName, nHealingTwo);								
							}

							nPlayerTurn = 0; // end of player turn
						}
					} else { // If player has no potions.

						displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, PLAYER_POTION_EMPTY, nAreaNo, nEldenThroneStage);
					}

					break;

				case MOVE_SKIP: //if player chose 4 or skip

					displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, PLAYER_SKIP, nAreaNo, nEldenThroneStage);

					nPlayerTurn = 0; // end of player turn
					
					break;

			} 

		} 

		// If Player has killed enemy. 
		if(sEnemy.nHP <= 0 && strcmp(sEnemy.strName, "RADAGON OF THE GOLDEN ORDER"))
			return WIN; 

		if (!nPlayerTurn && sEnemy.nHP > 0) { //enemy turn starts here

			displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, ENEMY_ATTACK, nAreaNo, nEldenThroneStage);

			if (nDodgeTurn) {

				printMultiple(" ", SCREEN_PADDING);
				printf ("%s dodged %s's attack !\n", pPlayer->strName, sEnemy.strName);

			} else {
				
				displayBattleScreen(pPlayer, sEnemy, nPlayerTurn, ENEMY_ATTACK, nAreaNo, nEldenThroneStage);

				pPlayer->nPlayerHP -= sEnemy.nAtk;
				printMultiple(" ", SCREEN_PADDING);
				printf ("%s dealt %d damage !\n", sEnemy.strName, sEnemy.nAtk);
			}

			nPlayerTurn = 1;
		}

		// If Enemy killed player.
		if(pPlayer->nPlayerHP <= 0)
			return LOSE;

	} 

	if (!strcmp(sEnemy.strName, "RADAGON OF THE GOLDEN ORDER")) {
		sEnemy = spawnBoss(nAreaNo, 2);

		openBattleScreen(sEnemy, pPlayer, nAreaNo);
	}

	return -1;
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
void displayBattleScreen(Player* pPlayer, Enemy sEnemy, int nTurn, int nPrompt, int nArea, int nEldenThroneStage) {

	//Sleep(3000);

	//system("cls");

	printHeader("BATTLE TIME", 11);

	//ENEMY sprite
	printf("\t\t[ENEMY NAME]: %s\n", sEnemy.strName);
	printEnemyHealth(sEnemy.nHP, sEnemy.nMaxHP);
	printf("%d\n", sEnemy.nHP);

	switch(nArea){
		case STORMVEIL:

			switch(sEnemy.nType){
				case 1:
					printf("\t\t\t ██  ████████\n");
					printf("\t\t\t █ ██   ::   █ \n");
					printf("\t\t\t █ █    ::    █\n");
					printf("\t\t\t █ ██████████████\n");
					printf("\t\t\t █ █   █   █   █ \n");
					printf("\t\t\t █ █          █ \n");
					printf("\t\t\t█████    █████\n");
					printf("\t\t\t █ █\e[1;92m;\e[0m████\e[1;91m;;\e[0m█ █\n");
					printf("\t\t\t ███\e[1;92m;;\e[0m   \e[1;91m;;\e[0m███\n");
					printf("\t\t\t   █\e[1;92m;;\e[0m███\e[1;91m;;\e[0m█  \n");
					printf("\t\t\t   ███   ███ \n");
					printf("\n");
					break;
				case 2:
					printf("\t\t\t     ████████\n");
					printf("\t\t\t   ██   ::   █ \n");
					printf("\t\t\t   █    ::    █\n");
					printf("\t\t\t   ██████████████\n");
					printf("\t\t\t ███   █   █;;██  \n");
					printf("\t\t\t █:█        ;;  ███\n");
					printf("\t\t\t █:██    ███;;█    █\n");
					printf("\t\t\t █:█\e[1;92m;\e[0m████\e[1;91m;;\e[0m█;; █   █\n");
					printf("\t\t\t ███\e[1;92m;;\e[0m   \e[1;91m;;\e[0m█;;█    █\n");
					printf("\t\t\t   █\e[1;92m;;\e[0m███\e[1;91m;;\e[0m█;;  ███\n");
					printf("\t\t\t   ███   ███;;██\n");
					printf("\n");
					break;
				case 3:
					printf("\t\t\t ██  ████████\n");
					printf("\t\t\t █ ██   ::   █ \n");
					printf("\t\t\t █ █    ::    █\n");
					printf("\t\t\t █ ██████████████\n");
					printf("\t\t\t █ █   █   █   █ \n");
					printf("\t\t\t █ █          █ \n");
					printf("\t\t\t█████    ███████\n");
					printf("\t\t\t █ █\e[1;92m;\e[0m████\e[1;91m;;\e[0m█    █\n");
					printf("\t\t\t ███\e[1;92m;;\e[0m   \e[1;91m;;\e[0m█    █\n");
					printf("\t\t\t   █  ███  ██  █\n");
					printf("\t\t\t   ███   ███ ██\n");
					printf("\n");
					break;
				case 4:
					printf("\t\t\t   █    █     \e[1;97m;;;;\e[0m       \e[1;93m█\e[0m █   \n");
					printf("\t\t\t  █ █  █ █   ██████     \e[1;93m███\e[0m █ ██\n");
					printf("\t\t\t     █   █  \e[1;97m;\e[0m█    █\e[1;97m;\e[0m     \e[1;93m█\e[0m   █  █\n");
					printf("\t\t\t   ██ █   █\e[1;97m;;\e[0m█    █\e[1;97m;;\e[0m  ██\e[1;93m;\e[0m█ █   \n");
					printf("\t\t\t ██  █ █ █ \e[1;97m;;;\e[0m████\e[1;97m;;;\e[0m █ █\e[1;93m;\e[0m██  ██\n");
					printf("\t\t\t █    █ █ █ ██    ██ █ ██ █  █  █\n");
					printf("\t\t\t   ██  █ ███\e[1;93m;\e[0m     \e[1;93m;\e[0m ███ █ █ █  \n");
					printf("\t\t\t  █  █ ██ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ ██ ███\n");
					printf("\t\t\t █    █ █ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ █ █   █\n");
					printf("\t\t\t       ██ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ ██    \n");
					printf("\n");
					break;
			}

			break;

		case RAYA_LUCARIA:
			switch(sEnemy.nType){
				case 1:
					printf("\t\t\t          ████████\n");
					printf("\t\t\t         █\e[1;91m :::::: \e[0m█ \n");
					printf("\t\t\t     ████\e[1;91m :  ::  : \e[0m████\n");
					printf("\t\t\t    █  █\e[1;93m:\e[0m█\e[1;91m :::::: \e[0m█\e[1;93m:\e[0m█  █\n");
					printf("\t\t\t   █ ██\e[1;93m : \e[0m████████\e[0m\e[1;93m : \e[0m██ █\n");
					printf("\t\t\t  █  █\e[1;93m;  :  :;: : :  ;\e[0m█  █\n");
					printf("\t\t\t █   █\e[1;93m ; : ;: : :;: ; \e[0m█   █\n");
					printf("\t\t\t █   █\e[1;93m  ;;;;;;;;;;;;  \e[0m█   █\n");
					printf("\t\t\t  █   █              █   █\n");
					printf("\t\t\t   █ █ █            █ █ █\n");
					printf("\t\t\t    █   █          █   █\n");
					printf("\t\t\t   █ █   ██████████   █ █\n");
					printf("\n");
					break;
				case 2:
					printf("\t\t\t\e[1;92m    █ █ █\e[0m\e[1;94m █ █   █\e[0m\n");
					printf("\t\t\t\e[1;92m   █;█;█\e[1;94m;█;█;█ █ █\e[0m\n");
					printf("\t\t\t  ████████████  █ \n");
					printf("\t\t\t ███████████████ █\n");
					printf("\t\t\t█;;█;  █   █;█ █ █ \n");
					printf("\t\t\t█;;█;;     ;;█ █ █\n");
					printf("\t\t\t ██;;;;;;;;;;█ █ █\n");
					printf("\t\t\t   █████████████ █\n");
					printf("\t\t\t ███  \e[1;91m██  ██\e[0m █ █ █\n");
					printf("\t\t\t   █  \e[1;91m███ ███\e[0m ██ █ \n");
					printf("\t\t\t   ███   ███   ███\n");
					printf("\n");
					break;
				case 3:
					printf("\t\t\t    █████████   \e[1;92m█\e[0m\n");
					printf("\t\t\t   █         █ \e[1;92m█ █\e[0m\n");
					printf("\t\t\t  █  ███████  █ \e[1;92m█\e[0m\n");
					printf("\t\t\t █  █       █ ██ █\n");
					printf("\t\t\t█  █   █   █ █ █ █ \n");
					printf("\t\t\t█  █   █   █ █ █ █\n");
					printf("\t\t\t ██          █ █ █\n");
					printf("\t\t\t   █████████████ █\n");
					printf("\t\t\t ███\e[1;91m;;;;;;;;;\e[0m█ █ █\n");
					printf("\t\t\t   █\e[1;91m;;\e[0m███\e[1;91m;;;\e[0m█ ██ █ \n");
					printf("\t\t\t   ███   ███   ███\n");
					printf("\n");
					break;
				case 4:
					printf("\t\t\t             \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m██\e[0m    \e[1;93m;\e[0m \e[1;94m███\e[0m\n");
					printf("\t\t\t\e[1;93m   ███\e[0m      \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█   █   █\e[0m \e[1;93m;\e[0m \n");
					printf("\t\t\t\e[1;93m  █   █\e[0m    \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█   █\e[0m\e[1;93m;\e[0m \e[1;94m█   █\e[0m     \n");
					printf("\t\t\t\e[1;93m █ ;   █\e[0m    █   █        ███ ;\n");
					printf("\t\t\t\e[1;93m █ ;   █\e[0m    █   █         █\n");
					printf("\t\t\t\e[1;93m  █   █\e[0m    \e[1;91m█ ███ █\e[0m       ███\n");
					printf("\t\t\t\e[1;93m   ███\e[0m   ██       ██      █\e[1;93m:\e[0m    \n");
					printf("\t\t\t\e[1;94m         █         █\e[0m     \e[1;93m:\e[0m█    \n");
					printf("\t\t\t\e[1;94m         █         █\e[0m      █\e[1;93m:\e[0m   \n");
					printf("\t\t\t\e[1;94m         █         █\e[0m     \e[1;93m:\e[0m█    \n");
					printf("\n");
					break;
			}

			break;

		case REDMANE_CASTLE:
			switch(sEnemy.nType){
				case 1:
					printf("\t\t\t ██  ████████\n");
					printf("\t\t\t █ ██   ::   █ \n");
					printf("\t\t\t █ █    ::    █\n");
					printf("\t\t\t █ ██████████████\n");
					printf("\t\t\t █ █   █   █   █ \n");
					printf("\t\t\t █ █          █ \n");
					printf("\t\t\t█████    █████\n");
					printf("\t\t\t █ █\e[1;91m;\e[0m████ \e[1;91m;;\e[0m█ █\n");
					printf("\t\t\t ███\e[1;91m;;;;;;;\e[0m███\n");
					printf("\t\t\t   █\e[1;91m;;\e[0m███\e[1;91m;;\e[0m█  \n");
					printf("\t\t\t   ███   ███ \n");
					printf("\n");
					break;
				case 2:
					printf("\t\t\t     ████████\n");
					printf("\t\t\t   ██   ::   █ \n");
					printf("\t\t\t   █    ::    █\n");
					printf("\t\t\t   ██████████████\n");
					printf("\t\t\t ███   █   █;;██  \n");
					printf("\t\t\t █:█        ;;  ███\n");
					printf("\t\t\t █:██    ███;;█    █\n");
					printf("\t\t\t █:█\e[1;91m;\e[0m████ \e[1;91m;;\e[0m█;; █   █\n");
					printf("\t\t\t ███\e[1;91m;;;;;;;\e[0m█;;█    █\n");
					printf("\t\t\t   █\e[1;91m;;\e[0m███\e[1;91m;;\e[0m█;;  ███\n");
					printf("\t\t\t   ███   ███;;██\n");
					printf("\n");
					break;
				case 3:
					printf("\t\t\t ██  ████████\n");
					printf("\t\t\t █ ██   ::   █ \n");
					printf("\t\t\t █ █    ::    █\n");
					printf("\t\t\t █ ██████████████\n");
					printf("\t\t\t █ █   █   █   █ \n");
					printf("\t\t\t █ █          █ \n");
					printf("\t\t\t█████    ███████\n");
					printf("\t\t\t █ █\e[1;91m;\e[0m████ \e[1;91m;;\e[0m█    █\n");
					printf("\t\t\t ███\e[1;91m;;;;;;;\e[0m█    █\n");
					printf("\t\t\t   █\e[1;91m;;\e[0m███\e[1;91m;;\e[0m██  █\n");
					printf("\t\t\t   ███   ███ ██\n");
					printf("\n");
					break;
				case 4:
					printf("\t\t\t     █     \e[1;91m;:;;;:;     █\n");
					printf("\t\t\t   ██     \e[1;91m;:;:::;:;     ██ \n");
					printf("\t\t\t  █\e[1;93m:\e[0m █   \e[1;91m;\e[0m\e[1;93m█\e[0m\e[1;91m;:\e[0m\e[1;93m███\e[0m\e[1;91m:;\e[0m\e[1;93m█\e[0m\e[1;91m;\e[0m   █ \e[1;93m:\e[0m█\n");
					printf("\t\t\t █\e[1;93m:\e[0m  █   \e[1;91m:;\e[0m\e[1;93m██   ██\e[1;91m;:\e[0m   █  \e[1;93m:\e[0m█ \n");
					printf("\t\t\t █\e[1;93m:\e[0m  █    \e[1;91m:;\e[0m\e[1;93m█   █\e[1;91m;:\e[0m    █  \e[1;93m:\e[0m█\n");
					printf("\t\t\t  █\e[1;93m:\e[0m █\e[1;93m███\e[0m \e[1;91m██ ███ ██\e[0m \e[1;93m████\e[0m \e[1;93m:\e[0m█\n");
					printf("\t\t\t   █\e[1;93m:\e[0m█   \e[1;93m█         █\e[0m   █\e[1;93m:\e[0m█    \n");
					printf("\t\t\t   ██;\e[1;93m███\e[0m;         ;\e[1;93m███\e[0m;██  \n");
					printf("\t\t\t    ██;;;           ;;; ██   \n");
					printf("\t\t\t     █ \e[1;93m█             \e[1;93m█\e[0m  █     \n");
					printf("\n");
					break;
			}

			break;

		case VOLCANO_MANOR:
			switch(sEnemy.nType){
				case 1:
					printf("\t\t\t\e[1;91m ██\e[0m     ████████\n");
					printf("\t\t\t\e[1;91m █ █\e[0m  ██   ::   ██\n");
					printf("\t\t\t\e[1;91m █  █\e[0m █  █ :: █  █\n");
					printf("\t\t\t\e[1;91m █  █\e[0m ███      ███ \n");
					printf("\t\t\t\e[1;91m █ ██\e[0m  █ ██████ █   \n");
					printf("\t\t\t\e[1;91m █ █\e[0m █ █ █,,,,█ ████\n");
					printf("\t\t\t\e[1;91m█████\e[0m ██ █,,,,██    █\n");
					printf("\t\t\t\e[1;91m █ ██\e[0m █  █,,,,█      █\n");
					printf("\t\t\t\e[1;91m ███\e[0m ██  █,,,,██    █\n");
					printf("\t\t\t      █   ████  █  █ \n");
					printf("\t\t\t       ███   ███ ██\n");
					printf("\n");
					break;
				case 2:
					printf("\t\t\t\e[1;94m  █\e[0m     ████████\n");
					printf("\t\t\t\e[1;94m ███\e[0m  ██   ::   ██  \n");
					printf("\t\t\t\e[1;94m  █\e[0m   █  █ :: █  █ \n");
					printf("\t\t\t █ █  ███      ███  \n");
					printf("\t\t\t █ █   █  █████ █  █████\n");
					printf("\t\t\t █ ██  █ █ ;;  ██ █ ;;; █\n");
					printf("\t\t\t █ █ ███ █ ;;;  ██ ;;;; █\n");
					printf("\t\t\t █ ██ █  █ ;;;; ██ ;;;; █\n");
					printf("\t\t\t █ █ ██  █      ██      █\n");
					printf("\t\t\t █ █  █    ████████████ █\n");
					printf("\t\t\t ███   ███   ███   \n");
					printf("\n");
					break;
				case 3:
					printf("\t\t\t         ███ \n");
					printf("\t\t\t        █\e[1;93m;;;\e[0m█    \n");
					printf("\t\t\t       ███████    \n");
					printf("\t\t\t      █ █, ,█ █ \n");
					printf("\t\t\t     █  █ , █  █\n");
					printf("\t\t\t██████████ ██████████\n");
					printf("\t\t\t █  ; ;  ███  ; ;  █ \n");
					printf("\t\t\t  █ ; ; █\e[1;93m,,,\e[0m█ ; ; █\n");
					printf("\t\t\t  ;█████\e[1;93m,,,,,\e[0m█████;\n");
					printf("\t\t\t  ; ; █\e[1;93m,,,,,,,\e[0m█ ; ;\n");
					printf("\n");
					break;
				case 4:
					printf("\t\t\t\e[1;92m        ██████      \e[0m \e[1;91m  ;█; \e[0m\n");
					printf("\t\t\t\e[1;92m       █      █     \e[0m \e[1;91m ;██; \e[0m\n");
					printf("\t\t\t\e[1;92m      █        █    \e[0m \e[1;91m ;██; \e[0m\n");
					printf("\t\t\t\e[1;92m       █      █     \e[0m \e[1;91m ;██; \e[0m\n");
					printf("\t\t\t\e[1;92m        ██████      \e[0m \e[1;91m ;██; \e[0m\n");
					printf("\t\t\t\e[1;92m     ███ █,,,██  █  \e[0m \e[1;91m ;██; \e[0m\n");
					printf("\t\t\t\e[1;92m    █   █,,\e[1;93m█\e[0m\e[1;92m,,█ █ █\e[0m  \e[1;91m ;██; \e[0m\n");
					printf("\t\t\t\e[1;92m   █  █  ,,,,█ ██  █\e[0m \e[1;91m██████\e[0m\n");
					printf("\t\t\t\e[1;92m   █   ██████   █  █\e[0m \e[1;91m  ██  \e[0m\n");
					printf("\t\t\t\e[1;92m    █          █ █ █\e[0m \e[1;91m  ██  \e[0m\n");
					printf("\t\t\t\e[1;92m     ████████████ █ \e[0m \e[1;91m  ██  \e[0m\n");
					printf("\n");
					break;
			}

			break;

		case LEYNDELL_CAPITAL:
			switch(sEnemy.nType){
				case 1:
					printf("\t\t\t ██  ████████\n");
					printf("\t\t\t █ ██   ::   █ \n");
					printf("\t\t\t █ █    ::    █\n");
					printf("\t\t\t █ ██████████████\n");
					printf("\t\t\t █ █   █   █   █ \n");
					printf("\t\t\t █ █          █ \n");
					printf("\t\t\t█████    █████\n");
					printf("\t\t\t █ █\e[1;93m;\e[0m████\e[1;93m;;\e[0m█ █\n");
					printf("\t\t\t ███\e[1;93m;;;;;;;\e[0m███\n");
					printf("\t\t\t   █\e[1;93m;;\e[0m███\e[1;93m;;\e[0m█  \n");
					printf("\t\t\t   ███   ███ \n");
					printf("\n");
					break;
				case 2:
					printf("\t\t\t     ████████\n");
					printf("\t\t\t   ██   ::   █ \n");
					printf("\t\t\t   █    ::    █\n");
					printf("\t\t\t   ██████████████\n");
					printf("\t\t\t ███   █   █;;██  \n");
					printf("\t\t\t █:█        ;;  ███\n");
					printf("\t\t\t █:██    ███;;█    █\n");
					printf("\t\t\t █:█\e[1;93m;\e[0m████\e[1;93m;;\e[0m█;; █   █\n");
					printf("\t\t\t ███\e[1;93m;;;;;;;\e[0m█;;█    █\n");
					printf("\t\t\t   █\e[1;93m;;\e[0m███\e[1;93m;;\e[0m█;;  ███\n");
					printf("\t\t\t   ███   ███;;██\n");
					printf("\n");
					break;
				case 3:
					printf("\t\t\t ██  ████████\n");
					printf("\t\t\t █ ██   ::   █ \n");
					printf("\t\t\t █ █    ::    █\n");
					printf("\t\t\t █ ██████████████\n");
					printf("\t\t\t █ █   █   █   █ \n");
					printf("\t\t\t █ █          █ \n");
					printf("\t\t\t█████    ███████\n");
					printf("\t\t\t █ █\e[1;93m;\e[0m████\e[1;93m;;\e[0m█    █\n");
					printf("\t\t\t ███\e[1;93m;;;;;;;\e[0m█    █\n");
					printf("\t\t\t   █\e[1;93m;;\e[0m███\e[1;93m;;\e[0m██  █\n");
					printf("\t\t\t   ███   ███ ██\n");
					printf("\n");
					break;
				case 4:
					printf("\t\t\t     █  █ █;;;;;;;█ █   \n");
					printf("\t\t\t    █    █;█;███;█;█    \n");
					printf("\t\t\t   ██    ;█;█   █;█;   \n");
					printf("\t\t\t  ███   █;;██   ██;;█  \n");
					printf("\t\t\t  ██   █ ;;;█   █;;; █  \n");
					printf("\t\t\t ██   ██ ;██ ███ ██; ██\n");
					printf("\t\t\t  ██ █  ██         ██  █    \n");
					printf("\t\t\t ██   █   █████████   █\n");
					printf("\t\t\t  ██   █ ;    █    ; █  \n");
					printf("\t\t\t  :█:   █ ; ; █;  ; █        \n");
					printf("\n");
					break;	
			}

			break;

		case THE_ELDEN_THRONE: 
			if (nEldenThroneStage == 1) {
				printf("\t\t\t \e[1;93m,\e[0m ███ \e[1;93m,\e[0m     \e[1;91m;;;;;\e[0m      \n");
				printf("\t\t\t  █\e[1;93m;;;\e[0m█ \e[1;93m,\e[0m   \e[1;91m;;;;;;;\e[0m       \n");
				printf("\t\t\t\e[1;93m,\e[0m █\e[1;93m;;;\e[0m█\e[1;93m,\e[0m   \e[1;91m;;;;;;;;;\e[0m     \n");
				printf("\t\t\t\e[1;93m,\e[0m  ███  \e[1;93m,\e[0m \e[1;91m;;;\e[0m█ \e[1;91m;;\e[0m█\e[1;91m;;;\e[0m   \n");
				printf("\t\t\t    █     \e[1;91m;;;\e[0m█  \e[1;91m;\e[0m█\e[1;91m;;;\e[0m    \n");
				printf("\t\t\t   ███   \e[1;91m;;;\e[0m█ ███ █\e[1;91m;;\e[0m     \n");
				printf("\t\t\t    █   \e[1;91m;;\e[0m██   \e[1;93m:\e[0m   ██     \n");
				printf("\t\t\t    █   \e[1;91m;;\e[0m█ \e[1;93m, ,:, ,\e[0m █    \n");
				printf("\t\t\t    █   \e[1;91m;;\e[0m█\e[1;93m, ,:::, ,\e[0m█    \n");
				printf("\t\t\t    █   \e[1;91m;;\e[0m█  \e[1;93m,:::,\e[0m  █     \n");
				printf("\n");
			} else if (nEldenThroneStage == 2) {
				printf("\t\t\t\e[1;94m  ██     ███     ██\e[0m\n");
				printf("\t\t\t\e[1;94m █\e[0m\e[1;93m;\e[0m \e[1;94m█   █   █   █ \e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\n");
				printf("\t\t\t\e[1;94m █\e[0m \e[1;93m;\e[0m \e[1;94m█  █ █ █  █\e[0m \e[1;93m;\e[0m █\e[0m\n");
				printf("\t\t\t\e[1;94m  ██\e[0m\e[1;93m;\e[0m \e[1;94m███ \e[0m\e[1;93m;\e[0m \e[1;94m███\e[0m \e[1;93m;\e[0m\e[1;94m██\e[0m\n");
				printf("\t\t\t\e[1;94m █\e[0m\e[1;93m;\e[0m \e[1;94m█\e[0m\e[1;93m;\e[0m \e[1;94m█\e[0m  \e[1;93m;  \e[1;94m█\e[0m \e[1;93m;\e[0m\e[1;94m█\e[0m \e[1;93m;\e[0m\e[1;94m█\e[0m\n");
				printf("\t\t\t\e[1;94m█\e[0m \e[1;93m;\e[0m \e[1;94m█ █ \e[0m\e[1;93m; ; ;\e[0m \e[1;94m█ █ \e[0m\e[1;93m;\e[0m \e[1;94m█\e[0m\n");
				printf("\t\t\t\e[1;94m █\e[0m \e[1;93m;\e[0m \e[1;94m█ \e[0m\e[1;93m;  ;  ;\e[0m \e[1;94m█ \e[0m\e[1;93m;\e[0m \e[1;94m█\e[0m\n");
				printf("\t\t\t\e[1;94m  █ █\e[0m \e[1;93m; ; ; ; ;\e[0m \e[1;94m█ █\e[0m\n");
				printf("\t\t\t\e[1;94m █ ██\e[0m \e[1;93m; ; ; ; ;\e[0m \e[1;94m██ █\e[0m\n");
				printf("\t\t\t\e[1;94m█\e[0m \e[1;93m;\e[0m \e[1;94m█ \e[0m\e[1;93m; ; ; ; ;\e[0m \e[1;94m█\e[0m \e[1;93m;\e[0m \e[1;94m█\e[0m\n");
			}
				
	}

	printf("\t\t[INCOMING ENEMY DAMAGE]: %d\n", sEnemy.nAtk);
	printf("\n");
	
	printf("\t\t[NAME]: %s\n", pPlayer->strName);
	printPlayerHealth(pPlayer->nPlayerHP, pPlayer->nPlayerMaxHP);
	printf("%d", pPlayer->nPlayerHP);
	printf("\n\n\n");

	printf("\n\t    ██   \n");
	printf("\t   ████  \n");
	printf("\t  █\e[1;91m████\e[0m█ \n");
	printf("\t   ████  \n\n");

	printf("\t[POTIONS]: %d\n\n\n", pPlayer->nPotions);
	printf("\n");
	
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