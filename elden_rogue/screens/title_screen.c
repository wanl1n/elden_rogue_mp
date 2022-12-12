// ────────────────────────── 〔 LIBRARIES 〕 ────────────────────────── //
#include "title_screen.h" //Contains constants needed for Title Screen.
#include "chara_creation_screen.h" //When Player chooses Play.
#include "roundtable_screen.h" // When Player chooses Continue.
#include "../driver.h" //Contains all the structures used in the code.



// ────────────────────── 〔 CENTRAL FUNCTION 〕 ─────────────────────── //
/* 	openTitleScreen		Opens the Title Screen.
	
	@param	pPlayer		The Player Structure containing all of the 
						Player's statistics and items.

	Pre-condition		pPlayer should be initiated and all members 
						should have a value.						   */
void openTitleScreen(Player* pPlayer) {
	displayTitleScreen(3);

	int nInput;

	nInput = scanIntInput(0, 2);

	displayTitleScreen(nInput);

	switch(nInput) {
		case START:
			if (!strcmp(pPlayer->strName, "") || !strcmp(pPlayer->strJobClass, ""))
				openCharacterCreationScreen(pPlayer);
			else
				openRoundTableHoldScreen(pPlayer);
			break;
		case CONTINUE:
			if (!strcmp(pPlayer->strName, "") || !strcmp(pPlayer->strJobClass, "")) {
				printf("You do not have saved data. Redirecting you to character creation.\n");
				openCharacterCreationScreen(pPlayer);
			} else
				openRoundTableHoldScreen(pPlayer);			
			break;
		case EXIT:
			break;
	}
}



// ─────────────────────── 〔 USER INTERFACE 〕 ──────────────────────── //
/* 	displayTitleScreen	Prints the User Interface of the Title Screen.
	
	@param	nPrompt		An integer value containing the prompt integer
						code.										   */
