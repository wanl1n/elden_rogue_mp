// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "questline_screen.h" // Constants needed for this screen.
#include "../roundtable_screen.h" // When player goes back.

#include "../../utility/inventory_manager.h" // To add the reward to inventory.
#include "../../utility/scanner.h" // To ask for user input.

#include "../../driver.h" //Contains all the structures used in the code.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openQuestScreen 	Opens the quest Screen.
	
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void openQuestScreen(Player* pPlayer) {

	// First, get the details of the Quest.
	if (pPlayer->pQuestLine == NULL) {
		// Player has not yet started a quest.
		pPlayer->pQuestLine = createQuestline(TWINKLE_TOES);

	} 
	else if (pPlayer->nCompletedQuests == 1 && pPlayer->pQuestLine->nQuestNumber != 2) {
		// Player is done with 1st quest.
		pPlayer->pQuestLine = createQuestline(SWIFT_BROIL);
			
	} else if (pPlayer->nCompletedQuests == 2) {
		
		// Pet Khloe.			
	} 

	// If there's no active quest, ask player if they want to take a quest.
	if (pPlayer->pQuestLine->nQuestStatus != QUEST_IN_PROG) {
	
		talkingStage(pPlayer);

	} 
	// If there's an active quest, check quest progress
	else if (pPlayer->pQuestLine->nQuestStatus == QUEST_IN_PROG) {

		pPlayer->pQuestLine->nQuestStatus = checkQuestProgress(pPlayer);

		// If player isn't done yet.
		if (pPlayer->pQuestLine->nQuestStatus == QUEST_IN_PROG) {
			talkingInProgress(pPlayer);
		} 
		// If player is done.
		else if (pPlayer->pQuestLine->nQuestStatus == QUEST_COMPLETE){
			
			giveQuestRewards(pPlayer);

			// Set to next stage
			pPlayer->pQuestLine->nStage++;
			pPlayer->pQuestLine->nQuestStatus = QUEST_INACTIVE;
			pPlayer->nQuestProgress = 0;

			if (pPlayer->pQuestLine->nStage < 4) {
				openQuestScreen(pPlayer);
			} else {
				pPlayer->nCompletedQuests += 1;
				talkingComplete(pPlayer);
			}
			
		}	
	}
}



// ────────────────────── 〔 UTILITY FUNCTIONS 〕 ────────────────────── //
/* 	createQuestLine 	Creates the questline and the NPC.
	
	@param nQuestline 	An integer variable containing the number of
						the quest to be created.

	@return 			A Quest pointer variable containing the details
						of the questline.

	Pre-condition 		nQuestline should only be 1 or 2. 			   */
