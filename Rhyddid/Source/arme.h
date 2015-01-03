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

/* Initialise l'arme de l'inventaire dans le fichier Inventaire/arme.txt */
void initialiserArmeInventaire(void);
/* Charge l'arme de l'inventaire grace au fichier Inventaire/arme.txt */
void chargerArmeInventaire(void);
/* Sauvegarde l'arme de l'inventaire dans le fichier Inventaire/arme.txt */
void sauvegarderArmeInventaire(void);
/* Affiche la section Arme de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherArmeInventaire(void);


/* Genere une arme au hasard situee dans un coffre */
void genererArmeCoffre(Arme *arme);
/* Affiche la section Arme d'un coffre lorsqu'on l'ouvre */
void afficherArmeCoffre(const Coffre *coffre);
/* Prend l'arme situee dans le coffre que le joueur vient d'ouvrir */
void prendreArmeCoffre(const Arme *arme);

/* ----- Declaration ----- */

#endif
