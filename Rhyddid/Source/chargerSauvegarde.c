#include <stdio.h>

#include "chargerSauvegarde.h"
#include "sauvegarde.h"
#include "jeu.h"

/* Charge une sauvegarde nomPartie (recupere toutes les infos du personnage), puis lance le jeu */
void chargerSauvegarde(const char *nomSauvegarde)
{
	/* On recupere les informations du personnage de la sauvegarde */
	recupererInformationPersonnage(nomSauvegarde);
	/* On lance le jeu */
	jeu();
}
