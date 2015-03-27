#ifndef CAVERNE_H
#define CAVERNE_H

/* caverne.c/caverne.h : permet de gerer les cavernes */

/* ----- A inclure ----- */

#include "ennemi.h"

/* ----- Define ----- */

#define LONGUEUR_CAVERNE 5
#define LARGUEUR_CAVERNE 9

#define NB_COFFRE_MAX_CAVERNE 5
#define NB_ENNEMI_MAX_CAVERNE 12

#define NON_CAVERNE 0
#define CAVERNE 1

#define CHANCE_MAX_CAVERNE_PIEGE 10

/* ----- Structure + Enumeration ----- */

typedef struct Caverne Caverne;
struct Caverne
{
	unsigned int directionEntree;

	unsigned int ligDebut;
	unsigned int colDebut;

	char mapSalle[40][80];
	Ennemi ennemi[NB_ENNEMI_MAX_CAVERNE];
	unsigned int nbEnnemi;
};

/* ----- Prototype ----- */

void placerCaverneNouveauNiveau(void);


unsigned int testerPlacementCaverneNouveauNiveau(
	const unsigned int indexSalle, const unsigned int ligneCaverne, 
	const unsigned int colonneCaverne);
void determinerPositionCaverne(const unsigned int indexSalle);
void placerCaverne(const unsigned int indexSalle);
void bloquerAccesIndispensableEntreeCaverne(const unsigned int indexSalle);
void genererSalleCaverne(const unsigned int indexSalle);
void genererContenuCaverne(const unsigned int indexSalle);
void genererCaverne(const unsigned int indexSalle);


void entrerCaverne(void);


void rechercherEntreeCaverne(unsigned int *ligneEntreeCaverne, 
	unsigned int *colonneEntreeCaverne);
int positionSortieCaverne(const unsigned int direction, const unsigned int dimension);
void sortirCaverne(void);

/* ----- Declaration ----- */

#endif
