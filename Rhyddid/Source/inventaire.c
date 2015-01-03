#include <stdio.h>

#include "inventaire.h"
#include "effacer.h"
#include "couleur.h"
#include "personnage.h"
#include "fonctionsUtiles.h"
#include "creerDossier.h"

/* Affiche l'inventaire du joueur */
void afficherInventaire(void)
{
	effacer();
	titre("Inventaire", VERT);

	/* On affiche la cle de fin de niveau (si le joueur la possede) */
	afficherCleInventaire();

	/* On affiche l'inventaire complet (tek, armure, arme, tresor, potion) */

	afficherTekInventaire();
	afficherArmureInventaire();
	afficherArmeInventaire();
	afficherTresorInventaire();
	afficherPotionInventaire();
}

/* Ouvre l'inventaire du joueur */
void ouvrirInventaire(void)
{
	/* On affiche l'inventaire */
	afficherInventaire();

	appuyezEntree("\nAppuyez sur ENTREE pour revenir au jeu");
}

/* Cree le dossier de sauvegarde Inventaire du joueur */
void creerNouveauDossierInventaire(void)
{
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire", personnage.nom);

	creerNouveauDossier(chemin);
}

/* Initialise l'inventaire du joueur */
void initialiserInventaire(void)
{
	/* On cree le dossier Inventaire */
	creerNouveauDossierInventaire();

	/* On initialise la cle de fin de niveau */
	initialiserCleInventaire();

	/* On initialise l'inventaire complet (tek, armure, arme, tresor, potion) */

	initialiserTekInventaire();
	initialiserArmureInventaire();
	initialiserArmeInventaire();
	initialiserTresorInventaire();
	initialiserPotionInventaire();
}

/* Charge l'inventaire du joueur */
void chargerInventaire(void)
{
	/* On charge la cle de fin de niveau */
	chargerCleInventaire();

	/* On charge l'inventaire complet (tek, armure, arme, tresor, potion) */

	chargerTekInventaire();
	chargerArmureInventaire();
	chargerArmeInventaire();
	chargerTresorInventaire();
	chargerPotionInventaire();
}

/* Sauvegarde l'inventaire du joueur */
void sauvegarderInventaire(void)
{
	/* On sauvegarde la cle de fin de niveau */
	sauvegarderCleInventaire();

	/* On sauvegarde l'inventaire complet (tek, armure, arme, tresor, potion) */
	
	sauvegarderTekInventaire();
	sauvegarderArmureInventaire();
	sauvegarderArmeInventaire();
	sauvegarderTresorInventaire();
	sauvegarderPotionInventaire();
}
