#include <stdio.h>

#include "pause.h"
#include "effacer.h"
#include "couleur.h"
#include "menu.h"
#include "sauvegarderNiveau.h"
#include "menuPrincipal.h"
#include "fonctionsUtiles.h"

void reprendrePartie(void)
{
	return ;
}

void menuPause(void)
{
	Menu pause;

	effacer();
	titre("Pause", VERT);

	menuNouveau(&pause);

	menuAjouter(&pause, reprendrePartie, "Reprendre partie");
	menuAjouter(&pause, sauvegarderNiveau, "Sauvegarder");
	menuAjouter(&pause, sauvegarderEtQuitterNiveau, "Sauvegarder et quitter");
	menuAjouter(&pause, revenirMenuPrincipal, "Revenir au menu principal");

	menuChoisirSansOperationPossible(&pause, "Que souhaitez-vous faire ?");
}