Quest* createQuestline(int nQuestline) {

	Quest* pQuest = malloc(sizeof(Quest));
	
	char aFleta[19][DIALOGUE_LENGTH] = {// Intro (1)
										"Hi, traveller! I'm Fleta Harrisone. I heard you were going on an adventure. Would you mind doing something for me while you're out there? I'll give you 100 runes for it.", 
										// [1] Sure, what is it? (2)
									    "Great! Here's the deal. Recently, the creatures in the Stormveil Castle have been loud and I can't sleep at all! I would really appreciate if you can get rid of at least 5 of them, but if you wanna kill more of them that would be great too.",
									    // [0] Not up for it, sorry. (3)
									    "Aw that sucks. Well, it's fine. I wish you safe travels and if you ever feel like you might be up for it, I'll be here!",
										// [1] Alright, I'll take you up on that. (4)
									    "Thanks for accepting my request! I wish you safe travels and success in your journey ahead.", 
										// [0] Eh... that's too much for me. (5)
									    "Oh, that's okay. I understand. Best of luck in your travels!",
									    // In Progress TWINKLE TOES I (6)
									    "Still waiting for you to kill 5 creatures from Stormveil Castle. Really looking forward to a good sleep soon.",
									    // Completed TWINKLE TOES I (7)
									    "Thank you so much! I've been sleeping wayyy better now thanks to you. Here's 100 runes as promised! If you're up for it, I actually have another request. I'll give you 200 runes this time.",
										// [1] Sure, I gotchu. (8)
									    "Okay so I've been walking past the Raya Lucaria Academy and I've noticed how messy that place is. Can you possibly clear up some space there? Around 7 tiles should be good. I'm too scared to go in but perhaps it'd make the place look cleaner.",
										// [0] Nah, one's enough. (9)
									    "Can't be helped. Someone like you must be busy with other things. That's perfectly okay. See you around and I hope you come back safe! If you ever change your mind, I'm right here.",
									    // [1] I'll help. (10)
									    "You're such a dear for that! This whole place honestly needs a little revamp and you are making it much easier for us. Thank you!",
									    // [0] You don't need me for that. (11)
									    "Oh, well an extra hand never hurt anyone. But if you're too busy, that's fine. Best of luck in your travels!",
									    // In Progress (12)
									 	"You getting around to clearing out 7 tiles in the Raya Lucaria Academy? No rush.",
									    // Completed TWINKLE TOES II (13)
									    "You're so sweet. Thanks for going out of your way to do this. I already feel the change in atmosphere. Here's your 200 runes! By the way, if you're up for it, there's just one more thing I need. I'll give you something special.",
									    // [1] What is it? (14)
									    "Yay! So, the big guy at Redmane Castle, Starscourge Radahn? Yeah, he's been pestering me lately. Not sure why. If you can put him in his place, I'd appreciate it so much!",
									    // [0] Sorry, I can't right now. (15)
									    "Oh, okay. But if you ever feel like hearing me out, do come by again!",
									    // [1] Oh, him? Sure, that's too easy. (16)
									    "You are a godsend. I hope you shut that dude up once and for all. Thanks!",
									    // [0] Ah... I don't think I can. (17)
									    "Oh, I understand. Facing him might be quite intimidating. That's alright! Safe travels to you, traveller!",
									    // In progress (18)
									    "I know you have a lot on your plate, and I appreciate you agreeing to defeat the Starscourge Radahn in the Redmane Castle.",
									    // Completed TWINKLE TOES III (19)
									    "You are amazing! Thanks for defeating that weird guy. Honestly, the world is so much better without him. Anyway, as promised, you can take this. I was once an adventurer like you, until I took an arrow to the knee. But this really helped me in my travels and I hope it does the same for you!"};
	char aHilda[19][DIALOGUE_LENGTH] = {"Greetings, weary traveler. I know you but you don't know me, I'm Hilda Aytone. A little birdie told me you were leaving soon for an adventure. Do you mind if I make a request? I'll give you 200 runes for it!",
										"Fleta and I have been arguing a lot about how strong the creatures are. I've been saying they're easy peasy lemon squeezy but she's utterly scared of them. Can you defeat one of them without using potions?",
										"Oh, that's fine. If you ever have some time, do come by!",
										"Sounds great! I'll be awaiting your good news.",
										"I guess it just isn't my day today.",
										"Hey, you get around to killing a creature without using potions yet? Fleta's just not budging.",
										"Ha! I knew they were small fries. *BARK* Thanks for accepting my request! *BARK* Actually, I've got another if *BARK* you're interested. This time it's a serious *BARK* request. I'll give you 500 runes for it *BARK*.",
										"Great! *BARK* Well, I have a dog, *BARK* I'm sure you heard him, his name is Khloe, *BARK* and he's been barking a *BARK* lot lately because the creatures have been *BARK* multipying a LOT *BARK* recently. I would be so grateful *BARK* if you could defeat at least 10 of them. I just want a *BARK* peaceful day without constant barking.",
										"Oh, well *BARK* if you're ever *BARK* up for it, I'm always here. *BARK*",
										"Khloe and I *BARK* are awaiting your great news. Really *BARK* looking forward to that.",
										"Oh *BARK* okay. Better luck next time I guess. *BARK*",
										"Anytime now *BARK* would be great *BARK*. Just defeat 10 *BARK* creatures. That's all.",
										"Ahh... Finally, some peace of mind. Thank you so much! Here's your 500 runes! If you want you can pet Khloe! :)",
										"*HAPPY BARK* He says thank you! By the way, one more thing. I'll give you a special weapon I've got if you help me defeat Morgott the Omen King. His aura's been seeping out lately and it's bothering all of us here. Can you do it?",
										"Oh, that's fine. Not all people like dogs but nevertheless we're grateful.",
										"I have full confidence in you! Khloe and I will be waiting for your good news right here!",
										"Ah, that's alright. If you think you can do it, do drop by again.",
										"Morgott's aura is still lingering. I hope you defeat him soon. It's time for a little cleansing in the Leyndell Capital.",
										"WOW! You're awesome! *BARK BARK* Khloe says you're the best! Thanks as always. Here, this weapon has helped me punish some... bad boys and girls. Take it and whip some discipline into those creatures!"};

	int i;
	
	// Initializing a Quest Line.
	pQuest->nQuestNumber = nQuestline;
	pQuest->nStage = 1;
	pQuest->nQuestStatus = QUEST_INACTIVE;
	
	switch(nQuestline) {

		case TWINKLE_TOES:

			strcpy(pQuest->strNPCName, "FLETA HARRISONE");
			strcpy(pQuest->strQuestName, "TWINKLE TOES");

			for(i = 0; i < 19; i++) {
				strcpy(pQuest->aDialogue[i], aFleta[i]);
			}

			break;

		case SWIFT_BROIL:

			strcpy(pQuest->strNPCName, "HILDA AYTONE");
			strcpy(pQuest->strQuestName, "SWIFT BROIL");

			for(i = 0; i < 19; i++) {
				strcpy(pQuest->aDialogue[i], aHilda[i]);
			}

			break;
	}

	return pQuest;
}

