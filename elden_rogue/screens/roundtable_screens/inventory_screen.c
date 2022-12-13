// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "../roundtable_screen.h" //When Player goes back.
#include "inventory_screen.h" //Contains constants for inventory screen.

#include "../../driver.h" //Contains all the structure definitions.

#include "../../config/settings.h" //Contains printing settings.
#include "../../utility/inventory_manager.h" //Contains the functions managing the inventory.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openInventory		Opens the Inventory of the Player.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void openInventory(Player* pPlayer) {

	// Input Variables
	int nInputInventory = -1; //random value basta wala sa choices

	// Temporary Variables
	int nPage = 1;

	displayInventory(-1, pPlayer, nPage);

	while(nInputInventory != 0) {

		nInputInventory = scanIntInput(0, 3); // Contains the Player's choice.

		processInventoryInput(nInputInventory, pPlayer, &nPage);
	}
}



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/*	processInventoryInput	Gets the Player's input and lets the player 
							select a weapon from their inventory.
	
	@param nInput 			An integer variable containing the player's
							input from the Inventory Screen.
	@param pPlayer			The Player Structure containing all of the 
							Player's statistics and items.
	@param nPage			An integer variable containing the current
							page of the inventory the Player is on.

	Pre-condition			nInput should be an integer value from 0-3.
							pPlayer should be initiated and all members 
							should have a value.	  					
							nPage should be an integer value.          */
void processInventoryInput(int nInput, Player* pPlayer, int* pPage) {
	
	// Get the amount of Weapons the Player has.
	int nPlayerWeapons;
	nPlayerWeapons = getPlayerWeapons(&(pPlayer->pInventory));

	// Input variables.
	int nInputWeapon = -1;

	// Slot containing the Player's selected weapon.
	Slot* pSelectedWeapon = NULL;
	int nTemp;
	int nPageTotal = INVENTORY_MAX_COLS * INVENTORY_MAX_ROWS;

	switch (nInput) {
			
		case SELECT:

			// Ask Player which weapon they want by inputting index.
			printInputTag();
			scanf("%d", &nInputWeapon); //Input Weapon Index
			
			// check if the index has a corresponding weapon in inventory.
			if (nInputWeapon != 0) 
				pSelectedWeapon = findWeaponSlot(nInputWeapon, pPlayer->pInventory); 
				//returns NULL if there is not weapon at that index.

			// if the index the player inputted has a weapon
			if (pSelectedWeapon != NULL) { 

				if (pSelectedWeapon->sWeapon.nDexReq <= pPlayer->nDexterity) {
					if (strcmp(pPlayer->sEquippedWeapon.strWeaponName, "NONE")){
						addWeapon(putWeaponInSlot(pPlayer->sEquippedWeapon), &(pPlayer->pInventory));
					}

					pPlayer->sEquippedWeapon = pSelectedWeapon->sWeapon;

					removeWeapon(pSelectedWeapon, &(pPlayer->pInventory));
					displayInventory(SELECT, pPlayer, *pPage);
				} else {
					displayInventory(LACK_DEX, pPlayer, *pPage);
				}	
				

			} else {
				displayInventory(NO_EXIST, pPlayer, *pPage);
			}

			break;

		case PREVIOUS:

			if (*pPage > 1) 
				*pPage -= 1;
			
			displayInventory(PREVIOUS, pPlayer, *pPage);

			break;

		case NEXT:

			nTemp = nPlayerWeapons / nPageTotal;

			if (nPlayerWeapons % nPageTotal != 0)
				nTemp++;

			if (*pPage < nTemp)
				*pPage += 1;

			displayInventory(NEXT, pPlayer, *pPage);

			break;

		case I_BACK:

			displayInventory(I_BACK, pPlayer, *pPage);
			openRoundTableHoldScreen(pPlayer);
			break;

	}
}

/* 	getPlayerWeapons	Gets the amount of weapons the player has in 
						their inventory.

	@param pInventoryHead	A pointer pointing to the Slot pointer
							pointing at the Inventory Head.	

	Pre-condition		pInventoryHead has to be the address of the Slot
						pointer pointing to the Inventory.  	 	   */
int getPlayerWeapons(Slot** pInventoryHead) {
	int nPlayerWeapons = 0;

	Slot* pInventorySlot = *pInventoryHead; //get the first weapon

	if (pInventorySlot == NULL) {
		return 0;
	} else {
		//Get the last inventory slot.
		while (pInventorySlot != NULL) {
			pInventorySlot = pInventorySlot->pNext;
			nPlayerWeapons++;
		}
	}
	
	return nPlayerWeapons;
}

