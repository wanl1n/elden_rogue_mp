#ifndef CHARACTER_CREATION_SCREEN
#define CHARACTER_CREATION_SCREEN

//CHARACTER SCREEN CHOICES
#define NAME				1
#define JOB 				2
#define CC_CONFIRM			3
#define CC_BACK				0

//CHARACTER SCREEN CHOICES
#define SET_NAME			4
#define SET_JOB 			5

//JOB CLASSES
#define VAGABOND 			1
#define SAMURAI 			2
#define WARRIOR 			3
#define HERO 				4
#define PROPHET 			5
#define ASTROLOGER 			6

void displayCharacterCreationScreen(int nPrompt, Player* pPlayer);
void displayJobScreen(int nPrompt, Player* pPlayer);
void displayJobClassScreen(int nJobClass);

void setJobClass(int nInput, Player* pPlayer);
void openCharacterCreationScreen(Player* pPlayer);
void openJobScreen(Player* pPlayer);

#endif 