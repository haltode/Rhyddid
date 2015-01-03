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

/* Affiche le menu principal */
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

/* Menu principal */
void menuPrincipal(void)
{
	Menu menu;
	int choixJoueur;

	/* On cree le menu principal dans la variable menu */
	menuNouveau(&menu);

	menuAjouter(&menu, sauvegarde, "Sauvegarde");
	menuAjouter(&menu, highscore, "Highscore");
	menuAjouter(&menu, aide, "Aide");
	menuAjouter(&menu, quitter, "Quitter");

	/* On affiche le menu principal */
	afficherMenuPrincipal();

	/* On demande ce que le joueur veut faire */
	choixJoueur = choisirMenu(NB_MENU_MAXIMUM);

	/* Si le joueur veut revenir en arriere*/
	if(choixJoueur == REVENIR_ARRIERE)
	{
		/* On affiche l'ecran titre */
		afficherEcranTitre();
		/* On affiche le menu principal */
		menuPrincipal();
	}
	/* Sinon si le joueur veut quitter */
	else if(choixJoueur == QUITTER)
		/* On quitte */
		quitter();
	/* Sinon */
	else
		/* On fait ce que le joueur veut faire */
		menuAction(&menu, choixJoueur);
}

/* Reviens au menu principal lorsque le jeu est en pause */
void revenirMenuPrincipal(void)
{
	/* Si le joueur n'a pas sauvegarder */
	if(estNouvellePartie())
	{
		unsigned int choixJoueur;

		/* On demande la confirmation du joueur */
		choixJoueur = demanderConfirmation("Vous n'avez pas sauvegarde, etes-vous sur de vouloir revenir au menu principal ? (0/1)", SEPARATION);

		/* Si le joueur veut revenir tout de meme */
		if(choixJoueur == OUI)
			/* On appelle la fonction menuPrincipal */
			menuPrincipal();
		/* Sinon on reprend la partie */
		else if(choixJoueur == NON)
			reprendrePartie();
	}
	/* Sinon */
	else
		/* On appelle la fonction menuPrincipal */
		menuPrincipal();
}
