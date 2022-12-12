#ifndef QUESTLINE
#define QUESTLINE

#define TWINKLE_TOES		1
#define	SWIFT_BROIL			2

#define QUEST_INACTIVE		0
#define QUEST_IN_PROG		1
#define QUEST_COMPLETE 		2


void openQuestScreen(Player* pPlayer);

Quest* createQuestline(int nQuestline);
int checkQuestProgress();

void talkingStage(Player* pPlayer);
void talkingInProgress(Player* pPlayer);

void displayQuestScreen(Player* pPlayer, int nLine);


#endif 
