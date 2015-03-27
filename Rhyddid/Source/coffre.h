#ifndef COFFRE_H
#define COFFRE_H

/* coffre.c/coffre.h : permet de gerer les coffres et coffres pieges */

/* ----- A inclure ----- */

#include "inventaire.h"

/* ----- Define ----- */

#define CHANCE_MAX_TEK 2
#define CHANCE_MAX_ARMURE 12
#define CHANCE_MAX_ARME 12
#define CHANCE_MAX_TRESOR 10
#define CHANCE_MAX_POTION 7

#define NB_OBJET_COFFRE_MAX 5

#define CHANCE_MAX_COFFRE_PIEGE 15

/* ----- Structure + Enumeration ----- */

typedef struct ObjetCoffre ObjetCoffre;
struct ObjetCoffre
{
	unsigned int estDansCoffre;
	void (*pointeur)(void);
};

typedef struct Coffre Coffre;
struct Coffre
{
	Inventaire inventaire;

	unsigned int tek;
	unsigned int armure;
	unsigned int arme;
	unsigned int tresor;
	unsigned int potion;

	unsigned int typePotion;
	unsigned int niveauPotion;
};


/* ----- Prototype ----- */

void placerCoffreAleatoireNouveauNiveau(const unsigned int indexSalle, 
	unsigned int nbCoffre, const unsigned int estCaverne);
	

void initialiserContenuCoffre(Coffre *coffre);
void deciderContenuCoffre(Coffre *coffre);
void remplirContenuCoffre(Coffre *coffre);
void genererContenuCoffre(Coffre *coffre);
void afficherContenuCoffre(const Coffre *coffre);
void prendreContenuCoffre(const Coffre *coffre);


unsigned int estCoffreVide(const Coffre *coffre);


void coffrePiege(void);


void supprimerCoffre(void);


void ouvrirCoffre(void);

/* ----- Declaration ----- */

#endif
