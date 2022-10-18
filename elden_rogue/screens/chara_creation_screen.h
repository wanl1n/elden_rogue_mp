#ifndef CHARACTER_CREATION_SCREEN
#define CHARACTER_CREATION_SCREEN

//CHARACTER SCREEN PROMPTS
#define PROMPT_NAME			1
#define PROMPT_JOB 			2
#define PROMPT_CC_CONFIRM	3
#define PROMPT_CC_BACK		0

//JOB SCREEN PROMPTS
#define PROMPT_VAGABOND 	1
#define PROMPT_SAMURAI 		2
#define PROMPT_WARRIOR 		3
#define PROMPT_HERO 		4
#define PROMPT_PROPHET 		5
#define PROMPT_ASTROLOGER	6

//CHARACTER SCREEN CHOICES
#define NAME				1
#define JOB 				2
#define CC_CONFIRM			3
#define CC_BACK				0

//JOB CLASSES
#define VAGABOND 			1
#define SAMURAI 			2
#define WARRIOR 			3
#define HERO 				4
#define PROPHET 			5
#define ASTROLOGER 			6

void displayCharacterCreationScreen(int pPrompt, struct sPlayer sPlayer);
void displayJobScreen(int pPrompt, struct sPlayer sPlayer);
void displayJobClassScreen(int nJobClass);
void openCharacterCreationScreen(struct sPlayer sPlayer);
void openJobScreen(struct sPlayer sPlayer);

#endif 