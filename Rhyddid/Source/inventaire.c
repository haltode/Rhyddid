#include <stdio.h>

#include "inventaire.h"
#include "effacer.h"
#include "couleur.h"
#include "personnage.h"
#include "fonctionsUtiles.h"
#include "creerDossier.h"

void afficherInventaire(void)
{
	effacer();
	titre("Inventaire", VERT);

	afficherCleInventaire();
	afficherTekInventaire();
	afficherArmureInventaire();
	afficherArmeInventaire();
	afficherTresorInventaire();
	afficherPotionInventaire();
}

void ouvrirInventaire(void)
{
	afficherInventaire();
	appuyezEntree("\nAppuyez sur ENTREE pour revenir au jeu");
}

void creerNouveauDossierInventaire(void)
{
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Inventaire", personnage.nom);
	creerNouveauDossier(chemin);
}

void initialiserInventaire(void)
{
	creerNouveauDossierInventaire();

	initialiserCleInventaire();
	initialiserTekInventaire();
	initialiserArmureInventaire();
	initialiserArmeInventaire();
	initialiserTresorInventaire();
	initialiserPotionInventaire();
}

void chargerInventaire(void)
{
	chargerCleInventaire();
	chargerTekInventaire();
	chargerArmureInventaire();
	chargerArmeInventaire();
	chargerTresorInventaire();
	chargerPotionInventaire();
}

void sauvegarderInventaire(void)
{
	sauvegarderCleInventaire();
	sauvegarderTekInventaire();
	sauvegarderArmureInventaire();
	sauvegarderArmeInventaire();
	sauvegarderTresorInventaire();
	sauvegarderPotionInventaire();
}
