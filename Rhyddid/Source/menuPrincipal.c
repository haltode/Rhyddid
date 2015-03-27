#include <stdio.h>

#include "menuPrincipal.h"
#include "menu.h"
#include "effacer.h"
#include "couleur.h"
#include "sauvegarde.h"
#include "highscore.h"
#include "aide.h"
#include "quitter.h"
#include "fonctionsUtiles.h"
#include "ecranTitre.h"
#include "jeu.h"
#include "pause.h"

void afficherMenuPrincipal(void)
{
	effacer();
	titre("Menu principal", VERT);

	printf("Que souhaitez-vous faire ?\n\n");

	printf("\t1 - ");
	coloration("Sauvegarde\n\n", BLEU);
	printf("\t2 - ");
	coloration("Highscore\n\n", BLEU);
	printf("\t3 - ");
	coloration("Aide\n\n", VERT);
	printf("\t4 - ");
	coloration("Quitter\n\n", ROUGE);
}

void menuPrincipal(void)
{
	Menu menu;
	int choixJoueur;

	menuNouveau(&menu);

	menuAjouter(&menu, sauvegarde, "Sauvegarde");
	menuAjouter(&menu, highscore, "Highscore");
	menuAjouter(&menu, aide, "Aide");
	menuAjouter(&menu, quitter, "Quitter");

	afficherMenuPrincipal();

	choixJoueur = choisirMenu(NB_MENU_MAXIMUM);

	if(choixJoueur == REVENIR_ARRIERE)
	{
		afficherEcranTitre();
		menuPrincipal();
	}
	else if(choixJoueur == QUITTER)
		quitter();
	else
		menuAction(&menu, choixJoueur);
}

void revenirMenuPrincipal(void)
{
	if(estNouvellePartie())
	{
		unsigned int choixJoueur;

		choixJoueur = demanderConfirmation("Vous n'avez pas sauvegarde, etes-vous sur de vouloir revenir au menu principal ? (0/1)", SEPARATION);

		if(choixJoueur == OUI)
			menuPrincipal();
		else if(choixJoueur == NON)
			reprendrePartie();
	}
	else
		menuPrincipal();
}
