#ifndef ARMURE_H
#define ARMURE_H

/* armure.c/armure.h : permet de l'initialisation, le chargement, la sauvegarde, l'affichage etc. 
des armures */

/* ----- A inclure ----- */

#include "fonctionsUtiles.h"

/* ----- Define ----- */

#define NB_ARMURE 30

/* ----- Structure + Enumeration ----- */

typedef struct Coffre Coffre;

typedef struct Armure Armure;
struct Armure
{
	char nom[TAILLE_MAX];
	unsigned int protection;
};

/* ----- Prototype ----- */

void initialiserArmureInventaire(void);
void chargerArmureInventaire(void);
void sauvegarderArmureInventaire(void);
void afficherArmureInventaire(void);


void genererArmureCoffre(Armure *armure);
void afficherArmureCoffre(const Coffre *coffre);
void prendreArmureCoffre(const Armure *armure);

/* ----- Declaration ----- */

#endif
