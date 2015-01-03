#include <stdio.h>

#include "entree.h"
#include "effacer.h"
#include "couleur.h"
#include "fonctionsUtiles.h"

/* Affiche le texte de la porte d'entree du niveau */
void afficherTextePorteEntree(void)
{
	effacer();
	titre("Porte d'entree", VERT);

	lireEtAfficher("Entree/Texte_Porte_Entree.txt");

	appuyezEntree("\nAppuyez sur ENTREE pour continuer");
}
