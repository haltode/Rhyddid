#ifndef ARME_H
#define ARME_H

/* arme.c/arme.h : permet de l'initialisation, le chargement, la sauvegarde, l'affichage etc. 
des armes */

/* ----- A inclure ----- */

#include "fonctionsUtiles.h"

/* ----- Define ----- */

#define NB_ARME 35

/* ----- Structure + Enumeration ----- */

typedef struct Coffre Coffre;

typedef struct Arme Arme;
struct Arme
{
	char nom[TAILLE_MAX];
	unsigned int degat;
	unsigned int portee;
};

/* ----- Prototype ----- */

void initialiserArmeInventaire(void);
void chargerArmeInventaire(void);
void sauvegarderArmeInventaire(void);
void afficherArmeInventaire(void);


void genererArmeCoffre(Arme *arme);
void afficherArmeCoffre(const Coffre *coffre);
void prendreArmeCoffre(const Arme *arme);

/* ----- Declaration ----- */

#endif
