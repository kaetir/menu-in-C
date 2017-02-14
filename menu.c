#include "menu.h"
#include <string.h>
#include <stdio.h>
#include "ConsoleTools.h"



MENU initMenu(int estMultichoix)
{
	//le titre ne doit pas depasser les 100 caractères et les choix un total de 1000 caractère 
	MENU monMenu;
	monMenu.titre = malloc(100);
	monMenu.Reponse = -1;
	monMenu.nbReponse = 0;
	monMenu.isMulti = estMultichoix;
	monMenu.multireponse = malloc(1 * sizeof(int));
	monMenu.choix = malloc(10 * 100 * sizeof(char));
	return monMenu;
}

//renvoie 0 si np et -1 si erreur
int setTitre(MENU* monMenu, char* titre)
{
	if (monMenu->titre == NULL)
		return -1;
	if (strlen(titre) > 98);
	monMenu->titre = realloc(monMenu->titre, strlen(titre) * sizeof(char));
	if (monMenu->titre == NULL)
		return -1;
	for (size_t i = 0; i < strlen(titre); i++) //on évite les problèmes de retour a la ligne
		if (titre[i] == '\n')
			titre[i] = '\0';
	monMenu->titre = titre;
	return 0;
}

//permet d'ajouter un champs a un menu
int addchoix(MENU* monMenu, char* choix)
{
	for (size_t i = 0; i < strlen(choix); i++) //on évite les problèmes de retour a la ligne
		if (choix[i]=='\n')
			choix[i] = '\0';

	monMenu->choix[monMenu->nbReponse] = choix;
	monMenu->nbReponse++;

	return 0;
}

//retourne le choix
int useMenu(MENU *monMenu)
{
	system("cls");  //on efface l'écran
	char saisie;
	OpenConsole(); //pour gotoXY et plotChar
	COORD posCurs = { 8,3 };//les coordonnées du curseur (need a function to know the width
	printf("\t\t%s\n\n\n", monMenu->titre); //affichage du titre formaté

	for (size_t i = 0; i < monMenu->nbReponse; i++) //on affiche la liste des choix peu importe le type de menu
	{
		printf("\t :%s\n", monMenu->choix[i]);
	}

	if (monMenu->isMulti) //si le menu est multichoix 
	{
		printf("\t :Valider");  //on ajoute le choix qui permet de quiter le menu
		monMenu->multireponse = calloc(monMenu->multireponse, monMenu->nbReponse * sizeof(int)); //on aloue une mémoire pour mettre les réponses
		do
		{
			GotoXY(posCurs.X, posCurs.Y);//on place le curseur
			saisie = _getch();  //on récupere une saisie clavier
			if (saisie == 224)  //verification des touches spéciales composé de deux caractères
				saisie = _getch();
			switch (saisie)
			{
			case  ENTER:
			{
				if (monMenu->multireponse[posCurs.Y - 3])
				{
					monMenu->multireponse[posCurs.Y - 3] = 0;
					PlotChar(' ');
				}
				else
				{
					monMenu->multireponse[posCurs.Y - 3] = 1;
					PlotChar('*');
				}
				if (posCurs.Y < monMenu->nbReponse + 3)
					posCurs.Y++;
				else
				{
					CloseConsole();
					return monMenu->multireponse;
				}
				break;
			}
			case  KEY_UP:
			{
				if (monMenu->multireponse[posCurs.Y - 3] == 0)
					PlotChar(' ');
				if (posCurs.Y > 3)
					posCurs.Y--;
				break;
			}
			case KEY_DOWN:
			{
				if (monMenu->multireponse[posCurs.Y - 3] == 0)
					PlotChar(' ');
				if (posCurs.Y < monMenu->nbReponse + 3)
					posCurs.Y++;
				break;
			}
			default:
				break;
			}
		} while (1);
	}
	else
	{
		do
		{
			GotoXY(posCurs.X, posCurs.Y);
			PlotChar('*');
			saisie = _getch();
			if (saisie == 224)
				saisie = _getch();
			if (saisie == KEY_UP) {
				GotoXY(posCurs.X, posCurs.Y); PlotChar(' '); //on efface le * avant de le déplacer
				if (posCurs.Y > 3)
					posCurs.Y--;
			}
			else if (saisie == KEY_DOWN) {
				GotoXY(posCurs.X, posCurs.Y); PlotChar(' '); //on efface le * avant de le déplacer
				if (posCurs.Y < monMenu->nbReponse + 2)
					posCurs.Y++;
			}
		} while (saisie != ENTER);
		monMenu->Reponse = posCurs.Y - 3;
		CloseConsole();
		return monMenu->Reponse;
	}
}