/* 	checkQuestProgress 	Checks the player's progress in the current 
						active quest.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
int checkQuestProgress(Player* pPlayer) {
	
	int nStage = pPlayer->pQuestLine->nStage;

	switch(pPlayer->pQuestLine->nQuestNumber) {
		
		// For Twinkle Toes Quest,
		case TWINKLE_TOES:

			// Depending on the stage, check progress
			switch (nStage) {
				case 1:
					if (pPlayer->nQuestProgress >= 5) // Killed 5 or more creatures from Stormveil.
						return QUEST_COMPLETE;
					else
						return QUEST_IN_PROG;
					break;
				case 2:
					if (pPlayer->nQuestProgress >= 7) // Collected 7 or more rune tiles from Redmane Castle.
						return QUEST_COMPLETE;
					else
						return QUEST_IN_PROG;
					break;
				case 3:
					if (pPlayer->nQuestProgress >= 1) // Killed Starscourge Radahn.
						return QUEST_COMPLETE;
					else
						return QUEST_IN_PROG;
					break;
			}

			break;

		// For Swift Broil Quest,
		case SWIFT_BROIL:

			// Depending on the stage, check progress
			switch (nStage) {
				case 1:
					if (pPlayer->nQuestProgress >= 1) // Won a battle without using potions.
						return QUEST_COMPLETE;
					else
						return QUEST_IN_PROG;
					break;
				case 2:
					if (pPlayer->nQuestProgress >= 10) // Kill 10 enemies.
						return QUEST_COMPLETE;
					else
						return QUEST_IN_PROG;
					break;
				case 3:
					if (pPlayer->nQuestProgress >= 1) // Kill Leyndell Capital boss.
						return QUEST_COMPLETE;
					else
						return QUEST_IN_PROG;
					break;
			}

			break;

	}
	
	return 0;
}

/* 	talkingStage 		Starts the dialogue to introduce the quest to the
						Player.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void talkingStage(Player* pPlayer) {
	
	int nInput, i;
	int nStage = pPlayer->pQuestLine->nStage;

	int nLine = 1 + (6 * (nStage - 1)); //line 7
	
	displayQuestScreen(pPlayer, nLine);

	for(i = 0; i < 2; i++) {
		
		nInput = scanIntInput(0, 1);

		if (nInput == 1) {

			nLine = (2 + (6 * (nStage - 1))) + (2*i); // 8 and 10
			displayQuestScreen(pPlayer, nLine);

			pPlayer->pQuestLine->nQuestStatus = QUEST_IN_PROG;
			pPlayer->nQuestProgress = 0; 
			// Quest is now active

		} else {

			nLine = (3 + (6 * (nStage - 1))) + (2*i); // 9 and 11
			displayQuestScreen(pPlayer, nLine);
			pPlayer->pQuestLine->nQuestStatus = QUEST_INACTIVE; 
			openRoundTableHoldScreen(pPlayer);
		}
	}

	// After accepting the quest, go back to roundtable hold.
	scanIntInput(0, 0);
	openRoundTableHoldScreen(pPlayer);
}

/* 	talkingInProgress 	Prints the dialogue when player is currently 
						not done with a quest.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void talkingInProgress(Player* pPlayer) {

	int nStage = pPlayer->pQuestLine->nStage;

	int nLine = 6 * nStage;
	displayQuestScreen(pPlayer, nLine);

	scanIntInput(0, 0);
	openRoundTableHoldScreen(pPlayer);
}

/*  talkingComplete 	Prints the dialogue when the player finishes
						a whole questline.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void talkingComplete(Player* pPlayer) {

	int nLine = 19;
	displayQuestScreen(pPlayer, nLine);

	scanIntInput(0, 0);
	openRoundTableHoldScreen(pPlayer);
}

/* 	giveQuestRewards 	Gives the player's rewards from the quest.
	
	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void giveQuestRewards(Player* pPlayer) {

	int nStage = pPlayer->pQuestLine->nStage;

	switch(pPlayer->pQuestLine->nQuestNumber) {
		
		// For Twinkle Toes Quest,
		case TWINKLE_TOES:

			// Depending on the stage, give rewards
			switch (nStage) {
				case 1:
					pPlayer->nRunes += 100;
					break;
				case 2:
					pPlayer->nRunes += 200;
					break;
				case 3:
					addWeapon(createUniqueWeapon(pPlayer), &(pPlayer->pInventory));
					break;
			}

			break;

		// For Swift Broil Quest,
		case SWIFT_BROIL:

			// Depending on the stage, give rewards
			switch (nStage) {
				case 1:
					pPlayer->nRunes += 200;
					break;
				case 2:
					pPlayer->nRunes += 500;
					break;
				case 3:
					addWeapon(createUniqueWeapon(pPlayer), &(pPlayer->pInventory));
					break;
			}

			break;

	}
}

/* 	createUniqueWeapon 	Creates the unique weapon that's given as a reward
						at the final stage completion.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	
	@return 			Returns a weapon slot variable containing the 
						weapon details of the reward weapon.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
Slot* createUniqueWeapon(Player* pPlayer) {

	Weapon sWeapon;
	Slot* pSlot = malloc(sizeof(Slot));

	sWeapon.nWeaponIndex = 0;
	sWeapon.nWeaponType = 7; //WEAPON_SPECIAL

	if (pPlayer->pQuestLine->nQuestNumber == 1) {

		strcpy(sWeapon.strWeaponName, "SWIFT SLIPPER");

		sWeapon.nDexReq = 32;
		sWeapon.nHP = 10;
		sWeapon.nInt = 10;
		sWeapon.nEnd = 10;
		sWeapon.nStr = 70;
		sWeapon.nFth = 30;

	} else if (pPlayer->pQuestLine->nQuestNumber == 2) {

		strcpy(sWeapon.strWeaponName, "GIANT'S BELT");

		sWeapon.nDexReq = 40;
		sWeapon.nHP = 30;
		sWeapon.nInt = 20;
		sWeapon.nEnd = 15;
		sWeapon.nStr = 65;
		sWeapon.nFth = 15;
	}

	pSlot->sWeapon = sWeapon;
	pSlot->pNext = NULL;

	return pSlot;
}

void petKhloe() {

	displayQuestScreen()
}

// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayQuestScreen	Displays the Quest Screen.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.
	@param nLine 		An integer variable containing the line number
						to be printed.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void displayQuestScreen(Player* pPlayer, int nLine) {

	system("cls");

	if (pPlayer->pQuestLine->nQuestNumber == 1) {
		if (pPlayer->pQuestLine->nQuestStatus == 1){
			printHeader("FLETA HARRISONE", 15);
		} else {
			printHeader("???", 3);
		}
	} else if (pPlayer->pQuestLine->nQuestNumber == 2) {
		if (pPlayer->pQuestLine->nQuestStatus == 1){
			printHeader("HILDA AYTONE", 12);
		} else {
			printHeader("???", 3);
		}
	}

	printTopBorder();
	printNPC(pPlayer);
	printDiaTopBorder();

	printDialogueText(pPlayer->pQuestLine->aDialogue[nLine-1]);

	printDiaBottBorder();
	printBottomBorder();

	if (nLine != 4 && nLine != 5 && nLine != 4+6 && nLine != 5+6 && nLine != 4+12 && nLine != 5+12 && nLine % 6 != 0 && nLine != 19) {
		
		printOption(1, "OKAY.");
		printOption(0, "NAH.");
	} else {
		printOption(0, "BACK.");
	}
	
}

void displayPetScreen(Player* pPlayer, int nLine) {

	system("cls");

	printHeader("KHLOE", 5);

	printTopBorder();
	printDog();
	printDiaTopBorder();

	printMultiple(" ", SCREEN_PADDING);
	printf("║");
	printMultiple(" ", SCREEN_PADDING);
	printf("║");
	printMultiple(" ", SCREEN_PADDING);

	printf("[Tail Wagging] *BARK BARK*!");

	printMultiple(" ", SCREEN_PADDING);
	printf("║");
	printMultiple(" ", SCREEN_PADDING);
	printf("║");
	printf("\n");

	printDiaBottBorder();
	printBottomBorder();

	if (nLine != 4 && nLine != 5 && nLine != 4+6 && nLine != 5+6 && nLine != 4+12 && nLine != 5+12 && nLine % 6 != 0 && nLine != 19) {
		
		printOption(1, "OKAY.");
		printOption(0, "NAH.");
	} else {
		printOption(0, "BACK.");
	}
	
}

/* 	printTopBorder 		Prints the Top border of the Quest Screen. 	   */
void printTopBorder() {
	
	printMultiple(" ", SCREEN_PADDING);

	printf("╔");
	printMultiple("═", SCREEN_WIDTH);
	printf("╗");

	printf("\n");
}

