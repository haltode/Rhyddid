#include <stdio.h>

#include "ecranTitre.h"
#include "couleur.h"
#include "fonctionsUtiles.h"
#include "effacer.h"

void afficherEcranTitre(void)
{
	effacer();

	couleur(VERT);
	lireEtAfficher("ASCII_Art/ASCII_Art_Ecran_Titre.txt");
	couleur(BLANC);

	appuyezEntree("APPUYEZ SUR ENTREE POUR COMMENCER");
}
