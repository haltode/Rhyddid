#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "fonctionsUtiles.h"

void menuNouveau(Menu *menu)
{
	compteur indexTab;

	for(indexTab = 0; indexTab < TAILLE_MAX_COMPOSANTS; ++indexTab)
	{
		menu->nomFonction[indexTab] = NULL;
		menu->nomComposant[indexTab][0] = '\0';
	}

	menu->nbComposant = 0;
}

void menuAfficher(const Menu *menu)
{
	compteur indexTab;

	for(indexTab = 0; indexTab < menu->nbComposant; ++indexTab)
		printf("\t%d - %s\n", indexTab + 1, menu->nomComposant[indexTab]);

	putchar('\n');
}

void menuAjouter(Menu *menu, const callback pointeurFonction, const char *nom)
{
	menu->nomFonction[menu->nbComposant] = pointeurFonction;
	strcpy(menu->nomComposant[menu->nbComposant], nom);
	++(menu->nbComposant);
}

void menuEnlever(Menu *menu, const char *nom)
{
	compteur indexTab, indexDecale;

	for(indexTab = 0; indexTab < menu->nbComposant; ++indexTab)
	{
		if(strcmp(menu->nomComposant[indexTab], nom) == 0)
		{
			for(indexDecale = indexTab; indexDecale < menu->nbComposant - 1; ++indexDecale)
			{
				menu->nomFonction[indexDecale] = menu->nomFonction[indexDecale + 1];
				strcpy(menu->nomComposant[indexDecale], menu->nomComposant[indexDecale + 1]);
			}
		}
	}

	--(menu->nbComposant);
}

void menuAction(const Menu *menu, const unsigned int choixAction)
{
	(menu->nomFonction[choixAction - 1])();
}

int menuChoisir(const Menu *menu, const char *messageAvantMenu)
{
	int choixJoueur;

	if(messageAvantMenu != NULL)
		printf("%s\n\n", messageAvantMenu);

	menuAfficher(menu);
	choixJoueur = choisirMenu(menu->nbComposant);

	return choixJoueur;
}

void menuChoisirSansOperationPossible(const Menu *menu, const char *messageAvantMenu)
{
	unsigned int choixJoueur;

	if(messageAvantMenu != NULL)
		printf("%s\n\n", messageAvantMenu);

	menuAfficher(menu);
	choixJoueur = choisirMenuSansOperationPossible(menu->nbComposant);
	menuAction(menu, choixJoueur);
}