/* 	printNPC 			Prints the NPC Sprite.

	@param pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.	  					   */
void printNPC(Player* pPlayer) {

	int i;

	char aFletaSprite[12][SCREEN_WIDTH - 3] = {"                                                                  ",
											   "                             FLETA                                ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  "};
	char aHildaSprite[12][SCREEN_WIDTH - 3] = {"                                                                  ",
											   "                              HILDA                               ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  ",
											   "                                                                  "};

	for (i = 0; i < 12; i++) {
		
		printMultiple(" ", SCREEN_PADDING);
		printf("║");
		printMultiple(" ", 2);

		if (pPlayer->pQuestLine->nQuestNumber == 1) 
			printf("%s", aFletaSprite[i]);
		else 
			printf("%s", aHildaSprite[i]);

		printMultiple(" ", 2);
		printf("║");

		printf("\n");
	}
}

/* 	printTopBorder 		Prints the dog sprite.					 	   */
void printDog() {
	char aDogSprite[12][SCREEN_WIDTH - 3] = {"                                                                  ",
										     "                             KHLOE                                ",
											 "                                                                  ",
											 "                                                                  ",
											 "                                                                  ",
											 "                                                                  ",
											 "                                                                  ",
											 "                                                                  ",
											 "                                                                  ",
											 "                                                                  ",
											 "                                                                  ",
											 "                                                                  "};
	
}