void displayTitleScreen(int nPrompt) {
	
	system("cls");

	printf("\e[1;93m					 █                   █\n");
	printf("					  ███             ███\n");
	printf("					     ██	        ██\n");
	printf("					       █████████\n");
	printf("					           █    \n");
	printf("					           █    \n");
	printf("					        ███████  \n");
	printf("					      ██   █   ██ \n");
	printf("					   ███   █████   ███ \n");
	printf("					  █    ██  █  ██    █\n");
	printf("	 _______  _        ______   _______  _          _______  _______  _______           _______ \n");
	printf("	(  ____ %c( %c      (  __  %c (  ____ %c( (    /|  (  ____ )(  ___  )(  ____ %c|%c     /|(  ____ %c\n", 92, 92, 92, 92, 92, 92, 92);
	printf("	| (    %c/| (      | (  %c  )| (    %c/|  %c  ( |  | (    )|| (   ) || (    %c/| )   ( || (    %c/\n", 92, 92, 92, 92, 92, 92);
	printf("	| (__    | |      | |   ) || (__    |   %c | |  | (____)|| |   | || |      | |   | || (__    \n", 92);
	printf("	|  __)   | |      | |   | ||  __)   | (%c %c) |  |     __)| |   | || | ____ | |   | ||  __)   \n", 92, 92);
	printf("	| (      | |      | |   ) || (      | | %c   |  | (%c (   | |   | || | %c_  )| |   | || (      \n", 92, 92, 92);
	printf("	| (____/%c| (____/%c| (__/  )| (____/%c| )  %c  |  | ) %c %c__| (___) || (___) || (___) || (____/%c\n", 92, 92, 92, 92, 92, 92, 92);
	printf("	(_______/(_______/(______/ (_______/|/    )_)  |/   %c__/(_______)(_______)(_______)(_______%c\e[0m\n", 92, 92);
	printf("                                                                                 \n");
	printf("					      \e[1;94m%c\e[0m\e[1;94m[\e[1;93m1\e[0m\e[1;94m]\e[0m \e[1;93mSTART\e[0m    \e[1;94m%c\e[0m\n",186,186);
	printf("					      \e[1;94m%c\e[0m\e[1;94m[\e[1;93m2\e[0m\e[1;94m]\e[0m \e[1;93mCONTINUE\e[0m  \e[1;94m%c\e[0m\n",186,186);
	printf("					      \e[1;94m%c                  %c\e[0m\n",186,186);
	printf("					      \e[1;94m%c\e[0m\e[1;94m[\e[1;93m0\e[0m\e[1;94m]\e[0m \e[1;93mExit\e[0m          \e[1;94m%c\e[0m\n",186,186);

	//swords:
	//shortsword 10 28
	printf("                ███         \n");
	printf("               █  █         \n");
	printf("           ██ █   █         \n");
	printf("           ███   █          \n");
	printf("             █  █           \n");
	printf("            ███  █          \n");
	printf("          ███  ███          \n");
	printf("          █ █               \n");
	printf("          ███               \n");
	printf("                            \n");
	// 10 13
	printf("         ███ \n");
	printf("        █  █ \n");
	printf("    ██ █   █ \n");
	printf("    ███   █  \n");
	printf("      █  █   \n");
	printf("     ███  █  \n");
	printf("   ███  ███  \n");
	printf("   █ █       \n");
	printf("   ███       \n");
	printf("             \n");
	//rogier's rapier 10
	printf("                  █         \n");
	printf("                 ██         \n");
	printf("                ██          \n");
	printf("               ██           \n");
	printf("            █ ██            \n");
	printf("             ██             \n");
	printf("          ████ █            \n");
	printf("          █ █               \n");
	printf("          ███               \n");
	printf("                            \n");
	//10 13
	printf("           █ \n");
	printf("         ██  \n");
	printf("        ██   \n");
	printf("       ██    \n");
	printf("    █ ██     \n");
	printf("     ██      \n");
	printf("  ████ █     \n");
	printf("  █ █        \n");
	printf("  ███        \n");
	printf("             \n");
	//coded sword 10
	printf("                  ;         \n");
	printf("                 ;:         \n");
	printf("                :;          \n");
	printf("               ;:           \n");
	printf("            ; ;;            \n");
	printf("             ;;             \n");
	printf("          ████ ;            \n");
	printf("          █ █               \n");
	printf("          ███               \n");
	printf("                            \n");
	//10 13
	printf("           ; \n");
	printf("          ;: \n");
	printf("         :;  \n");
	printf("        ;:   \n");
	printf("     ; ;;    \n");
	printf("      ;;     \n");
	printf("   ████ ;    \n");
	printf("   █ █       \n");
	printf("   ███       \n");
	printf("             \n");
	//night and flame 10
	printf("                  █:        \n");
	printf("                 █:█        \n");
	printf("                █:█         \n");
	printf("               █:█          \n");
	printf("              █:█           \n");
	printf("           █ █:█            \n");
	printf("            ███             \n");
	printf("            ██              \n");
	printf("           █  █             \n");
	printf("                            \n");
	//10 13
	printf("          █: \n");
	printf("         █:█ \n");
	printf("        █:█  \n");
	printf("       █:█   \n");
	printf("      █:█    \n");
	printf("   █ █:█     \n");
	printf("    ███      \n");
	printf("    ██       \n");
	printf("   █  █      \n");
	printf("             \n");
	//katana
	//uchiga 10
	printf("               █            \n");
	printf("              █             \n");
	printf("             █              \n");
	printf("            █               \n");
	printf("            █               \n");
	printf("            █               \n");
	printf("             █  █           \n");
	printf("              ██            \n");
	printf("             █ ██           \n");
	printf("                            \n");
	//10 13
	printf("       █     \n");
	printf("      █      \n");
	printf("     █       \n");
	printf("    █        \n");
	printf("    █        \n");
	printf("    █        \n");
	printf("     █  █    \n");
	printf("      ██     \n");
	printf("     █ ██    \n");
	printf("             \n");
	//moon 10
	printf("              ;             \n");
	printf("              █;            \n");
	printf("               █;           \n");
	printf("                █           \n");
	printf("               █;           \n");
	printf("               █            \n");
	printf("             █ ;            \n");
	printf("              █             \n");
	printf("            ██ █            \n");
	printf("                            \n");
	//10 13
	printf("      ;      \n");
	printf("      █;     \n");
	printf("       █;    \n");
	printf("        █    \n");
	printf("       █;    \n");
	printf("       █     \n");
	printf("     █ ;     \n");
	printf("      █      \n");
	printf("    ██ █     \n");
	printf("             \n");
	//rivers of blood
	printf("              █;            \n");
	printf("              ██;           \n");
	printf("               ██;          \n");
	printf("                █;          \n");
	printf("               ██;          \n");
	printf("               █;;          \n");
	printf("             █ █;;          \n");
	printf("              █;;           \n");
	printf("            ██ █            \n");
	printf("                            \n");
	// 10 13
	printf("      █;     \n");
	printf("      ██;    \n");
	printf("       ██;   \n");
	printf("        █;   \n");
	printf("       ██;   \n");
	printf("       █;;   \n");
	printf("     █ █;;   \n");
	printf("      █;;    \n");
	printf("    ██ █     \n");
	printf("             \n");
	//hand of malenia
	printf("             █              \n");
	printf("             ██             \n");
	printf("              ██            \n");
	printf("               █            \n");
	printf("              ██            \n");
	printf("              █             \n");
	printf("              █             \n");
	printf("             ;;             \n");
	printf("            ;;              \n");
	printf("                            \n");
	//10 13
	printf("     █       \n");
	printf("     ██      \n");
	printf("      ██     \n");
	printf("       █     \n");
	printf("      ██     \n");
	printf("      █      \n");
	printf("      █      \n");
	printf("     ;;      \n");
	printf("    ;;       \n");
	printf("             \n");
	//whip
	//whip 10 28
	printf("            █████           \n");
	printf("           ██   ██          \n");
	printf("          ██     ██         \n");
	printf("         █        ██        \n");
	printf("         █         █        \n");
	printf("          ██       █        \n");
	printf("         █ █  █   █         \n");
	printf("          ██  █  ██         \n");
	printf("         ██ █  ███          \n");
	printf("                            \n");
	//10 13
	printf("     █████   \n");
	printf("    ██   ██  \n");
	printf("   ██     ██ \n");
	printf("  █        █ \n");
	printf("  █        █ \n");
	printf("   ██      █ \n");
	printf("  █ █ █   █  \n");
	printf("   ██ █  ██  \n");
	printf(" ██ █ ███    \n");
	printf("             \n");
	//urumi
	printf("            █████  █ █      \n");
	printf("           ███  ██  █       \n");
	printf("          ██      ██ █      \n");
	printf("         ██       ██        \n");
	printf("         ██       ██        \n");
	printf("         ██       ██        \n");
	printf("          ██   █ ██         \n");
	printf("           ██   ██          \n");
	printf("            █████ █         \n");
	printf("                            \n");
	//10 13
	printf("    █████ █ █ \n");
	printf("   ███  ██ █ \n");
	printf("  ██      █ █\n");
	printf(" ██       █  \n");
	printf(" ██       █  \n");
	printf(" ██      ██  \n");
	printf("  ██  █ ██   \n");
	printf("   ██  ██    \n");
	printf("    ████ █   \n");
	printf("             \n");
	//thorned whip 10 28
	printf("           ;█████;  ██      \n");
	printf("          ;█;;;;;█;██       \n");
	printf("         ;█;     ;██;       \n");
	printf("         █;       ;█;       \n");
	printf("         █;       ;█;       \n");
	printf("         █;      ;;█;       \n");
	printf("         ;█;    ;;█;        \n");
	printf("          ;█;;;;;█;         \n");
	printf("           ;█████;          \n");
	printf("                            \n");
	//10 13
	printf("   ;███;  ██ \n");
	printf("  ;█;;;█;██  \n");
	printf(" ;█;   ;██;  \n");
	printf(" █;     ;█;  \n");
	printf(" █;     ;█;  \n");
	printf(" █;    ;;█;  \n");
	printf(" ;█;  ;;█;   \n");
	printf("  ;█;;;█;    \n");
	printf("   ;███;     \n");
	printf("             \n");
	//hoslow petal whip
	printf("                 ██         \n");
	printf("                █ █         \n");
	printf("           ;;;;█; █         \n");
	printf("          ;  ██ ;██         \n");
	printf("         ;;  ██;██          \n");
	printf("         ;;   █ ██          \n");
	printf("          ;   ████          \n");
	printf("          ;; ; ███          \n");
	printf("           ;;;█;█           \n");
	printf("                            \n");
	//10 13
	printf("          ██ \n");
	printf("         █ █ \n");
	printf("    ;;;;█; █ \n");
	printf("   ;  ██ ;██ \n");
	printf("  ;;  ██;██  \n");
	printf("  ;;   █ ██  \n");
	printf("   ;   ████  \n");
	printf("   ;; ; ███  \n");
	printf("    ;;;█;█   \n");
	printf("             \n");
	//greatsword:
	//claymore
	printf("                  █         \n");
	printf("                 ███        \n");
	printf("                ███         \n");
	printf("               █:█          \n");
	printf("           █  █:█           \n");
	printf("            █ █:█           \n");
	printf("             █:█            \n");
	printf("             ██             \n");
	printf("            █  █            \n");
	printf("                            \n");
	//10 13
	printf("         █   \n");
	printf("        ███  \n");
	printf("       ███   \n");
	printf("      █:█    \n");
	printf("  █  █:█     \n");
	printf("   █ █:█     \n");
	printf("    █:█      \n");
	printf("    ██       \n");
	printf("   █  █      \n");
	printf("             \n");
	//starscourge greatsword 10 13
	printf("                    ██      \n");
	printf("               █   ██       \n");
	printf("              ██████        \n");
	printf("            ███████         \n");
	printf("           █████████        \n");
	printf("          ███████           \n");
	printf("         ██████             \n");
	printf("          ███               \n");
	printf("           █                \n");
	printf("                            \n");
	//10 13
	printf("         ██  \n");
	printf("     █   ██  \n");
	printf("    ██████   \n");
	printf("    █████    \n");
	printf("   ███████   \n");
	printf("  █████      \n");
	printf("  █████      \n");
	printf("   ██        \n");
	printf("    █        \n");
	printf("             \n");
	//inseparable sword 10
	printf("                   ██       \n");
	printf("                █ ██        \n");
	printf("                 ██         \n");
	printf("               ███ █        \n");
	printf("              ███           \n");
	printf("             ██:            \n");
	printf("            ██:             \n");
	printf("           ███              \n");
	printf("          ██                \n");
	printf("                            \n");
	//10 13
	printf("          ██ \n");
	printf("       █ ██  \n");
	printf("        ██   \n");
	printf("      ███ █  \n");
	printf("     ██      \n");
	printf("    ██:      \n");
	printf("   ██:       \n");
	printf("  ███        \n");
	printf(" ██          \n");
	printf("             \n");
	//maliketh 10
	printf("                     ██     \n");
	printf("                      ██    \n");
	printf("               ███  ██ █    \n");
	printf("                █████       \n");
	printf("               ███████      \n");
	printf("            ████████ ███    \n");
	printf("           ██████           \n");
	printf("           ████             \n");
	printf("          ██                \n");
	printf("                            \n");
	//10 13
	printf("         ██  \n");
	printf("          ██ \n");
	printf("   ███  ██ █ \n");
	printf("     █████   \n");
	printf("    ████████ \n");
	printf("   ██████  █ \n");
	printf("  █████      \n");
	printf("  ███        \n");
	printf(" ██          \n");
	printf("             \n");
	//stave
	//astrologer staff
	printf("                   ██       \n");
	printf("                 ;█;        \n");
	printf("               ;██;         \n");
	printf("              ;██;          \n");
	printf("             ;█;;█;         \n");
	printf("             █   ;█;        \n");
	printf("            █               \n");
	printf("           █                \n");
	printf("          █                 \n");
	printf("                            \n");	
	//10 13
	printf("          ██ \n");
	printf("        ;█;  \n");
	printf("      ;██;   \n");
	printf("     ;██;    \n");
	printf("    ;█;;█;   \n");
	printf("    █   ;█;  \n");
	printf("   █         \n");
	printf("  █          \n");
	printf(" █           \n");
	printf("             \n");
	//albinauric staff
	printf("                   ██       \n");
	printf("                  █         \n");
	printf("                 █          \n");
	printf("                █  █        \n");
	printf("               █████        \n");
	printf("              █             \n");
	printf("             █              \n");
	printf("            █               \n");
	printf("           █                \n");
	printf("                            \n");
	//10 13
	printf("         ██  \n");
	printf("        █    \n");
	printf("       █     \n");
	printf("      █  █   \n");
	printf("     █████   \n");
	printf("    █        \n");
	printf("   █         \n");
	printf("  █          \n");
	printf(" █           \n");
	printf("             \n");
	//staff of the guilty
	printf("        ;█; █ █:█ ; █ █     \n");
	printf("         ; █ ::█::█; ;      \n");
	printf("          ; █ █:█ ;█        \n");
	printf("           ; █ ; █;         \n");
	printf("            █;█ ;           \n");
	printf("           █                \n");
	printf("          █                 \n");
	printf("         █                  \n");
	printf("        █                   \n");
	printf("                            \n");
	//10 13
	printf(" █ ; █ █: █; \n");
	printf(" ;█ ::█::█;█ \n");
	printf("   █ █:█ ;█  \n");
	printf("  ; █ ; █;   \n");
	printf("    ;█ ;     \n");
	printf("    █        \n");
	printf("   █         \n");
	printf("  █          \n");
	printf(" █           \n");
	printf("             \n");
	//carian regal
	printf("                   █        \n");
	printf("                  ██        \n");
	printf("                 ██         \n");
	printf("                ██          \n");
	printf("               ██           \n");
	printf("              ██            \n");
	printf("           █  █             \n");
	printf("            ██              \n");
	printf("           █  █             \n");
	printf("                            \n");
	//10 13
	printf("           █ \n");
	printf("          ██ \n");
	printf("         ██  \n");
	printf("        ██   \n");
	printf("       ██    \n");
	printf("      ██     \n");
	printf("   █  █      \n");
	printf("    ██       \n");
	printf("   █  █      \n");
	printf("             \n");

	//seal
	//finger seal
	printf("              ██   ██       \n");
	printf("             █:█   █:█      \n");
	printf("            █;;█  █ █       \n");
	printf("            █ █  █;█        \n");
	printf("            █;█ █  █        \n");
	printf("             █ ██;█         \n");
	printf("           ████  █          \n");
	printf("           █ ████           \n");
	printf("           ███              \n");
	printf("                            \n");
	//10 13
	printf("     ██  ██  \n");
	printf("    █:█  █:█ \n");
	printf("   █;;█ █ █  \n");
	printf("   █ █ █;█   \n");
	printf("   █;█ █  █  \n");
	printf("    █ ██;█   \n");
	printf("  ████  █    \n");
	printf("  █ ████     \n");
	printf("  ███        \n");
	printf("             \n");
	//godslayers seal
	printf("               █  ██        \n");
	printf("               ███          \n");
	printf("              █ . ██        \n");
	printf("              █   █         \n");
	printf("              ████          \n");
	printf("             █ █            \n");
	printf("            █ █             \n");
	printf("           █ █              \n");
	printf("            █               \n");
	printf("                            \n");
	//10 13
	printf("      █  ██  \n");
	printf("      ███    \n");
	printf("     █ . ██  \n");
	printf("     █   █   \n");
	printf("     ████    \n");
	printf("    █ █      \n");
	printf("   █ █       \n");
	printf("  █ █        \n");
	printf("   █         \n");
	printf("             \n");
	//golden order
	printf("\e[1;93m            :::::           \n");
	printf("         ███████████        \n");
	printf("      :::█::    :::█:::     \n");
	printf("     :   █: ::::  :█  ::    \n");
	printf("     :    █: ::  :█    :    \n");
	printf("     :     █:::::█     :    \n");
	printf("      :    █  :  █    :     \n");
	printf("       :    █: :█   ::      \n");
	printf("        :::: █ █ :::        \n");
	printf("              █             \e[0m\n");
	//10 13
	printf("\e[1;93m     :::     \n");
	printf("    :   :    \n");
	printf("  █████████  \n");
	printf(" :█: ::: :█: \n");
	printf(" : █ : : █ : \n");
	printf(" :  █ : █  : \n");
	printf(" :   █ █   : \n");
	printf("  ::: █ :::  \n");
	printf("              \n");
	printf("             \e[0m\n");
	//dragon comm
	printf("\e[1;91m          ;  ;███;█;        \n");
	printf("          █; █   █;         \n");
	printf("          ██;█  █;;█        \n");
	printf("          █ ██ █;;█;█       \n");
	printf("          ██ ███;█; ;       \n");
	printf("          ;;██  █;;█        \n");
	printf("          █;;███;;█         \n");
	printf("           █;;;;;█          \n");
	printf("            █████           \n");
	printf("                            \e[0m\n");
	//10 13
	printf("\e[1;91m ;  ;███;█;  \n");
	printf(" █; █   █;   \n");
	printf(" ██;█  █;;█  \n");
	printf(" █ ██ █;;█;█ \n");
	printf(" ██ ███;█; ; \n");
	printf(" ;;██  █;;█  \n");
	printf(" █;;███;;█   \n");
	printf("  █;;;;;█    \n");
	printf("   █████     \n");
	printf("             \e[0m\n");
	//player sprite
	//vagabond
	printf("   █   ██,,,,,██\n");
	printf("  █ █  █ : : : █\n");
	printf("  █ █  █ : : : █\n");
	printf("  █ █   █: : :█\n");
	printf("  █ █   █: : :█\n");
	printf("  █ █    █ : █\n");
	printf("█ █ █ █  █ : █\n");
	printf(" █████    █:█\n");
	printf("  ███     █:█\n");
	printf("   █       █\n");
	//samurai
	printf("  █      █\n");
	printf("  ██     ███  \n");
	printf("  █ █    █:█  \n");
	printf("  █:█    █:█ \n");
	printf("  █:█    █:█ \n");
	printf("  █ █    █:█  \n");
	printf("  █:█    █:█  \n");
	printf(" █████  █████\n");
	printf("         ███\n");
	printf("          █\n");
	//warrior
	printf("    █     █\n");
	printf("   ███     █\n");
	printf("   █:█  █ █:█\n");
	printf("   █:█   █ ::█\n");
	printf("   █:█    █ :█\n");
	printf("   █:█    █ :█\n");
	printf("   █:█     █:█\n");
	printf("  █████   ████\n");
	printf("   ███   ██████\n");
	printf("    █      ██\n");
	//hero
	printf(" █  █  ██      ███\n");
	printf("█:█ █ █ :█    █ : █\n");
	printf("█: ███  ::█  █: : :█\n");
	printf("█:████  ::█ █ : : : █\n");
	printf(" █  █ █ :█  █ : : : █\n");
	printf("    █  ██   █ : : : █\n");
	printf("    █        █: : :█\n");
	printf("    █        █: : :█\n");
	printf("    █         █ : █\n");
	printf("    █          ███\n");
	//prophet
	printf("  █     ████\n");
	printf(" ███   █    █\n");
	printf(" ███   █    █\n");
	printf("  █     █;;█\n");
	printf("  █     █  █\n");
	printf("  █     █  █\n");
	printf("  █     █ ██   ███\n");
	printf("  █    ████ ███   █\n");
	printf("  █    █ █    ;   █\n");
	printf("  █    ███████████ \n");
	//astrologer
	printf("    ██         ███\n");
	printf("    ██        █ : █\n");
	printf("    █████    █: : :█\n");
	printf("    ██      █ : : : █\n");
	printf("    ██      █ : : : █\n");
	printf("    ██      █ : : : █\n");
	printf("    ██       █: : :█\n");
	printf("    ██       █: : :█\n");
	printf("    ██        █ : █\n");
	printf("    ██         ███\n");
	//potion
	printf("     █\n");
	printf("   ██ ██\n");
	printf("    █ █\n");
	printf("  ██   ██ \n");
	printf(" █ ;     █\n");
	printf("█ ;;      █\n");
	printf(" █;;     █\n");
	printf("  █;    █\n");
	printf("   █████\n");
	printf("\n");
	//tsinelas
	printf("    █████\n");
	printf("   █     █\n");
	printf("  █   █   █\n");
	printf("  █  ███  █ \n");
	printf("  █ █  █  █\n");
	printf(" █ █    ██ \n");
	printf(" ██      █\n");
	printf("  █     █\n");
	printf("   █████\n");
	printf("\n");
	//giant belt
	printf("      ████████\n");
	printf("    ██        ██\n");
	printf("   █   ██████   █\n");
	printf("   █  █      █  █\n");
	printf("   █  █      █  █\n");
	printf("  █ ██ █    █ ██ █\n");
	printf("   █  ████████  █ \n");
	printf("    ██ █:,:█  █\n");
	printf("      ████████ \n");
	printf("              \n");
	//STORMVEIL, REDMANE, LEYNDELL
	//warrior
	printf(" ██  ████████\n");
	printf(" █ ██   ::   █ \n");
	printf(" █ █    ::    █\n");
	printf(" █ ██████████████\n");
	printf(" █ █   █   █   █ \n");
	printf(" █ █          █ \n");
	printf("█████    █████\n");
	printf(" █ █ ████  █ █\n");
	printf(" ███       ███\n");
	printf("   █  ███  █  \n");
	printf("   ███   ███ \n");
	printf("\n");
	//archer
	printf("     ████████\n");
	printf("   ██   ::   █ \n");
	printf("   █    ::    █\n");
	printf("   ██████████████\n");
	printf(" ███   █   █;;██  \n");
	printf(" █:█        ;;  ███\n");
	printf(" █:██    ███;;█    █\n");
	printf(" █:█ ████  █;; █   █\n");
	printf(" ███       █;;█    █\n");
	printf("   █  ███  █;;  ███\n");
	printf("   ███   ███;;██\n");
	printf("\n");
	//knight
	printf(" ██  ████████\n");
	printf(" █ ██   ::   █ \n");
	printf(" █ █    ::    █\n");
	printf(" █ ██████████████\n");
	printf(" █ █   █   █   █ \n");
	printf(" █ █          █ \n");
	printf("█████    ███████\n");
	printf(" █ █ ████  █    █\n");
	printf(" ███       █    █\n");
	printf("   █  ███  ██  █\n");
	printf("   ███   ███ ██\n");
	printf("\n");
	//RAYA LUCARIA ACADEMY
	//living jar
	printf("          ████████\n");
	printf("         █ :::::: █ \n");
	printf("     ████ :  ::  : ████\n");
	printf("    █  █:█ :::::: █:█  █\n");
	printf("   █ ██ : ████████ : ██ █\n");
	printf("  █  █;  :  :;: : :  ;█  █\n");
	printf(" █   █ ; : ;: : :;: ; █   █\n");
	printf(" █   █  ;;;;;;;;;;;;  █   █\n");
	printf("  █   █              █   █\n");
	printf("   █ █ █            █ █ █\n");
	printf("    █   █          █   █\n");
	printf("   █ █   ██████████   █ █\n");
	printf("\n");
	//glinstone sorcerer
	printf("    █ █ █ █ █   █\n");
	printf("   █;█;█;█;█;█ █ █\n");
	printf("  ████████████  █ \n");
	printf(" ███████████████ █\n");
	printf("█;;█;  █   █;█ █ █ \n");
	printf("█;;█;;     ;;█ █ █\n");
	printf(" ██;;;;;;;;;;█ █ █\n");
	printf("   █████████████ █\n");
	printf(" ███  ██  ██ █ █ █\n");
	printf("   █  ███ ███ ██ █ \n");
	printf("   ███   ███   ███\n");
	printf("\n");
	//battlemage
	printf("    █████████   █\n");
	printf("   █         █ █ █\n");
	printf("  █  ███████  █ █\n");
	printf(" █  █       █ ██ █\n");
	printf("█  █   █   █ █ █ █ \n");
	printf("█  █   █   █ █ █ █\n");
	printf(" ██          █ █ █\n");
	printf("   █████████████ █\n");
	printf(" ███         █ █ █\n");
	printf("   █  ███   █ ██ █ \n");
	printf("   ███   ███   ███\n");
	printf("\n");
	//volcano manor
	//man serpent
	printf(" ██     ████████\n");
	printf(" █ █  ██   ::   ██\n");
	printf(" █  █ █  █ :: █  █\n");
	printf(" █  █ ███      ███ \n");
	printf(" █ ██  █ ██████ █   \n");
	printf(" █ █ █ █ █,,,,█ ████\n");
	printf("█████ ██ █,,,,██    █\n");
	printf(" █ ██ █  █,,,,█      █\n");
	printf(" ███ ██  █,,,,██    █\n");
	printf("      █   ████  █  █ \n");
	printf("       ███   ███ ██\n");
	printf("\n");
	//mage serpent
	printf("  █     ████████\n");
	printf(" ███  ██   ::   ██  \n");
	printf("  █   █  █ :: █  █ \n");
	printf(" █ █  ███      ███  \n");
	printf(" █ █   █  █████ █  █████\n");
	printf(" █ ██  █ █ ;;  ██ █ ;;; █\n");
	printf(" █ █ ███ █ ;;;  ██ ;;;; █\n");
	printf(" █ ██ █  █ ;;;; ██ ;;;; █\n");
	printf(" █ █ ██  █      ██      █\n");
	printf(" █ █  █    ████████████ █\n");
	printf(" ███   ███   ███   \n");
	printf("\n");
	//abductor virgin
	printf("         ███ \n");
	printf("        █;;;█    \n");
	printf("       ███████    \n");
	printf("      █ █, ,█ █ \n");
	printf("     █  █ , █  █\n");
	printf("██████████ ██████████\n");
	printf(" █  ; ;  ███  ; ;  █ \n");
	printf("  █ ; ; █,,,█ ; ; █\n");
	printf("  ;█████,,,,,█████;\n");
	printf("  ; ; █,,,,,,,█ ; ;\n");
	printf("\n");
	//boss
	//godrick the grafted
	printf("   █    █     \e[1;97m;;;;\e[0m       \e[1;93m█\e[0m █   \n");
	printf("  █ █  █ █   ██████     \e[1;93m███\e[0m █ ██\n");
	printf("     █   █  \e[1;97m;\e[0m█    █\e[1;97m;\e[0m     \e[1;93m█\e[0m   █  █\n");
	printf("   ██ █   █\e[1;97m;;\e[0m█    █\e[1;97m;;\e[0m  ██\e[1;93m;\e[0m█ █   \n");
	printf(" ██  █ █ █ \e[1;97m;;;\e[0m████\e[1;97m;;;\e[0m █ █\e[1;93m;\e[0m██  ██\n");
	printf(" █    █ █ █ ██    ██ █ ██ █  █  █\n");
	printf("   ██  █ ███\e[1;93m;\e[0m     \e[1;93m;\e[0m ███ █ █ █  \n");
	printf("  █  █ ██ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ ██ ███\n");
	printf(" █    █ █ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ █ █   █\n");
	printf("       ██ \e[1;93m;;;\e[0m     \e[1;93m;;;\e[0m  ██ ██    \n");
	printf("\n");
	//rennala
	printf("             \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m██\e[0m    \e[1;93m;\e[0m \e[1;94m███\e[0m\n");
	printf("\e[1;93m   ███\e[0m      \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█   █   █\e[0m \e[1;93m;\e[0m \n");
	printf("\e[1;93m  █   █\e[0m    \e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█\e[0m\e[1;93m;\e[0m\e[1;94m█   █\e[0m\e[1;93m;\e[0m \e[1;94m█   █\e[0m     \n");
	printf("\e[1;93m █ ;   █\e[0m    █   █        ███ ;\n");
	printf("\e[1;93m █ ;   █\e[0m    █   █         █\n");
	printf("\e[1;93m  █   █\e[0m    \e[1;91m█ ███ █\e[0m       ███\n");
	printf("\e[1;93m   ███\e[0m   ██       ██      █\e[1;93m:\e[0m    \n");
	printf("\e[1;94m         █         █\e[0m     \e[1;93m:\e[0m█    \n");
	printf("\e[1;94m         █         █\e[0m      █\e[1;93m:\e[0m   \n");
	printf("\e[1;94m         █         █\e[0m     \e[1;93m:\e[0m█    \n");
	printf("\n");
	//radahn
	printf("     █     \e[1;91m;:;;;:;     █\n");
	printf("   ██     \e[1;91m;:;:::;:;     ██ \n");
	printf("  █\e[1;93m:\e[0m █   \e[1;91m;\e[0m\e[1;93m█\e[0m\e[1;91m;:\e[0m\e[1;93m███\e[0m\e[1;91m:;\e[0m\e[1;93m█\e[0m\e[1;91m;\e[0m   █ \e[1;93m:\e[0m█\n");
	printf(" █\e[1;93m:\e[0m  █   \e[1;91m:;\e[0m\e[1;93m██   ██\e[1;91m;:\e[0m   █  \e[1;93m:\e[0m█ \n");
	printf(" █\e[1;93m:\e[0m  █    \e[1;91m:;\e[0m\e[1;93m█   █\e[1;91m;:\e[0m    █  \e[1;93m:\e[0m█\n");
	printf("  █\e[1;93m:\e[0m █\e[1;93m███\e[0m \e[1;91m██ ███ ██\e[0m \e[1;93m████\e[0m \e[1;93m:\e[0m█\n");
	printf("   █\e[1;93m:\e[0m█   \e[1;93m█         █\e[0m   █\e[1;93m:\e[0m█    \n");
	printf("   ██;\e[1;93m███\e[0m;         ;\e[1;93m███\e[0m;██  \n");
	printf("    ██;;;           ;;; ██   \n");
	printf("     █ \e[1;93m█             \e[1;93m█\e[0m  █     \n");
	printf("\n");
	//rykard
	printf("\e[1;92m        ██████      \e[0m \e[1;91m  ;█; \e[0m\n");
	printf("\e[1;92m       █      █     \e[0m \e[1;91m ;██; \e[0m\n");
	printf("\e[1;92m      █        █    \e[0m \e[1;91m ;██; \e[0m\n");
	printf("\e[1;92m       █      █     \e[0m \e[1;91m ;██; \e[0m\n");
	printf("\e[1;92m        ██████      \e[0m \e[1;91m ;██; \e[0m\n");
	printf("\e[1;92m     ███ █,,,██  █  \e[0m \e[1;91m ;██; \e[0m\n");
	printf("\e[1;92m    █   █,,\e[1;93m█\e[0m\e[1;92m,,█ █ █\e[0m  \e[1;91m ;██; \e[0m\n");
	printf("\e[1;92m   █  █  ,,,,█ ██  █\e[0m \e[1;91m██████\e[0m\n");
	printf("\e[1;92m   █   ██████   █  █\e[0m \e[1;91m  ██  \e[0m\n");
	printf("\e[1;92m    █          █ █ █\e[0m \e[1;91m  ██  \e[0m\n");
	printf("\e[1;92m     ████████████ █ \e[0m \e[1;91m  ██  \e[0m\n");
	printf("\n");
	//morgott
	printf("     █  █ █;;;;;;;█ █   \n");
	printf("    █    █;█;███;█;█    \n");
	printf("   ██    ;█;█   █;█;   \n");
	printf("  ███   █;;██   ██;;█  \n");
	printf("  ██   █ ;;;█   █;;; █  \n");
	printf(" ██   ██ ;██ ███ ██; ██\n");
	printf("  ██ █  ██         ██  █    \n");
	printf(" ██   █   █████████   █\n");
	printf("  ██   █ ;    █    ; █  \n");
	printf("  :█:   █ ; ; █;  ; █        \n");
	printf("\n");
	//radagon
	printf(" \e[1;93m,\e[0m ███ \e[1;93m,\e[0m     \e[1;91m;;;;;\e[0m      \n");
	printf("  █\e[1;93m;;;\e[0m█ \e[1;93m,\e[0m   \e[1;91m;;;;;;;\e[0m       \n");
	printf("\e[1;93m,\e[0m █\e[1;93m;;;\e[0m█\e[1;93m,\e[0m   \e[1;91m;;;;;;;;;\e[0m     \n");
	printf("\e[1;93m,\e[0m  ███  \e[1;93m,\e[0m \e[1;91m;;;\e[0m█ \e[1;91m;;\e[0m█\e[1;91m;;;\e[0m   \n");
	printf("    █     \e[1;91m;;;\e[0m█  \e[1;91m;\e[0m█\e[1;91m;;;\e[0m    \n");
	printf("   ███   \e[1;91m;;;\e[0m█ ███ █\e[1;91m;;\e[0m     \n");
	printf("    █   \e[1;91m;;\e[0m██   \e[1;93m:\e[0m   ██     \n");
	printf("    █   \e[1;91m;;\e[0m█ \e[1;93m, ,:, ,\e[0m █    \n");
	printf("    █   \e[1;91m;;\e[0m█\e[1;93m, ,:::, ,\e[0m█    \n");
	printf("    █   \e[1;91m;;\e[0m█  \e[1;93m,:::,\e[0m  █     \n");
	printf("\n");
	//elden beast
	printf("  ██     ███     ██\n");
	printf(" █; █   █   █   █ ;█\n");
	printf(" █ ; █  █ █ █  █ ; █\n");
	printf("  ██; ███ ; ███ ;██\n");
	printf(" █; █; █  ;  █ ;█ ;█\n");
	printf("█ ; █ █ ; ; ; █ █ ; █\n");
	printf(" █ ; █ ;  ;  ; █ ; █\n");
	printf("  █ █ ; ; ; ; ; █ █\n");
	printf(" █ ██ ; ; ; ; ; ██ █\n");
	printf("█ ; █ ; ; ; ; ; █ ; █\n");

	/*printHeader("ELDEN ROGUE", 11);
	printOption(1, "START");
	printOption(2, "CONTINUE");
	printOption(0, "EXIT");*/
	printf("\n\n");

	switch(nPrompt) {
		case START:
			printSystemMessage("Starting game...");
			break;
		case CONTINUE:
			printSystemMessage("Continuing previously saved progress...");
			break;
		case EXIT:
			printSystemMessage("Exiting game...");
			break;
		default:
			break;
	}

	Sleep(DELAY);
}

