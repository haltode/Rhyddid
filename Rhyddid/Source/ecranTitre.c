#include <stdio.h>

#include "ecranTitre.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "effacer.h"

/* Affiche l'ecran titre du jeu */
void afficherEcranTitre(void)
{
	effacer();

	/* On affiche le ASCII Art */
	couleur(VERT);
	lireEtAfficher("ASCII_Art/ASCII_Art_Ecran_Titre.txt");
	couleur(BLANC);

	appuyezEntree("APPUYEZ SUR ENTREE POUR COMMENCER");
}
