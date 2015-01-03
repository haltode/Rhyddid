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

/* Initialise l'armure de l'inventaire dans le fichier Inventaire/armure.txt */
void initialiserArmureInventaire(void);
/* Charge l'armure de l'inventaire grace au fichier Inventaire/armure.txt */
void chargerArmureInventaire(void);
/* Sauvegarde l'armure de l'inventaire dans le fichier Inventaire/armure.txt */
void sauvegarderArmureInventaire(void);
/* Affiche la section Armure de l'inventaire lorsqu'on ouvre l'inventaire */
void afficherArmureInventaire(void);


/* Genere une armure au hasard situee dans un coffre */
void genererArmureCoffre(Armure *armure);
/* Affiche la section Armure d'un coffre lorsqu'on l'ouvre */
void afficherArmureCoffre(const Coffre *coffre);
/* Prend l'armure situee dans le coffre que le joueur vient d'ouvrir (donnee en parametre) */
void prendreArmureCoffre(const Armure *armure);

/* ----- Declaration ----- */

#endif
