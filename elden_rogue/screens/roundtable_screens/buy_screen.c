// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "../roundtable_screen.h" //When Player goes back.
#include "inventory_screen.h" //When adding the bought weapon to inventory.

#include "../../driver.h" //Contains all the structure definitions.

#include "../../config/settings.h" //Contains printing settings.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/*	openBuyScreen 		Opens the buy screen.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void openBuyScreen(Player* pPlayer) {

	int nInputBuy = 100;
	int nInputWeaponType = 100;

	Stock* pStockOfType; //list of weapons of the same type
	Stock sStockToBeBought; //weapon to be bought
	Slot* pWeaponChosen;

	displayBuyTypes(-1, pPlayer);

	while (nInputWeaponType != 0) {

		nInputWeaponType = scanIntInput(0, 6); //Input what type of weapon.

		if(nInputWeaponType != 0) {
			
			pStockOfType = getStocksFromType(nInputWeaponType);

			displayBuyStocks(-1, pPlayer, pStockOfType);

			while (nInputBuy != 0) {

				nInputBuy = scanIntInput(0, 4); //Input which weapon.

				if (nInputBuy != 0) {

					sStockToBeBought = pStockOfType[nInputBuy-1];
					pWeaponChosen = convertStockToSlot(sStockToBeBought);

					if (sStockToBeBought.nCost <= pPlayer->nRunes) {

						addWeapon(pWeaponChosen, &(pPlayer->pInventory));
						pPlayer->nRunes -= sStockToBeBought.nCost;
						displayBuyStocks(nInputBuy, pPlayer, pStockOfType);

					} else {

						displayBuyStocks(UNSUCCESSFUL, pPlayer, pStockOfType);
					}
				} else {
					nInputWeaponType = 0;
				}
			}
		}
	}

	openRoundTableHoldScreen(pPlayer);
}



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/*	getStocksFromType	Gets the list of weapons and their cost and 
						returns it as a Stock pointer array.

	@param nWeaponType 	An integer value containing the type of weapon
						to make a list of.

	@return 			A Stock pointer.

	Pre-condition		nWeaponType should be an integer from 1 to 6.  */
