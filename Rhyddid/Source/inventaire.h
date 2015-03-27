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

void afficherInventaire(void);
void ouvrirInventaire(void);


void creerNouveauDossierInventaire(void);


void initialiserInventaire(void);
void chargerInventaire(void);
void sauvegarderInventaire(void);

/* ----- Declaration ----- */

Inventaire inventaire;

#endif
