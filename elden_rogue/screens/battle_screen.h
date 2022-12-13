#ifndef BATTLE_SCREEN
#define BATTLE_SCREEN

#define MOVE_ATTACK		1
#define MOVE_DODGE		2
#define MOVE_POTION		3
#define MOVE_SKIP		4

#define ATTACK_PHYSICAL 	1
#define ATTACK_SORCERY 		2
#define ATTACK_INCANTATION 	3

#define PLAYER_DODGE		2
#define PLAYER_POTION_FULL	31
#define PLAYER_POTION_EMPTY	32
#define PLAYER_SKIP			4
#define ENEMY_ATTACK		5

#define WIN 	1
#define LOSE 	0

void displayBattleScreen(Player* pPlayer, Enemy sEnemy, int nTurn, int nPrompt, int nArea);
int openBattleScreen(Enemy sEnemy, Player* pPlayer, int nAreaNo);
void printSubAttacks();

int attackPhy(Enemy sEnemy, Player* pPlayer);
int attackSor(Enemy sEnemy, Player* pPlayer);
int attackInc(Enemy sEnemy, Player* pPlayer);
int getDodgeRate(Enemy sEnemy, Player* pPlayer);

#endif 