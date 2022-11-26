#include "../chara_creation_screen.h"
#include "../title_screen.h"
#include "../roundtable_screen.h"
#include "../areas_screen.h"
#include "inventory_screen.h"

#include "../../driver.h"

#include "../../config/settings.h"

void printShopSlot(Stock sShopStock) {
	
	Weapon sWeapon = sShopStock.sWeapon;
	int nSpaces = 2;

	int nLength = strlen(sWeapon.strWeaponName);

	printf("\n");

	// Print top border.
	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("╔");
	printMultiple("═", SHOP_SLOT_WIDTH);
	printf("╗\n");

	// Print Weapon Name.
	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%-*.*s", SHOP_SLOT_WIDTH-4, nLength/2, sWeapon.strWeaponName);
	printMultiple(" ", nSpaces);
	printf("│\n");

	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%-*.*s", SHOP_SLOT_WIDTH-4, SHOP_SLOT_WIDTH-4, sWeapon.strWeaponName + nLength/2);
	printMultiple(" ", nSpaces);
	printf("│\n");

	//Print Weapon Image.
	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	//add weapon image
	printf("  <weapon>  ");
	printMultiple(" ", nSpaces);
	printf("│\n");

	//Print Weapon Cost.
	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", SHOP_SLOT_WIDTH-4, sShopStock.nCost);
	printMultiple(" ", nSpaces);
	printf("│\n");
	
	//Print Weapon Stats.
	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("DEXTERITY  |  %*d", SHOP_SLOT_WIDTH-18, sShopStock.nCost);
	printMultiple(" ", nSpaces);
	printf("│\n");

	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("HP ");
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", 2, sWeapon.nHP);
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("END");
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", 2, sWeapon.nEnd);
	printMultiple(" ", nSpaces);
	printf("│\n");

	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("DEX");
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", 2, 0);
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("STR");
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", 2, sWeapon.nStr);
	printMultiple(" ", nSpaces);
	printf("│\n");

	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("INT");
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", 2, sWeapon.nInt);
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("FTH");
	printMultiple(" ", nSpaces);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", 2, sWeapon.nFth);
	printMultiple(" ", nSpaces);
	printf("│\n");
	
	//Print Weapon Index.
	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("│");
	printMultiple(" ", nSpaces);
	printf("%*d", SHOP_SLOT_WIDTH-4, sWeapon.nWeaponIndex);
	printMultiple(" ", nSpaces);
	printf("│\n");

	// Print bottom border.
	printMultiple(" ", SHOP_SCREEN_PADDING);
	printf("╚");
	printMultiple("═", SHOP_SLOT_WIDTH);
	printf("╝\n");

	printf("\n");
}

void displayBuyStocks(int nPrompt, Player* pPlayer, Stock* sStockList) {
	
	system("cls");

	int i;

	printHeader("BUY A WEAPON", 12);
	
	printf("\n[RUNES]: %d\n", pPlayer->nRunes);
	printf("\n\t\tCHOOSE A WEAPON\n");

	for (i = 0; i < 4; i++) {
		printShopSlot(*(sStockList + i));
	}

	printf("\n\t\tINPUT THE WEAPON NUMBER (middle right).\n");

	printOption(B_BACK, "BACK");

	switch(nPrompt) {
		case ITEM_ONE:
			printf("[SYSTEM MESSAGE]: You bought %s.\n", 
				*(sStockList + ITEM_ONE - 1)->sWeapon.strWeaponName);
			break;
		case ITEM_TWO:
			printf("[SYSTEM MESSAGE]: You bought %s.\n", 
				*(sStockList + ITEM_TWO - 1)->sWeapon.strWeaponName);
			break;
		case ITEM_THREE:
			printf("[SYSTEM MESSAGE]: You bought %s.\n", 
				*(sStockList + ITEM_THREE - 1)->sWeapon.strWeaponName);
			break;
		case ITEM_FOUR:
			printf("[SYSTEM MESSAGE]: You bought %s.\n", 
				*(sStockList + ITEM_FOUR - 1)->sWeapon.strWeaponName);
			break;
		case UNSUCCESSFUL:
			printf("[SYSTEM MESSAGE]: You don't have enough runes to buy that.\n"); 
			break;
		case B_BACK:
			printSystemMessage("Going back to Weapon Types.");
			break;
		default:
			break;
	}
}

void displayBuyTypes(int nPrompt, Player* pPlayer) {
	
	system("cls");

	printHeader("ROUNDTABLE HOLD", 15);
	
	printf("\n[RUNES]: %d\n", pPlayer->nRunes);
	printf("\n\t\tCHOOSE A WEAPON TYPE\n");

	printOption(WEAPON_SWORD, "SWORD");
	printOption(WEAPON_KATANA, "KATANA");
	printOption(WEAPON_WHIP, "WHIP");
	printOption(WEAPON_GREATSWORD, "GREATSWORD");
	printOption(WEAPON_STAVE, "STAVE");
	printOption(WEAPON_SEAL, "SEAL");
	printOption(B_BACK, "BACK");

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

Stock getStockFromShop(Stock* sChosenType, int nIndex) {

	int i;

	for(i = 1; i <= 4; i++) {
		if (sChosenType->sWeapon.nWeaponIndex == nIndex)
			return *(sChosenType + (nIndex-1));
	}
}

void openBuyScreen(Player* pPlayer) {

	int nInputBuy = 100;
	int nInputWeaponType = 100;
	Stock* pStockOfType;
	Stock sStockToBeBought;
	Weapon* pWeaponChosen;

	displayBuyTypes(-1, pPlayer);

	while (nInputWeaponType != 0) {

		nInputWeaponType = scanIntInput(0, 6); //Input what type of weapon.

		pStockOfType = getStocksFromType(nInputWeaponType);

		displayBuyStocks(-1, pPlayer, pStockOfType);

		while (nInputBuy != 0) {

			nInputBuy = scanIntInput(0, 4); //Input which weapon.

			sStockToBeBought = getStockFromShop(pStockOfType, nInputWeaponType);

			if (sStockToBeBought.nCost <= pPlayer->nRunes) {

				addWeaponToInventory(&sStockToBeBought.sWeapon, pPlayer);
				pPlayer->nRunes -= sStockToBeBought.nCost;
				displayBuyStocks(nInputBuy, pPlayer, pStockOfType);

			} else {

				displayBuyStocks(UNSUCCESSFUL, pPlayer, pStockOfType);

			}
		}
	}
}