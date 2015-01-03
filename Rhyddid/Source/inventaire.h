#ifndef INVENTAIRE_H
#define INVENTAIRE_H

/* inventaire.c/inventaire.h : permet de gerer l'inventaire */

/* ----- A inclure ----- */

#include "tek.h"
#include "armure.h"
#include "arme.h"
#include "tresor.h"
#include "potion.h"
#include "cle.h"

/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */

typedef struct Inventaire Inventaire;
struct Inventaire
{
	Tek tek;
	Armure armure;
	Arme arme;
	Tresor tresor[NB_TRESOR_MAX];
	Potion sante;
	Potion force;
	Potion resistance;

	unsigned int tresorActuel;
	unsigned int possedeCleFinNiveau;
};

/* ----- Prototype ----- */

/* Affiche l'inventaire du joueur */
void afficherInventaire(void);
/* Ouvre l'inventaire du joueur */
void ouvrirInventaire(void);


/* Cree le dossier de sauvegarde Inventaire du joueur */
void creerNouveauDossierInventaire(void);


/* Initialise l'inventaire du joueur */
void initialiserInventaire(void);
/* Charge l'inventaire du joueur */
void chargerInventaire(void);
/* Sauvegarde l'inventaire du joueur */
void sauvegarderInventaire(void);

/* ----- Declaration ----- */

Inventaire inventaire;

#endif