Stock* getStocksFromType(int nWeaponType) {
	Stock* pWeaponsOfType = malloc(sizeof(Stock) * 4);

	Stock aSwords[4] = {{{ITEM_ONE, "SHORT SWORD", WEAPON_SWORD, 13, 0, 15, 15, 15, 15}, 1000},
						{{ITEM_TWO, "ROGIER'S RAPIER", WEAPON_SWORD, 18, 10, 35, 25, 35, 35}, 2000},
						{{ITEM_THREE, "CODED SWORD", WEAPON_SWORD, 21, 20, 40, 35, 40, 40}, 4000},
						{{ITEM_FOUR, "SWORD OF NIGHT AND FLAME", WEAPON_SWORD, 25, 30, 55, 45, 55, 55}, 8000}};
	
	Stock aKatanas[4] = {{{ITEM_ONE, "UCHIGATANA", WEAPON_KATANA, 15, 20, 0, 35, 30, 0}, 1875},
						 {{ITEM_TWO, "MOONVEIL", WEAPON_KATANA, 20, 30, 0, 40, 45, 0}, 3750},
						 {{ITEM_THREE, "RIVERS OF BLOOD", WEAPON_KATANA, 25, 40, 0, 45, 60, 0}, 7500},
						 {{ITEM_FOUR, "HAND OF MALENIA", WEAPON_KATANA, 30, 50, 0, 50, 75, 0}, 15000}};
	
	Stock aWhips[4] = {{{ITEM_ONE, "WHIP", WEAPON_WHIP, 20, 15, 0, 60, 20, 0}, 1500},
					   {{ITEM_TWO, "URUMI", WEAPON_WHIP, 25, 20, 10, 70, 40, 0}, 3000},
					   {{ITEM_THREE, "THORNED WHIP", WEAPON_WHIP, 30, 30, 0, 80, 50, 40}, 5000},
					   {{ITEM_FOUR, "HOSLOW’S PETAL WHIP", WEAPON_WHIP, 35, 35, 20, 90, 55, 20}, 10000}};
	
	Stock aGreatswords[4] = {{{ITEM_ONE, "CLAYMORE", WEAPON_GREATSWORD, 9, 15, 0, 10, 20, 0}, 3000},
						     {{ITEM_TWO, "STARSCOURGE GREATSWORD", WEAPON_GREATSWORD, 14, 20, 0, 15, 40, 20}, 6000},
						     {{ITEM_THREE, "INSEPARABLE SWORD", WEAPON_GREATSWORD, 19, 25, 60, 20, 70, 60}, 12000},
						     {{ITEM_FOUR, "MALIKETH’S BLACK BLADE", WEAPON_GREATSWORD, 24, 30, 40, 25, 80, 60}, 24000}};
	
	Stock aStaves[4] = {{{ITEM_ONE, "ASTROLOGER’S STAFF", WEAPON_STAVE, 12, 5, 25, 20, 5, 15}, 2000},
						 {{ITEM_TWO, "ALBINAURIC STAFF", WEAPON_STAVE, 14, 10, 45, 30, 10, 35}, 4000},
						 {{ITEM_THREE, "STAFF OF THE GUILTY", WEAPON_STAVE, 16, 15, 65, 40, 15, 60}, 8000},
						 {{ITEM_FOUR, "CARIAN REGAL SCEPTER", WEAPON_STAVE, 18, 25, 85, 50, 20, 75}, 16000}};
	
	Stock aSeals[4] = {{{ITEM_ONE, "FINGER SEAL", WEAPON_SEAL, 10, 10, 16, 45, 0, 20}, 2500},
					   {{ITEM_TWO, "GODSLAYER’S SEAL", WEAPON_SEAL, 12, 15, 35, 50, 0, 40}, 5000},
					   {{ITEM_THREE, "GOLDEN ORDER SEAL", WEAPON_SEAL, 14, 20, 65, 55, 0, 65}, 10000},
					   {{ITEM_FOUR, "DRAGON COMMUNION SEAL", WEAPON_SEAL, 18, 25, 75, 60, 0, 80}, 15000}};

	int i;


	switch(nWeaponType) {
		case WEAPON_SWORD:
			for(i = 0; i < 4; i++) {
				*(pWeaponsOfType + i) = aSwords[i];
			}

			break;

		case WEAPON_KATANA:
			for(i = 0; i < 4; i++) {
				*(pWeaponsOfType + i) = aKatanas[i];
			}

			break;
		case WEAPON_WHIP:
			for(i = 0; i < 4; i++) {
				*(pWeaponsOfType + i) = aWhips[i];
			}

			break;
		case WEAPON_GREATSWORD:
			for(i = 0; i < 4; i++) {
				*(pWeaponsOfType + i) = aGreatswords[i];
			}

			break;
		case WEAPON_STAVE:
			for(i = 0; i < 4; i++) {
				*(pWeaponsOfType + i) = aStaves[i];
			}

			break;
		case WEAPON_SEAL:
			for(i = 0; i < 4; i++) {
				*(pWeaponsOfType + i) = aSeals[i];
			}

			break;
	}

	return pWeaponsOfType;
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/*	printTopShopBorders		Prints the top borders of the shop.
	
	@param nCols 			An integer variable containing the number of
							times the border will be printed.

	Pre-condition			nCols has an integer value.				   */
void printTopShopBorders(int nCols) {

	int i;

	for (i = 0; i < nCols; i++) {
		printf("╔");
		printMultiple("═", SHOP_SLOT_WIDTH);
		printf("╗");
	}

}

/*	printBottomShopBorder	Prints the bottom borders of the shop.
	
	@param nCols 			An integer variable containing the number of
							times the border will be printed.

	Pre-condition			nCols has an integer value.				   */
void printBottomShopBorder(int nCols) {

	int i;

	for (i = 0; i < nCols; i++) {
		printf("╚");
		printMultiple("═", SHOP_SLOT_WIDTH);
		printf("╝");
	}

	printf("\n");
}

/*	printShopContent		Prints one line of a Weapon in a single slot.
	
	@param sShopStock		A Stock variable containing the stats and
							cost of the weapon to be displayed.
	@param nLine 			An integer variable containing the line
							number of the slot being printed.

	Pre-condition			sShopStock should contain valid Stock values
							nLine should be from 1 to SHOP_SLOT_HEIGHT.*/
void printShopContent(Stock sShopStock, int nLine) {

	Weapon sWeapon = sShopStock.sWeapon;
	int nSpaces = 2;
	int nStatSpaces = 6;
	

	switch (nLine) {
		case 1:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("%-*.*s", SHOP_SLOT_WIDTH-4, SHOP_SLOT_WIDTH-4, sWeapon.strWeaponName);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 2:
			printf("│");
			printMultiple(" ", nSpaces);
			if (strlen(sShopStock.sWeapon.strWeaponName) > SHOP_SLOT_WIDTH-4)								
				printf("%-*.*s", SHOP_SLOT_WIDTH-4, SHOP_SLOT_WIDTH-4, sWeapon.strWeaponName + SHOP_SLOT_WIDTH-4);
			else
				printMultiple(" ", SHOP_SLOT_WIDTH-4);
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
			printWeaponSprite(sShopStock, nLine);
			break;
		case 13:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("COST: %*d", SHOP_SLOT_WIDTH-10, sShopStock.nCost);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 14:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("DEXTERITY    ││  %*d", SHOP_SLOT_WIDTH-21, sWeapon.nDexReq);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 15:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("HP ");
			printMultiple(" ", nStatSpaces);
			printf("%*d", 2, sWeapon.nHP);
			printMultiple(" ", nSpaces);
			printf("││");
			printMultiple(" ", nSpaces);
			printf("END");
			printMultiple(" ", nStatSpaces);
			printf("%*d", 2, sWeapon.nEnd);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 16:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("DEX");
			printMultiple(" ", nStatSpaces);
			printf("%*d", 2, 0);
			printMultiple(" ", nSpaces);
			printf("││");
			printMultiple(" ", nSpaces);
			printf("STR");
			printMultiple(" ", nStatSpaces);
			printf("%*d", 2, sWeapon.nStr);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 17:
			printf("│");
			printMultiple(" ", nSpaces);
			printf("INT");
			printMultiple(" ", nStatSpaces);
			printf("%*d", 2, sWeapon.nInt);
			printMultiple(" ", nSpaces);
			printf("││");
			printMultiple(" ", nSpaces);
			printf("FTH");
			printMultiple(" ", nStatSpaces);
			printf("%*d", 2, sWeapon.nFth);
			printMultiple(" ", nSpaces);
			printf("│");
			break;
		case 18:
			printf("│");
			printMultiple(" ", (SHOP_SLOT_WIDTH-6)/2);
			printf("> %0.*d <", 2, sWeapon.nWeaponIndex);
			printMultiple(" ", (SHOP_SLOT_WIDTH-6)/2);
			printf("│");
			break;
	}
}

/* 	printWeaponSprite 		Prints the weapon sprite.
	
	@param sShopStock 		A Stock variable containing the weapon details.
	@param nLine 			An integer variable containing the line number
							to be printed.

	Pre-condition			sShopStock should contain valid Stock values
							nLine should be from 3 to 12.			   */
void printWeaponSprite(Stock sShopStock, int nLine) {

	char strSprite[60];
	nLine -= 3;

	char aSwordOne[10][60] = {"                ███         ",
							  "               █  █         ",
							  "           ██ █   █         ",
							  "           ███   █          ",
							  "             █  █           ",
							  "            ██████          ",
							  "          ███  ███          ",
							  "          █ █               ",
							  "          ███               ",
							  "                            "};
	char aSwordTwo[10][60] = {"                  █         ",
							  "                 ██         ",
							  "                ██          ",
							  "               ██           ",
							  "            █ ██            ",
							  "             ██             ",
							  "          ████ █            ",
							  "          █ █               ",
							  "          ███               ",
							  "                            "};	
  	char aSwordThr[10][60] = {"                  ;         ",
							  "                 ;:         ",
							  "                :;          ",
							  "               ;:           ",
							  "            ; ;;            ",
							  "             ;;             ",
							  "          ████ ;            ",
							  "          █ █               ",
							  "          ███               ",
							  "                            "};						
	char aSwordFou[10][60] = {"                  █:        ",
						      "                 █:█        ",
						      "                █:█         ",
						      "               █:█          ",
						      "              █:█           ",
						      "           █ █:█            ",
						      "            ███             ",
						      "            ██              ",
						      "           █  █             ",
						      "                            "};
	char aKatanaOne[10][60] = {"               █            ",
							   "              █             ",
							   "             █              ",
							   "            █               ",
							   "            █               ",
							   "            █               ",
							   "             █  █           ",
							   "              ██            ",
							   "             █ ██           ",
							   "                            "};
	char aKatanaTwo[10][60] = {"              ;             ",
							   "              █;            ",
							   "               █;           ",
							   "                █           ",
							   "               █;           ",
							   "               █            ",
							   "             █ ;            ",
							   "              █             ",
							   "            ██ █            ",
							   "                            "};
	char aKatanaThr[10][60] = {"              █;            ",
							   "              ██;           ",
							   "               ██;          ",
							   "                █;          ",
							   "               ██;          ",
							   "               █;;          ",
							   "             █ █;;          ",
							   "              █;;           ",
							   "            ██ █            ",
							   "                            "};
	char aKatanaFou[10][60] = {"             █              ",
							   "             ██             ",
							   "              ██            ",
							   "               █            ",
							   "              ██            ",
							   "              █             ",
							   "              █             ",
							   "             ;;             ",
						       "            ;;              ",
							   "                            "};
	char aWhipOne[10][60] = {"            █████           ",
							 "           ██   ██          ",
							 "          ██     ██         ",
							 "         █        ██        ",
							 "         █         █        ",
							 "          ██       █        ",
							 "         █ █  █   █         ",
							 "          ██  █  ██         ",
							 "         ██ █  ███          ",
							 "                            "};
	char aWhipTwo[10][60] = {"            █████  █ █      ",
							 "           ███  ██  █       ",
							 "          ██      ██ █      ",
							 "         ██       ██        ",
							 "         ██       ██        ",
							 "         ██       ██        ",
							 "          ██   █ ██         ",
							 "           ██   ██          ",
							 "            █████ █         ",
							 "                            "};
	char aWhipThr[10][60] = {"           ;█████;  ██      ",
							 "          ;█;;;;;█;██       ",
							 "         ;█;     ;██;       ",
							 "         █;       ;█;       ",
							 "         █;       ;█;       ",
							 "         █;      ;;█;       ",
							 "         ;█;    ;;█;        ",
							 "          ;█;;;;;█;         ",
							 "           ;█████;          ",
							 "                            "};
	char aWhipFou[10][60] = {"                 ██         ",
						     "                █ █         ",
						     "           ;;;;█; █         ",
						     "          ;  ██ ;██         ",
						     "         ;;  ██;██          ",
						     "         ;;   █ ██          ",
						     "          ;   ████          ",
						     "          ;; ; ███          ",
						     "           ;;;█;█           ",
						     "                            "};
	char aGreatSwordOne[10][60] = {"                  █         ",
								   "                 ███        ",
								   "                ███         ",
								   "               █:█          ",
								   "           █  █:█           ",
								   "            █ █:█           ",
								   "             █:█            ",
								   "             ██             ",
								   "            █  █            ",
								   "                            "};
	char aGreatSwordTwo[10][60] = {"                    ██      ",
								   "               █   ██       ",
								   "              ██████        ",
								   "            ███████         ",
								   "           █████████        ",
								   "          ███████           ",
								   "         ██████             ",
								   "          ███               ",
								   "           █                ",
								   "                            "};
	char aGreatSwordThr[10][60] = {"                   ██       ",
								   "                █ ██        ",
								   "                 ██         ",
								   "               ███ █        ",
								   "              ███           ",
								   "             ██:            ",
								   "            ██:             ",
								   "           ███              ",
								   "          ██                ",
								   "                            "};					      
	char aGreatSwordFou[10][60] = {"                     ██     ",
								   "                      ██    ",
								   "               ███  ██ █    ",
								   "                █████       ",
								   "               ███████      ",
								   "            ████████ ███    ",
								   "           ██████           ",
								   "           ████             ",
								   "          ██                ",
								   "                            "};
	char aStaveOne[10][60] = {"                   ██       ",
							  "                 ;█;        ",
							  "               ;██;         ",
							  "              ;██;          ",
							  "             ;█;;█;         ",
							  "             █   ;█;        ",
							  "            █               ",
							  "           █                ",
							  "          █                 ",
							  "                            "};
	char aStaveTwo[10][60] = {"                   ██       ",
							  "                  █         ",
							  "                 █          ",
							  "                █  █        ",
							  "               █████        ",
							  "              █             ",
							  "             █              ",
							  "            █               ",
							  "           █                ",
							  "                            "};
	char aStaveThr[10][60] = {"        ;█; █ █:█ ; █ █     ",
							  "         ; █ ::█::█; ;      ",
							  "          ; █ █:█ ;█        ",
							  "           ; █ ; █;         ",
							  "            █;█ ;           ",
							  "           █                ",
							  "          █                 ",
							  "         █                  ",
							  "        █                   ",
							  "                            "};
	char aStaveFou[10][60] = {"                   █        ",
						      "                  ██        ",
						      "                 ██         ",
						      "                ██          ",
						      "               ██           ",
						      "              ██            ",
						      "           █  █             ",
						      "            ██              ",
						      "           █  █             ",
						      "                            "};
	char aSealOne[10][60] = {"              ██   ██       ",
							 "             █:█   █:█      ",
							 "            █;;█  █ █       ",
							 "            █ █  █;█        ",
							 "            █;█ █  █        ",
							 "             █ ██;█         ",
							 "           ████  █          ",
							 "           █ ████           ",
							 "           ███              ",
							 "                            "};
	char aSealTwo[10][60] = {"               █  ██        ",
							 "               ███          ",
							 "              █ . ██        ",
							 "              █   █         ",
							 "              ████          ",
							 "             █ █            ",
							 "            █ █             ",
							 "           █ █              ",
							 "            █               ",
							 "                            "};
	char aSealThr[10][60] = {"            :::::           ",
							 "         ███████████        ",
							 "      :::█::    :::█:::     ",
							 "     :   █: ::::  :█  ::    ",
							 "     :    █: ::  :█    :    ",
							 "     :     █:::::█     :    ",
							 "      :    █  :  █    :     ",
							 "       :    █: :█   ::      ",
							 "        :::: █ █ :::        ",
							 "              █             "};
	char aSealFou[10][60] = {"          ;  ;███;█;        ",
						     "          █; █   █;         ",
						     "          ██;█  █;;█        ",
						     "          █ ██ █;;█;█       ",
						     "          ██ ███;█; ;       ",
						     "          ;;██  █;;█        ",
						     "          █;;███;;█         ",
						     "           █;;;;;█          ",
						     "            █████           ",
						     "                            "};	

	switch (sShopStock.sWeapon.nWeaponType) {

		case WEAPON_SWORD:
			switch(sShopStock.sWeapon.nWeaponIndex){
				case ITEM_ONE:
					strcpy(strSprite, aSwordOne[nLine]);
					break;
				case ITEM_TWO:
					strcpy(strSprite, aSwordTwo[nLine]);
					break;
				case ITEM_THREE:
					strcpy(strSprite, aSwordThr[nLine]);
					break;
				case ITEM_FOUR:
					strcpy(strSprite, aSwordFou[nLine]);
					break;
			}
			break;
		case WEAPON_KATANA:
			switch(sShopStock.sWeapon.nWeaponIndex){
				case ITEM_ONE:
					strcpy(strSprite, aKatanaOne[nLine]);
					break;
				case ITEM_TWO:
					strcpy(strSprite, aKatanaTwo[nLine]);
					break;
				case ITEM_THREE:
					strcpy(strSprite, aKatanaThr[nLine]);
					break;
				case ITEM_FOUR:
					strcpy(strSprite, aKatanaFou[nLine]);
					break;
			}
			break;
		case WEAPON_WHIP:
			switch(sShopStock.sWeapon.nWeaponIndex){
				case ITEM_ONE:
					strcpy(strSprite, aWhipOne[nLine]);
					break;
				case ITEM_TWO:
					strcpy(strSprite, aWhipTwo[nLine]);
					break;
				case ITEM_THREE:
					strcpy(strSprite, aWhipThr[nLine]);
					break;
				case ITEM_FOUR:
					strcpy(strSprite, aWhipFou[nLine]);
					break;
			}
			break;
		case WEAPON_GREATSWORD:
			switch(sShopStock.sWeapon.nWeaponIndex){
				case ITEM_ONE:
					strcpy(strSprite, aGreatSwordOne[nLine]);
					break;
				case ITEM_TWO:
					strcpy(strSprite, aGreatSwordTwo[nLine]);
					break;
				case ITEM_THREE:
					strcpy(strSprite, aGreatSwordThr[nLine]);
					break;
				case ITEM_FOUR:
					strcpy(strSprite, aGreatSwordFou[nLine]);
					break;
			}
			break;
		case WEAPON_STAVE:
			switch(sShopStock.sWeapon.nWeaponIndex){
				case ITEM_ONE:
					strcpy(strSprite, aStaveOne[nLine]);
					break;
				case ITEM_TWO:
					strcpy(strSprite, aStaveTwo[nLine]);
					break;
				case ITEM_THREE:
					strcpy(strSprite, aStaveThr[nLine]);
					break;
				case ITEM_FOUR:
					strcpy(strSprite, aStaveFou[nLine]);
					break;
			}
			break;
		case WEAPON_SEAL:
			switch(sShopStock.sWeapon.nWeaponIndex){
				case ITEM_ONE:
					strcpy(strSprite, aSealOne[nLine]);
					break;
				case ITEM_TWO:
					strcpy(strSprite, aSealTwo[nLine]);
					break;
				case ITEM_THREE:
					strcpy(strSprite, aSealThr[nLine]);
					break;
				case ITEM_FOUR:
					strcpy(strSprite, aSealFou[nLine]);
					break;
			}
			break;
	}

	printf("│");
	printMultiple(" ", ((SHOP_SLOT_WIDTH - WEAPON_WIDTH) / 2)-1);
	printf("%s ", strSprite);
	printMultiple(" ", (SHOP_SLOT_WIDTH - WEAPON_WIDTH) / 2);
	printf("│");
}

/*	displayBuyStocks	Displays the weapons from a specified weapon
						type taken as user input in the previous screen.
	
	@param nPrompt		An integer variable containing the user's input.
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items. 
	@param pStockList	A Stock pointer that points to the list of stocks
						that are under the specified weapon type.

	Pre-condition		nPrompt should be an integer.		   
						pPlayer should be initiated and all members 
						should have a value.	   
						pStockList should point to a valid Stock. 	   */
void displayBuyStocks(int nPrompt, Player* pPlayer, Stock* pStockList) {
	
	system("cls");

	int i, j, k;

	printHeader("BUY A WEAPON", 12);
	
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("YOUR RUNES ► %d\n", pPlayer->nRunes);
	printf("\n");

	for (j = 1; j <= 2; j++) {

		printMultiple(" ", SCREEN_PADDING+1);
		printTopShopBorders(2);

		for (i = 0; i < SHOP_SLOT_HEIGHT; i++) {

			printMultiple(" ", SCREEN_PADDING+1);

			for (k = 0 + ((j-1)*2); k < 2 + ((j-1)*2); k++) {
				printShopContent(pStockList[k], i);
			}
			
			printf("\n");
		}
		
		printMultiple(" ", SCREEN_PADDING+1);
		printBottomShopBorder(2);
	}
	
	printOption(B_BACK, "BACK");
	
	printf("\n\n");
	printSystemMessage("Just tell me the number.");

	switch(nPrompt) {
		case ITEM_ONE:
		case ITEM_TWO:
		case ITEM_THREE:
		case ITEM_FOUR:
			printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
			printf("The elder says ►  You bought %s.\n", 
				pStockList[nPrompt - 1].sWeapon.strWeaponName);
			break;
		case UNSUCCESSFUL:
			printSystemMessage("You don't have enough runes to buy that.");
			break;
		case B_BACK:
			printSystemMessage("Going back to Weapon Types.");
			break;
		default:
			break;
	}
}

/*	displayBuyTypes		Displays the weapon types the player can choose
						from.

	@param nPrompt		An integer variable containing the user's input.
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items. 

	Pre-condition		nPrompt should be an integer.		   
						pPlayer should be initiated and all members 
						should have a value.	   					   */
void displayBuyTypes(int nPrompt, Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("YOUR RUNES ► %d\n", pPlayer->nRunes);
	printMultiple(" ", SCREEN_PADDING * (SCREEN_WIDTH / 10));
	printf("CHOOSE A WEAPON TYPE\n");

	printOption(WEAPON_SWORD, "SWORD");
	printOption(WEAPON_KATANA, "KATANA");
	printOption(WEAPON_WHIP, "WHIP");
	printOption(WEAPON_GREATSWORD, "GREATSWORD");
	printOption(WEAPON_STAVE, "STAVE");
	printOption(WEAPON_SEAL, "SEAL");
	printOption(B_BACK, "BACK");
	printf("\n");

	switch(nPrompt) {
		case WEAPON_SWORD:
			printSystemMessage("Showing you the Swords shop.");
			break;
		case WEAPON_KATANA:
			printSystemMessage("Showing you the Katanas shop.");
			break;
		case WEAPON_WHIP:
			printSystemMessage("Showing you the Whips shop.");
			break;
		case WEAPON_GREATSWORD:
			printSystemMessage("Showing you the Greatswords shop.");
			break;
		case WEAPON_STAVE:
			printSystemMessage("Showing you the Staves shop.");
			break;
		case WEAPON_SEAL:
			printSystemMessage("Showing you the Seals shop.");
			break;
		case B_BACK:
			printSystemMessage("Going back to Roundtable Hold.");
			break;
		default:
			break;
	}
}