/*	getSpriteFromWeapon	Gets the corresponding sprite of the given Weapon.
	
	@param sWeapon 		A Weapon variable containing the details of the
						needed weapon.
	
	@return 			A character pointer that's pointing to a string.

	Pre-condition 		sWeapon is initialized and has valid values.   */
char* getSpriteFromWeapon(Weapon sWeapon) {
	
	int nIndex, nWeaponOrder, i;
	int nEmptySpaces;
	char* strSprite = malloc(sizeof(char) * (SLOT_WIDTH - 3) * 10);
	
	char aSprites[24][(SLOT_WIDTH - 3) * 10] = {"         ███         █  █     ██ █   █     ███   █        █  █        ██████     ███  ███     █ █          ███                    ",
										  	    "           █          ██          ██          ██        █ ██          ██        ████ █       █ █          ███                     ",
										  	    "           ;           ;:          :;          ;:        ; ;;          ;;        ████ ;       █ █          ███                    ",
										        "          █:          █:█         █:█         █:█         █:█       █ █:█         ███          ██          █  █                   ",
										        "       █           █           █           █            █            █             █  █          ██          █ ██                 ",
										        "      ;            █;            █;            █           █;           █          █ ;           █          ██ █                  ",
										        "      █;           ██;           ██;           █;          ██;          █;;        █ █;;         █;;        ██ █                  ",
										        "     █            ██            ██            █           ██           █            █           ;;          ;;                    ",
										        "     █████       ██   ██     ██     ██   █        █   █        █    ██      █   █ █ █   █     ██ █  ██   ██ █ ███                 ",
										        "    ████ █ █    ██   ███    ██      ██  ██       █   ██       █   ██      ██    ██  █ ██      ██  ██        ████ █                ",
										        "   ;███;  ██   ;█;;;█;██   ;█;   ;██;   █;     ;█;   █;     ;█;   █;    ;;█;   ;█;  ;;█;     ;█;;;█;       ;███;                  ",
										        "          ██          █ █     ;;;;█; █    ;  ██ ;██   ;;  ██;██    ;;   █ ██     ;   ████     ;; ; ███      ;;;█;█                ",
										        "         █           ███         ███         █:█      █  █:█        █ █:█         █:█          ██          █  █                   ",
										        "         ██       █   ██      ██████       █████       ███████     █████        █████         ██            █                     ",
										        "          ██        █ ██          ██         ███ █       ██          ██:         ██:         ███         ██                       ",
										        "         ██            ██    ███  ██ █      █████       ████████    ██████  █   █████        ███         ██                       ",
										        "          ██         ;█;        ;██;        ;██;        ;█;;█;       █   ;█;     █           █           █                        ",
										        "         ██          █           █           █  █        █████       █           █           █           █                        ",
										        " █ ; █ █: █;  ;█ ::█::█;█    █ █:█ ;█    ; █ ; █;       ;█ ;         █           █           █           █                        ",
										        "           █           ██          ██          ██          ██          ██        █  █          ██          █  █                   ",
										        "     ██  ██      █:█  █:█    █;;█ █ █     █ █ █;█      █;█ █  █      █ ██;█     ████  █      █ ████       ███                     ",
										        "      █  ██        ███         █ . ██       █   █        ████        █ █         █ █         █ █           █                      ",
										        "                  :::         :   :      █████████   :█: ::: :█:  : █ : : █ :  :  █ : █  :  :   █ █   :   ::: █ :::               ",
										        " ;  ;███;█;   █; █   █;    ██;█  █;;█   █ ██ █;;█;█  ██ ███;█; ;  ;;██  █;;█   █;;███;;█     █;;;;;█       █████                  "};
	
	if (!strcmp(sWeapon.strWeaponName, "SHORT SWORD") || 
		!strcmp(sWeapon.strWeaponName, "UCHIGATANA") ||
		!strcmp(sWeapon.strWeaponName, "WHIP") ||
		!strcmp(sWeapon.strWeaponName, "CLAYMORE") ||
		!strcmp(sWeapon.strWeaponName, "ASTROLOGER’S STAFF") ||
		!strcmp(sWeapon.strWeaponName, "FINGER SEAL"))
		nWeaponOrder = 0;
	else if (!strcmp(sWeapon.strWeaponName, "ROGIER'S RAPIER") ||
		!strcmp(sWeapon.strWeaponName, "MOONVEIL") ||
		!strcmp(sWeapon.strWeaponName, "URUMI") ||
		!strcmp(sWeapon.strWeaponName, "STARSCOURGE GREATSWORD") ||
		!strcmp(sWeapon.strWeaponName, "ALBINAURIC STAFF") ||
		!strcmp(sWeapon.strWeaponName, "GODSLAYER’S SEAL"))
		nWeaponOrder = 1;
	else if (!strcmp(sWeapon.strWeaponName, "CODED SWORD") ||
		!strcmp(sWeapon.strWeaponName, "RIVERS OF BLOOD") ||
		!strcmp(sWeapon.strWeaponName, "THORNED WHIP") ||
		!strcmp(sWeapon.strWeaponName, "INSEPARABLE SWORD") ||
		!strcmp(sWeapon.strWeaponName, "STAFF OF THE GUILTY") ||
		!strcmp(sWeapon.strWeaponName, "GOLDEN ORDER SEAL"))
		nWeaponOrder = 2;
	else if (!strcmp(sWeapon.strWeaponName, "SWORD OF NIGHT AND FLAME") ||
		!strcmp(sWeapon.strWeaponName, "HAND OF MALENIA") ||
		!strcmp(sWeapon.strWeaponName, "HOSLOW’S PETAL WHIP") ||
		!strcmp(sWeapon.strWeaponName, "MALIKETH’S BLACK BLADE") ||
		!strcmp(sWeapon.strWeaponName, "CARIAN REGAL SCEPTER") ||
		!strcmp(sWeapon.strWeaponName, "DRAGON COMMUNION SEAL"))
		nWeaponOrder = 3;

	nIndex = ((sWeapon.nWeaponType - 1) * 4) + nWeaponOrder;
	strcpy(strSprite, aSprites[nIndex]);

	nEmptySpaces = ((SLOT_WIDTH - 3) * 10) - strlen(strSprite);

	for (i = 0; i < nEmptySpaces; i++) {
		strcat(strSprite, " ");
	}

	return strSprite;
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	printTopBorderSlots 	Prints the Top Border of the Inventory 
							screen.

	@param nCols 			An integer variable containing the number of
							times the border will be printed.

	Pre-condition			nCols has an integer value. 			   */
void printTopBorderSlots(int nCols) {

	int i;

	printMultiple(" ", SCREEN_PADDING);

	for (i = 0; i < nCols; i++) {
		printf("╔");
		printMultiple("═", SLOT_WIDTH);
		printf("╗");
	}

	printf("\n");
}

/* 	printBottomBorderSlots 	Prints the bottom Border of the Inventory 
							screen.

	@param nCols 			An integer variable containing the number of
							times the border will be printed.

	Pre-condition			nCols has an integer value. 			   */
void printBottomBorderSlots(int nCols) {

	int i;

	printMultiple(" ", SCREEN_PADDING);

	for (i = 0; i < nCols; i++) {
		printf("╚");
		printMultiple("═", SLOT_WIDTH);
		printf("╝");
	}

	printf("\n");
}

/*	printShopContent	Prints one line of a Weapon in a single slot.
	
	@param sWeapon		A Weapon variable containing the Weapon stats to
						be printed.
	@param nLine 		An integer variable containing the line number 
						of the slot being printed.

	Pre-condition		sWeapon should contain valid Weapon values.
						nLine should be from 1 to 7. 				   */
void printContentSlot(Weapon sWeapon, int nLine) {

	int nSpaces = 2;

	switch (nLine) {
		case 1:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("%-*.*s", SLOT_WIDTH-4, SLOT_WIDTH-4, sWeapon.strWeaponName);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 2:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("%-*.*s", SLOT_WIDTH-4, SLOT_WIDTH-4, sWeapon.strWeaponName + SLOT_WIDTH-4);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			printSprite(sWeapon, nLine);
			break;
		case 13:
			printf("│");
			printf("HP ");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nHP);
			printf("END");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nEnd);
			printf("│");
			break;
		case 14:
			printf("│");
			printf("DEX");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nDexReq);
			printf("STR");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nStr);
			printf("│");
			break;
		case 15:
			printf("│");
			printf("INT");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nInt);
			printf("FTH");
			printMultiple(" ", nSpaces);
			printf("%*d ", 2, sWeapon.nFth);
			printf("│");
			break;
		case 16:
			printf("│");
			printMultiple(" ", (SLOT_WIDTH-6)/2);
			printf("> %0.*d <", 2, sWeapon.nWeaponIndex);
			printMultiple(" ", (SLOT_WIDTH-6)/2);
			printf("│");
			break;
	}
}