/* 	printDiaTopBorder 	Prints the Top border of the dialogue box.	   */
void printDiaTopBorder() {
	
	int nDialogueWidth = SCREEN_WIDTH - ((SCREEN_PADDING * 2) + 2);

	printMultiple(" ", SCREEN_PADDING);

	printf("║");
	printMultiple(" ", SCREEN_PADDING);

	printf("╓");
	printMultiple("—", nDialogueWidth);
	printf("╖");

	printMultiple(" ", SCREEN_PADDING);
	printf("║");

	printf("\n");
}

/* 	printDialogueText 		Prints the dialogue of the NPC.
	
	@param pDialogueLine 	A character pointer pointing to a string 
							containing the dialogue line.

	Pre-condition 			pDialogueLine must be initialized.		   */
void printDialogueText(char* pDialogueLine) {

	int i;

	int nDialogueWidth = SCREEN_WIDTH - ((SCREEN_PADDING * 4) + 2) -1 ;
	int nDiagLines = ceil(350.0 / nDialogueWidth);

	for (i = 0; i < nDiagLines; i++) {
		printMultiple(" ", SCREEN_PADDING);

		printf("║");
		printMultiple(" ", SCREEN_PADDING);

		printf("║");
		printMultiple(" ", SCREEN_PADDING);

		printf("%-*.*s ", nDialogueWidth, nDialogueWidth, pDialogueLine + (i * nDialogueWidth));

		printMultiple(" ", SCREEN_PADDING);
		printf("║");

		printMultiple(" ", SCREEN_PADDING);
		printf("║");

		printf("\n");
	}
}

/* 	printDiaBottBorder 	Prints the Bottom border of the dialogue box.  */
void printDiaBottBorder() {

	int nDialogueWidth = SCREEN_WIDTH - ((SCREEN_PADDING * 2) + 2);

	printMultiple(" ", SCREEN_PADDING);

	printf("║");
	printMultiple(" ", SCREEN_PADDING);

	printf("╙");
	printMultiple("—", nDialogueWidth);
	printf("╜");

	printMultiple(" ", SCREEN_PADDING);
	printf("║");

	printf("\n");
}

/* 	printBottomBorder 	Prints the bottom border of the Quest Screen.  */
void printBottomBorder() {
	
	printMultiple(" ", SCREEN_PADDING);

	printf("╚");
	printMultiple("═", SCREEN_WIDTH);
	printf("╝");

	printf("\n");
}