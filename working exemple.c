#include "menu.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	MENU menuMulti = initMenu(1);
	setTitre(&menuMulti, "type de filles que vous aimer");
	addchoix(&menuMulti, "blonde");
	addchoix(&menuMulti, "rouse");
	addchoix(&menuMulti, "brune");
	addchoix(&menuMulti, "moche");

	int *resultat  = useMenu(&menuMulti);


	MENU menuOneChoix = initMenu(0);
	setTitre(&menuOneChoix, "a partir de quelle taille");
	addchoix(&menuOneChoix, "1m50");
	addchoix(&menuOneChoix, "1m60");
	addchoix(&menuOneChoix, "1m70");
	addchoix(&menuOneChoix, "1m80");
	addchoix(&menuOneChoix, "1m90");

	int LaPositionDeLaReponse = useMenu(&menuOneChoix);


	system("cls & pause>NUL");
	return 0;
}










