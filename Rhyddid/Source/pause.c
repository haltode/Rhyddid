#include <stdio.h>

#include "pause.h"
#include "effacer.h"
#include "couleur.h"
#include "menu.h"
#include "sauvegarderNiveau.h"
#include "menuPrincipal.h"
#include "fonctionsUtiles.h"

/* Permet de reprendre la partie en cours */
void reprendrePartie(void)
{
	/* Pour reprendre la partie en cours il suffit juste de ne rien faire */
	return ;
}

/* Menu pause */
void menuPause(void)
{
	Menu pause;

	effacer();
	titre("Pause", VERT);

	/* On cree un menu pause contenant chaque choix possible, on demande au joueur son choix
	et on le fait */
	
	menuNouveau(&pause);

	menuAjouter(&pause, reprendrePartie, "Reprendre partie");
	menuAjouter(&pause, sauvegarderNiveau, "Sauvegarder");
	menuAjouter(&pause, sauvegarderEtQuitterNiveau, "Sauvegarder et quitter");
	menuAjouter(&pause, revenirMenuPrincipal, "Revenir au menu principal");

	menuChoisirSansOperationPossible(&pause, "Que souhaitez-vous faire ?");
}
