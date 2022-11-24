#ifndef BATTLE_SCREEN
#define BATTLE_SCREEN

#define MOVE_ATTACK		1
#define MOVE_DODGE		2
#define MOVE_POTION		3
#define MOVE_SKIP		4

#define ATTACK_PHYSICAL 	1
#define ATTACK_SORCERY 		2
#define ATTACK_INCANTATION 	3

void openBattleScreen(Enemy sEnemy, Player* pPlayer);

#endif 