#pragma once


typedef struct menu {
	char* titre;
	char **choix;
	int Reponse,
		isMulti,
		*multireponse,
		nbReponse;	
}MENU;

#define ENTER 13
#define KEY_UP 72
#define	KEY_DOWN 80

MENU initMenu(int multichoix);

int setTitre(MENU*, const char*);


int addchoix(MENU* monMenu, char* choix);

int useMenu(MENU* monMenu);
