#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "fonctionsUtiles.h"

/* Initialise le menu donne en parametre */
void menuNouveau(Menu *menu)
{
	compteur indexTab;

	/* On initialise tous les elements du menu a 0 ou a NULL */

	for(indexTab = 0; indexTab < TAILLE_MAX_COMPOSANTS; ++indexTab)
	{
		menu->nomFonction[indexTab] = NULL;
		menu->nomComposant[indexTab][0] = '\0';
	}

	menu->nbComposant = 0;
}

/* Affiche le menu donne en paramtre */
void menuAfficher(const Menu *menu)
{
	compteur indexTab;

	/* Pour chaque composant du menu */
	for(indexTab = 0; indexTab < menu->nbComposant; ++indexTab)
		printf("\t%d - %s\n", indexTab + 1, menu->nomComposant[indexTab]);

	putchar('\n');
}

/* Ajoute un element donne en parametre au menu donne en parametre */
void menuAjouter(Menu *menu, const callback pointeurFonction, const char *nom)
{
	/* On ajoute le pointeur sur fonction du composant */
	menu->nomFonction[menu->nbComposant] = pointeurFonction;
	/* On ajoute le nom du composant */
	strcpy(menu->nomComposant[menu->nbComposant], nom);
	/* On incremente le nombre de composant */
	++(menu->nbComposant);
}

/* Enleve un element donne en parametre au menu donne en parametre */
void menuEnlever(Menu *menu, const char *nom)
{
	compteur indexTab, indexDecale;

	/* On decale tous les elements de droite a gauche a partir de l'element a enlever */

	for (indexTab = 0; indexTab < menu->nbComposant; ++indexTab)
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

	/* On decremente le nombre de composant */
	--(menu->nbComposant);
}

/* Execute une action du menu donne en parametre */
void menuAction(const Menu *menu, const unsigned int choixAction)
{
	/* On appelle la fonction choisit */
	(menu->nomFonction[choixAction - 1])();
}

/* Permet de choisir un element du menu donne en parametre */
int menuChoisir(const Menu *menu, const char *messageAvantMenu)
{
	int choixJoueur;

	if(messageAvantMenu != NULL)
		printf("%s\n\n", messageAvantMenu);

	/* On affiche le menu */
	menuAfficher(menu);
	/* On demande au joueur ce qu'il veut */
	choixJoueur = choisirMenu(menu->nbComposant);

	/* On retourne le choix du joueur */
	return choixJoueur;
}

/* Permet de choisir un element du menu donne en parametre sans pouvoir retourner en 
arriere ou de quitter le jeu et execute le choix du joueur */
void menuChoisirSansOperationPossible(const Menu *menu, const char *messageAvantMenu)
{
	unsigned int choixJoueur;

	if(messageAvantMenu != NULL)
		printf("%s\n\n", messageAvantMenu);

	/* On affiche le menu */
	menuAfficher(menu);
	/* On demande au joueur ce qu'il veut */
	choixJoueur = choisirMenuSansOperationPossible(menu->nbComposant);
	/* On execute le choix du joueur */
	menuAction(menu, choixJoueur);
}