/* 	printSprite 	Prints the sprite of the weapon by line.
	
	@param sWeapon 		A Weapon variable containing the details of the
						needed weapon.
	@param nLine		An integer variable containing the line number
						to be printed.

	Pre-condition 		sWeapon is initialized and has valid values.   
						nLine has to be from 3 to 12.				   */
void printSprite(Weapon sWeapon, int nLine) {

	char* strSprite = getSpriteFromWeapon(sWeapon);
	nLine -= 3;

	printf("│");
	printMultiple(" ", 2);
	printf("%-*.*s ", SLOT_WIDTH-5, SLOT_WIDTH-5, strSprite + (nLine * (SLOT_WIDTH-5)));
	printMultiple(" ", 2);
	printf("│");

	free(strSprite);
}

/*	printEmptySlot		Prints one line of an empty slot.			   */
void printEmptySlot() {
	
	printf("│");
	printMultiple(" ", SLOT_WIDTH);
	printf("│");
}

/*	printInventoryGrid	Displays the weapons in the Player's inventory.
	
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items. 
	@param nPage		An integer variable containing the page number
						the Player is currently viewing.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	   
						nPage should be an integer value.			   */
void printInventoryGrid(Player* pPlayer, int nPage) {

	// Contains the values need to be printed.
	Slot* pInventoryHead = pPlayer->pInventory; // Head of the inventory.
	Slot* pTempHead;

	int i, j, k; // Counts the rows, columns, and offsets the head.

	// Page numbers start at 1. So, offset the Head by 8 for every additional page.
	// nPage - 1 because at the first page (nPage = 1), the condition will be false 
	// at and there won't be any offset.
	for (k = 0; k < (INVENTORY_MAX_COLS * INVENTORY_MAX_ROWS) * (nPage-1); k++) {
		pInventoryHead = pInventoryHead->pNext;
	}

	printf("\n");

	//Print existing weapons in a 5x4 grid.
	for(i = 0; i < INVENTORY_MAX_ROWS; i++) {

		printTopBorderSlots(INVENTORY_MAX_COLS);

		for (k = 1; k <= INVENTORY_SLOT_HEIGHT; k++) {

			printMultiple(" ", SCREEN_PADDING);
			pTempHead = pInventoryHead; //reset every line

			for (j = 0; j < INVENTORY_MAX_COLS; j++) {
				
				if (pTempHead != NULL) {
					if (strcmp(pTempHead->sWeapon.strWeaponName, "NONE")) {
						
						printContentSlot(pTempHead->sWeapon, k);
						pTempHead = pTempHead->pNext;
					} else {
						printEmptySlot(INVENTORY_MAX_COLS, INVENTORY_MAX_ROWS);
					}
				} else {
					printEmptySlot(INVENTORY_MAX_COLS, INVENTORY_MAX_ROWS);
				}
			}

			printf("\n");
		}

		//Update the outer one too.
		for (k = 0; k < INVENTORY_MAX_COLS; k++) {
			
			if (pInventoryHead != NULL)
				pInventoryHead = pInventoryHead->pNext;
		}				
			
		printBottomBorderSlots(INVENTORY_MAX_COLS);
	}
}

/* 	displayInventory	Displays the Inventory screen.
	
	@param nPrompt 		An integer variable containing the player's input 
						from the Inventory Screen.
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param nPage		An integer variable containing the current page 
						of the inventory the Player is on.

	Pre-condition		nPrompt should be an integer value from 0-5.
						pPlayer should be initiated and all members 
						should have a value.	  					
						nPage should be an integer value.          	   */
void displayInventory(int nPrompt, Player* pPlayer, int nPage) {
	
	system("cls");

	printHeader("INVENTORY", 9);

	printInventoryGrid(pPlayer, nPage);

	printf("\n");
	printOption(1, "SELECT WEAPON");
	printOption(2, "PREVIOUS PAGE");
	printOption(3, "NEXT PAGE");
	printOption(0, "BACK");
	printf("\n");

	switch(nPrompt) {
		case SELECT:
			printMultiple(" ", SCREEN_PADDING);
			printf("You equipped %s.", pPlayer->sEquippedWeapon.strWeaponName);
			break;
		case NO_EXIST:
			printSystemMessage("There's no weapon at that index.");
			break;

		case LACK_DEX:
			printSystemMessage("You don't have enough dexterity to equip that weapon.");
			break;

		case PREVIOUS:
		case NEXT:
			printMultiple(" ", SCREEN_PADDING);
			printf("You're now at PAGE %d.", nPage);
			break;

		case I_BACK:
			printSystemMessage("Going back to Roundtable Hold.");
			break;
		default:
			break;
	}

	Sleep(DELAY);
}